//include�t�@�C���ƃ��C�u�����t�@�C����ǂݍ���ł܂�
//�E�B���h�E�������̌���

#include"Global.h"
#include "Direct3D/direct3d.h"
#include "Direct3D/sprite.h"
#include "Direct3D/texture.h"
#include"Direct3D\Xfile.h"
#include"DirectSound/dxsound.h"
#include "DirectInput/directInput.h"
//#include"Direct3D\Camera.h"
#include"Player/Player.h"
#include"Game/Map.h"
#include "Game/SceneChange.h"
#include "Game/Title.h"
#include "Game/Chapter.h"
#include "Game/Chapter_GameOfTag.h"
#include"Game/Result.h"
#include"Game/Gameover.h"
//#include"DirectXAnimation/AnimateObject.h"
//#include"DirectXAnimation/MyAllocateHierarchy.h"

DWORD lasttime;

//FPS�Ǘ��p�ϐ�
//����J�n����
static int mStartTime;
//�J�E���^
static int mCount;
//FPS
static float mFps;
//���ς��Ƃ�T���v��
static const int N = 60;

void Wait();

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
	//DirectSound�f�o�C�X�̐ݒ�
	CSound sound(hWnd);

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
	//�X�v���C�g�̍쐬
	Sprite sprite[3];
	//-------------------------------------------------------------------------------------------


	//�X�L�����b�V���p�N���X
	CSkinMesh m_CSkinMesh;
	//�f�[�^�̃��[�h
	//m_CSkinMesh.Init(direct3d.pDevice3D,"xfile/hako.x");
	//D3DXMatrixIdentity(&direct3d.d3dMat);

	MSG msg = {};

	//��ʑJ��
	//SetRenderState(direct3d.pDevice3D, RENDER_DEFAULT);
	SetRenderState(direct3d.pDevice3D, RENDER_ALPHATEST);
	SceneChange::scenechange = new Title();	//�^�C�g��
	DirectXText fps;
	fps.Create(direct3d.pDevice3D, 32);
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
			if (mCount == 0)
			{
				mStartTime = timeGetTime();
			}
			if (mCount == N)
			{
				int t = timeGetTime();
				mFps = 1000.0f / ((t - mStartTime) / (float)N);
				mCount = 0;
				mStartTime = t;
			}
			if (SUCCEEDED(direct3d.pDevice3D->BeginScene()))
			{
				//�L�[��ԍX�V
				DirectInput::GetInstance().Update();
				
				
				//SceneChange::scenechange->Update();
				
				DWORD BlackColor = 0x0000cc;//�w�i���F
				//�w�i�N���A
				direct3d.pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, BlackColor, 1.0f, 0);
				////Map�`��
				//map.MapRender();
			//	m_CSkinMesh.Draw(direct3d.pDevice3D);
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
				fps.Draw(D3DXCOLOR(255, 255, 255, 10), 20, 20, _T("%.1f"), mFps);
				
				direct3d.pDevice3D->EndScene();
			}

			mCount++;
			Wait();
			//�`�攽�f
			direct3d.pDevice3D->Present(NULL, NULL, NULL, NULL);		
		}
	}	
	DirectInput::GetInstance().Release();
	direct3d.pDevice3D->Release();
	direct3d.pD3D9->Release();
	return 0;
}

void Wait()
{
	int tookTime = timeGetTime() - mStartTime;
	int waitTime =( mCount * 1000 / FPS) - tookTime;
	if (waitTime > 0)
	{
		Sleep(waitTime);
	}
}