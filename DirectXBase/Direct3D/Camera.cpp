#include"Camera.h"

float Camera::aspect;
float Camera::aspect1;
//�R���X�g���N�^
Camera::Camera()
{
	Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
}

// �R���X�g���N�^
Camera::Camera(D3DXVECTOR3 pos, D3DXVECTOR3 rota)
{
	Create2(pos, rota);
}

//�f�X�g���N�^
Camera::~Camera()
{

}

//�������ʏ���
void Camera::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rota)
{

	SetViewPort();
	
	Camera::pos[0] = pos;
	Camera::rota[0] = rota;



		//�ˉe�s��̏�����
		D3DXMatrixIdentity(&m_projection);

		//�ˉe�s��̍쐬

		D3DXMatrixPerspectiveFovLH(&m_projection, D3DXToRadian(45.0f), aspect, 1.0f, 100000.0f);
	//	D3DXMatrixPerspectiveFovLH(&m_projection, D3DXToRadian(45.0f), aspect1, 1.0f, 100000.0f);
		//�ˉe�s����p�C�v���C���ɐݒ�
		pDevice3D->SetTransform(D3DTS_PROJECTION, &m_projection);
	
	
	View(pos,rota);

	//Create2(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
}


void Camera::Create2(D3DXVECTOR3 pos, D3DXVECTOR3 rota)
{

	SetViewPort2();

	Camera::pos[1] = pos;
	Camera::rota[1] = rota;



	//�ˉe�s��̏�����
	D3DXMatrixIdentity(&m_projection);

	//�ˉe�s��̍쐬

	D3DXMatrixPerspectiveFovLH(&m_projection, D3DXToRadian(45.0f), aspect1, 1.0f, 100000.0f);
	//D3DXMatrixPerspectiveFovLH(&m_projection, D3DXToRadian(45.0f), aspect1, 1.0f, 100000.0f);
	//�ˉe�s����p�C�v���C���ɐݒ�
	pDevice3D->SetTransform(D3DTS_PROJECTION, &m_projection);


	View2(pos, rota);
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


void Camera::View2(D3DXVECTOR3 pos, D3DXVECTOR3 rota)
{
	D3DXMATRIX *m_temp2 = new D3DXMATRIX;
	D3DXMatrixIdentity(&m_view[1]);

	D3DXMatrixIdentity(m_temp2);

	//�s�����]����
	D3DXMatrixRotationYawPitchRoll(m_temp2, rota.y, rota.x, rota.z);
	m_view[1] *= *m_temp2;

	//�s��𕽍s�ړ�������
	D3DXMatrixTranslation(m_temp2, pos.x, pos.y, pos.z);
	m_view[1] *= *m_temp2;

	D3DXMatrixIdentity(m_temp2);
	//�J�����̋t�s������߂�
	D3DXMatrixInverse(m_temp2, nullptr, &m_view[1]);

	//�r���[�s���ݒ�
	pDevice3D->SetTransform(D3DTS_VIEW, m_temp2);



	delete m_temp2;




}

//�r���[�|�[�g�̐ݒ�(�J�����̕���)int x, int y, int width, int height,int num
void Camera::SetViewPort()
{
	
	//viewPort[num].X = x;
	//viewPort[num].Y = y;
	//viewPort[num].Width = width;
	//viewPort[num].Height = height;
	//viewPort[num].MinZ = 0.0f;
	//viewPort[num].MaxZ = 1.0f;
	
	

	//const D3DVIEWPORT9 viewData2 = { WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT, 0.0f, 1.0f };

	//����
	pDevice3D->SetViewport(&viewData1);
	pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xcc00cc, 1.0f, 0);
	//�`��

		//�E��
	pDevice3D->SetViewport(&viewData2);
		pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00cccc, 1.0f, 0);
	//�`��
	/*pDevice3D->SetViewport(&viewPort[num]);
	pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x0000cc, 1.0f, 0);*/


	aspect = (float)viewData1.Width / (float)viewData1.Height;
//	aspect1 = (float)viewData2.Width / (float)viewData2.Height;
}


//�r���[�|�[�g�̐ݒ�(�J�����̕���)
void Camera::SetViewPort2()
{

	//viewPort[num].X = x;
	//viewPort[num].Y = y;
	//viewPort[num].Width = width;
	//viewPort[num].Height = height;
	//viewPort[num].MinZ = 0.0f;
	//viewPort[num].MaxZ = 1.0f;
	//D3DVIEWPORT9 viewData1 = { 0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT, 0.0f, 1.0f };
	

	//����
	//pDevice3D->SetViewport(&viewData1);
	//pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xcc00cc, 1.0f, 0);
	//�`��

	//�E��
	pDevice3D->SetViewport(&viewData2);
	pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00cccc, 1.0f, 0);
	//�`��
	/*pDevice3D->SetViewport(&viewPort[num]);
	pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x0000cc, 1.0f, 0);*/


	//aspect = (float)viewData1.Width / (float)viewData1.Height;
	aspect1 = (float)viewData2.Width / (float)viewData2.Height;
}



