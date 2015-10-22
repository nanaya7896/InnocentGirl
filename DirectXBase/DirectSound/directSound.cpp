#include "directSound.h"


//�R���X�g���N�^
DirectSound::DirectSound()
{
	pDirectSound8 = NULL;

}
//�f�X�g���N�^
DirectSound::~DirectSound()
{
	if (pDirectSound8 != NULL)
	{
		pDirectSound8->Release();
	}
}

//�T�E���h�f�o�C�X�̍쐬
bool DirectSound::Create(HWND hWnd)
{
	//�f�o�C�X�쐬
	DirectSoundCreate8(NULL, &pDirectSound8, NULL);

	//�������x���̃Z�b�g�i�����ŉ���炷�E�B���h�E���w�肷��K�v������j
	if (FAILED(pDirectSound8->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
	{
		//���s
		return false;
	}

	return true;
}
