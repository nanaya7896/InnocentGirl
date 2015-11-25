#include "dxsound.h"

IDirectSound8* CSound::pDS8;


CSound::CSound(){
	Init();
}
CSound::CSound(HWND hwnd){
	int a = 0;

	hWnd = hwnd;

	Init();

}

HRESULT CSound::Init(){

	if (pDS8 == NULL){
		HRESULT hresult = DirectSoundCreate8(NULL, &pDS8, NULL);
		if (FAILED(hresult)){
			MessageBox(hWnd, _T("sound�Ńf�o�C�X�̍쐬�Ɏ��s���܂���"), _T("Err"), MB_ICONSTOP);
			return FALSE;
		}

		hresult = pDS8->SetCooperativeLevel(hWnd, DSSCL_NORMAL);
		if (FAILED(hresult)){
			MessageBox(hWnd, _T("�������x���̐ݒ�Ɏ��s���܂���"), _T("Err"), MB_ICONSTOP);
			return FALSE;
		}
	}
	return S_OK;
}

bool CSound::openWave(TCHAR *filepath, WAVEFORMATEX &waveFormatEx, char** ppData, DWORD &dataSize) {
	if (filepath == 0)
		return false;

	HMMIO hMmio = NULL;
	MMIOINFO mmioInfo;

	// Wave�t�@�C���I�[�v��
	memset(&mmioInfo, 0, sizeof(MMIOINFO));
	hMmio = mmioOpen(filepath, &mmioInfo, MMIO_READ);
	if (!hMmio)
		return false; // �t�@�C���I�[�v�����s

	// RIFF�`�����N����
	MMRESULT mmRes;
	MMCKINFO riffChunk;
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);
	if (mmRes != MMSYSERR_NOERROR) {
		mmioClose(hMmio, 0);
		return false;
	}

	// �t�H�[�}�b�g�`�����N����
	MMCKINFO formatChunk;
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);
	if (mmRes != MMSYSERR_NOERROR) {
		mmioClose(hMmio, 0);
		return false;
	}
	DWORD fmsize = formatChunk.cksize;
	DWORD size = mmioRead(hMmio, (HPSTR)&waveFormatEx, fmsize);
	if (size != fmsize) {
		mmioClose(hMmio, 0);
		return false;
	}

	mmioAscend(hMmio, &formatChunk, 0);

	// �f�[�^�`�����N����
	MMCKINFO dataChunk;
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);
	if (mmRes != MMSYSERR_NOERROR) {
		mmioClose(hMmio, 0);
		return false;
	}
	*ppData = new char[dataChunk.cksize];
	size = mmioRead(hMmio, (HPSTR)*ppData, dataChunk.cksize);
	if (size != dataChunk.cksize) {
		delete[] * ppData;
		return false;
	}
	dataSize = size;

	// �n���h���N���[�Y
	mmioClose(hMmio, 0);

	return true;
}


bool CSound::Load(TCHAR *filepath){
	// Wave�t�@�C���I�[�v��
	WAVEFORMATEX wFmt;
	char *pWaveData = 0;
	DWORD waveSize = 0;
	if (!openWave(filepath, wFmt, &pWaveData, waveSize)){
		MessageBox(hWnd, _T("music file Opne�Ɏ��s���܂���"), _T("Err"), MB_ICONSTOP);
		return false;
	}




	DSBufferDesc.dwSize = sizeof(DSBUFFERDESC);
	DSBufferDesc.dwFlags = DSBCAPS_GLOBALFOCUS; // �O���[�o���t�H�[�J�X
	DSBufferDesc.dwBufferBytes = waveSize;
	DSBufferDesc.dwReserved = 0;
	DSBufferDesc.lpwfxFormat = &wFmt;
	DSBufferDesc.guid3DAlgorithm = GUID_NULL;

	ptmpBuf = 0;
	pDS8->CreateSoundBuffer(&DSBufferDesc, &ptmpBuf, NULL);
	ptmpBuf->QueryInterface(IID_IDirectSoundBuffer8, (void**)&pDSBuffer);
	ptmpBuf->Release();

	if (pDSBuffer == 0) {
		pDS8->Release();
		MessageBox(hWnd, _T("�T�E���h�f�o�C�X�ݒ�Ɏ��s���܂���"), _T("Err"), MB_ICONSTOP);
	}

	// �Z�J���_���o�b�t�@��Wave�f�[�^��������
	LPVOID lpvWrite = 0;
	DWORD dwLength = 0;
	if (DS_OK == pDSBuffer->Lock(0, 0, &lpvWrite, &dwLength, NULL, NULL, DSBLOCK_ENTIREBUFFER)) {
		memcpy(lpvWrite, pWaveData, dwLength);
		pDSBuffer->Unlock(lpvWrite, dwLength, NULL, 0);
	}
	delete[] pWaveData; // �����͂�������Ȃ�
	return true;
}


void CSound::Play(bool loop){
	pDSBuffer->Play(0, 0, loop ? DSBPLAY_LOOPING : 0);
}

void CSound::pause(){
	pDSBuffer->Stop();
}
void CSound::Stop(){
	pDSBuffer->Stop();
	pDSBuffer->SetCurrentPosition(0);
}



void CSound::ReleaseDevice(){
	if (pDS8){
		pDS8->Release();
		pDS8 = NULL;
	}
}

CSound::~CSound(){
	if (pDSBuffer)
	{
		pDSBuffer->Stop();
		pDSBuffer->SetCurrentPosition(0 /* byte��(�J�����g�|�W�V�����̐ݒ�) */);
		pDSBuffer->Release();
		pDSBuffer = NULL;

	}
}