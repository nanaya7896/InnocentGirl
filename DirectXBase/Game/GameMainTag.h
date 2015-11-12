#pragma once

#include "../Direct3D\texture.h"
#include "../Direct3D\sprite.h"
#include "../Direct3D/direct3d.h"
#include "../DirectInput\directInput.h"
#include"../Player/Player.h"
#include"../Direct3D/Camera.h"
#include "SceneChange.h"
#include"../DirectXAnimation/MyAllocateHierarchy.h"
#include"../DirectXAnimation/AnimateObject.h"
#include"../Direct3D/font.h"
class GameMainTag :public SceneChange,Direct3D
{
private:
	//テクスチャインスタンス
	Texture timeTexture[10];
	//スプライトインスタンス
	Sprite timeSprite[2];
	//プレイヤーインスタンス
	Player player;
	//カメラインスタンス
	Camera camera;
	//アニメーションインスタンス
	MyAllocateHierarchy mah;
	//メッシュインスタンス
	CSkinMesh cskinMesh;
	//テキストインスタンス
	DirectXText timeText;
	//時間用メンバ変数
	int time;
	int timeframe;
	//time10の位
	int tentime=9;
	//time1の位
	int onetime=0;
public:


	//コンストラクタ
	GameMainTag();

	//デストラクタ
	~GameMainTag();

	void Update();
	void Draw();

	void Load();

	//当たり判定関数
	HRESULT Player_HitBox();
protected:
	D3DXVECTOR3 PlayerPos;
	D3DXVECTOR3 PlayerAngle;

};