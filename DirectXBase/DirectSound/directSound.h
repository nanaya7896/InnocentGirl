#pragma once

#include"../Global.h"


//DirectSound�N���X

class DirectSound
{
public:
	IDirectSound8 * pDirectSound8;//directsound�f�o�C�X(�T�E���h��炷���߂̃f�o�C�X)

	DirectSound();
	~DirectSound();

	bool Create(HWND hWnd);

};
