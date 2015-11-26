#include"Chapter.h"


//コンストラクタ
Chapter::Chapter()
{
	ContFlag = false;
	Load();
	wave[0].Play(false);
}

//デストラクタ
Chapter::~Chapter()
{
	ContFlag = false;
}

void Chapter::Update()
{
	//デバッグ用
	//std::complex<double> cmp=pJoypad->getLStick(0.1);

	//鬼ごっこ選択
	if (pJoypad->getLStick(0.1).imag() >= 0.5 || DirectInput::GetInstance().KeyDown(DIK_UP))
	{
		wave[2].Play(false);
		marker_flag = false;
		chapter_flag = false;
	}
	//ドッヂ選択
	if (pJoypad->getLStick(0.1).imag() <= -0.5 || DirectInput::GetInstance().KeyDown(DIK_DOWN))
	{
		wave[2].Play(false);
		marker_flag = true;
		chapter_flag = true;
	}

	//ともだちと選択
	if (pJoypad->getLStick(0.1).real() >= 0.5 || DirectInput::GetInstance().KeyDown(DIK_RIGHT))
	{
		wave[2].Play(false);
		member_flag = true;
	}
	//ひとり選択
	if (pJoypad->getLStick(0.1).real() <= -0.5 || DirectInput::GetInstance().KeyDown(DIK_LEFT))
	{
		wave[2].Play(false);
		member_flag = false;
	}


	
	//GameMainおにごっこひとりプレイに画面遷移
	if (pJoypad->isPushed(Joypad::Button::B) == true || DirectInput::GetInstance().KeyDown(DIK_RETURN))
	{
		ContFlag = true;
	}
	if (ContFlag == true)
	{
		sContTx.Draw(pDevice3D, tContTx.GetTexture());
		//GameMainおにごっこひとりプレイに画面遷移
		if (pJoypad->isPushed(Joypad::Button::B) == true || DirectInput::GetInstance().KeyDown(DIK_SPACE) && chapter_flag == false && member_flag == false)
		{
			sContTx.Draw(pDevice3D, tContTx.GetTexture());
			wave[0].Stop();
			wave[1].Play(false);
			delete scenechange;
			scenechange = new GameMainTag();		//おにごっこひとりプレイ
			return;
		}
		//GameMainおにごっこともだちとプレイに画面遷移

		if (pJoypad->isPushed(Joypad::Button::B) == true || DirectInput::GetInstance().KeyDown(DIK_SPACE) && chapter_flag == false && member_flag == true)
		{
			sContTx.Draw(pDevice3D, tContTx.GetTexture());
			wave[0].Stop();
			wave[1].Play(false);
			delete scenechange;
			scenechange = new GameMainTag2P();		//おにごっこともだちとプレイ
			return;
		}
	}
	
	

}

void Chapter::Draw()
{
	//マーカー
	smarker[!marker_flag].Draw(pDevice3D, marker.pTexture);
	//おにごっこ
	schapter_onigo.Draw(pDevice3D, chapter_onigo.pTexture);
	//ドッヂボール
	schapter_dodge.Draw(pDevice3D, chapter_dodge.pTexture);
	//ひとり
	shitori[!member_flag].Draw(pDevice3D, hitori[!member_flag].pTexture);
	//ふたり
	stomodati[!member_flag].Draw(pDevice3D, tomodati[!member_flag].pTexture);
	//チャプター
	schapter[!chapter_flag].Draw(pDevice3D, chapter[!chapter_flag].pTexture);
	//背景
	schapter_bg.Draw(pDevice3D, chapter_bg.pTexture);
}

void Chapter::Load()
{
	//鬼ごっこの描画
	chapter_onigo.Load(_T("texture/onigokko.png"));
	schapter_onigo.SetPos(450, 300);
	schapter_onigo.SetSize(648, 168);

	//ドッヂボールの描画
	chapter_dodge.Load(_T("texture/dodgeball.png"));
	schapter_dodge.SetPos(450, 600);
	schapter_dodge.SetSize(648, 168);

	//マーカー
	marker.Load(_T("texture/ma-ka-.png"));
	smarker[!marker_flag].SetPos(70, 300);
	smarker[!marker_flag].SetSize(130, 130);
	smarker[marker_flag].SetPos(70, 600);
	smarker[marker_flag].SetSize(130, 130);

	//チャプター
	chapter[!chapter_flag].Load(_T("texture/chapter_oni.png"));
	schapter[!chapter_flag].SetPos(1200, 430);
	schapter[!chapter_flag].SetSize(700, 850);
	chapter[chapter_flag].Load(_T("texture/chapter_dodge.png"));
	schapter[chapter_flag].SetPos(1200, 430);
	schapter[chapter_flag].SetSize(700, 850);

	//ひとり
	hitori[member_flag].Load(_T("texture/hitori.png"));
	shitori[member_flag].SetPos(1100, 700);
	shitori[member_flag].SetSize(250, 200);
	hitori[!member_flag].Load(_T("texture/hitori_big.png"));
	shitori[!member_flag].SetPos(1100, 700);
	shitori[!member_flag].SetSize(250, 200);
	//ともだち
	tomodati[!member_flag].Load(_T("texture/tomodatito.png"));
	stomodati[!member_flag].SetPos(1350, 700);
	stomodati[!member_flag].SetSize(250, 200);
	tomodati[member_flag].Load(_T("texture/tomodatito_big.png"));
	stomodati[member_flag].SetPos(1350, 700);
	stomodati[member_flag].SetSize(250, 200);
	//操作説明
	tContTx.Load(_T("texture/sousaonigo.png"));
	sContTx.SetPos(WINDOW_WIDTH/2,WINDOW_HEIGHT/2);
	sContTx.SetSize(WINDOW_WIDTH,WINDOW_HEIGHT);

	//背景読み込み
	chapter_bg.Load(_T("texture/taitoru2.png"));
	//画像の場所指定
	schapter_bg.SetPos(800, 450);
	//画像の縦横のサイズ指定
	schapter_bg.SetSize(1600, 900);
	//WAVEの読み込み
	wave[0].Load(_T("BGM/taitoru.wav"));
	wave[1].Load(_T("BGM/kettei.wav"));
	wave[2].Load(_T("BGM/ka-soruidou.wav"));
}