
#include "Result.h"

//コンストラクタ
CResult::CResult(ISceneChanger *changer) : BaseScene(changer)
{
	randomNum = 0;
	
}

//デストラクタ
CResult::~CResult()
{

	//動的なメモリ確保などがないのでなし
}

//ゲームの初期化
//ゲーム開始の際に行う準備
void CResult::Initialize()
{
	randomNum = Random((int)(1), (int)(3));
	//テクスチャ　スプライトの準備
	yukiR1Tex.Load(_T("texture/yuki-R1.png"));          //画像（ユキ１）の読み込み
	yukiR2Tex.Load(_T("texture/yuki-R2.png"));          //画像（ユキ２）の読み込み
	yukiR3Tex.Load(_T("texture/yuki-R3.png"));          //画像（ユキ３）の読み込み


	gameclear1.Load(_T("texture/gameclear1.png"));      //画像（クリア１）の読み込み
	gameclear2.Load(_T("texture/gameclear2.png"));      //画像（クリア２）の読み込み
	gameclear3.Load(_T("texture/gameclear3.png"));      //画像（クリア３）の読み込み

	yukiR1Sprite.SetSize(YUKI_SPRITE_SIZE_X, YUKI_SPRITE_SIZE_Y);              //スプライトのサイズ設定                   
	yukiR2Sprite.SetSize(YUKI_SPRITE_SIZE_X, YUKI_SPRITE_SIZE_Y);              //スプライトのサイズ設定
	yukiR3Sprite.SetSize(YUKI_SPRITE_SIZE_X, YUKI_SPRITE_SIZE_Y);              //スプライトのサイズ設定

	gameclearSprite1.SetSize(GAMECLEAR1_SPRITE_SIZE_X, GAMECLEAR1_SPRITE_SIZE_Y);//スプライトのサイズ設定
	gameclearSprite2.SetSize(GAMECLEAR2_SPRITE_SIZE_X, GAMECLEAR2_SPRITE_SIZE_Y);//スプライトのサイズ設定
	gameclearSprite3.SetSize(GAMECLEAR3_SPRITE_SIZE_X, GAMECLEAR3_SPRITE_SIZE_Y);//スプライトのサイズ設定

	//wavファイル読み込み
	wave[0].Load(_T("BGM/rizaruto.wav"));
	wave[1].Load(_T("BGM/kettei.wav"));
	wave[0].Play(false);
}

void CResult::Finalize()
{



}


void CResult::Update()
{
	rInput.checkControllers();
	rInput.readControllers();
	if (rInput.getGamepadB(0)|| DirectInput::GetInstance().KeyDown(DIK_RETURN)==true)
	{
		wave[0].Stop();
		wave[1].Play(false);
		mSceneChanger->ChangeScene(eScene_Chapter);
		return;
	}

}


void CResult::Draw()
{
	switch (randomNum)
	{
	case 1:
		yukiR1Sprite.SetPos(YUKI_SPRITE_POS_X, YUKI_SPRITE_POS_Y);
		yukiR1Sprite.Draw(pDevice3D, yukiR1Tex.GetTexture());
		break;

	case 2:
		yukiR2Sprite.SetPos(YUKI_SPRITE_POS_X, YUKI_SPRITE_POS_Y);
		yukiR2Sprite.Draw(pDevice3D, yukiR2Tex.GetTexture());
		break;

	case 3:
		yukiR3Sprite.SetPos(YUKI_SPRITE_POS_X, YUKI_SPRITE_POS_Y);
		yukiR3Sprite.Draw(pDevice3D, yukiR3Tex.GetTexture());
		break;
	}
	gameclearSprite3.SetPos(GAMECLEAR3_SPRITE_POS_X, GAMECLEAR3_SPRITE_POS_Y);
	gameclearSprite3.Draw(pDevice3D, gameclear3.GetTexture());

	gameclearSprite2.SetPos(GAMECLEAR2_SPRITE_POS_X, GAMECLEAR2_SPRITE_POS_Y);
	gameclearSprite2.Draw(pDevice3D, gameclear2.GetTexture());

	gameclearSprite1.SetPos(GAMECLEAR1_SPRITE_POS_X, GAMECLEAR1_SPRITE_POS_Y);
	gameclearSprite1.Draw(pDevice3D, gameclear1.GetTexture());
}

float CResult::Random(float min, float max)
{
	return ((float)rand() / (float)RAND_MAX) * (max - min) + min;
}