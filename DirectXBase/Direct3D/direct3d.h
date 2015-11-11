#pragma once 

#define D3D_DEBUG_INFO	//Direct3D�f�o�b�O�t���O
#include"../Global.h"



enum RENDERSTATE
{
	RENDER_DEFAULT,		//�f�t�H���g
	RENDER_ALPHATEST,	//���e�X�g
	RENDER_HALFADD,		//�����Z����
	RENDER_ADD			//���Z����

};


void SetRenderState(IDirect3DDevice9* pD3Device, RENDERSTATE RenderrState);

//-------------------------------
class Direct3D
{
public:

	

	//�R���X�g���N�^�@�f�X�g���N�^
	Direct3D();
	~Direct3D();

	//�֐���`
	bool Create(HWND hWmd, int Width, int Height);
	friend int _stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int);

protected:
	static LPDIRECT3D9	pD3D9;				//Direct3D�f�o�C�X�����p�I�u�W�F�N�g
	static LPDIRECT3DDEVICE9 pDevice3D;		//Direct3D�̃f�o�C�X�@�X�v���C�g�̕\����e�N�X�`���̃��[�h���ɕK�v
	//�s��ɕK�v
	static D3DXMATRIX d3dMat;
};
