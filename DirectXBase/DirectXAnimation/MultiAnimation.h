#pragma once
#include"../Global.h"
#include"../Direct3D/direct3d.h"
#include"../Direct3D/Texture.h"
//�錾
class CMultiAnim;
class CAnimInstance;


/*
Name: class CMultiANimAllocateHierarchy
Desc: ID3DXAllcateHierarchy����󂯌p��.���̃N���X�̓A�j���[�V�����t���[���ƃ��b�V���Ŏg��ꂽ�������̊��蓖�ĂƉ�����s��
	  �A�v���P�[�V�����h���C�o�́A�������̉���Ɣz�u�̑O�ɁA�N���X�̃o�[�W������ύX���邱�Ƃ��ł���
	  ID3DXAllocateHierarchy��d3dxanim.h
*/

class CMultiAnimAllocateHierarchy : public ID3DXAllocateHierarchy
{
	//D3DXFrame-derived�̍쐬�Ə������̌Ăяo��
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);
	//D3DXMESHCONTAINER-derived�쐬�Ə������̌Ăяo��
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

	//D3DXFrame�̉���̌Ăяo��
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);

	//D3DXMESHCONTAINER�h���C�o�̉���̌Ăяo��
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree);

public:
	CMultiAnimAllocateHierarchy();

	//���\�b�h�̃Z�b�g�A�b�v
	STDMETHOD(SetMA)(THIS_ CMultiAnim *pMA);


private:
	CMultiAnim* m_pMA;
};

/*
Name MultiAnimFrame�̍\����
Desk D3DXFRAME����󂯌p���B�A�j���[�V�����t���[���ƃ��b�V����㗝����
*/
struct MultiAnimFrame : public D3DXFRAME
{

};

/*
Name MultiAnimMC�̍\����
Desc D3DXMESHCONTAINER����󂯌p���B�擾�������b�V���I�u�W�F�N�g�̒��_��㗝���A�t���[�����̊K�w�̊�Ղ��f���o��
*/

struct MultiAnimMC : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9 pTexture;
	LPD3DXMESH m_pWorkingMesh;
	//pSkinInfo����{�[���̃I�t�Z�b�g�s����������
	D3DXMATRIX* m_amxBoneOffsets;
	//�{�[���̍s���T���H
	D3DXMATRIX** m_apmxBonePointers;

	DWORD m_dwNumPaletteEntries;
	DWORD m_dwMaxNumFaceInfls;
	DWORD m_dwNumAttrGroups;
	LPD3DXBUFFER m_pBufBoneCombos;

	HRESULT SetupBonePtrs(D3DXFRAME* pFrameRoot);
};

/*
Name Class CMultiAnim
Desc ���̃N���X�́A���b�V���K�w�̂�v�񂷂�B�i�T�^�I�ɁAX�t�@�C���̃��[�h��j
	 CAnimInstance�̃��X�g�̓��b�V���K�w�̂����L����B
	 �A�j���[�V�����R���g���[���[�̃R�s�[�𓯂��悤�ɃR�s�[����
	 CMultiAnim�͌��ʃI�u�W�F�N�g�̃��[�h�ƕێ�������b�V���ƈꏏ�ɕ`�悷��
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
	//�L�����N�^�[��`�悷�����
	char* m_sRechnique;
	DWORD m_dwWorkingPaletteSize;
	D3DXMATRIX* m_amxWorkingPalette;

	//��ԏd�v
	std::vector<CAnimInstance*>m_v_pAnimInstance;
	//�ʂȕ��@�ŏ�����

	//���������Ă���Ԃɋ��L����
	MultiAnimFrame* m_pFrameRoot;
	//AnimationController�́A�q�I�u�W�F�N�g���N���[�������鰰�N���[���ɂ��邽�߂̌��͂Ȃ�
	LPD3DXANIMATIONCONTROLLER m_pAC;

	//�g���Â����A�v���f�[�^�͉���ł���
	float m_fBoundingRadius;


private:

	HRESULT		CreateInstance(CAnimInstance** ppAnimInstance);
	HRESULT		SetupBonePtrs(MultiAnimFrame* pFrame);

public:

	//�R���X�g���N�^
	CMultiAnim();
	//�f�X�g���N�^�̉��z�֐�
	virtual ~CMultiAnim();
	//Setup�֐��̉��z��
	virtual HRESULT		Setup(
		LPDIRECT3DDEVICE9 pDevice,
		TCHAR sXFile[],
		TCHAR sFxFile[],
		CMultiAnimAllocateHierarchy* pAH,
		LPD3DXLOADUSERDATA pLUD = NULL);
	//Cleanup�֐��̉��z��
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
Desc �A�j���[�V�����̏��������A�j���[�V�����R���g���[���[�ƈꏏ�ɓ����
*/
class CAnimInstance
{
	friend class CMultiAnim;

protected:
	//�����o�ϐ�
	CMultiAnim* m_pMultiAnim;
	D3DXMATRIX m_mxWorld;
	LPD3DXANIMATIONCONTROLLER m_pAC;

private:

	//�֐��̉��z��
	virtual HRESULT Setup(LPD3DXANIMATIONCONTROLLER pAC);
	virtual void    UpdateFrames(MultiAnimFrame* pFrame, D3DXMATRIX* pmxBase);
	virtual void   DrawFrames(MultiAnimFrame* pFrame);
	virtual void   DrawMeshFrame(MultiAnimFrame* pFrame);

public:
	//�R���X�g���N�^
	CAnimInstance();
	//�f�X�g���N�^�̉��z��
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