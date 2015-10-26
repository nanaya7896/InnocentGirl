#include"Camera.h"


//コンストラクタ
Camera::Camera()
{
	Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
}

// コンストラクタ
Camera::Camera(D3DXVECTOR3 pos, D3DXVECTOR3 rota)
{
	Create(pos, rota);
}

//デストラクタ
Camera::~Camera()
{

}

//生成共通処理
void Camera::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rota)
{
	SetViewPort(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	Camera::pos = pos;
	Camera::rota = rota;

	//射影行列の初期化
	D3DXMatrixIdentity(&m_projection);

	//射影行列の作成
	D3DXMatrixPerspectiveFovLH(&m_projection, D3DXToRadian(45.0f), aspect, 1.0f, 100000.0f);

	//射影行列をパイプラインに設定
	pDevice3D->SetTransform(D3DTS_PROJECTION,&m_projection);
	//環境光
	//pDevice3D->SetRenderState(D3DRS_AMBIENT, 0xff030303);
	
	View();

	
}

void Camera::View()
{
	D3DXMATRIX *m_temp = new D3DXMATRIX;
	D3DXMatrixIdentity(&m_view);
	D3DXMatrixIdentity(m_temp);

	//行列を回転する
	D3DXMatrixRotationYawPitchRoll(m_temp, rota.y, rota.x, rota.z);
	m_view *= *m_temp;

	//行列を平行移動させる
	D3DXMatrixTranslation(m_temp,pos.x,pos.y,pos.z);
	m_view *= *m_temp;

	D3DXMatrixIdentity(m_temp);
	//カメラの逆行列を求める
	D3DXMatrixInverse(m_temp, nullptr, &m_view);

	//ビュー行列を設定
	pDevice3D->SetTransform(D3DTS_VIEW,m_temp);

	delete m_temp;


	
}

//ビューポートの設定(2人視点)
void Camera::SetViewPort(int x, int y, int width, int height)
{
	D3DVIEWPORT9 viewPort;
	viewPort.X = x;
	viewPort.Y = y;
	viewPort.Width = width;
	viewPort.Height = height;
	viewPort.MinZ = 0.0f;
	viewPort.MaxZ = 1.0f;

	pDevice3D->SetViewport(&viewPort);

	aspect = (float)viewPort.Width / (float)viewPort.Height;

}



