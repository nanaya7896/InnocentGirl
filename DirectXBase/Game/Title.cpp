#include"Title.h"

//コンストラクタ
Title::Title()
{
	Load();
}

//デストラクタ
Title::~Title()
{

}



void Title::Update()
{
	//press buttonの点滅処理
	//フレーム加算
	frame++;
	//もしフレームが３０で割り切れた場合
	if (frame % 30 == 0)
	{
		//点滅ON/OFFフラグを反転
		TitleBlink = !TitleBlink;
		//もしフレームが60を超えたら
		if (frame >=60)
		{
			//フレームを初期化
			frame = 0;
		}
	}
	//もしリターンキーが押された場合
	if (DirectInput::GetInstance().KeyDown(DIK_RETURN) == true)
	{
		//現在のシーンのメモリを解放
		delete scenechange;
		//次のシーン:チャプターのメモリをシーンチェンジに入れる
		scenechange = new Chapter();
	}

}

//タイトル画面
void Title::Draw()
{
	


	if (TitleBlink==true)
	{
		//タイトル描画処理
		stitle_bar.Draw(pDevice3D,title_bar1.GetTexture());
	}
	else if(TitleBlink==false)
	{
		//タイトルに白い画像を重ねる
		stitle_bar.Draw(pDevice3D,title_bar2.GetTexture());
	}
	//背景の描画
	stitle.Draw(pDevice3D, title_Background.pTexture);
	

}

void Title::Load()
{
	//背景の読み込み
	title_Background.Load(_T("texture/title_kari.png"));
	//画像の場所指定
	stitle.SetPos(800, 450);
	//画像の縦横のサイズ指定
	stitle.SetSize(1600, 900);
	//press buttonの描画
	title_bar1.Load(_T("texture/start.png"));
	//白い画像の描画
	title_bar2.Load(_T("texture/aho.png"));
	stitle_bar.SetPos(800, 700);
	stitle_bar.SetSize(720, 200);

	TitleBlink = false;

}