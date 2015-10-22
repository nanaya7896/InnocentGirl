#include "texture.h"

//�R���X�g���N�^
Texture::Texture()
{
	pTexture = NULL;
}

//�f�X�g���N�^
Texture::~Texture()
{
	//�ǂݍ��܂�Ă�����j��
	if (pTexture != NULL)
	{
		pTexture->Release();
	}
}

bool Texture::Load(IDirect3DDevice9* pDevice3D, TCHAR* FileName)
{
	//�摜�ǂݍ���
	//DirectX��WindowsAPI�̊֐���HRESULT�����ʂɕԂ��֐�������
	//FAILED�}�N���Ŏ��s�������̔��f
	//SUCEEDED�}�N���Ŋ֐��������������̔��f
	if (FAILED(D3DXCreateTextureFromFile(pDevice3D, FileName, &pTexture)))
	{
		//�ǂݍ��ݎ��s�i�t�@�C���������\���������j
		return false;
	}

	//�ǂݍ��ݐ���
	return true;
}