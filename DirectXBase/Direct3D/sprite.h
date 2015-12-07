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
	//�|���S�����_���
	struct Vertex
	{
		float x, y, z;	//3�������W
		float rhw;		//2D�ϊ��ς݃t���O
		float u, v;		//UV���W

	};
	//FVF(�_��Ȓ��_�\���̐錾)
	static const DWORD SPRITE_FVF = D3DFVF_XYZRHW | D3DFVF_TEX1;

	D3DXVECTOR2 pos;

	//�X�v���C�g�T�C�Y
	int width;
	int height;

	//UV�̕�����(�����ł̓e�N�X�`�����������������̂Ƃ��Ĉ�����)
	unsigned int divU;
	unsigned int divV;
	//UV�̔ԍ�(���������摜�̔ԍ�)
	unsigned int numU;
	unsigned int numV;

	//��]�l(���W�A��)
	float rotate;

	//�R���X�g���N�^
	Sprite();
	//~�f�X�g���N�^
	~Sprite();

	void SetPos(float x, float y);
	void SetSize(int Width, int Height);
	void SetRotate(float Rotate);

	void SetDivide(unsigned int DivU, unsigned int DivV);
	void SetUVNum(unsigned int NumU, unsigned int NumV);

	void Draw(IDirect3DDevice9* pDevice3D, IDirect3DTexture9* pTexture, bool isTurn = false);

	//�X�^�~�i��p��Sprite::Draw
	void Draw_Stamina(IDirect3DDevice9* pDevice3D, IDirect3DTexture9* pTexture, bool isTurn = false);

};