#include "Chapter_GameOfTag.h"


//コンストラクタ
CGameOfTag::CGameOfTag()
{
	sousaflag = false;
	Load();
}

//デストラクタ
CGameOfTag::~CGameOfTag()
{

}

void CGameOfTag::Update()
{
	if (DirectInput::GetInstance().KeyDown(DIK_RETURN) && sousaflag == false)
	{
		sousaflag = true;
	}
	if (DirectInput::GetInstance().KeyDown(DIK_SPACE) && sousaflag == true)
	{ 
		delete scenechange;
		//scenechange = new GameMainTag();
		scenechange = new GameMainTag2P();
	}
	if (DirectInput::GetInstance().KeyDown(DIK_LEFT)&&sousaflag==false)
	{
		onigo_flag = false;
	}
	else if (DirectInput::GetInstance().KeyDown(DIK_RIGHT) && sousaflag == false)
	{
		onigo_flag = true;
	}
	


}

void CGameOfTag::Draw()
{
	if (sousaflag == false)
	{
		//チャプター画像の描画
		onigo_chapter_sprite.Draw(pDevice3D, onigo_chapter_texture.pTexture);


		//ひとり画像の描画	
		//ともだち画像の描画
		if (onigo_flag == false)
		{
			//	onigo_hitori_sprite[1].Draw(pDevice3D, onigo_hitori_texture[1].pTexture);
			onigo_tomodati_sprite[0].Draw(pDevice3D, onigo_tomodati_texture[0].pTexture);

		}
		else if (onigo_flag == true)
		{
			onigo_hitori_sprite[0].Draw(pDevice3D, onigo_hitori_texture[0].pTexture);
			//onigo_tomodati_sprite[1].Draw(pDevice3D, onigo_tomodati_texture[1].pTexture);

		}
		s_bgcgo.Draw(pDevice3D, t_bgcgo.GetTexture());
	}
	else
	{
		s_Info.Draw(pDevice3D, t_Info.GetTexture());
	}
}

void CGameOfTag::Load()
{
	//チャプター画像の読み込み
	onigo_chapter_texture.Load(_T("texture/chapter_oni.png"));
	onigo_chapter_sprite.SetPos(1200, 430);
	onigo_chapter_sprite.SetSize(700, 850);

	//ひとり画像の読み込み
	onigo_hitori_texture[0].Load( _T("texture/hitori.png"));
	//onigo_hitori_texture[1].Load( _T("texture/hitori_big.png"));
	onigo_hitori_sprite[0].SetPos(600, 200);
	//onigo_hitori_sprite[1].SetPos(100, 430);
	onigo_hitori_sprite[0].SetSize(600, 850);
	//onigo_hitori_sprite[1].SetSize(700, 850);


	//ともだちと画像の読み込み
	onigo_tomodati_texture[0].Load(_T("texture/tomodatito.png"));
	//onigo_tomodati_texture[1].Load(_T("texture/tomodatito_big.png"));
	onigo_tomodati_sprite[0].SetPos(600, 500);
	//onigo_tomodati_sprite[1].SetPos(300, 430);
	onigo_tomodati_sprite[0].SetSize(600, 850);
	//onigo_tomodati_sprite[1].SetSize(700, 850);

	//背景のロード
	t_bgcgo.Load(_T("texture/taitoru2.png"));

	//画像の場所指定
	s_bgcgo.SetPos(800, 450);
	//画像の縦横のサイズ指定
	s_bgcgo.SetSize(1600, 900);

	t_Info.Load(_T("texture/sousaonigo.png"));
	//画像の場所指定
	s_Info.SetPos(800, 450);
	//画像の縦横のサイズ指定
	s_Info.SetSize(1600, 900);

}
