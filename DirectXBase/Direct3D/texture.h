#pragma once

#include "direct3d.h"

class Texture : public Direct3D
{
public:
	LPDIRECT3DTEXTURE9		pTexture;
	//�R���X�g���N�^ �f�X�g���N�^
	Texture();
	Texture(const TCHAR* FileName);
	~Texture();

	void Load(const TCHAR* FileName);

	LPDIRECT3DTEXTURE9 GetTexture();

};