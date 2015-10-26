#include"Camera.h"


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
	SetViewPort(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	Camera::pos = pos;
	Camera::rota = rota;

	//�ˉe�s��̏�����
	D3DXMatrixIdentity(&m_projection);

	//�ˉe�s��̍쐬
	D3DXMatrixPerspectiveFovLH(&m_projection, D3DXToRadian(45.0f), aspect, 1.0f, 100000.0f);

	//�ˉe�s����p�C�v���C���ɐݒ�
	pDevice3D->SetTransform(D3DTS_PROJECTION,&m_projection);
	//����
	//pDevice3D->SetRenderState(D3DRS_AMBIENT, 0xff030303);
	
	View();

	
}

void Camera::View()
{
	D3DXMATRIX *m_temp = new D3DXMATRIX;
	D3DXMatrixIdentity(&m_view);
	D3DXMatrixIdentity(m_temp);

	//�s�����]����
	D3DXMatrixRotationYawPitchRoll(m_temp, rota.y, rota.x, rota.z);
	m_view *= *m_temp;

	//�s��𕽍s�ړ�������
	D3DXMatrixTranslation(m_temp,pos.x,pos.y,pos.z);
	m_view *= *m_temp;

	D3DXMatrixIdentity(m_temp);
	//�J�����̋t�s������߂�
	D3DXMatrixInverse(m_temp, nullptr, &m_view);

	//�r���[�s���ݒ�
	pDevice3D->SetTransform(D3DTS_VIEW,m_temp);

	delete m_temp;


	
}

//�r���[�|�[�g�̐ݒ�(2�l���_)
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



