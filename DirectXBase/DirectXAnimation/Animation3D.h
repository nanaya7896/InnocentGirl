#pragma once
#include"../Global.h"
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

class Animation3D : public ID3DXAllocateHierarchy
{
private:



public:
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);




protected:

	D3DXFRAME*	g_pFrameRoot;
	ID3DXAnimationController* g_pAnimController;


};