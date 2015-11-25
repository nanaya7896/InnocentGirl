#include"Camera.h"

float Camera::aspect;
float Camera::aspect1;

struct MY_VIEW
{
	D3DXVECTOR3 vEyePt;
	D3DXVECTOR3 vLookatPt;
	D3DXVECTOR3 vUpVec;
	D3DXMATRIX matView;
};
D3DVIEWPORT9 g_port[] = {
	{ 0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT, 0.0f, 1.0f },
	{ WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT, 0.0f, 1.0f }
};

MY_VIEW g_view[] = {
	{ D3DXVECTOR3(0.0f, 1.0f, 30.0f), D3DXVECTOR3(0.0f , 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f) },
	{ D3DXVECTOR3(0.0f, 1.0f, -30.0f), D3DXVECTOR3(0.0f - (D3DX_PI / 2.0f), 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f) }
};

//�R���X�g���N�^
Camera::Camera()
{
	Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
}

// �R���X�g���N�^
Camera::Camera(D3DXVECTOR3 pos, D3DXVECTOR3 rota)
{
	Create(pos, rota);
}

//�f�X�g���N�^
Camera::~Camera()
{

}

//�������ʏ���
void Camera::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rota)
{

	SetViewPort(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
	
	Camera::pos = pos;
	Camera::rota = rota;



		//�ˉe�s��̏�����
		D3DXMatrixIdentity(&m_projection);

		//�ˉe�s��̍쐬

		D3DXMatrixPerspectiveFovLH(&m_projection, D3DXToRadian(45.0f), aspect, 1.0f, 100000.0f);
		//�ˉe�s����p�C�v���C���ɐݒ�
		pDevice3D->SetTransform(D3DTS_PROJECTION, &m_projection);
		
	View(pos,rota);

}

void Camera::View(D3DXVECTOR3 pos, D3DXVECTOR3 rota)
{
	D3DXMATRIX *m_temp =  new D3DXMATRIX ;
	D3DXMatrixIdentity(&m_view[0]);

		D3DXMatrixIdentity(m_temp);

		//�s�����]����
		D3DXMatrixRotationYawPitchRoll(m_temp, rota.y, rota.x, rota.z);
		m_view[0] *= *m_temp;

		//�s��𕽍s�ړ�������
		D3DXMatrixTranslation(m_temp, pos.x, pos.y, pos.z);
		m_view [0]*= *m_temp;

		D3DXMatrixIdentity(m_temp);
		//�J�����̋t�s������߂�
		D3DXMatrixInverse(m_temp, nullptr, &m_view[0]);

		//�r���[�s���ݒ�
		pDevice3D->SetTransform(D3DTS_VIEW, m_temp);

		
	
		delete m_temp;	
}


//�r���[�|�[�g�̐ݒ�(�J�����̕���)int x, int y, int width, int height,int num
void Camera::SetViewPort(int x, int y, int width, int height)
{
	D3DVIEWPORT9 viewPort;
	
	viewPort.X = x;
	viewPort.Y = y;
	viewPort.Width = width;
	viewPort.Height = height;
	viewPort.MinZ = 0.0f;
	viewPort.MaxZ = 1.0f;
	
	

	//����
	pDevice3D->SetViewport(&viewPort);
	//pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xcc00cc, 1.0f, 0);
	//�`��




	aspect = (float)g_port[0].Width / (float)g_port[0].Height;
}

void Camera::View1P(D3DXVECTOR3 pos, D3DXVECTOR3 rota)
{
	D3DXMATRIX *m_temp1 = new D3DXMATRIX;
	D3DXMatrixIdentity(&g_view[0].matView);

	D3DXMatrixIdentity(m_temp1);




	//�s�����]����
	D3DXMatrixRotationYawPitchRoll(m_temp1, rota.y, rota.x, rota.z);
	g_view[0].matView *= *m_temp1;

	//�s��𕽍s�ړ�������
	D3DXMatrixTranslation(m_temp1, pos.x, pos.y, pos.z);
	g_view[0].matView *= *m_temp1;

	D3DXMatrixIdentity(m_temp1);
	//�J�����̋t�s������߂�
	D3DXMatrixInverse(m_temp1, nullptr, &g_view[0].matView);

	//�r���[�s���ݒ�
	pDevice3D->SetTransform(D3DTS_VIEW,m_temp1);



	delete m_temp1;
}


void Camera::View2P(D3DXVECTOR3 pos, D3DXVECTOR3 rota)
{
	D3DXMATRIX *m_temp2 = new D3DXMATRIX;
	D3DXMatrixIdentity(&g_view[1].matView);

	D3DXMatrixIdentity(m_temp2);

	//�s�����]����
	D3DXMatrixRotationYawPitchRoll(m_temp2, rota.y, rota.x, rota.z);
	g_view[1].matView *= *m_temp2;

	//�s��𕽍s�ړ�������
	D3DXMatrixTranslation(m_temp2, pos.x, pos.y, pos.z);
	g_view[1].matView *= *m_temp2;

	D3DXMatrixIdentity(m_temp2);
	//�J�����̋t�s������߂�
	D3DXMatrixInverse(m_temp2, nullptr, &g_view[1].matView);

	//�r���[�s���ݒ�
	pDevice3D->SetTransform(D3DTS_VIEW, m_temp2);



	delete m_temp2;
}


HRESULT Camera::Camera2P()
{


	//pDevice3D->SetRenderState(D3DRS_LIGHTING, FALSE);
	//pDevice3D->SetRenderState(D3DRS_DITHERENABLE, TRUE);
	//pDevice3D->SetRenderState(D3DRS_ZENABLE, TRUE);
	//pDevice3D->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//pDevice3D->SetRenderState(D3DRS_AMBIENT, 0x33333333);
	//pDevice3D->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	//pDevice3D->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice3D->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//pDevice3D->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//pDevice3D->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//pDevice3D->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//�r���[�s��̍쐬

	//for (int i = 0, count = sizeof(g_view) / sizeof(g_view[0]); i < count; i++)
	//{
		D3DXMatrixLookAtLH(&g_view[0].matView, &g_view[0].vEyePt, &g_view[0].vLookatPt, &g_view[0].vUpVec);
		pDevice3D->SetTransform(D3DTS_VIEW, &g_view[0].matView);
		D3DXMatrixLookAtLH(&g_view[1].matView, &g_view[1].vEyePt, &g_view[1].vLookatPt, &g_view[1].vUpVec);
		pDevice3D->SetTransform(D3DTS_VIEW, &g_view[1].matView);
	//}
	

	//�ˉe�s��̍쐬
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(45.0f), (float)1600 / 900, 1.0f, 10000.0f);
	pDevice3D->SetTransform(D3DTS_PROJECTION, &matProj);

	return S_OK;
}

void Camera::Camera1PUpdate()
{
	//�`��̈��ύX�i�r���[�|�[�g�s��j
	pDevice3D->SetViewport(&g_port[0]);
	//�J�����̍��W��ύX�i�r���[�s��j
//	pDevice3D->SetTransform(D3DTS_VIEW, &g_view[0].matView);
	//�`��̈�ɂ�������C�ӂ̐F�ŃN���A
	pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DXCOLOR(10.0f,255,255,255), 1.0f, 0);
}

void Camera::Camera2PUpdate()
{
	//�`��̈��ύX�i�r���[�|�[�g�s��j
	pDevice3D->SetViewport(&g_port[1]);
	//�J�����̍��W��ύX�i�r���[�s��j
//pDevice3D->SetTransform(D3DTS_VIEW, &g_view[1].matView);
	//�`��̈�ɂ�������C�ӂ̐F�ŃN���A
	pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DXCOLOR(10.0f,255,255,255), 1.0f, 0);
}