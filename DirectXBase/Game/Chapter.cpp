#include"Chapter.h"


//�R���X�g���N�^
Chapter::Chapter()
{
	Load();
}

//�f�X�g���N�^
Chapter::~Chapter()
{

}

void Chapter::Update()
{

	
	//���L�[�������ꂽ�Ƃ�
	if (DirectInput::GetInstance().KeyDown(DIK_UP))
	{
		if (y >= 400)
		{
			y -= 300;
		}
	}
	//���L�[�������ꂽ�Ƃ�
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

	
	//Chapter���ɂ������ɉ�ʑJ��
	if (/*pJoypad->isPushed(Joypad::Button::Start) == true || */DirectInput::GetInstance().KeyDown(DIK_RETURN))
	{
		delete scenechange;
		scenechange = new CGameOfTag();		//�`���v�^�[�I��

	}

}

void Chapter::Draw()
{
	chapter_sprite_onigo.Draw(pDevice3D, chapter_texture_onigo.pTexture);	//�S������
	chapter_sprite_dodge.Draw(pDevice3D, chapter_texture_dodge.pTexture);	//�h�b�a�{�[��
	chapter_sprite_marker.Draw(pDevice3D, chapter_texture_marker.pTexture);	//�}�[�J�[
}

void Chapter::Load()
{
	//�S�������̕`��
	chapter_texture_onigo.Load(_T("texture/onigokko.png"));
	chapter_sprite_onigo.SetPos(450, 300);
	chapter_sprite_onigo.SetSize(648, 168);

	//�h�b�a�{�[���̕`��
	chapter_texture_dodge.Load(_T("texture/dodgeball.png"));
	chapter_sprite_dodge.SetPos(450, 600);
	chapter_sprite_dodge.SetSize(648, 168);

	//�}�[�J�[
	chapter_texture_marker.Load(_T("texture/ma-ka-.png"));
	chapter_sprite_marker.SetPos(70, y);
	chapter_sprite_marker.SetSize(130, 130);

}