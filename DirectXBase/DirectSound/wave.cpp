#define _CRT_SECURE_NO_WARNINGS

#include "wave.h"


//�R���X�g���N�^
Wave::Wave()
{
	memset(&WaveFormat, 0, sizeof(WAVEFORMATEX));
	WaveData = NULL;
	DataSize = 0;
}

//�f�X�g���N�^
Wave::~Wave()
{
	if (WaveData != NULL)
	{
		delete[] WaveData;
	}
}


//Wav�t�@�C���ǂݍ���
//Wav�t�@�C���f�[�^�t�H�[�}�b�g�Q��
bool Wave::Load(TCHAR* FileName)
{
	FILE* fp;

	//�o�C�i���^���J�����߂̏���
	if (!(fp = _tfopen(FileName, _T("rb"))))
	{
		return false;
	}

	char chunkId[5] = {};
	char tmp[5] = {};
	unsigned int chunkSize = 0;

	//RIFF�`�����N�ǂݍ���
	fread(chunkId, sizeof(char) * 4, 1, fp);
	fread(&chunkSize, sizeof(unsigned int), 1, fp);
	fread(tmp, sizeof(char) * 4, 1, fp);

	//strcmp�@���S��v��0 �s��v����1 �܂���-1�i�������Ɍ��炸�����̑召�֌W�ŋA���Ă���j
	//�����������n�ɂ���Č��ʂ͈قȂ�
	//�o�͌`����ǂݍ���
	if (strcmp(chunkId, "RIFF") || strcmp(tmp, "WAVE"))
	{
		return false;
		//WAV�t�@�C������Ȃ�
	}

	//�q�`�����N�ǂݍ���
	bool fmtchunk = false;
	bool datachunk = false;

	while (true)
	{
		fread(chunkId, sizeof(char) * 4, 1, fp);
		fread(&chunkSize, sizeof(unsigned int), 1, fp);

		if (!strcmp(chunkId, "fmt "))//�X�y�[�X�܂�
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
			//�f�[�^�T�C�Y�m��
			DataSize = chunkSize;
			WaveData = new byte[chunkSize];
			//�f�[�^�ǂݍ���
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
		//�t�@�C���T�C�Y�`�F�b�N���s���������ǂ�����

	}
	fclose(fp);

	return true;
}
