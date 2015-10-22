#include "direct3d.h"

//コンストラクタ
Direct3D::Direct3D()
{
	pD3D9 = NULL;
	pDevice3D = NULL;
}

//デストラクタ
Direct3D::~Direct3D()
{
	pDevice3D->Release();
	pD3D9->Release();
}

void SetRenderState(IDirect3DDevice9* pD3DDevice, RENDERSTATE RenderState)
{
	switch (RenderState)
	{

		case RENDER_DEFAULT:
		{
			pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);	
			pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);	//αブレンドの無効化
		}
		break;

		case RENDER_ALPHATEST:
		{
			//αテストによる透明領域の切り抜き
			pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			//αテストの有効化//αテスト(透明度の情報を加味して描画)
			pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x80);					// アルファ参照値
			pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	//αテスト合格基準

			pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);			//αブレンドの無効化
		}
		break;

		case RENDER_HALFADD:
		{
			//半加算
			pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);	//αテストの無効化
			pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	//αブレンディングの有効化
			pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);		//Zバッファを行わない

			//pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);			//zテストを行わない
			//pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);		//ライティングを行わない

			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		//ブレンディングオプション加算
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	//SRCの設定
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		//DESTの設定

		}
		break;

		case RENDER_ADD:
		{
			//全加算合成
			pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	//αブレンディングの有効化
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);	//ブレンディングオプション加算
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);	//SRCの設定
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);	//DESTの設定
			pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);	//αテストの無効化

		}
		break;

	}
}


bool Direct3D::Create(HWND hWnd, int Width, int Height)
{
	//Direct3D9オブジェクトの作成
	pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	//ディスプレイ情報取得
	D3DDISPLAYMODE Display;
	pD3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &Display);

	//スワップチェイン設定
	//スワップチェイン　バックバッファをフロントバッファに書きかえる
	//DISCARDはスワップチェインの方法をDIrectXに任せるという設定
	D3DPRESENT_PARAMETERS D3DParam =
	{
		Width, Height, Display.Format, 1, D3DMULTISAMPLE_NONE, 0,
		D3DSWAPEFFECT_DISCARD, hWnd, TRUE, TRUE, D3DFMT_D24S8, 0, 0, D3DPRESENT_INTERVAL_DEFAULT
	};

	//幾つかの設定でデバイス作成を試みる
	//HALモードで3Dデバイス作成
	if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DParam.hDeviceWindow,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D)))
	{
		if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DParam.hDeviceWindow,
			D3DCREATE_MIXED_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D)))
		{
			//Refモードで3Dデバイス作成
			if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, D3DParam.hDeviceWindow,
				D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D)))
			{
				if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, D3DParam.hDeviceWindow,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D)))
				{
					// 3Dデバイス作成失敗
					pD3D9->Release();
					return false;
				}
			}
		}
	}
	return true;
}