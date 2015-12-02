
#pragma once

#include"../Global.h"
#include"../Direct3D/direct3d.h"
#include"../Direct3D/sprite.h"
#include"../Direct3D/texture.h"
#include"../DirectInput/directInput.h"
#include "../SceneChanger/BaseScene.h"
#include "../SceneChanger/ISceneChanger.h"
#include"GameMainTag.h"
#include"Title.h"
#include"../Enemy/Enemy.h"
#include"../Xinput/XbonInput.h"

#define GAMEOVER1_SPRITE_SIZE_X 1600   //ゲームオーバー１（背景）のサイズ（Ｘ）
#define GAMEOVER1_SPRITE_SIZE_Y 900    //ゲームオーバー１（背景）のサイズ（Ｙ）

#define GAMEOVER2_SPRITE_SIZE_X 70    //ゲームオーバー２（やじるし）のサイズ（Ｘ）
#define GAMEOVER2_SPRITE_SIZE_Y 70    //ゲームオーバー２（やじるし）のサイズ（Ｙ）

#define GAMEOVER3_SPRITE_SIZE_X 210   //ゲームオーバー３（リトライ）のサイズ（Ｘ）
#define GAMEOVER3_SPRITE_SIZE_Y 70    //ゲームオーバー３（リトライ）のサイズ（Ｙ）

#define GAMEOVER4_SPRITE_SIZE_X 490   //ゲームオーバー４（チャプターへ）のサイズ（Ｘ）
#define GAMEOVER4_SPRITE_SIZE_Y 70    //ゲームオーバー４（チャプターへ）のサイズ（Ｙ）

#define GAMEOVER1_SPRITE_POS_X 800     //ゲームオーバー１（背景）の位置（Ｘ）
#define GAMEOVER1_SPRITE_POS_Y 450     //ゲームオーバー１（背景）の位置（Ｙ）

#define GAMEOVER2_SPRITE_POS_X 370     //ゲームオーバー２（やじるし）の位置（Ｘ）
#define GAMEOVER2_SPRITE_POS_Y 700     //ゲームオーバー２（やじるし）の位置（Ｙ）

#define GAMEOVER3_SPRITE_POS_X 500     //ゲームオーバー３（リトライ）の位置（Ｘ）
#define GAMEOVER3_SPRITE_POS_Y 700     //ゲームオーバー３（リトライ）の位置（Ｙ）

#define GAMEOVER4_SPRITE_POS_X 1100     //ゲームオーバー４（チャプターへ）の位置（Ｘ）
#define GAMEOVER4_SPRITE_POS_Y 700     //ゲームオーバー４（チャプターへ）の位置（Ｙ）



class Gameover :public BaseScene, Direct3D
{
private:
	//テクスチャとスプライト
	//背景
	Texture gameover1;
	Sprite gameoverSprite1;

	//矢印
	Texture gameover2;
	Sprite gameoverSprite2[2];

	//文字
	//リトライ
	Texture gameover3;
	Sprite gameoverSprite3;
	//チャプターへ
	Texture gameover4;
	Sprite gameoverSprite4;

	CSound wave[2];
	
	//スコア描画用
	Enemy Gscore;
	DirectXText dGScore;
	int a;

	//Xboxコントローラーコントローラークラスのインスタンス
	XboxInput gInput;
public:
	//フラグ
	bool go_marker_flag;

	//コンストラクタ　デストラクタ
	Gameover(ISceneChanger *changer);
	~Gameover();

	void Initialize() override;
	void Finalize() override;
	//update
	void Update() override;

	//draw
	void Draw() override;

};