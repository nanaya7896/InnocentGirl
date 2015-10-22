#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define  _CRT_NON_CONFORMING_SWPRINTFS
#include"direct3d.h"

/////////////////////
//�e�L�X�g�`��N���X
class DirectXText
{
private:
	ID3DXFont*			pFont;//Direct3DFont
	RECT				Rect;//�`��̈�
	std::vector<TCHAR>	Buf;//������o�b�t�@
public:
	//�R���X�g���N�^
	DirectXText();
	//�f�X�g���N�^
	virtual ~DirectXText();

	//DirectXFont�쐬
	bool Create(IDirect3DDevice9* pD3DDevice, int FontHeight = 16);

	//������̕`��
	void Draw(DWORD Color, int x, int y, const TCHAR* Str, ...);



};


