#include "sprite.h"


//�R���X�g���N�^
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

//�f�X�g���N�^

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
	//���_�̈ʒu
	//�摜�̒��_�̈ʒu
	Vertex vtx[4]
	{
		//{x,y,z, 2D�ϊ��ς݃t���O(1����2D�ň���) , u,v}
		//uv���W�̓e�N�X�`���̂ǂ̊p��\�����邩 (0,0)����	(1,0)�E��	(0,1)����	(1,1)�E��	(0.5,0.5 )�e�N�X�`���̒��S
		//���̊p�Ƀe�N�X�`���̉��p�[�Z���g�̈ʒu�����邩���w��
		
		//�E��
		{ (float)width / 2,  -(float)height / 2, 0.0f, 1.0f, 
			(isTurn ? static_cast<float>(numU) / divU		: static_cast<float>(numU+1) / divU	), static_cast<float>(numV) / divV
		},
		//�E��
		{ (float)width / 2,  (float)height / 2, 0.0f, 1.0f, 
			(isTurn ? static_cast<float>(numU) / divU		: static_cast<float>(numU + 1) / divU	), static_cast<float>(numV + 1) / divV
		},
		//����
		{ -(float)width / 2, - (float)height / 2, 0.0f, 1.0f, 
			(isTurn ? static_cast<float>(numU + 1) / divU	: static_cast<float>(numU) / divU		), static_cast<float>(numV )/ divV
		},
		//����
		{  -(float)width / 2,  (float)height / 2, 0.0f, 1.0f, 
			(isTurn ? static_cast<float>(numU + 1) / divU	: static_cast<float>(numU) / divU		), static_cast<float>(numV + 1) / divV
		},
		/*�E��
		{ (float)width / 2, -(float)height / 2, 0.0f, 1.0f,
		(isturn ? static_cast<float>(numu) / divu : static_cast<float>(numu + 1) / divu), static_cast<float>(numv) / divv
		},
		�E��
		{ (float)width / 2, (float)height / 2, 0.0f, 1.0f,
		(isturn ? static_cast<float>(numu) / divu : static_cast<float>(numu + 1) / divu), static_cast<float>(numv + 1) / divv
		},
		����
		{ -(float)width / 2, -(float)height / 2, 0.0f, 1.0f,
		(isturn ? static_cast<float>(numu + 1) / divu : static_cast<float>(numu) / divu), static_cast<float>(numv) / divv
		},
		����
		{ -(float)width / 2, (float)height / 2, 0.0f, 1.0f,
		(isturn ? static_cast<float>(numu + 1) / divu : static_cast<float>(numu) / divu), static_cast<float>(numv + 1) / divv
		},*/
	};

	for (int i = 0; i < 4; i++)
	{
		//��]
		float x = vtx[i].x*cosf(rotate) - vtx[i].y*sinf(rotate);
		float y = vtx[i].x*sinf(rotate) + vtx[i].y*cosf(rotate);
		
		//���s�ړ�
		vtx[i].x = x + pos.x;
		vtx[i].y = y + pos.y;

	}

	//�e�N�X�`���̃Z�b�g
	pDevice3D->SetTexture(0, pTexture);
	//���_�\���̐錾���Z�b�g
	pDevice3D->SetFVF(SPRITE_FVF);
	//�X�v���C�g�`��
	pDevice3D->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vtx, sizeof(Vertex));
	//�Ō��sizeof(Vartex�̓o�C�g���̕ύX)

	//�`��I��

}
//---------------------------------------

//�e�N�X�`�����c�����������ė��p���邩��ݒ�
void Sprite::SetDivide(unsigned int DivU, unsigned int DivV)
{
	if (DivU <= 0 || DivV <= 0)
	{
		return;
	}

	divU = DivU;
	divV = DivV;
}

//���������e�N�X�`���̏c�����Ԗڂ��g�������w��
void Sprite::SetUVNum(unsigned int NumU, unsigned int NumV)
{
	if (NumU >= divU)return;
	if (NumV >= divV)return;

	numU = NumU;
	numV = NumV;
}

//��]��ݒ� ���W�A��
void Sprite::SetRotate(float Rotate)
{
	rotate = Rotate;
}