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

	//メンバ変数
	D3DXVECTOR3 pos[2];
	D3DXVECTOR3 rota[2];
	//D3DVIEWPORT9 viewPort[2];

	//コンストラクタ
	Camera();
	//コンストラクタ
	Camera(D3DXVECTOR3 pos, D3DXVECTOR3 rota);
	//デストラクタ
	~Camera();

	//生成共通処理
	void Create(D3DXVECTOR3 pos, D3DXVECTOR3 rota);
	void Create2(D3DXVECTOR3 pos, D3DXVECTOR3 rota);
	//撮影
	void View(D3DXVECTOR3 pos, D3DXVECTOR3 rota);
	void View2(D3DXVECTOR3 pos, D3DXVECTOR3 rota);
	//ビューポートの設定int x,int y,int width,int height,int num
	void SetViewPort();
	void SetViewPort2();
	//カメラの移動
	D3DXVECTOR3 CmeraMove();


	
protected:
	//メンバ変数
	static float aspect;
	static float aspect1;
};