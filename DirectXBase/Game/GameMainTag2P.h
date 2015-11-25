#pragma once

#include"../Global.h"
#include"../Direct3D/Camera.h"
#include"SceneChange.h"
#include"../Game/Map.h"
#include"../Enemy/Enemy.h"
#include"../Player/Player.h"
#include"Result.h"
#include "../Direct3D/texture.h"
#include "../Direct3D/sprite.h"


struct pCameraInfo1P{
	D3DXVECTOR3 CameraPos1P;
	D3DXVECTOR3 CameraAngle1P;
};

struct pCameraInfo2P{
	D3DXVECTOR3 CameraPos2P;
	D3DXVECTOR3 CameraAngle2P;
};

class GameMainTag2P :public SceneChange,Direct3D
{
private:
	//Camera camera2P;
	//Camera camera1P;
	Camera *camera1;
	Map *map2P;
	//テクスチャインスタンス
	Texture *timeTexture2;
	//スプライトインスタンス
	Sprite *timeSprite2;
	//プレイヤーインスタンス
	Player *player;
	//enemyのインスタンス
	Enemy *enemy2;
	//１Pの構造体
	pCameraInfo1P pInfo1P;
	//２Pの構造体
	pCameraInfo2P pInfo2P;
	//wave読み込み
	CSound wave[2];
	//時間用メンバ変数
	int timeframe2;
	//time10の位
	int tentime2 = 9;
	//time1の位
	int onetime2 = 0;
public:

	//デフォルトコンストラクタ
	GameMainTag2P();
	//デストラクタ
	~GameMainTag2P();
	//初期化
	void Init();
	//アップデート
	void  Update();
	//描画
	void Draw();


protected:
	D3DXVECTOR3 PlayerPos1P;
	D3DXVECTOR3 PlayerPos2P;
	D3DXVECTOR3 PlayerAngle1P;
	D3DXVECTOR3 PlayerAngle2P;


};