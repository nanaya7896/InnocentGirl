#include "sprite.h"


//コンストラクタ
Sprite::Sprite()
{
	pos.x = pos.y = 0.0f;
	width = height = 0;

	divU = 1;
	divV = 1;
	numU = 0;
	numV = 0;
	rotate = 0.0f;
}

//デストラクタ

Sprite::~Sprite()
{

}

//------------------------

void Sprite::SetPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
}


//------------------------

void Sprite::SetSize(int Width, int Height)
{
	width = Width;
	height = Height;
}


//------------------------

void Sprite::Draw(IDirect3DDevice9*pDevice3D, IDirect3DTexture9* pTexture,bool isTurn)
{
	//頂点の位置
	//画像の頂点の位置
	Vertex vtx[4]
	{
		//{x,y,z, 2D変換済みフラグ(1だと2Dで扱う) , u,v}
		//uv座標はテクスチャのどの角を表示するか (0,0)左上	(1,0)右上	(0,1)左下	(1,1)右下	(0.5,0.5 )テクスチャの中心
		//その角にテクスチャの何パーセントの位置が来るかを指定
		
		//右上
		{ (float)width / 2,  -(float)height / 2, 0.0f, 1.0f, 
			(isTurn ? static_cast<float>(numU) / divU		: static_cast<float>(numU+1) / divU	), static_cast<float>(numV) / divV
		},
		//右下
		{ (float)width / 2,  (float)height / 2, 0.0f, 1.0f, 
			(isTurn ? static_cast<float>(numU) / divU		: static_cast<float>(numU + 1) / divU	), static_cast<float>(numV + 1) / divV
		},
		//左上
		{ -(float)width / 2, - (float)height / 2, 0.0f, 1.0f, 
			(isTurn ? static_cast<float>(numU + 1) / divU	: static_cast<float>(numU) / divU		), static_cast<float>(numV )/ divV
		},
		//左下
		{  -(float)width / 2,  (float)height / 2, 0.0f, 1.0f, 
			(isTurn ? static_cast<float>(numU + 1) / divU	: static_cast<float>(numU) / divU		), static_cast<float>(numV + 1) / divV
		},
		/*右上
		{ (float)width / 2, -(float)height / 2, 0.0f, 1.0f,
		(isturn ? static_cast<float>(numu) / divu : static_cast<float>(numu + 1) / divu), static_cast<float>(numv) / divv
		},
		右下
		{ (float)width / 2, (float)height / 2, 0.0f, 1.0f,
		(isturn ? static_cast<float>(numu) / divu : static_cast<float>(numu + 1) / divu), static_cast<float>(numv + 1) / divv
		},
		左上
		{ -(float)width / 2, -(float)height / 2, 0.0f, 1.0f,
		(isturn ? static_cast<float>(numu + 1) / divu : static_cast<float>(numu) / divu), static_cast<float>(numv) / divv
		},
		左下
		{ -(float)width / 2, (float)height / 2, 0.0f, 1.0f,
		(isturn ? static_cast<float>(numu + 1) / divu : static_cast<float>(numu) / divu), static_cast<float>(numv + 1) / divv
		},*/
	};

	for (int i = 0; i < 4; i++)
	{
		//回転
		float x = vtx[i].x*cosf(rotate) - vtx[i].y*sinf(rotate);
		float y = vtx[i].x*sinf(rotate) + vtx[i].y*cosf(rotate);
		
		//平行移動
		vtx[i].x = x + pos.x;
		vtx[i].y = y + pos.y;

	}

	//テクスチャのセット
	pDevice3D->SetTexture(0, pTexture);
	//頂点構造体宣言をセット
	pDevice3D->SetFVF(SPRITE_FVF);
	//スプライト描画
	pDevice3D->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vtx, sizeof(Vertex));
	//最後のsizeof(Vartexはバイト数の変更)

	//描画終了

}
//---------------------------------------

//テクスチャを縦横何分割して利用するかを設定
void Sprite::SetDivide(unsigned int DivU, unsigned int DivV)
{
	if (DivU <= 0 || DivV <= 0)
	{
		return;
	}

	divU = DivU;
	divV = DivV;
}

//分割したテクスチャの縦横何番目を使うかを指定
void Sprite::SetUVNum(unsigned int NumU, unsigned int NumV)
{
	if (NumU >= divU)return;
	if (NumV >= divV)return;

	numU = NumU;
	numV = NumV;
}

//回転を設定 ラジアン
void Sprite::SetRotate(float Rotate)
{
	rotate = Rotate;
}