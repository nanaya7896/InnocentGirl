#include "directSound.h"


//コンストラクタ
DirectSound::DirectSound()
{
	pDirectSound8 = NULL;

}
//デストラクタ
DirectSound::~DirectSound()
{
	if (pDirectSound8 != NULL)
	{
		pDirectSound8->Release();
	}
}

//サウンドデバイスの作成
bool DirectSound::Create(HWND hWnd)
{
	//デバイス作成
	DirectSoundCreate8(NULL, &pDirectSound8, NULL);

	//協調レベルのセット（ここで音を鳴らすウィンドウを指定する必要がある）
	if (FAILED(pDirectSound8->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
	{
		//失敗
		return false;
	}

	return true;
}
