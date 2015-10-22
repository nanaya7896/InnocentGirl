#pragma once

#include "directSound.h"

class SoundBuffer
{
public:
	IDirectSoundBuffer8* pSecondaryBuffer;//セカンダリバッファ
	//コンストラクタ
	SoundBuffer();
	~SoundBuffer();

	bool Create(IDirectSound8* pDirectSound8, WAVEFORMATEX& WaveFormat, byte* WaveData, int DataSize);

	void Play(bool isLoop);
	void Stop();

};