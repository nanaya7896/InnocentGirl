#pragma once
#include"../Global.h"
#include"../Direct3D/direct3d.h"
#include"../Direct3D/Texture.h"
//宣言
class CMultiAnim;
class CAnimInstance;


/*
Name: class CMultiANimAllocateHierarchy
Desc: ID3DXAllcateHierarchyから受け継ぐ.このクラスはアニメーションフレームとメッシュで使われたメモリの割り当てと解放を行う
	  アプリケーションドライバは、メモリの解放と配置の前に、クラスのバージョンを変更することができる
	  ID3DXAllocateHierarchyはd3dxanim.h
*/

class CMultiAnimAllocateHierarchy : public ID3DXAllocateHierarchy
{
	//D3DXFrame-derivedの作成と初期化の呼び出し
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);
	//D3DXMESHCONTAINER-derived作成と初期化の呼び出し
	STDMETHOD(CreateMeshContainer)(
		THIS_ LPCSTR Name,
		CONST D3DXMESHDATA *pMeshData,
		CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials,
		CONST DWORD *pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer
		);

	//D3DXFrameの解放の呼び出し
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);

	//D3DXMESHCONTAINERドライバの解放の呼び出し
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree);

public:
	CMultiAnimAllocateHierarchy();

	//メソッドのセットアップ
	STDMETHOD(SetMA)(THIS_ CMultiAnim *pMA);


private:
	CMultiAnim* m_pMA;
};

/*
Name MultiAnimFrameの構造体
Desk D3DXFRAMEから受け継ぐ。アニメーションフレームとメッシュを代理する
*/
struct MultiAnimFrame : public D3DXFRAME
{

};

/*
Name MultiAnimMCの構造体
Desc D3DXMESHCONTAINERから受け継ぐ。取得したメッシュオブジェクトの頂点を代理し、フレーム情報の階層の基盤を映し出す
*/

struct MultiAnimMC : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9 pTexture;
	LPD3DXMESH m_pWorkingMesh;
	//pSkinInfoからボーンのオフセット行列を回収する
	D3DXMATRIX* m_amxBoneOffsets;
	//ボーンの行列を探す？
	D3DXMATRIX** m_apmxBonePointers;

	DWORD m_dwNumPaletteEntries;
	DWORD m_dwMaxNumFaceInfls;
	DWORD m_dwNumAttrGroups;
	LPD3DXBUFFER m_pBufBoneCombos;

	HRESULT SetupBonePtrs(D3DXFRAME* pFrameRoot);
};

/*
Name Class CMultiAnim
Desc このクラスは、メッシュ階層体を要約する。（典型的に、Xファイルのロード後）
	 CAnimInstanceのリストはメッシュ階層体を共有する。
	 アニメーションコントローラーのコピーを同じようにコピーする
	 CMultiAnimは効果オブジェクトのロードと保守をしメッシュと一緒に描画する
*/
class CMultiAnim
{
	friend class CMultiAnimAllocateHierarchy;
	friend class CAnimInstance;
	friend struct MultiAnimFrame;
	friend struct MultiAnimMC;
protected:
	LPDIRECT3DDEVICE9 pDevice9;
	LPD3DXEFFECT m_pEffect;
	//キャラクターを描画するやり方
	char* m_sRechnique;
	DWORD m_dwWorkingPaletteSize;
	D3DXMATRIX* m_amxWorkingPalette;

	//一番重要
	std::vector<CAnimInstance*>m_v_pAnimInstance;
	//別な方法で初期化

	//初期化している間に共有する
	MultiAnimFrame* m_pFrameRoot;
	//AnimationControllerは、子オブジェクトをクローン化するｰｰクローンにするための鍵はない
	LPD3DXANIMATIONCONTROLLER m_pAC;

	//使い古したアプリデータは回収できる
	float m_fBoundingRadius;


private:

	HRESULT		CreateInstance(CAnimInstance** ppAnimInstance);
	HRESULT		SetupBonePtrs(MultiAnimFrame* pFrame);

public:

	//コンストラクタ
	CMultiAnim();
	//デストラクタの仮想関数
	virtual ~CMultiAnim();
	//Setup関数の仮想化
	virtual HRESULT		Setup(
		LPDIRECT3DDEVICE9 pDevice,
		TCHAR sXFile[],
		TCHAR sFxFile[],
		CMultiAnimAllocateHierarchy* pAH,
		LPD3DXLOADUSERDATA pLUD = NULL);
	//Cleanup関数の仮想化
	virtual HRESULT		Cleanup(CMultiAnimAllocateHierarchy* pAH);

	LPDIRECT3DDEVICE9	GetDevice();
	LPD3DXEFFECT		GetEffect();
	DWORD				GetNumInstances();
	CAnimInstance* GetInstance(DWORD dwIdx);
	float			GetBoundingRadius();

	virtual HRESULT		CreateNewInstance(DWORD* pdwNewIdx);

	virtual void		SetTechnique(char* sTechnique);

	virtual HRESULT		Draw();

};

/*
Name class CAnimInstance
Desc アニメーションの初期化をアニメーションコントローラーと一緒に内包する
*/
class CAnimInstance
{
	friend class CMultiAnim;

protected:
	//メンバ変数
	CMultiAnim* m_pMultiAnim;
	D3DXMATRIX m_mxWorld;
	LPD3DXANIMATIONCONTROLLER m_pAC;

private:

	//関数の仮想化
	virtual HRESULT Setup(LPD3DXANIMATIONCONTROLLER pAC);
	virtual void    UpdateFrames(MultiAnimFrame* pFrame, D3DXMATRIX* pmxBase);
	virtual void   DrawFrames(MultiAnimFrame* pFrame);
	virtual void   DrawMeshFrame(MultiAnimFrame* pFrame);

public:
	//コンストラクタ
	CAnimInstance();
	//デストラクタの仮想化
	virtual ~CAnimInstance();

	virtual void		Cleanup();

	CMultiAnim* GetMultiAnim();
	void		GetAnimController(LPD3DXANIMATIONCONTROLLER* ppAC);

	D3DXMATRIX	GetWorldTransform();
	void		SetWorldTransform(const D3DXMATRIX* pmxWorld);

	virtual HRESULT AsvanceTime(DOUBLE dTimeDelta, ID3DXAnimationCallbackHandler* pCH);
	virtual HRESULT ResetTime();
	virtual HRESULT Draw();

};