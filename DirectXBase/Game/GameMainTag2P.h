#pragma once

#include"../Global.h"
#include"../Direct3D/Camera.h"
#include"SceneChange.h"
#include"Chapter_GameOfTag.h"
#include"../Game/Map.h"
#include"../Enemy/Enemy.h"
#include"../Player/Player.h"


class GameMainTag2P :public SceneChange,Direct3D
{
private:
	Camera camera2P;
	Map *map2P;

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


};