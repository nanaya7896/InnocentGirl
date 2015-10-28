#pragma once

#include"../Global.h"
#include"SceneChange.h"
#include "../Direct3D\texture.h"
#include "../Direct3D\sprite.h"
#include "../Direct3D/direct3d.h"
#include "../DirectInput\directInput.h"
#include"GameMainTag.h"
class CGameOfTag : public SceneChange ,Direct3D
{
private:


public:
	Texture onigo_chapter_texture;
	Texture onigo_hitori_texture[2];
	Texture onigo_tomodati_texture[2];
	Sprite onigo_chapter_sprite;
	Sprite onigo_hitori_sprite[2];
	Sprite onigo_tomodati_sprite[2];
	


	bool onigo_flag = false;

	//コンストラクタ
	CGameOfTag();

	//デストラクタ
	~CGameOfTag();

	void Update();
	void Draw();

	void Load();
};
