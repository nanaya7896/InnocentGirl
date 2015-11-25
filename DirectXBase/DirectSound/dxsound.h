#pragma once

#include <dsound.h>
#include "../Global.h"

#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "dsound.lib" )



class CSound//:public 
{
private:
	static IDirectSound8 *pDS8;

	HWND		  hWnd;

	bool openWave(TCHAR *filepath, WAVEFORMATEX &waveFormatEx, char** ppData, DWORD &dataSize);



protected:
	IDirectSoundBuffer8 *pDSBuffer;
	DSBUFFERDESC DSBufferDesc;
	IDirectSoundBuffer *ptmpBuf;

public:
	CSound();
	CSound(HWND hwnd);
	~CSound();
	//コンストラクタ
	HRESULT Init();
	//初期化

	bool Load(TCHAR *filepath);
	void Play(bool);
	void pause();
	void Stop();
	void ReleaseDevice();
};

