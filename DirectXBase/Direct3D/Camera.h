#pragma once

#include"../Global.h"
#include"direct3d.h"




class Camera: public Direct3D
{
private:
	
	D3DXMATRIX m_view[2];
	D3DXMATRIX m_projection;

public:

	//メンバ変数
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rota;
	//D3DVIEWPORT9 viewPort[2];



	//コンストラクタ
	Camera();
	//コンストラクタ
	Camera(D3DXVECTOR3 pos, D3DXVECTOR3 rota);
	//デストラクタ
	~Camera();

	//生成共通処理
	void Create(D3DXVECTOR3 pos, D3DXVECTOR3 rota);
	//撮影
	void View(D3DXVECTOR3 pos, D3DXVECTOR3 rota);
	//２P対戦用
	void View1P(D3DXVECTOR3 pos, D3DXVECTOR3 rota);
	void View2P(D3DXVECTOR3 pos, D3DXVECTOR3 rota);
	//ビューポートの設定int x,int y,int width,int height,int num
	void SetViewPort(int x, int y, int width, int height);
	//カメラの移動
	D3DXVECTOR3 CmeraMove();

	//2人対戦用カメラの関数
	HRESULT Camera2P();
	void Camera1PUpdate();
	void Camera2PUpdate();
	
	
protected:
	//メンバ変数
	static float aspect;
	static float aspect1;
};