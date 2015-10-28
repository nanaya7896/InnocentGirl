#include "texture.h"

//�R���X�g���N�^
Texture::Texture()
{

}

Texture::Texture(const TCHAR*FileName)
{
	Load(FileName);

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

BOOL Texture::Load(const TCHAR* FileName)
{
	//�摜�ǂݍ���
	//DirectX��WindowsAPI�̊֐���HRESULT�����ʂɕԂ��֐�������
	//FAILED�}�N���Ŏ��s�������̔��f
	//SUCEEDED�}�N���Ŋ֐��������������̔��f
	if (FAILED(D3DXCreateTextureFromFile(pDevice3D, FileName ,&pTexture)))
	{
		//�ǂݍ��ݎ��s�i�t�@�C���������\���������j
		return FALSE;
	}

	return TRUE;
}

LPDIRECT3DTEXTURE9 Texture::GetTexture()
{
	return pTexture;
}
