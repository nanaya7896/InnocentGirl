//includeファイルとライブラリファイルを読み込んでます
//ウィンドウ幅高さの決定



#include"Global.h"
#include "Direct3D/direct3d.h"
#include "Direct3D/sprite.h"
#include "Direct3D/texture.h"
#include"Direct3D\Xfile.h"
#include "DirectSound/directSound.h"
#include "DirectSound/soundbuffer.h"
#include "DirectSound/wave.h"
#include "DirectInput/directInput.h"
#include"Direct3D\Camera.h"

DWORD lasttime;

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
		_T("Apprication"),													//ウィンドウ名
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
	//DirectSoundデバイス作成
	DirectSound directSound;
	directSound.Create(hWnd);

	//wavファイル読み込み
	Wave wave[3];
	//wavファイルは何か適当に用意してください

	wave[0].Load(_T("katana.wav"));
	wave[1].Load(_T("bomb.wav"));
	wave[2].Load(_T("battle.wav"));
	//ファイル読み込みはここまで

	//セカンダリバッファの作成　読み込んだと音データをコピー
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
	//テクスチャのロード
	Texture t_Player(_T("yukitxture.jpg"));
	//画像は何か適当に用意してください
	

	//スプライトの作成
	Sprite sprite[3];
	//-------------------------------------------------------------------------------------------

	//音声の再世
	/*sb[0].Play(false);
	sb[1].Play(true);
	sb[2].Play(true);*/

	
	//----------------------------------------------------
	//カメラのロード
	//----------------------------------------------------
	Camera camera;
	

	//----------------------------------------------------
	//Xファイルのロード
	//----------------------------------------------------
	X_FILE xfile(_T("yukicyan2.X"));

	//xfile.XfileLoader(direct3d.pDevice3D, _T("catsenkan.X"));
	//----------------------------------------------------
	//Playerのロード
	//----------------------------------------------------
	

	/*direct3d.pDevice3D->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	direct3d.pDevice3D->SetRenderState(D3DRS_ZENABLE, TRUE);
	SetRenderState(direct3d.pDevice3D, RENDER_ALPHATEST);*/

	MSG msg = {};

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
			if (SUCCEEDED(direct3d.pDevice3D->BeginScene()))
			{
				//キー状態更新
				//directInput.Update();
				DWORD BlackColor = 0x0000cc;//背景黒色
				//背景クリア
				direct3d.pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, BlackColor, 1.0f, 0);
//
//
//				//デフォルト
//				SetRenderState(direct3d.pDevice3D, RENDER_DEFAULT);
//				sprite[0].SetSize(100, 100);
//				sprite[0].SetPos(200, 300);
//				sprite[0].Draw(direct3d.pDevice3D, font.pTexture);
//
//				/*α
//				SetRenderState(direct3d.pDevice3D, RENDER_ALPHATEST);
//				sprite[1].SetPos(300, 300);
//				sprite[1].Draw(direct3d.pDevice3D, bomb_tex.pTexture);
//
//				加算合成
//				SetRenderState(direct3d.pDevice3D, RENDER_HALFADD);
//				sprite[1].SetPos(400, 300);
//				sprite[1].Draw(direct3d.pDevice3D, bomb_tex.pTexture);
//
//				半加算合成
//				SetRenderState(direct3d.pDevice3D, RENDER_ADD);
//				sprite[1].SetPos(500, 300);
//				sprite[1].Draw(direct3d.pDevice3D, bomb_tex.pTexture);
//
//				SetRenderState(direct3d.pDevice3D, RENDER_DEFAULT);
//*/	
				// 3Dのマテリアル等のセットアップ
					//xfile.SetupMatrices(direct3d.pDevice3D, hWnd, lasttime);

					//カメラのポジションと角度
					camera.Create(D3DXVECTOR3(0, 0,-100), D3DXVECTOR3(0, 0, 0));
				//描画
				xfile.Render(&D3DXVECTOR3(0,0,0),&D3DXVECTOR3(180,60,0),&D3DXVECTOR3(1,1,1),t_Player.GetTexture());
				direct3d.pDevice3D->EndScene();
			}


			//描画反映
			direct3d.pDevice3D->Present(NULL, NULL, NULL, NULL);

			
		}
	}
	
	directInput.Release();
	direct3d.pDevice3D->Release();
	direct3d.pD3D9->Release();
	return 0;
}