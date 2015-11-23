#include"../Global.h"
#include"direct3d.h"

const D3DVIEWPORT9 viewData1 = { 0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT, 0.0f, 1.0f };
const D3DVIEWPORT9 viewData2 = { WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT, 0.0f, 1.0f };
class Camera: public Direct3D
{
private:
	
	D3DXMATRIX m_view[2];
	D3DXMATRIX m_projection;

public:

	//�����o�ϐ�
	D3DXVECTOR3 pos[2];
	D3DXVECTOR3 rota[2];
	//D3DVIEWPORT9 viewPort[2];

	//�R���X�g���N�^
	Camera();
	//�R���X�g���N�^
	Camera(D3DXVECTOR3 pos, D3DXVECTOR3 rota);
	//�f�X�g���N�^
	~Camera();

	//�������ʏ���
	void Create(D3DXVECTOR3 pos, D3DXVECTOR3 rota);
	void Create2(D3DXVECTOR3 pos, D3DXVECTOR3 rota);
	//�B�e
	void View(D3DXVECTOR3 pos, D3DXVECTOR3 rota);
	void View2(D3DXVECTOR3 pos, D3DXVECTOR3 rota);
	//�r���[�|�[�g�̐ݒ�int x,int y,int width,int height,int num
	void SetViewPort();
	void SetViewPort2();
	//�J�����̈ړ�
	D3DXVECTOR3 CmeraMove();


	
protected:
	//�����o�ϐ�
	static float aspect;
	static float aspect1;
};