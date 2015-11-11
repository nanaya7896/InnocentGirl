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
	int time;
	int timeframe;
public:


	//コンストラクタ
	GameMainTag();

	//デストラクタ
	~GameMainTag();

	void Update();
	void Draw();

	void Load();
protected:
	D3DXVECTOR3 PlayerPos;
	D3DXVECTOR3 PlayerAngle;

};