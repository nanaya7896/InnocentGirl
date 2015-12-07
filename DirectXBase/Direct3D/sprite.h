#pragma once

#include "direct3d.h"

struct AnimationNum
{
	unsigned int numU;
	unsigned int numV;
};


class Sprite
{
public:
	//板ポリゴン頂点情報
	struct Vertex
	{
		float x, y, z;	//3次元座標
		float rhw;		//2D変換済みフラグ
		float u, v;		//UV座標

	};
	//FVF(柔軟な頂点構造体宣言)
	static const DWORD SPRITE_FVF = D3DFVF_XYZRHW | D3DFVF_TEX1;

	D3DXVECTOR2 pos;

	//スプライトサイズ
	int width;
	int height;

	//UVの分割数(ここではテクスチャを何分割したものとして扱うか)
	unsigned int divU;
	unsigned int divV;
	//UVの番号(分割した画像の番号)
	unsigned int numU;
	unsigned int numV;

	//回転値(ラジアン)
	float rotate;

	//コンストラクタ
	Sprite();
	//~デストラクタ
	~Sprite();

	void SetPos(float x, float y);
	void SetSize(int Width, int Height);
	void SetRotate(float Rotate);

	void SetDivide(unsigned int DivU, unsigned int DivV);
	void SetUVNum(unsigned int NumU, unsigned int NumV);

	void Draw(IDirect3DDevice9* pDevice3D, IDirect3DTexture9* pTexture, bool isTurn = false);

	//スタミナ専用のSprite::Draw
	void Draw_Stamina(IDirect3DDevice9* pDevice3D, IDirect3DTexture9* pTexture, bool isTurn = false);

};