#pragma once

#include "direct3d.h"

class Texture : public Direct3D
{
public:
	LPDIRECT3DTEXTURE9		pTexture;
	//コンストラクタ デストラクタ
	Texture();
	Texture(const TCHAR* FileName);
	~Texture();

	BOOL Load(const TCHAR* FileName);

	LPDIRECT3DTEXTURE9 GetTexture();

};