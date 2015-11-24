#include"Camera.h"

float Camera::aspect;
float Camera::aspect1;

struct MY_VIEW
{
	D3DXVECTOR3 vEyePt;
	D3DXVECTOR3 vLookatPt;
	D3DXVECTOR3 vUpVec;
	D3DXMATRIXA16 matView;
};
D3DVIEWPORT9 g_port[] = {
	{ 0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT, 0.0f, 1.0f },
	{ WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT, 0.0f, 1.0f }
};

MY_VIEW g_view[] = {
	{ D3DXVECTOR3(0.0f, 1.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f) },
	{ D3DXVECTOR3(0.0f, 1.0f, -20.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f) }
};

//コンストラクタ
Camera::Camera()
{
	Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
}

// コンストラクタ
Camera::Camera(D3DXVECTOR3 pos, D3DXVECTOR3 rota)
{
	Create2(pos, rota);
}

//デストラクタ
Camera::~Camera()
{

}

//生成共通処理
void Camera::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rota)
{

	SetViewPort(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
	
	Camera::pos = pos;
	Camera::rota = rota;



		//射影行列の初期化
		D3DXMatrixIdentity(&m_projection);

		//射影行列の作成

		D3DXMatrixPerspectiveFovLH(&m_projection, D3DXToRadian(45.0f), aspect, 1.0f, 100000.0f);
		//射影行列をパイプラインに設定
		pDevice3D->SetTransform(D3DTS_PROJECTION, &m_projection);
		
	View(pos,rota);

}


void Camera::Create2(D3DXVECTOR3 pos, D3DXVECTOR3 rota)
{


	Camera::pos = pos;
	Camera::rota = rota;



	//射影行列の初期化
	D3DXMatrixIdentity(&m_projection);

	//射影行列の作成

	D3DXMatrixPerspectiveFovLH(&m_projection, D3DXToRadian(45.0f), aspect1, 1.0f, 100000.0f);
	//D3DXMatrixPerspectiveFovLH(&m_projection, D3DXToRadian(45.0f), aspect1, 1.0f, 100000.0f);
	//射影行列をパイプラインに設定
	pDevice3D->SetTransform(D3DTS_PROJECTION, &m_projection);


	View2(pos, rota);
}

void Camera::View(D3DXVECTOR3 pos, D3DXVECTOR3 rota)
{
	D3DXMATRIX *m_temp =  new D3DXMATRIX ;
	D3DXMatrixIdentity(&m_view[0]);

		D3DXMatrixIdentity(m_temp);

		//行列を回転する
		D3DXMatrixRotationYawPitchRoll(m_temp, rota.y, rota.x, rota.z);
		m_view[0] *= *m_temp;

		//行列を平行移動させる
		D3DXMatrixTranslation(m_temp, pos.x, pos.y, pos.z);
		m_view [0]*= *m_temp;

		D3DXMatrixIdentity(m_temp);
		//カメラの逆行列を求める
		D3DXMatrixInverse(m_temp, nullptr, &m_view[0]);

		//ビュー行列を設定
		pDevice3D->SetTransform(D3DTS_VIEW, m_temp);

		
	
		delete m_temp;	
}


void Camera::View2(D3DXVECTOR3 pos, D3DXVECTOR3 rota)
{
	D3DXMATRIX *m_temp2 = new D3DXMATRIX;
	D3DXMatrixIdentity(&m_view[1]);

	D3DXMatrixIdentity(m_temp2);

	//行列を回転する
	D3DXMatrixRotationYawPitchRoll(m_temp2, rota.y, rota.x, rota.z);
	m_view[1] *= *m_temp2;

	//行列を平行移動させる
	D3DXMatrixTranslation(m_temp2, pos.x, pos.y, pos.z);
	m_view[1] *= *m_temp2;

	D3DXMatrixIdentity(m_temp2);
	//カメラの逆行列を求める
	D3DXMatrixInverse(m_temp2, nullptr, &m_view[1]);

	//ビュー行列を設定
	pDevice3D->SetTransform(D3DTS_VIEW, m_temp2);



	delete m_temp2;




}

//ビューポートの設定(カメラの分割)int x, int y, int width, int height,int num
void Camera::SetViewPort(int x, int y, int width, int height)
{
	D3DVIEWPORT9 viewPort;
	
	viewPort.X = x;
	viewPort.Y = y;
	viewPort.Width = width;
	viewPort.Height = height;
	viewPort.MinZ = 0.0f;
	viewPort.MaxZ = 1.0f;
	
	

	//左上
	pDevice3D->SetViewport(&viewPort);
	//pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xcc00cc, 1.0f, 0);
	//描画




	aspect = (float)g_port[0].Width / (float)g_port[0].Height;
}


//ビューポートの設定(カメラの分割)
void Camera::SetViewPort2()
{

	//viewPort[num].X = x;
	//viewPort[num].Y = y;
	//viewPort[num].Width = width;
	//viewPort[num].Height = height;
	//viewPort[num].MinZ = 0.0f;
	//viewPort[num].MaxZ = 1.0f;
	//D3DVIEWPORT9 viewData1 = { 0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT, 0.0f, 1.0f };
	

	//左上
	//pDevice3D->SetViewport(&viewData1);
	//pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xcc00cc, 1.0f, 0);
	//描画

	//右上
	//pDevice3D->SetViewport(&viewData2);
	pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00cccc, 1.0f, 0);
	//描画
	/*pDevice3D->SetViewport(&viewPort[num]);
	pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x0000cc, 1.0f, 0);*/


	//aspect = (float)viewData1.Width / (float)viewData1.Height;
	//aspect1 = (float)viewData2.Width / (float)viewData2.Height;
}

HRESULT Camera::Camera2P()
{

	pDevice3D->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice3D->SetRenderState(D3DRS_DITHERENABLE, TRUE);
	pDevice3D->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice3D->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice3D->SetRenderState(D3DRS_AMBIENT, 0x33333333);
	pDevice3D->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	pDevice3D->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice3D->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice3D->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice3D->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pDevice3D->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//ビュー行列の作成
	for (int i = 0, count = sizeof(g_view) / sizeof(g_view[0]); i < count; i++)
	{
		D3DXMatrixLookAtLH(&g_view[i].matView, &g_view[i].vEyePt, &g_view[i].vLookatPt, &g_view[i].vUpVec);
	
	}
	pDevice3D->SetTransform(D3DTS_VIEW, &g_view[0].matView);

	//射影行列の作成
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(45.0f), (float)1600 / 900, 1.0f, 100.0f);
	pDevice3D->SetTransform(D3DTS_PROJECTION, &matProj);

	return S_OK;
}

void Camera::Camera2PUpdate()
{
	
	for (int i = 0, count = sizeof(g_port) / sizeof(g_port[0]); i < count; i++)
	{
		//描画領域を変更（ビューポート行列）
		pDevice3D->SetViewport(&g_port[i]);
		//カメラの座標を変更（ビュー行列）
		pDevice3D->SetTransform(D3DTS_VIEW, &g_view[i].matView);
		//描画領域にした所を任意の色でクリア
		//pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DXCOLOR(10.0f,255,255,255), 1.0f, 0);
	}



}