#include"Map.h"

//コンストラクタ
Map::Map()
{

}
//
Map::~Map()
{

}


HRESULT Map::LoadBuldings()
{
	Building buildings[MAXBUILDING] = {
		{ xfloor1.XfileLoader(L"xfile/floor1.x"), tfloor1.Load(_T("texture/floor1.bmp")) },
		{ xfloor2.XfileLoader(L"xfile/floor2.x"), tfloor2.Load(_T("texture/floor2.bmp")) },
		{ xfloor3.XfileLoader(L"xfile/floor3.x"), tfloor3.Load(_T("texture/floor3.bmp")) },
		{ xfloor4.XfileLoader(L"xfile/floor4.x"), tfloor4.Load(_T("texture/floor4.bmp")) },
		{ xroof1.XfileLoader(L"xfile/roof1.x"), troof1.Load(_T("roof1.bmp")) },
		{ xroof2.XfileLoader(L"xfile/roof2.x"), troof2.Load(_T("roof2.bmp")) },
		{ xroof3.XfileLoader(L"xfile/roof3.x"), troof3.Load(_T("roof3.bmp")) },
		{ xroof4.XfileLoader(L"xfile/roof4.x"), troof4.Load(_T("roof4.bmp")) },
		{ xpaneln1.XfileLoader(L"xfile/paneln1.x"), tpanel1.Load(_T("texture/panel1.bmp")) },
		{ xpaneln2.XfileLoader(L"xfile/paneln2.x"), tpanel1.Load(_T("texture/panel1.bmp")) },
		{ xpanels1.XfileLoader(L"xfile/panels1.x"), tpanel2.Load(_T("texture/panel2.bmp")) },
		{ xpanels2.XfileLoader(L"xfile/panels2.x"), tpanel2.Load(_T("texture/panel2.bmp")) },
		{ xpanelw1.XfileLoader(L"xfile/panelw1.x"), tpanel3.Load(_T("texture/panel3.bmp")) },
		{ xpanelw2.XfileLoader(L"xfile/panelw2.x"), tpanel3.Load(_T("texture/panel3.bmp")) },
		{ xpanele1.XfileLoader(L"xfile/panele1.x"), tpanel4.Load(_T("texture/panel4.bmp")) },
		{ xpanele2.XfileLoader(L"xfile/panele2.x"), tpanel4.Load(_T("texture/panel4.bmp")) },
		{ xhouse.XfileLoader(L"xfile/house.x"), thouse.Load(_T("texture/house.bmp")) },
		{ xleaf.XfileLoader(L"xfile/leaf.x"), tleaf.Load(_T("texture/leaf.bmp")) },
		{ xtree.XfileLoader(L"xfile/tree.x"), ttree.Load(_T("texture/tree.bmp")) },
		{ xball.XfileLoader(L"xfile/ball.x"), tball.Load(_T("texture/ball.bmp")) },
	};


		
	return S_OK;
}

void Map::MapRender()
{
	xfloor1.Render(&D3DXVECTOR3(-6,0,6), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,1),tfloor1.GetTexture());
	xfloor2.Render(&D3DXVECTOR3(6, 0, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloor2.GetTexture());
	xfloor3.Render(&D3DXVECTOR3(-6, 0, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloor3.GetTexture());
	xfloor4.Render(&D3DXVECTOR3(6, 0, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloor4.GetTexture());

	xroof1.Render(&D3DXVECTOR3(-6, 12, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), troof1.GetTexture());
	xroof2.Render(&D3DXVECTOR3(6, 12, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), troof2.GetTexture());
	xroof3.Render(&D3DXVECTOR3(-6, 12, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), troof3.GetTexture());
	xroof4.Render(&D3DXVECTOR3(6, 12, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), troof4.GetTexture());

	xpaneln1.Render(&D3DXVECTOR3(6, 6, 12), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanel1.GetTexture());
	xpaneln2.Render(&D3DXVECTOR3(-6, 6, 12), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanel1.GetTexture());
	xpanels1.Render(&D3DXVECTOR3(-6, 6, -12), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanel2.GetTexture());
	xpanels2.Render(&D3DXVECTOR3(6, 6, -12), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanel2.GetTexture());
	xpanelw1.Render(&D3DXVECTOR3(-12, 6, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanel3.GetTexture());
	xpanelw2.Render(&D3DXVECTOR3(-12, 6, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanel3.GetTexture());
	xpanele1.Render(&D3DXVECTOR3(12, 6, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanel4.GetTexture());
	xpanele2.Render(&D3DXVECTOR3(12, 6, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanel4.GetTexture());

	xhouse.Render(&D3DXVECTOR3(4, 2, 4), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), thouse.GetTexture());
	xtree.Render(&D3DXVECTOR3(4, 0.8f, -1), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), ttree.GetTexture());
	xleaf.Render(&D3DXVECTOR3(-4, 3, -4), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tleaf.GetTexture());
	xball.Render(&D3DXVECTOR3(-4, 8, -4), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tball.GetTexture());


}