#include "texture.h"

//コンストラクタ
Texture::Texture()
{

}

Texture::Texture(const TCHAR*FileName)
{
	Load(FileName);

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

BOOL Texture::Load(const TCHAR* FileName)
{
	//画像読み込み
	//DirectXやWindowsAPIの関数はHRESULTを結果に返す関数が多い
	//FAILEDマクロで失敗したかの判断
	//SUCEEDEDマクロで関数が成功したかの判断
	if (FAILED(D3DXCreateTextureFromFile(pDevice3D, FileName ,&pTexture)))
	{
		//読み込み失敗（ファイルが無い可能性が高い）
		return FALSE;
	}

	return TRUE;
}

LPDIRECT3DTEXTURE9 Texture::GetTexture()
{
	return pTexture;
}
