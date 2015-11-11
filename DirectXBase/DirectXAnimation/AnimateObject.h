#pragma once
#include"../Global.h"
#include"MyAllocateHierarchy.h"
#include"../Direct3D/Xfile.h"
#include"../Direct3D/Texture.h"
#include"../Direct3D/Xfile.h"

// スキンメッシュクラス
class CSkinMesh :public Direct3D
{
public:
	

	//メッシュクラスの初期化
	// VOID InitBase(SMESH_DATA_FILE* _pSMeshData);
	//メッシュの現在のMatrixデータ取得
	D3DXMATRIX GetMatrix();
	CSkinMesh();
	~CSkinMesh(){
		Release();
	}
	//スキンメッシュ内部処理
	HRESULT Init(LPDIRECT3DDEVICE9 lpD3DDevice, LPSTR pMeshPass);
	HRESULT AllocateBoneMatrix(LPD3DXFRAME pFrameRoot, LPD3DXMESHCONTAINER pMeshContainerBase);
	HRESULT AllocateAllBoneMatrices(LPD3DXFRAME pFrameRoot, LPD3DXFRAME pFrameBase);
	VOID RenderMeshContainer(LPDIRECT3DDEVICE9 lpD3DDevice, MYMESHCONTAINER*, MYFRAME*);
	VOID UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
	VOID DrawFrame(PDIRECT3DDEVICE9 lpD3DDevice, LPD3DXFRAME);
	//フレーム解放
	VOID FreeAnim(LPD3DXFRAME pFrame);
	//解放処理
	VOID Release();
	//更新処理
	VOID Update(D3DXMATRIX);
	//描画処理
	VOID Draw(LPDIRECT3DDEVICE9 lpD3DDevice);
	//オブジェクトのアニメーション変更( メッシュオブジェクトの操作用番号, 変更するアニメーション番号 )
	VOID ChangeAnim(DWORD NewAnimNum);
	//現在のアニメーション番号取得
	DWORD GetAnimTrack(){ return m_CurrentTrack; }
	//現在のアニメーションタイム(アニメーション開始からの時間)を取得
	DWORD GetAnimTime(){ return m_AnimeTime; }
	//アニメーション速度を取得
	FLOAT GetAnimSpeed(){ return m_AnimSpeed; }
	//アニメーション速度を設定
	VOID SetAnimSpeed(FLOAT _AnimSpeed){ m_AnimSpeed = _AnimSpeed; }
private:
	//対象のボーンを検索
	MYFRAME* SearchBoneFrame(LPSTR _BoneName, D3DXFRAME* _pFrame);
public:
	//ボーンのマトリックス取得( ボーンの名前 )
	D3DXMATRIX GetBoneMatrix(LPSTR _BoneName);
	//ボーンのマトリックスポインタ取得( ボーンの名前 )
	D3DXMATRIX* GetpBoneMatrix(LPSTR _BoneName);
private:
	//追加
	//すべてのフレームポインタ格納処理関数
	VOID CreateFrameArray(LPD3DXFRAME _pFrame);
	// フレーム参照用配列
	std::vector<MYFRAME*> m_FrameArray; // 全フレーム参照配列
	std::vector<MYFRAME*> m_IntoMeshFrameArray;// メッシュコンテナありのフレーム参照配列
	//ボーン情報
	LPD3DXFRAME m_pFrameRoot;
	//アニメーションコントローラ
	LPD3DXANIMATIONCONTROLLER m_pAnimController;
	//ヒエラルキークラス変数
	MyAllocateHierarchy m_cHierarchy;
	//アニメーションデータ格納用変数(ここは可変に変更したほうがいい)
	LPD3DXANIMATIONSET m_pAnimSet[20];
	//現在のアニメーションが開始されてからの時間(1/60秒)
	DWORD m_AnimeTime;
	//アニメーションスピード
	FLOAT m_AnimSpeed;
	//現在のアニメーショントラック
	DWORD m_CurrentTrack;
	//現在のアニメーションデータトラック
	D3DXTRACK_DESC m_CurrentTrackDesc;
	//進行方向
	D3DXMATRIX m_World;
	//メッシュのマテリアル関係
	//マテリアル変更フラグ
	BOOL m_MaterialFlg;
	//マテリアルデータ
	D3DMATERIAL9 m_Material;


};