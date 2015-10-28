#pragma once

#include "../Direct3D\texture.h"
#include "../Direct3D\sprite.h"
#include "../Direct3D/direct3d.h"
#include "../DirectInput\directInput.h"
#include"../Player/Player.h"
#include"../Direct3D/Camera.h"
#include "SceneChange.h"

class GameMainTag :public SceneChange,Direct3D
{
private:
	
public:
	Player player;
	Camera camera;

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