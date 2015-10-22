#include "texture.h"

//コンストラクタ
Texture::Texture()
{
	pTexture = NULL;
}

//デストラクタ
Texture::~Texture()
{
	//読み込まれていたら破棄
	if (pTexture != NULL)
	{
		pTexture->Release();
	}
}

bool Texture::Load(IDirect3DDevice9* pDevice3D, TCHAR* FileName)
{
	//画像読み込み
	//DirectXやWindowsAPIの関数はHRESULTを結果に返す関数が多い
	//FAILEDマクロで失敗したかの判断
	//SUCEEDEDマクロで関数が成功したかの判断
	if (FAILED(D3DXCreateTextureFromFile(pDevice3D, FileName, &pTexture)))
	{
		//読み込み失敗（ファイルが無い可能性が高い）
		return false;
	}

	//読み込み成功
	return true;
}