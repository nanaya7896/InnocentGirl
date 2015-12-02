#pragma once

#include "../SceneChanger/BaseScene.h"
#include "../SceneChanger/ISceneChanger.h"
#include"../Direct3D/direct3d.h"
#include"../Direct3D/Texture.h"
#include"../Direct3D/sprite.h"
#include"../DirectInput/directInput.h"
#include"Chapter.h"
#include"Result.h"
#include"../Xinput/XbonInput.h"


//派生クラス:タイトル	基底クラス:SceneChange　
class Title : public BaseScene,Direct3D
{
private:
	//文字点滅用フレーム
	unsigned long frame = 0;
	//継承元
	XboxInput xboxInput;
public:
	//メンバ変数
	Texture title_Background;
	Texture title_bar1;
	Texture title_bar2;
	Sprite stitle_bar;
	Sprite stitle;
	//サウンド読み込み
	CSound wave[2];
	bool TitleBlink;

	//コンストラクタ
	Title(ISceneChanger *changer);
	//デストラクタ
	~Title();
	
	void Initialize() override;    //初期化処理をオーバーライド。
	void Finalize() override;        //終了処理をオーバーライド
	void Update() override;
	void Draw() override;


protected:

	

};