#pragma once

#include "../Global.h"

#include "../Direct3D\texture.h"
#include "../Direct3D\sprite.h"
#include "../Direct3D/direct3d.h"
#include "../SceneChanger/BaseScene.h"
#include "../SceneChanger/ISceneChanger.h"
#include "../DirectInput\directInput.h"
#include"Title.h"
#include "GameMainTag.h"
#include "GameMainTag2P.h"


#include"../DirectSound/dxsound.h"

#include"../Xinput/XbonInput.h"


//派生クラス:Chapter 基底クラス:SceneChange,Direct3D
class Chapter :public BaseScene, Direct3D
{
public:
	//背景
	Texture chapter_bg;
	Sprite schapter_bg;
	//操作説明
	Texture tContTx;
	Sprite sContTx;
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

	XboxInput chaInput;
	//フラグ
	bool chapter_flag;
	bool member_flag;
	bool marker_flag;
	bool ContFlag;

	//コンストラクタ
	Chapter(ISceneChanger *changer);
	//デストラクタ
	~Chapter();

	void Initialize() override;    //初期化処理をオーバーライド。
	void Finalize() override;        //終了処理をオーバーライド。
	void Update() override;
	void Draw() override;
};