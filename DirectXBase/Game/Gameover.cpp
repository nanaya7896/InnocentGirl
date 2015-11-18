#include"GameOver.h"

//コンストラクタ
Gameover::Gameover()
{
	Load();
}

//デストラクタ
Gameover::~Gameover()
{
	//動的なメモリ確保などがないのでなし
}

//インスタンスの初期化
void Gameover::Load()
{
	//テクスチャ　スプライトの準備

	gameover1.Load(_T("Texture/gameover1.png"));      //画像（ゲームオーバー１）の読み込み
	gameover2.Load(_T("Texture/gameover2.png"));      //画像（ゲームオーバー２）の読み込み
	gameover3.Load(_T("Texture/gameover3.png"));      //画像（ゲームオーバー３）の読み込み
	gameover4.Load(_T("Texture/gameover4.png"));      //画像（ゲームオーバー４）の読み込み

	gameoverSprite1.SetSize(GAMEOVER1_SPRITE_SIZE_X, GAMEOVER1_SPRITE_SIZE_Y);//スプライトのサイズ設定
	gameoverSprite2.SetSize(GAMEOVER2_SPRITE_SIZE_X, GAMEOVER2_SPRITE_SIZE_Y);//スプライトのサイズ設定
	gameoverSprite3.SetSize(GAMEOVER3_SPRITE_SIZE_X, GAMEOVER3_SPRITE_SIZE_Y);//スプライトのサイズ設定
	gameoverSprite4.SetSize(GAMEOVER4_SPRITE_SIZE_X, GAMEOVER4_SPRITE_SIZE_Y);//スプライトのサイズ設定
}
//ゲームの初期化
//ゲーム開始の際に行う準備
void Gameover::Update()
{
	if (DirectInput::GetInstance().KeyDown(DIK_RETURN))
	{
		delete scenechange;
		scenechange = new Title();
	}
}

void Gameover::Draw()
{
	gameoverSprite1.SetPos(GAMEOVER1_SPRITE_POS_X, GAMEOVER1_SPRITE_POS_Y);
	gameoverSprite1.Draw(pDevice3D, gameover1.pTexture, false);

	gameoverSprite2.SetPos(GAMEOVER2_SPRITE_POS_X, GAMEOVER2_SPRITE_POS_Y);
	gameoverSprite2.Draw(pDevice3D, gameover2.pTexture);

	gameoverSprite3.SetPos(GAMEOVER3_SPRITE_POS_X, GAMEOVER3_SPRITE_POS_Y);
	gameoverSprite3.Draw(pDevice3D, gameover3.pTexture);

	gameoverSprite4.SetPos(GAMEOVER4_SPRITE_POS_X, GAMEOVER4_SPRITE_POS_Y);
	gameoverSprite4.Draw(pDevice3D, gameover4.pTexture);


}
