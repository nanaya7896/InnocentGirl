#pragma once

#include"SceneChange.h"
#include"../Direct3D/direct3d.h"
#include"../Direct3D/Texture.h"
#include"../Direct3D/sprite.h"
#include"../DirectInput/directInput.h"
#include"Chapter.h"
//派生クラス:タイトル	基底クラス:SceneChange　
class Title : public SceneChange,Direct3D
{
private:
	//文字点滅用フレーム
	unsigned long frame = 0;


public:
	//メンバ変数
	Texture title_Background;
	Texture title_bar[2];
	Sprite stitle_bar;
	Sprite stitle;

	bool TitleBlink;

	//コンストラクタ
	Title();
	//デストラクタ
	~Title();

	//メンバ関数
	void Update();
	void Draw();
	void Load();

protected:



};