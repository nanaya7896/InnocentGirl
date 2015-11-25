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
	//�f�o�b�O�p
	//std::complex<double> cmp=pJoypad->getLStick(0.1);

	//�S�������I��
	if (pJoypad->getLStick(0.1).imag() >= 0.5 || DirectInput::GetInstance().KeyDown(DIK_UP))
	{
		marker_flag = false;
		chapter_flag = false;
	}
	//�h�b�a�I��
	if (pJoypad->getLStick(0.1).imag() <= -0.5 || DirectInput::GetInstance().KeyDown(DIK_DOWN))
	{
		marker_flag = true;
		chapter_flag = true;
	}

	//�Ƃ������ƑI��
	if (pJoypad->getLStick(0.1).real() >= 0.5 || DirectInput::GetInstance().KeyDown(DIK_RIGHT))
	{
		member_flag = true;
	}
	//�ЂƂ�I��
	if (pJoypad->getLStick(0.1).real() <= -0.5 || DirectInput::GetInstance().KeyDown(DIK_LEFT))
	{
		member_flag = false;
	}


	//GameMain���ɂ������ЂƂ�v���C�ɉ�ʑJ��
	if (pJoypad->isPushed(Joypad::Button::B) == true || DirectInput::GetInstance().KeyDown(DIK_RETURN) && chapter_flag == false && member_flag == false)
	{
		delete scenechange;
		scenechange = new GameMainTag();		//���ɂ������ЂƂ�v���C
		return;
	}
	//GameMain���ɂ������Ƃ������ƃv���C�ɉ�ʑJ��

	if (pJoypad->isPushed(Joypad::Button::B) == true || DirectInput::GetInstance().KeyDown(DIK_RETURN) && chapter_flag == false && member_flag == true)
	{
		delete scenechange;
		scenechange = new GameMainTag2P();		//���ɂ������Ƃ������ƃv���C
		return;
	}

}

void Chapter::Draw()
{
	//�}�[�J�[
	smarker[!marker_flag].Draw(pDevice3D, marker.pTexture);
	//���ɂ�����
	schapter_onigo.Draw(pDevice3D, chapter_onigo.pTexture);
	//�h�b�a�{�[��
	schapter_dodge.Draw(pDevice3D, chapter_dodge.pTexture);
	//�ЂƂ�
	shitori[!member_flag].Draw(pDevice3D, hitori[!member_flag].pTexture);
	//�ӂ���
	stomodati[!member_flag].Draw(pDevice3D, tomodati[!member_flag].pTexture);
	//�`���v�^�[
	schapter[!chapter_flag].Draw(pDevice3D, chapter[!chapter_flag].pTexture);
	//�w�i
	schapter_bg.Draw(pDevice3D, chapter_bg.pTexture);
}

void Chapter::Load()
{
	//�S�������̕`��
	chapter_onigo.Load(_T("texture/onigokko.png"));
	schapter_onigo.SetPos(450, 300);
	schapter_onigo.SetSize(648, 168);

	//�h�b�a�{�[���̕`��
	chapter_dodge.Load(_T("texture/dodgeball.png"));
	schapter_dodge.SetPos(450, 600);
	schapter_dodge.SetSize(648, 168);

	//�}�[�J�[
	marker.Load(_T("texture/ma-ka-.png"));
	smarker[!marker_flag].SetPos(70, 300);
	smarker[!marker_flag].SetSize(130, 130);
	smarker[marker_flag].SetPos(70, 600);
	smarker[marker_flag].SetSize(130, 130);

	//�`���v�^�[
	chapter[!chapter_flag].Load(_T("texture/chapter_oni.png"));
	schapter[!chapter_flag].SetPos(1200, 430);
	schapter[!chapter_flag].SetSize(700, 850);
	chapter[chapter_flag].Load(_T("texture/chapter_dodge.png"));
	schapter[chapter_flag].SetPos(1200, 430);
	schapter[chapter_flag].SetSize(700, 850);

	//�ЂƂ�
	hitori[member_flag].Load(_T("texture/hitori.png"));
	shitori[member_flag].SetPos(1100, 700);
	shitori[member_flag].SetSize(250, 200);
	hitori[!member_flag].Load(_T("texture/hitori_big.png"));
	shitori[!member_flag].SetPos(1100, 700);
	shitori[!member_flag].SetSize(250, 200);
	//�Ƃ�����
	tomodati[!member_flag].Load(_T("texture/tomodatito.png"));
	stomodati[!member_flag].SetPos(1350, 700);
	stomodati[!member_flag].SetSize(250, 200);
	tomodati[member_flag].Load(_T("texture/tomodatito_big.png"));
	stomodati[member_flag].SetPos(1350, 700);
	stomodati[member_flag].SetSize(250, 200);


	//�w�i�ǂݍ���
	chapter_bg.Load(_T("texture/taitoru2.png"));
	//�摜�̏ꏊ�w��
	schapter_bg.SetPos(800, 450);
	//�摜�̏c���̃T�C�Y�w��
	schapter_bg.SetSize(1600, 900);

}