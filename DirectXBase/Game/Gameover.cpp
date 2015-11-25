#include"GameOver.h"

//コンストラクタ
Gameover::Gameover()
	:go_marker_flag(false)
{
	Load();
}

//デストラクタ
Gameover::~Gameover()
{
	//動的なメモリ確保などがないのでなし
}

//テクスチャのロード
void Gameover::Load()
{

	//背景
	gameover1.Load(_T("Texture/gameover1.png"));      //画像（ゲームオーバー１）の読み込み
	gameoverSprite1.SetSize(GAMEOVER1_SPRITE_SIZE_X, GAMEOVER1_SPRITE_SIZE_Y);
	gameoverSprite1.SetPos(GAMEOVER1_SPRITE_POS_X, GAMEOVER1_SPRITE_POS_Y);

	//やじるし
	gameover2.Load(_T("Texture/gameover2.png"));      //画像（ゲームオーバー２）の読み込み
	gameoverSprite2[!go_marker_flag].SetSize(GAMEOVER2_SPRITE_SIZE_X, GAMEOVER2_SPRITE_SIZE_Y);
	gameoverSprite2[!go_marker_flag].SetPos(GAMEOVER2_SPRITE_POS_X, GAMEOVER2_SPRITE_POS_Y);
	gameoverSprite2[go_marker_flag].SetSize(GAMEOVER2_SPRITE_SIZE_X, GAMEOVER2_SPRITE_SIZE_Y);
	gameoverSprite2[go_marker_flag].SetPos(GAMEOVER2_SPRITE_POS_X + 430, GAMEOVER2_SPRITE_POS_Y);

	//文字
	//リトライ
	gameover3.Load(_T("Texture/gameover3.png"));      //画像（ゲームオーバー３）の読み込み
	gameoverSprite3.SetSize(GAMEOVER3_SPRITE_SIZE_X, GAMEOVER3_SPRITE_SIZE_Y);
	gameoverSprite3.SetPos(GAMEOVER3_SPRITE_POS_X, GAMEOVER3_SPRITE_POS_Y);
	//ちゃぷたーへ
	gameover4.Load(_T("Texture/gameover4.png"));
	gameoverSprite4.SetSize(GAMEOVER4_SPRITE_SIZE_X, GAMEOVER4_SPRITE_SIZE_Y);
	gameoverSprite4.SetPos(GAMEOVER4_SPRITE_POS_X, GAMEOVER4_SPRITE_POS_Y);

}
//ゲームの初期化
//ゲーム開始の際に行う準備
void Gameover::Update()
{
	//やじるし移動
	//右
	if (DirectInput::GetInstance().KeyDown(DIK_RIGHT))
	{
		go_marker_flag = true;
	}
	//左
	if (DirectInput::GetInstance().KeyDown(DIK_LEFT))
	{
		go_marker_flag = false;
	}

	//画面遷移
	//リトライ
	if (DirectInput::GetInstance().KeyDown(DIK_RETURN) && go_marker_flag == false)
	{
		delete scenechange;
		scenechange = new GameMainTag();
		return;
	}
	//チャプターへ
	if (DirectInput::GetInstance().KeyDown(DIK_RETURN) && go_marker_flag == true)
	{
		delete scenechange;
		scenechange = new Chapter();
		return;
	}

}

void Gameover::Draw()
{
	//やじるし
	gameoverSprite2[!go_marker_flag].Draw(pDevice3D, gameover2.pTexture);

	//文字
	//リトライ
	gameoverSprite3.Draw(pDevice3D, gameover3.pTexture);
	//チャプターへ
	gameoverSprite4.Draw(pDevice3D, gameover4.pTexture);

	//背景
	gameoverSprite1.Draw(pDevice3D, gameover1.pTexture, false);

}
