#pragma once

#include"../Global.h"


//DirectSoundクラス

class DirectSound
{
public:
	IDirectSound8 * pDirectSound8;//directsoundデバイス(サウンドを鳴らすためのデバイス)

	DirectSound();
	~DirectSound();

	bool Create(HWND hWnd);

};
