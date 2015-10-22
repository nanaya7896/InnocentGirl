#pragma once

#include "directSound.h"

class Wave
{

public:
	WAVEFORMATEX WaveFormat;
	byte*		 WaveData;
	int			 DataSize;

	//コンストラクタ　デストラクタ
	Wave();
	~Wave();

	//Wavファイル読み込み
	bool Load(TCHAR* FileName);


};