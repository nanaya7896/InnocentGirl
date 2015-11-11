#pragma once
#include"../Global.h"

//派生フレーム構造体 (それぞれのメッシュ用の最終ワールド行列を追加する）
struct MYFRAME : public D3DXFRAME
{
	D3DXMATRIX CombinedTransformationMatrix;
	// オフセット行列(インデックス付描画用)
	D3DXMATRIX OffsetMat;
	// 行列テーブルのインデックス番号(インデックス付用)
	DWORD OffsetID;
};

//派生メッシュコンテナー構造体(
//コンテナーがテクスチャを複数持てるようにポインターのポインターを追加する）
struct MYMESHCONTAINER : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9*  ppTextures;
	DWORD dwWeight; //重みの個数（重みとは頂点への影響。）
	DWORD dwBoneNum; //ボーンの数
	LPD3DXBUFFER pBoneBuffer; //ボーン・テーブル
	D3DXMATRIX** ppBoneMatrix; //全てのボーンのワールド行列の先頭ポインター
	D3DXMATRIX* pBoneOffsetMatrices; //フレームとしてのボーンのワールド行列のポインター
	LPD3DXMESH pOriMesh; //オリジナルメッシュ用
	DWORD NumPaletteEntries; //パレットサイズ
	// Work用
	std::vector<D3DXMATRIX> m_WorkBoneMatArray;
	// 影響するフレームへの参照配列。描画時にこのフレームの行列を使う。
	std::vector<MYFRAME*> BoneFrameArray;
	MYMESHCONTAINER(){
		ppBoneMatrix = NULL;
		pBoneOffsetMatrices = NULL;
	}
};

//Xファイル内のアニメーション階層を読み下してくれるクラスを派生させる。
//ID3DXAllocateHierarchyは派生すること想定して設計されている。
class MyAllocateHierarchy : public ID3DXAllocateHierarchy
{
public:
	MyAllocateHierarchy(){
	}
	STDMETHOD(CreateFrame)(THIS_ LPCSTR, LPD3DXFRAME *);
	STDMETHOD(CreateMeshContainer)(THIS_
		LPCTSTR,
		CONST D3DXMESHDATA*,
		CONST D3DXMATERIAL*,
		CONST D3DXEFFECTINSTANCE*,
		DWORD,
		CONST DWORD *,
		LPD3DXSKININFO,
		LPD3DXMESHCONTAINER *
		);
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME);
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER);
private:

};