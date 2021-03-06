//includeファイルとライブラリファイルを読み込んでます
//ウィンドウ幅高さの決定

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



//FPS管理用変数
//測定開始時刻
static int mStartTime;
//カウンタ
static int mCount;
//FPS
static float mFps;
//平均をとるサンプル
static const int N = 60;

void Wait();

//ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//メッセージが送られてきた場合
	switch (msg)
	{
		//ウィンドウを閉じるとき
	case WM_DESTROY:
		//WM_QUITが送られてくる
		PostQuitMessage(0);
		break;

	}
	//
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


//WinMain関数
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウ作成
	const TCHAR* WC_BASIC = _T("BASIC_WINDOW");

	//シンプルウィンドウクラス設定
	WNDCLASSEX wcex = { 
		sizeof(WNDCLASSEX),																						//構造体のサイズを設定
		CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,																	//ウィンドウクラスのスタイル
		WndProc,																								//ウィンドウプロシージャのアドレス
		0,																										//追加メモリが必要ならそのバイト数を書く
		0,																										//同上
		hInstance,																								//クラスを作成するインスタンスのハンドル
		(HICON)LoadImage(NULL, MAKEINTRESOURCE(IDI_APPLICATION),IMAGE_ICON,0,0,LR_DEFAULTSIZE | LR_SHARED),		//アイコンのハンドル
		//(HICON)LoadImage(NULL, "ico/yuki-R1.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED),		//アイコンのハンドル
		(HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED),	//カーソル(マウスポインタのハンドル)
		(HBRUSH)GetStockObject(WHITE_BRUSH),																	//背景色用のブラシハンドル
		NULL,																									//メニューリソースを表す名前
		WC_BASIC,																								//ウィンドウクラスの名前
		NULL																									//アイコン(小)のハンドル
	};
	

	//シンプルウィンドウクラス
	if (!RegisterClassEx(&wcex))
	{
		return false;
	}

	

	//ウィンドウの作成
	HWND hWnd = CreateWindowEx(
		0,																	//拡張ウィンドウスタイル
		WC_BASIC,															//登録されているクラス名
		_T("Inocent Girl"),													//ウィンドウ名
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_VISIBLE,					//ウィンドウスタイル
		CW_USEDEFAULT,														//ウィンドウの横方向の位置
		CW_USEDEFAULT,														//ウィンドウの縦方向の位置
		WINDOW_WIDTH,														//ウィンドウ幅
		WINDOW_HEIGHT,														//ウィンドウ高さ
		NULL,																//親ウィンドウまたはオーナーウィンドウのハンドル
		NULL,																//メニューハンドルまたは子識別子
		hInstance,															//アプリケーションのインスタンスのハンドル
		NULL																//ウィンドウの作成データ
		);

	//--------------------------------
	//DirectSoundデバイスの設定
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
	//Playerの初期化 主人公のロード
	//----------------------------------------------------
	Player Pplayer;
	//--------------------------------------------------------------------------------------------
	//テクスチャのロード/Xファイルのロード
	//Mapのロード
	Map map;
	//Mapの読み込み
	map.LoadBuldings();
	//スプライトの作成
	Sprite sprite[3];
	//-------------------------------------------------------------------------------------------


	//スキンメッシュ用クラス
	CSkinMesh m_CSkinMesh;
	//データのロード
	//m_CSkinMesh.Init(direct3d.pDevice3D,"xfile/hako.x");
	//D3DXMatrixIdentity(&direct3d.d3dMat);

	MSG msg = {};

	
	

	//画面遷移
	//SetRenderState(direct3d.pDevice3D, RENDER_DEFAULT);
	SetRenderState(direct3d.pDevice3D, RENDER_ALPHATEST);
	
	DirectXText fps;
	fps.Create(direct3d.pDevice3D, 32);
	lasttime = timeGetTime();
	while (msg.message != WM_QUIT)
	{
		// アプリケーションに送られてくるメッセージをメッセージキューから取得する
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			DispatchMessage(&msg);	// アプリケーションの各ウィンドウプロシージャにメッセージを転送する
		}
		// メッセージ処理をしていないとき
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
				//キー状態更新
				DirectInput::GetInstance().Update();				
				DWORD BlackColor = 0x0000cc;//背景黒色
				//背景クリア
				direct3d.pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, BlackColor, 1.0f, 0);
				//更新
				sceneChange.Update();
				//描画
				sceneChange.Draw();

				
				direct3d.pDevice3D->EndScene();
			}

			mCount++;
			Wait();
			//描画反映
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