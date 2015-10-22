#pragma once

#include "direct3d.h"

class Texture
{
public:
	IDirect3DTexture9* pTexture;
	//コンストラクタ デストラクタ
	Texture();
	~Texture();

	bool Load(IDirect3DDevice9* pDevice, TCHAR* FileName);


};