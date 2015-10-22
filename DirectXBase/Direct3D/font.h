#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define  _CRT_NON_CONFORMING_SWPRINTFS
#include"direct3d.h"

/////////////////////
//テキスト描画クラス
class DirectXText
{
private:
	ID3DXFont*			pFont;//Direct3DFont
	RECT				Rect;//描画領域
	std::vector<TCHAR>	Buf;//文字列バッファ
public:
	//コンストラクタ
	DirectXText();
	//デストラクタ
	virtual ~DirectXText();

	//DirectXFont作成
	bool Create(IDirect3DDevice9* pD3DDevice, int FontHeight = 16);

	//文字列の描画
	void Draw(DWORD Color, int x, int y, const TCHAR* Str, ...);



};


