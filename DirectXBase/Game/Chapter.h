#pragma once

#include"../Global.h"
#include "../Direct3D\texture.h"
#include "../Direct3D\sprite.h"
#include "../Direct3D/direct3d.h"
#include "../DirectInput\directInput.h"
#include"Chapter_GameOfTag.h"
#include "SceneChange.h"

//派生クラス:Chapter 基底クラス:SceneChange,Direct3D
class Chapter :public SceneChange,Direct3D
{
private:
	//マーカー
	float y = 300.0f;

public:
	Texture chapter_texture_onigo;
	Texture chapter_texture_dodge;
	Texture chapter_texture_marker;
	Sprite chapter_sprite_onigo;
	Sprite chapter_sprite_dodge;
	Sprite chapter_sprite_marker;
	bool chapter_flag;

	//コンストラクタ
	Chapter();
	//デストラクタ
	~Chapter();

	void Update();
	void Draw();

	void Load();
};