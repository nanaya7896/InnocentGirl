//include�t�@�C���ƃ��C�u�����t�@�C����ǂݍ���ł܂�
//�E�B���h�E�������̌���

#include"Global.h"
#include "Direct3D/direct3d.h"
#include "Direct3D/sprite.h"
#include "Direct3D/texture.h"
#include"Direct3D\Xfile.h"
#include "DirectSound/directSound.h"
#include "DirectSound/soundbuffer.h"
#include "DirectSound/wave.h"
#include "DirectInput/directInput.h"
//#include"Direct3D\Camera.h"
#include"Player/Player.h"
#include"Game/Map.h"
#include "Game/SceneChange.h"
#include "Game/Title.h"
#include "Game/Chapter.h"
#include "Game/Chapter_GameOfTag.h"
//#include"DirectXAnimation/AnimateObject.h"
//#include"DirectXAnimation/MyAllocateHierarchy.h"

DWORD lasttime;

D3DXVECTOR3 PlayerPos(0.0f,0.0f,0.0f);
D3DXVECTOR3 PlayerAngle(0.0f,0.0f,0.0f);
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
		_T("Inocent Girl"),													//�E�B���h�E��
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

		
	DirectInput::GetInstance().Init();

	//----------------------------------------------------
	//Player�̏����� ��l���̃��[�h
	//----------------------------------------------------
	Player Pplayer;
	//--------------------------------------------------------------------------------------------
	//�e�N�X�`���̃��[�h/X�t�@�C���̃��[�h
	//Map�̃��[�h
	Map map;
	//Map�̓ǂݍ���
	map.LoadBuldings();
	/*Texture tfloor1(_T("floor1.bmp"));
	Texture tfloor2(_T("floor2.bmp"));
	Texture tfloor3(_T("floor3.bmp"));
	Texture tfloor4(_T("floor4.bmp"));*/
	//�X�v���C�g�̍쐬
	Sprite sprite[3];
	//-------------------------------------------------------------------------------------------
	//�����̍Đ�
	/*sb[0].Play(false);
	sb[1].Play(true);
	sb[2].Play(true);*/
	//----------------------------------------------------
	//�J�����̃��[�h
	//----------------------------------------------------
//	Camera camera;
	//xfile.XfileLoader(direct3d.pDevice3D, _T("catsenkan.X"));
	//----------------------------------------------------
	//Player�̃��[�h
	//----------------------------------------------------
	/*direct3d.pDevice3D->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	direct3d.pDevice3D->SetRenderState(D3DRS_ZENABLE, TRUE);
	SetRenderState(direct3d.pDevice3D, RENDER_ALPHATEST);*/

	//�X�L�����b�V���p�N���X
	//CSkinMesh m_CSkinMesh;
	//�f�[�^�̃��[�h
	//m_CSkinMesh.Init(direct3d.pDevice3D,"");
	//D3DXMatrixIdentity(&direct3d.d3dMat);

	MSG msg = {};

	//��ʑJ��
	//SetRenderState(direct3d.pDevice3D, RENDER_DEFAULT);
	SetRenderState(direct3d.pDevice3D, RENDER_ALPHATEST);
	SceneChange::scenechange = new GameMainTag();	//�^�C�g��
	
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
				DirectInput::GetInstance().Update();
				
				
				//SceneChange::scenechange->Update();
				
				DWORD BlackColor = 0x0000cc;//�w�i���F
				//�w�i�N���A
				direct3d.pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, BlackColor, 1.0f, 0);
				////Map�`��
				map.MapRender();
				SceneChange::scenechange->Update();
				SceneChange::scenechange->Draw();
					//�v���C���[�̈ړ�
				//PlayerPos = Pplayer.PlayerMove(lasttime, D3DXVECTOR3(PlayerPos.x, PlayerPos.y, PlayerPos.z));
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
				// 3D�̃}�e���A�����̃Z�b�g�A�b�v
					//xfile.SetupMatrices(direct3d.pDevice3D, hWnd, lasttime);
				//D3DXVECTOR3 viewVecE(0.0f, 0.5f, -1.5f);
				//D3DXVECTOR3 viewVecL(0.0f, 0.0f, 0.0f);
				//�J�����̃|�W�V�����Ɗp�x
				//camera.Create(D3DXVECTOR3(PlayerPos.x + viewVecE.x, PlayerPos.y + viewVecE.y, PlayerPos.z + viewVecE.z), D3DXVECTOR3(PlayerAngle.x + viewVecL.x, PlayerAngle.y + viewVecL.y, PlayerAngle.z + viewVecL.z));
				////�`��
				//Pplayer.PlayerCreate(D3DXVECTOR3(PlayerPos.x,PlayerPos.y,PlayerPos.z));
				//map.MapRender();
				
				
				direct3d.pDevice3D->EndScene();
			}
			//�`�攽�f
			direct3d.pDevice3D->Present(NULL, NULL, NULL, NULL);		
		}
	}	
	DirectInput::GetInstance().Release();
	direct3d.pDevice3D->Release();
	direct3d.pD3D9->Release();
	return 0;
}