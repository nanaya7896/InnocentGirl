#pragma once
#include"../Global.h"
#include"../Direct3D/direct3d.h"
const int MAX_BONES=26;


//
struct D3DXFREAME_DERIVED : public D3DXFRAME
{
	D3DXMATRIXA16 CombinedTransformationMatrix;
};

//
struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
{
	//スキンメッシュの情報
	LPD3DXATTRIBUTERANGE pAttributeTable;
	DWORD NumAttributeGropus;
	DWORD NumInfl;
	LPD3DXBUFFER pBoneCombnationBuf;
	D3DXMATRIX** ppBoneMatrixPtrs;
	D3DXMATRIX*	 pBoneOffsetMatrices;
	DWORD NumPaletteEntries;
};

class Animation3D : public ID3DXAllocateHierarchy,Direct3D
{
private:



public:
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);
	STDMETHOD(CreateMeshContainer)(THIS_
		LPCSTR Name,
		CONST D3DXMESHDATA *pMeshData,
		CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials,
		CONST DWORD *pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer);

	STDMETHOD(DestroyFrame)(THIS_ LPD3DXMESHCONTAINER pMeshContainerBase);

	Animation3D()
	{}
	HRESULT FilterMesh(LPDIRECT3DDEVICE9 pDevice9,LPD3DXMESH *pMeshIn,LPD3DXMESH** ppMeshOut);


protected:

	D3DXFRAME*	g_pFrameRoot;
	ID3DXAnimationController* g_pAnimController;


};

//public functions
HRESULT SetupBoneMatrixPointersOnMesh(LPD3DXMESHCONTAINER pMeshContainer, D3DXFRAME* pFrameRoot);
HRESULT SetupBoneMatrixPointers(LPD3DXFRAME pFrame, D3DXFRAME* pFrameRoot);
void UpdaeFrameMatrices(LPD3DXFRAME pFrameBase, const D3DXMATRIX* pParentMatrix);
void UpdateSkinningmethod(LPD3DXFRAME pFrameBase);
HRESULT GenerateSkinnedMesh(LPDIRECT3DDEVICE9* pDevice9, D3DXMESHCONTAINER_DERIVED* pMeshContainer);