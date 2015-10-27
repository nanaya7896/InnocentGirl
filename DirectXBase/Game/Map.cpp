#include"Map.h"

HRESULT Map::LoadBuldings()
{
		xfloor1.XfileLoader(_T("xfile/floor1.x"));
		tfloor1.Load(_T("xfile/floor1.bmp"));
		xfloor2.XfileLoader(_T("xfile/floor2.x"));
		tfloor2.Load(_T("xfile/floor2.bmp"));
		xfloor3.XfileLoader(_T("xfile/floor3.x"));
		tfloor3.Load(_T("xfile/floor3.bmp"));
		xfloor4.XfileLoader(_T("xfile/floor4.x"));
		tfloor4.Load(_T("xfile/floor4.bmp"));

	return S_OK;
}

void Map::MapRender()
{
	xfloor1.Render(&D3DXVECTOR3(-6,0,6), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(5,5,5),tfloor1.GetTexture());
	xfloor2.Render(&D3DXVECTOR3(6, 0, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(5, 5, 5), tfloor2.GetTexture());
	xfloor3.Render(&D3DXVECTOR3(-6, 0, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(5, 5, 5), tfloor3.GetTexture());
	xfloor4.Render(&D3DXVECTOR3(6, 0, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(5, 5, 5), tfloor4.GetTexture());

}