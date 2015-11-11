#pragma once
#include"../Global.h"

//�h���t���[���\���� (���ꂼ��̃��b�V���p�̍ŏI���[���h�s���ǉ�����j
struct MYFRAME : public D3DXFRAME
{
	D3DXMATRIX CombinedTransformationMatrix;
	// �I�t�Z�b�g�s��(�C���f�b�N�X�t�`��p)
	D3DXMATRIX OffsetMat;
	// �s��e�[�u���̃C���f�b�N�X�ԍ�(�C���f�b�N�X�t�p)
	DWORD OffsetID;
};

//�h�����b�V���R���e�i�[�\����(
//�R���e�i�[���e�N�X�`���𕡐����Ă�悤�Ƀ|�C���^�[�̃|�C���^�[��ǉ�����j
struct MYMESHCONTAINER : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9*  ppTextures;
	DWORD dwWeight; //�d�݂̌��i�d�݂Ƃ͒��_�ւ̉e���B�j
	DWORD dwBoneNum; //�{�[���̐�
	LPD3DXBUFFER pBoneBuffer; //�{�[���E�e�[�u��
	D3DXMATRIX** ppBoneMatrix; //�S�Ẵ{�[���̃��[���h�s��̐擪�|�C���^�[
	D3DXMATRIX* pBoneOffsetMatrices; //�t���[���Ƃ��Ẵ{�[���̃��[���h�s��̃|�C���^�[
	LPD3DXMESH pOriMesh; //�I���W�i�����b�V���p
	DWORD NumPaletteEntries; //�p���b�g�T�C�Y
	// Work�p
	std::vector<D3DXMATRIX> m_WorkBoneMatArray;
	// �e������t���[���ւ̎Q�Ɣz��B�`�掞�ɂ��̃t���[���̍s����g���B
	std::vector<MYFRAME*> BoneFrameArray;
	MYMESHCONTAINER(){
		ppBoneMatrix = NULL;
		pBoneOffsetMatrices = NULL;
	}
};

//X�t�@�C�����̃A�j���[�V�����K�w��ǂ݉����Ă����N���X��h��������B
//ID3DXAllocateHierarchy�͔h�����邱�Ƒz�肵�Đ݌v����Ă���B
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