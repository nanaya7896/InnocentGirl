#include"../Global.h"
#include"direct3d.h"
class Camera: public Direct3D
{
private:
	//�����o�ϐ�
	float aspect;
	D3DXMATRIX m_view;
	D3DXMATRIX m_projection;

public:

	//�����o�ϐ�
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rota;

	//�R���X�g���N�^
	Camera();
	//�R���X�g���N�^
	Camera(D3DXVECTOR3 pos,D3DXVECTOR3 rota);
	//�f�X�g���N�^
	~Camera();

	//�������ʏ���
	void Create(D3DXVECTOR3 pos, D3DXVECTOR3 rota);

	//�B�e
	void View();

	//�r���[�|�[�g�̐ݒ�
	void SetViewPort(int x,int y,int width,int height);
};