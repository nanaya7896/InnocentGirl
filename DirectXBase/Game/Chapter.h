#pragma once

#include "../Global.h"

#include "../Direct3D\texture.h"
#include "../Direct3D\sprite.h"
#include "../Direct3D/direct3d.h"

#include "../DirectInput\directInput.h"

#include "GameMainTag.h"
#include "GameMainTag2P.h"

#include "SceneChange.h"

//派生クラス:Chapter 基底クラス:SceneChange,Direct3D
class Chapter :public SceneChange, Direct3D
{
public:
	//背景
	Texture chapter_bg;
	Sprite schapter_bg;
	//マーカー
	Texture marker;
	Sprite smarker[2];
	//おにごっこ
	Texture chapter_onigo;
	Sprite schapter_onigo;
	//ドッヂボール
	Texture chapter_dodge;
	Sprite schapter_dodge;
	//チャプター
	Texture chapter[2];
	Sprite schapter[2];
	//ゲーム画面
	Texture GameScreen[2];
	Sprite sGameScreen[2];
	//ひとり
	Texture hitori[2];
	Sprite shitori[2];
	//ともだち
	Texture tomodati[2];
	Sprite stomodati[2];
	//Coming Soon
	Texture coming;
	Sprite scoming;
	//Waveファイル
	CSound wave[3];

	//フラグ
	bool chapter_flag;
	bool member_flag;
	bool marker_flag;

	//コンストラクタ
	Chapter();
	//デストラクタ
	~Chapter();

	void Update();
	void Draw();

	void Load();
};