#pragma once

#include "directSound.h"

class Wave
{

public:
	WAVEFORMATEX WaveFormat;
	byte*		 WaveData;
	int			 DataSize;

	//�R���X�g���N�^�@�f�X�g���N�^
	Wave();
	~Wave();

	//Wav�t�@�C���ǂݍ���
	bool Load(TCHAR* FileName);


};