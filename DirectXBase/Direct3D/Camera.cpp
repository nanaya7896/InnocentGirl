#include"Camera.h"

float Camera::aspect;
float Camera::aspect1;
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

	SetViewPort();
	
	Camera::pos[0] = pos;
	Camera::rota[0] = rota;



		//射影行列の初期化
		D3DXMatrixIdentity(&m_projection);

		//射影行列の作成

		D3DXMatrixPerspectiveFovLH(&m_projection, D3DXToRadian(45.0f), aspect, 1.0f, 100000.0f);
	//	D3DXMatrixPerspectiveFovLH(&m_projection, D3DXToRadian(45.0f), aspect1, 1.0f, 100000.0f);
		//射影行列をパイプラインに設定
		pDevice3D->SetTransform(D3DTS_PROJECTION, &m_projection);
	
	
	View(pos,rota);

	//Create2(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
}


void Camera::Create2(D3DXVECTOR3 pos, D3DXVECTOR3 rota)
{

	SetViewPort2();

	Camera::pos[1] = pos;
	Camera::rota[1] = rota;



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
void Camera::SetViewPort()
{
	
	//viewPort[num].X = x;
	//viewPort[num].Y = y;
	//viewPort[num].Width = width;
	//viewPort[num].Height = height;
	//viewPort[num].MinZ = 0.0f;
	//viewPort[num].MaxZ = 1.0f;
	
	

	//const D3DVIEWPORT9 viewData2 = { WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT, 0.0f, 1.0f };

	//左上
	pDevice3D->SetViewport(&viewData1);
	pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xcc00cc, 1.0f, 0);
	//描画

		//右上
	pDevice3D->SetViewport(&viewData2);
		pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00cccc, 1.0f, 0);
	//描画
	/*pDevice3D->SetViewport(&viewPort[num]);
	pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x0000cc, 1.0f, 0);*/


	aspect = (float)viewData1.Width / (float)viewData1.Height;
//	aspect1 = (float)viewData2.Width / (float)viewData2.Height;
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
	pDevice3D->SetViewport(&viewData2);
	pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00cccc, 1.0f, 0);
	//描画
	/*pDevice3D->SetViewport(&viewPort[num]);
	pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x0000cc, 1.0f, 0);*/


	//aspect = (float)viewData1.Width / (float)viewData1.Height;
	aspect1 = (float)viewData2.Width / (float)viewData2.Height;
}



