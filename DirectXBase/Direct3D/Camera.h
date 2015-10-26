#include"../Global.h"
#include"direct3d.h"
class Camera: public Direct3D
{
private:
	//メンバ変数
	float aspect;
	D3DXMATRIX m_view;
	D3DXMATRIX m_projection;

public:

	//メンバ変数
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rota;

	//コンストラクタ
	Camera();
	//コンストラクタ
	Camera(D3DXVECTOR3 pos,D3DXVECTOR3 rota);
	//デストラクタ
	~Camera();

	//生成共通処理
	void Create(D3DXVECTOR3 pos, D3DXVECTOR3 rota);

	//撮影
	void View();

	//ビューポートの設定
	void SetViewPort(int x,int y,int width,int height);
};