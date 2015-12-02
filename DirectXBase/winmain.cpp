//include�t�@�C���ƃ��C�u�����t�@�C����ǂݍ���ł܂�
//�E�B���h�E�������̌���

#include"Global.h"
#include "Direct3D/direct3d.h"
#include "Direct3D/sprite.h"
#include "Direct3D/texture.h"
#include"Direct3D\Xfile.h"
#include"DirectSound/dxsound.h"
#include "DirectInput/directInput.h"
#include"SceneChanger\SceneChange.h"
#include"Player/Player.h"
#include"Game/Map.h"
#include "Game/Title.h"
#include "Game/Chapter.h"

#include"Game/Result.h"
#include"Game/Gameover.h"
//#include"DirectXAnimation/AnimateObject.h"
//#include"DirectXAnimation/MyAllocateHierarchy.h"
#include <io.h>
#include <Fcntl.h>

int hConsole = 0;

void createConsoleWindow() {
	AllocConsole();
	hConsole = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	*stdout = *_fdopen(hConsole, "w");
	setvbuf(stdout, NULL, _IONBF, 0);
}
void closeConsoleWindow() {
	_close(hConsole);
}


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
		//(HICON)LoadImage(NULL, "ico/yuki-R1.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED),		//�A�C�R���̃n���h��
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


	SceneChange sceneChange;
	sceneChange.Initialize();
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
				DWORD BlackColor = 0x0000cc;//�w�i���F
				//�w�i�N���A
				direct3d.pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, BlackColor, 1.0f, 0);
				//�X�V
				sceneChange.Update();
				//�`��
				sceneChange.Draw();

				
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