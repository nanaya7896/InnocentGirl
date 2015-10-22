#pragma once

#include "directSound.h"

class SoundBuffer
{
public:
	IDirectSoundBuffer8* pSecondaryBuffer;//�Z�J���_���o�b�t�@
	//�R���X�g���N�^
	SoundBuffer();
	~SoundBuffer();

	bool Create(IDirectSound8* pDirectSound8, WAVEFORMATEX& WaveFormat, byte* WaveData, int DataSize);

	void Play(bool isLoop);
	void Stop();

};