#define _CRT_SECURE_NO_WARNINGS

#include "wave.h"


//コンストラクタ
Wave::Wave()
{
	memset(&WaveFormat, 0, sizeof(WAVEFORMATEX));
	WaveData = NULL;
	DataSize = 0;
}

//デストラクタ
Wave::~Wave()
{
	if (WaveData != NULL)
	{
		delete[] WaveData;
	}
}


//Wavファイル読み込み
//Wavファイルデータフォーマット参照
bool Wave::Load(TCHAR* FileName)
{
	FILE* fp;

	//バイナリ型を開くための処理
	if (!(fp = _tfopen(FileName, _T("rb"))))
	{
		return false;
	}

	char chunkId[5] = {};
	char tmp[5] = {};
	unsigned int chunkSize = 0;

	//RIFFチャンク読み込み
	fread(chunkId, sizeof(char) * 4, 1, fp);
	fread(&chunkSize, sizeof(unsigned int), 1, fp);
	fread(tmp, sizeof(char) * 4, 1, fp);

	//strcmp　完全一致で0 不一致だと1 または-1（文字数に限らず文字の大小関係で帰ってくる）
	//ただし処理系によって結果は異なる
	//出力形式を読み込む
	if (strcmp(chunkId, "RIFF") || strcmp(tmp, "WAVE"))
	{
		return false;
		//WAVファイルじゃない
	}

	//子チャンク読み込み
	bool fmtchunk = false;
	bool datachunk = false;

	while (true)
	{
		fread(chunkId, sizeof(char) * 4, 1, fp);
		fread(&chunkSize, sizeof(unsigned int), 1, fp);

		if (!strcmp(chunkId, "fmt "))//スペースまで
		{
			if (chunkSize >= sizeof(WAVEFORMATEX))
			{
				fread(&WaveFormat, sizeof(WAVEFORMATEX), 1, fp);
				int diff = chunkSize - sizeof(WAVEFORMATEX);
				fseek(fp, diff, SEEK_CUR);
			}
			else
			{
				memset(&WaveFormat, 0, sizeof(WAVEFORMATEX));
				fread(&WaveFormat, chunkSize, 1, fp);

			}
			fmtchunk = true;

		}
		else if (!strcmp(chunkId, "data"))
		{
			//データサイズ確保
			DataSize = chunkSize;
			WaveData = new byte[chunkSize];
			//データ読み込み
			if (fread(WaveData, sizeof(byte), chunkSize, fp) != chunkSize)
			{
				fclose(fp);
				return false;
			}
			datachunk = true;
		}
		else
		{
			fseek(fp, chunkSize, SEEK_CUR);
		}

		if (fmtchunk && datachunk)
		{
			break;
		}
		//ファイルサイズチェックも行った方が良いかも

	}
	fclose(fp);

	return true;
}
