#include "direct3d.h"
LPDIRECT3D9 Direct3D::pD3D9=NULL;
LPDIRECT3DDEVICE9 Direct3D::pDevice3D=NULL;
D3DXMATRIX Direct3D::d3dMat;

DWORD FloatToDWORD(float v) { return *((DWORD *)&v); }
////�R���X�g���N�^
Direct3D::Direct3D()
{

}

//�f�X�g���N�^
Direct3D::~Direct3D()
{

}

void SetRenderState(IDirect3DDevice9* pD3DDevice, RENDERSTATE RenderState)
{
	switch (RenderState)
	{

		case RENDER_DEFAULT:
		{
			pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);	
			pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);	//���u�����h�̖�����
		}
		break;

		case RENDER_ALPHATEST:
		{
			//���e�X�g�ɂ�铧���̈�̐؂蔲��
			pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			//���e�X�g�̗L����//���e�X�g(�����x�̏����������ĕ`��)
			pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x80);					// �A���t�@�Q�ƒl
			pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	//���e�X�g���i�

			pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);			//���u�����h�̖�����
		}
		break;

		case RENDER_HALFADD:
		{
			//�����Z
			pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);	//���e�X�g�̖�����
			pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	//���u�����f�B���O�̗L����
			pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);		//Z�o�b�t�@���s��Ȃ�

			//pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);			//z�e�X�g���s��Ȃ�
			//pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);		//���C�e�B���O���s��Ȃ�

			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		//�u�����f�B���O�I�v�V�������Z
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	//SRC�̐ݒ�
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		//DEST�̐ݒ�

		}
		break;

		case RENDER_ADD:
		{
			//�S���Z����
			pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	//���u�����f�B���O�̗L����
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);	//�u�����f�B���O�I�v�V�������Z
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);	//SRC�̐ݒ�
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);	//DEST�̐ݒ�
			pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);	//���e�X�g�̖�����

		}
		break;

	}
}


bool Direct3D::Create(HWND hWnd, int Width, int Height)
{
	//Direct3D9�I�u�W�F�N�g�̍쐬
	pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	//�f�B�X�v���C���擾
	D3DDISPLAYMODE Display;
	pD3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &Display);

	//�X���b�v�`�F�C���ݒ�
	//�X���b�v�`�F�C���@�o�b�N�o�b�t�@���t�����g�o�b�t�@�ɏ���������
	//DISCARD�̓X���b�v�`�F�C���̕��@��DIrectX�ɔC����Ƃ����ݒ�
	D3DPRESENT_PARAMETERS D3DParam =
	{
		Width, Height, Display.Format, 1, D3DMULTISAMPLE_NONE, 0,
		D3DSWAPEFFECT_DISCARD, hWnd, TRUE, TRUE, D3DFMT_D16, 0, 0, D3DPRESENT_INTERVAL_DEFAULT
	};
	D3DParam.EnableAutoDepthStencil = TRUE;
	
	//����̐ݒ�Ńf�o�C�X�쐬�����݂�
	//HAL���[�h��3D�f�o�C�X�쐬
	if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DParam.hDeviceWindow,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D)))
	{
		if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DParam.hDeviceWindow,
			D3DCREATE_MIXED_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D)))
		{
			//Ref���[�h��3D�f�o�C�X�쐬
			if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, D3DParam.hDeviceWindow,
				D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D)))
			{
				if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, D3DParam.hDeviceWindow,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D)))
				{
					// 3D�f�o�C�X�쐬���s
					pD3D9->Release();
					return false;
				}
			}
		}
	}
	pDevice3D->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	pDevice3D->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice3D->SetRenderState(D3DRS_ZENABLE, true);
	pDevice3D->SetRenderState(D3DRS_ZWRITEENABLE, true);
	pDevice3D->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	pDevice3D->SetRenderState(D3DRS_LIGHTING, true);
	pDevice3D->SetRenderState(D3DRS_SPECULARENABLE, true);
	pDevice3D->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice3D->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice3D->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice3D->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice3D->SetRenderState(D3DRS_ALPHAREF, 0x00000000);
	pDevice3D->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice3D->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	pDevice3D->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice3D->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	pDevice3D->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	pDevice3D->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	pDevice3D->SetRenderState(D3DRS_POINTSIZE, FloatToDWORD(1.0f));
	pDevice3D->SetRenderState(D3DRS_POINTSIZE_MIN, FloatToDWORD(0.0f));
	pDevice3D->SetRenderState(D3DRS_POINTSCALE_A, FloatToDWORD(0.0f));
	pDevice3D->SetRenderState(D3DRS_POINTSCALE_B, FloatToDWORD(0.0f));
	pDevice3D->SetRenderState(D3DRS_POINTSCALE_C, FloatToDWORD(1.0f));

	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Direction = D3DXVECTOR3(1, -1, 1);
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;

	pDevice3D->SetLight(0, &light);
	pDevice3D->LightEnable(0, true);
	pDevice3D->SetRenderState(D3DRS_LIGHTING, false);
	pDevice3D->SetRenderState(D3DRS_AMBIENT, 0xff030303);



	return true;
}