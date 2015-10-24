//include�t�@�C���ƃ��C�u�����t�@�C����ǂݍ���ł܂�
#include"Global.h"

#include "Direct3D/direct3d.h"
#include "Direct3D/sprite.h"
#include "Direct3D/texture.h"
#include"Direct3D\Xfile.h"
#include "DirectSound/directSound.h"
#include "DirectSound/soundbuffer.h"
#include "DirectSound/wave.h"
#include "DirectInput/directInput.h"

//�E�B���h�E�������̌���
const int WINDOW_WIDTH = 1800;
const int WINDOW_HEIGHT = 900;
DWORD lasttime;

//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//���b�Z�[�W�������Ă����ꍇ
	switch (msg)
	{
		//�E�B���h�E�����Ƃ�
	case WM_DESTROY:
		//WM_QUIT�������Ă���
		PostQuitMessage(0);
		break;

	}
	//
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


//WinMain�֐�
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E�쐬
	const TCHAR* WC_BASIC = _T("BASIC_WINDOW");

	//�V���v���E�B���h�E�N���X�ݒ�
	WNDCLASSEX wcex = { 
		sizeof(WNDCLASSEX),																						//�\���̂̃T�C�Y��ݒ�
		CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,																	//�E�B���h�E�N���X�̃X�^�C��
		WndProc,																								//�E�B���h�E�v���V�[�W���̃A�h���X
		0,																										//�ǉ����������K�v�Ȃ炻�̃o�C�g��������
		0,																										//����
		hInstance,																								//�N���X���쐬����C���X�^���X�̃n���h��
		(HICON)LoadImage(NULL, MAKEINTRESOURCE(IDI_APPLICATION),IMAGE_ICON,0,0,LR_DEFAULTSIZE | LR_SHARED),		//�A�C�R���̃n���h��
		(HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED),	//�J�[�\��(�}�E�X�|�C���^�̃n���h��)
		(HBRUSH)GetStockObject(WHITE_BRUSH),																	//�w�i�F�p�̃u���V�n���h��
		NULL,																									//���j���[���\�[�X��\�����O
		WC_BASIC,																								//�E�B���h�E�N���X�̖��O
		NULL																									//�A�C�R��(��)�̃n���h��
	};
	

	//�V���v���E�B���h�E�N���X
	if (!RegisterClassEx(&wcex))
	{
		return false;
	}

	

	//�E�B���h�E�̍쐬
	HWND hWnd = CreateWindowEx(
		0,																	//�g���E�B���h�E�X�^�C��
		WC_BASIC,															//�o�^����Ă���N���X��
		_T("Apprication"),													//�E�B���h�E��
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_VISIBLE,					//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,														//�E�B���h�E�̉������̈ʒu
		CW_USEDEFAULT,														//�E�B���h�E�̏c�����̈ʒu
		WINDOW_WIDTH,														//�E�B���h�E��
		WINDOW_HEIGHT,														//�E�B���h�E����
		NULL,																//�e�E�B���h�E�܂��̓I�[�i�[�E�B���h�E�̃n���h��
		NULL,																//���j���[�n���h���܂��͎q���ʎq
		hInstance,															//�A�v���P�[�V�����̃C���X�^���X�̃n���h��
		NULL																//�E�B���h�E�̍쐬�f�[�^
		);

	//--------------------------------
	//DirectSound�f�o�C�X�쐬
	DirectSound directSound;
	directSound.Create(hWnd);

	//wav�t�@�C���ǂݍ���
	Wave wave[3];
	//wav�t�@�C���͉����K���ɗp�ӂ��Ă�������

	wave[0].Load(_T("katana.wav"));
	wave[1].Load(_T("bomb.wav"));
	wave[2].Load(_T("battle.wav"));
	//�t�@�C���ǂݍ��݂͂����܂�

	//�Z�J���_���o�b�t�@�̍쐬�@�ǂݍ��񂾂Ɖ��f�[�^���R�s�[
	SoundBuffer sb[3];
	for (int i = 0; i < 3; i++)
	{
		sb[i].Create(directSound.pDirectSound8, wave[i].WaveFormat, wave[i].WaveData, wave[i].DataSize);

	}

	//--------------------------------
	//direct3D

	Direct3D direct3d;
	direct3d.Create(hWnd, WINDOW_WIDTH, WINDOW_HEIGHT);

	//---------------------------------
	//directInput

	DirectInput directInput;
	//directInput.Init(hWnd);

	//--------------------------------------------------------------------------------------------
	//�e�N�X�`���̃��[�h
	Texture texture;
	//�摜�͉����K���ɗp�ӂ��Ă�������
	
	
	

	//�X�v���C�g�̍쐬
	Sprite sprite[3];
	//-------------------------------------------------------------------------------------------

	//�����̍Đ�
	/*sb[0].Play(false);
	sb[1].Play(true);
	sb[2].Play(true);*/




	//----------------------------------------------------
	//X�t�@�C���̃��[�h
	//----------------------------------------------------
	X_FILE xfile;
	//X�t�@�C�������[�h���܂�.
	xfile.XfileLoader(direct3d.pDevice3D, _T("yukicyan.X"));
	//xfile.XfileLoader(direct3d.pDevice3D, _T("catsenkan.X"));
	xfile.MaterialRead(direct3d.pDevice3D);
	//----------------------------------------------------
	//Player�̃��[�h
	//----------------------------------------------------
	

	direct3d.pDevice3D->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	

	direct3d.pDevice3D->SetRenderState(D3DRS_ZENABLE, TRUE);
	SetRenderState(direct3d.pDevice3D, RENDER_ALPHATEST);

	MSG msg = {};

	lasttime = timeGetTime();
	while (msg.message != WM_QUIT)
	{
		// �A�v���P�[�V�����ɑ����Ă��郁�b�Z�[�W�����b�Z�[�W�L���[����擾����
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			DispatchMessage(&msg);	// �A�v���P�[�V�����̊e�E�B���h�E�v���V�[�W���Ƀ��b�Z�[�W��]������
		}
		// ���b�Z�[�W���������Ă��Ȃ��Ƃ�
		else
		{
			if (SUCCEEDED(direct3d.pDevice3D->BeginScene()))
			{
				//�L�[��ԍX�V
				//directInput.Update();
				DWORD BlackColor = 0xff000000;//�w�i���F
				//�w�i�N���A
				direct3d.pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, BlackColor, 1.0f, 0);
//
//
//				//�f�t�H���g
//				SetRenderState(direct3d.pDevice3D, RENDER_DEFAULT);
//				sprite[0].SetSize(100, 100);
//				sprite[0].SetPos(200, 300);
//				sprite[0].Draw(direct3d.pDevice3D, font.pTexture);
//
//				/*��
//				SetRenderState(direct3d.pDevice3D, RENDER_ALPHATEST);
//				sprite[1].SetPos(300, 300);
//				sprite[1].Draw(direct3d.pDevice3D, bomb_tex.pTexture);
//
//				���Z����
//				SetRenderState(direct3d.pDevice3D, RENDER_HALFADD);
//				sprite[1].SetPos(400, 300);
//				sprite[1].Draw(direct3d.pDevice3D, bomb_tex.pTexture);
//
//				�����Z����
//				SetRenderState(direct3d.pDevice3D, RENDER_ADD);
//				sprite[1].SetPos(500, 300);
//				sprite[1].Draw(direct3d.pDevice3D, bomb_tex.pTexture);
//
//				SetRenderState(direct3d.pDevice3D, RENDER_DEFAULT);
//*/	
				
				//����
				xfile.NatureLight(direct3d.pDevice3D);
				
				// 3D�̃}�e���A�����̃Z�b�g�A�b�v
					xfile.SetupMatrices(direct3d.pDevice3D, hWnd, lasttime);
				//�`��
				xfile.Render(direct3d.pDevice3D);
				direct3d.pDevice3D->EndScene();
			}


			//�`�攽�f
			direct3d.pDevice3D->Present(NULL, NULL, NULL, NULL);

			
		}
	}
	
	directInput.Release();

	return 0;
}