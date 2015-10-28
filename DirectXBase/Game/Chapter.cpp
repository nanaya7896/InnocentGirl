#include"Chapter.h"


//コンストラクタ
Chapter::Chapter()
{
	Load();
}

//デストラクタ
Chapter::~Chapter()
{

}

void Chapter::Update()
{

	
	//↑キーが押されたとき
	if (DirectInput::GetInstance().KeyDown(DIK_UP))
	{
		if (y >= 400)
		{
			y -= 300;
		}
	}
	//↓キーが押されたとき
	else if (DirectInput::GetInstance().KeyDown(DIK_DOWN))
	{
		if (y <= 200)
		{
			y += 300;
		}
	}

	if (y > 700)
	{
		y = 600;
	}
	else if (y < 200)
	{
		y = 300;

	}

	
	//Chapterおにごっこに画面遷移
	if (/*pJoypad->isPushed(Joypad::Button::Start) == true || */DirectInput::GetInstance().KeyDown(DIK_RETURN))
	{
		delete scenechange;
		scenechange = new CGameOfTag();		//チャプター選択

	}

}

void Chapter::Draw()
{
	chapter_sprite_onigo.Draw(pDevice3D, chapter_texture_onigo.pTexture);	//鬼ごっこ
	chapter_sprite_dodge.Draw(pDevice3D, chapter_texture_dodge.pTexture);	//ドッヂボール
	chapter_sprite_marker.Draw(pDevice3D, chapter_texture_marker.pTexture);	//マーカー
}

void Chapter::Load()
{
	//鬼ごっこの描画
	chapter_texture_onigo.Load(_T("texture/onigokko.png"));
	chapter_sprite_onigo.SetPos(450, 300);
	chapter_sprite_onigo.SetSize(648, 168);

	//ドッヂボールの描画
	chapter_texture_dodge.Load(_T("texture/dodgeball.png"));
	chapter_sprite_dodge.SetPos(450, 600);
	chapter_sprite_dodge.SetSize(648, 168);

	//マーカー
	chapter_texture_marker.Load(_T("texture/ma-ka-.png"));
	chapter_sprite_marker.SetPos(70, y);
	chapter_sprite_marker.SetSize(130, 130);

}