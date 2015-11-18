#pragma once

#include "../Direct3D/direct3d.h"
#include "../Direct3D/sprite.h"
#include "../Direct3D/texture.h"
#include"../Global.h"
#include "../DirectInput/directInput.h"
#include"SceneChange.h"
#include"GameMainTag.h"
#include"Title.h"

#define YUKI_SPRITE_SIZE_X 450          //ユキちゃんのサイズ（Ｘ）
#define YUKI_SPRITE_SIZE_Y 900          //ユキちゃんのサイズ（Ｙ）

#define GAMECLEAR1_SPRITE_SIZE_X 1600   //ゲームクリア１のサイズ（Ｘ）
#define GAMECLEAR1_SPRITE_SIZE_Y 900    //ゲームクリア１のサイズ（Ｙ）

#define GAMECLEAR2_SPRITE_SIZE_X 950    //ゲームクリア２のサイズ（Ｘ）
#define GAMECLEAR2_SPRITE_SIZE_Y 100    //ゲームクリア２のサイズ（Ｙ）

#define GAMECLEAR3_SPRITE_SIZE_X 1100   //ゲームクリア３のサイズ（Ｘ）
#define GAMECLEAR3_SPRITE_SIZE_Y 220    //ゲームクリア３のサイズ（Ｙ）

#define YUKI_SPRITE_POS_X 1420         //ユキちゃんの位置（Ｘ）
#define YUKI_SPRITE_POS_Y 450          //ユキちゃんの位置（Ｙ）

#define GAMECLEAR1_SPRITE_POS_X 800     //ゲームクリア１の位置（Ｘ）
#define GAMECLEAR1_SPRITE_POS_Y 450     //ゲームクリア１の（Ｙ）

#define GAMECLEAR2_SPRITE_POS_X 700     //ゲームクリア２の位置（Ｘ）
#define GAMECLEAR2_SPRITE_POS_Y 550     //ゲームクリア２の位置（Ｙ）

#define GAMECLEAR3_SPRITE_POS_X 680     //ゲームクリア３の位置（Ｘ）
#define GAMECLEAR3_SPRITE_POS_Y 400     //ゲームクリア３の位置（Ｙ）



class CResult :public SceneChange,Direct3D
{
private:
	//テクスチャとスプライト
	Texture yukiR1Tex;
	Sprite yukiR1Sprite;

	Texture yukiR2Tex;
	Sprite yukiR2Sprite;

	Texture yukiR3Tex;
	Sprite yukiR3Sprite;

	Texture gameclear1;
	Sprite gameclearSprite1;

	Texture gameclear2;
	Sprite gameclearSprite2;

	Texture gameclear3;
	Sprite gameclearSprite3;

	int randomNum;    //ランダム変数格納用
public:

	//コンストラクタ　デストラクタ
	CResult();
	~CResult();


	void Load();

	//update
	void Update();

	//draw
	void Draw();

	// 最大と最小の間の値をランダムに返すヘルパー関数
	float Random(float min, float max);

};