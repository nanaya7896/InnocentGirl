#include "soundbuffer.h"

//�R���X�g���N�^
SoundBuffer::SoundBuffer()
{
	pSecondaryBuffer = NULL;
}

//�f�X�g���N�^
SoundBuffer::~SoundBuffer()
{
	Stop();//�Z�J���_���o�b�t�@�͔j������O�ɍĐ���~����
	if (pSecondaryBuffer != NULL)
	{
		pSecondaryBuffer->Release();
	}
}
//�Đ��J�n
void SoundBuffer::Play(bool isLoop)
{
	if (pSecondaryBuffer != NULL)
	{
		DWORD LoopFlag = (isLoop ? DSBPLAY_LOOPING : 0);
		pSecondaryBuffer->Play(0, 0, LoopFlag);
	}
}

//�Đ���~
void SoundBuffer::Stop()
{
	if (pSecondaryBuffer != NULL)
	{
		pSecondaryBuffer->Stop();
	}
}

//�o�b�t�@�쐬
bool SoundBuffer::Create(IDirectSound8* pDirectSound8, WAVEFORMATEX& WaveFormat, byte* WaveData, int DataSize)
{
	DSBUFFERDESC desc = {};	//�Z�J���_���o�b�t�@�쐬�p�ݒ�

	//�`�����l�����ł̕���@���m������1�`�����l���@�X�e���I��2�`�����l��

	if (WaveFormat.nChannels == 1)
	{
		//���m����
		desc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY |
			DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_STATIC;
		desc.guid3DAlgorithm = DS3DALG_NO_VIRTUALIZATION;
	}
	else
	{
		//�X�e���I
		desc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY |
			DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_CTRLPAN | DSBCAPS_STATIC;
		// |DSBCAPS_CTRFX; �G�t�F�N�g��ǉ������Duplicate�ł��Ȃ�
		desc.guid3DAlgorithm = GUID_NULL;
	}

	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.dwBufferBytes = DataSize;	//���f�[�^�T�C�Y�w��
	desc.lpwfxFormat = &WaveFormat;	//�t�H�[�}�b�g�w��

	IDirectSoundBuffer* pPrimaryBuffer = NULL;//�v���C�}���o�b�t�@

	//�v���C�}���o�b�t�@�쐬
	if (FAILED(pDirectSound8->CreateSoundBuffer(&desc, &pPrimaryBuffer, NULL)))
	{
		//�n���ꂽwave�f�[�^�ɖ�肪����
		//����������Ă��Ȃ���
		//���[�h���s
		//�̉\��

		return false;
	}
	//�v���C�}���o�b�t�@����Z�J���_���o�b�t�@�쐬
	pPrimaryBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&pSecondaryBuffer);
	pPrimaryBuffer->Release();//�Z�J���_���o�b�t�@���쐬�ł���΃v���C�}���o�b�t�@�͔j�����č\��Ȃ�

	unsigned char * block1 = NULL;
	unsigned char * block2 = NULL;
	unsigned long blockSize1 = 0;
	unsigned long blockSize2 = 0;

	//�Z�J���_���o�b�t�@�����b�N���ăf�[�^��������
	pSecondaryBuffer->Lock(0, DataSize, (void**)&block1, &blockSize1, (void**)&block2, &blockSize2, DSBLOCK_ENTIREBUFFER);
	//�Z�J���_���o�b�t�@�ɉ��f�[�^���R�s�[
	memcpy(block1, WaveData, DataSize);
	//�Z�J���_���o�b�t�@�̃��b�N������
	pSecondaryBuffer->Unlock(block1, blockSize1, block2, 0);

	return true;
}
