#include"GameOver.h"

extern int SceneRetry;

//コンストラクタ
Gameover::Gameover(ISceneChanger* changer)
	:BaseScene(changer),go_marker_flag(false)
{
	//wave[0].Play(true);
}

//デストラクタ
Gameover::~Gameover()
{

	//動的なメモリ確保などがないのでなし
}

//テクスチャのロード

//ゲームの初期化
//ゲーム開始の際に行う準備
void Gameover::Initialize()
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
	dGScore.Create(pDevice3D, 32);
	//wavファイル読み込み
	/*wave[0].Load(_T("BGM/gameover.wav"));
	wave[1].Load(_T("BGM/kettei.wav"));
	wave[2].Load(_T("BGM/ka-soruidou.wav"));
*/
}

void Gameover::Finalize()
{

}

void Gameover::Update()
{
	gInput.checkControllers();
	gInput.readControllers();
	//やじるし移動
	//右
	if (gInput.getGamepadThumbLX(0)>0 ||  DirectInput::GetInstance().KeyDown(DIK_RIGHT))
	{
		//wave[2].Play(false);
		go_marker_flag = true;
	}
	//左
	if (gInput.getGamepadThumbLX(0)<0|| DirectInput::GetInstance().KeyDown(DIK_LEFT))
	{
		//wave[2].Play(false);
		go_marker_flag = false;
	}

	//画面遷移
	//リトライ
	if ((gInput.getGamepadB(0) || DirectInput::GetInstance().KeyDown(DIK_RETURN)) && go_marker_flag == false)
	{
		/*wave[0].Stop();
		wave[1].Play(false);*/
		switch (SceneRetry)
		{
		case 0:
			mSceneChanger->ChangeScene(eScene_GameMainTag1P);
			break;
		case 1:
			mSceneChanger->ChangeScene(eScene_GameMainTag2P);
			break;
		case 2:
			mSceneChanger->ChangeScene(eScene_GameMainDodge1P);
			break;
		case 3:
			mSceneChanger->ChangeScene(eScene_GameMainDodge2P);
			break;
		}
		return;
	}
	//チャプターへ
	if ((gInput.getGamepadB(0) || DirectInput::GetInstance().KeyDown(DIK_RETURN)) && go_marker_flag == true)
	{
		/*wave[0].Stop();
		wave[1].Play(false);*/
		mSceneChanger->ChangeScene(eScene_Chapter);
		return;
	}
	//実際にスコアを受け取る
	//a = Gscore.score1P();
}

void Gameover::Draw()
{
	//dGScore.Draw(D3DXCOLOR(10, 255, 255, 255), 10, 100, "%d", a);
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
