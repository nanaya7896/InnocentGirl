#pragma once

#include "direct3d.h"

class Texture
{
public:
	IDirect3DTexture9* pTexture;
	//�R���X�g���N�^ �f�X�g���N�^
	Texture();
	~Texture();

	bool Load(IDirect3DDevice9* pDevice, TCHAR* FileName);


};