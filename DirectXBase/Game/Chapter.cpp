#include"Chapter.h"

//�R���X�g���N�^
Chapter::Chapter(ISceneChanger *changer) : BaseScene(changer)
{
	
}

//�f�X�g���N�^
Chapter::~Chapter()
{
	ContFlag = false;

}

void Chapter::Initialize()
{
	ContFlag = false;
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
	//�X�N�V��
	GameScreen[!chapter_flag].Load(_T("texture/tyaputa-o.png"));
	sGameScreen[!chapter_flag].SetPos(1200, 330);
	sGameScreen[!chapter_flag].SetSize(500, 450);
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
	//�������
	tContTx.Load(_T("texture/sousaonigo.png"));
	sContTx.SetPos(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	sContTx.SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	//�w�i�ǂݍ���
	chapter_bg.Load(_T("texture/taitoru2.png"));
	//�摜�̏ꏊ�w��
	schapter_bg.SetPos(800, 450);
	//�摜�̏c���̃T�C�Y�w��
	schapter_bg.SetSize(1600, 900);
	//WAVE�̓ǂݍ���
	wave[0].Load(_T("BGM/taitoru.wav"));
	wave[1].Load(_T("BGM/kettei.wav"));
	wave[2].Load(_T("BGM/ka-soruidou.wav"));
	wave[0].Play(false);
}

void Chapter::Finalize()
{


}

void Chapter::Update()
{
	//�f�o�b�O�p
	//std::complex<double> cmp=pJoypad->getLStick(0.1);

	chaInput.checkControllers();

	chaInput.readControllers();
	//�S�������I��
	if (chaInput.getGamepadThumbLY(0)>0|| DirectInput::GetInstance().KeyDown(DIK_UP))
	{
		wave[2].Play(false);
		marker_flag = false;
		chapter_flag = false;
	}
	//�h�b�a�I��
	if (chaInput.getGamepadThumbLY(0)<0|| DirectInput::GetInstance().KeyDown(DIK_DOWN))
	{
		wave[2].Play(false);
		marker_flag = true;
		chapter_flag = true;
	}

	//�Ƃ������ƑI��
	if (chaInput.getGamepadThumbLX(0)>0|| DirectInput::GetInstance().KeyDown(DIK_RIGHT))
	{
		wave[2].Play(false);
		member_flag = true;

	}
	//�ЂƂ�I��
	if (chaInput.getGamepadThumbLX(0)<0|| DirectInput::GetInstance().KeyDown(DIK_LEFT))
	{
		wave[2].Play(false);
		member_flag = false;
	}


	
	//GameMain���ɂ������ЂƂ�v���C�ɉ�ʑJ��
	if (chaInput.getGamepadB(0)|| DirectInput::GetInstance().KeyDown(DIK_RETURN))
	{
		ContFlag = true;
	}
	if (ContFlag == true)
	{
		sContTx.Draw(pDevice3D, tContTx.GetTexture());
		//GameMain���ɂ������ЂƂ�v���C�ɉ�ʑJ��
		if ((chaInput.getGamepadStart(0)|| DirectInput::GetInstance().KeyDown(DIK_SPACE)) && chapter_flag == false && member_flag == false)
		{
			wave[0].Stop();
			wave[1].Play(false);
			mSceneChanger->ChangeScene(eScene_GameMainTag1P);
			return;
		}
		//GameMain���ɂ������Ƃ������ƃv���C�ɉ�ʑJ��

		if ((chaInput.getGamepadStart(0) || DirectInput::GetInstance().KeyDown(DIK_SPACE)) && chapter_flag == false && member_flag == true)
		{
			//sContTx.Draw(pDevice3D, tContTx.GetTexture());
			wave[0].Stop();
			wave[1].Play(false);
			mSceneChanger->ChangeScene(eScene_GameMainTag2P);
			return;
		}
		//GameMain�h�b�a�{�[���ЂƂ�v���C�ɉ�ʑJ��
		if ((chaInput.getGamepadStart(0) || DirectInput::GetInstance().KeyDown(DIK_SPACE)) && chapter_flag == true && member_flag == false)
		{
			wave[0].Stop();
			wave[1].Play(false);
			mSceneChanger->ChangeScene(eScene_GameMainDodge1P);
			return;
		}
		//GameMain�h�b�a�{�[���ЂƂ�v���C�ɉ�ʑJ��
		if ((chaInput.getGamepadStart(0) || DirectInput::GetInstance().KeyDown(DIK_SPACE)) && chapter_flag == true && member_flag == true)
		{
			wave[0].Stop();
			wave[1].Play(false);
			mSceneChanger->ChangeScene(eScene_GameMainDodge2P);
			return;
		}
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
	//�X�N�V��
	sGameScreen[!chapter_flag].Draw(pDevice3D, GameScreen[!chapter_flag].pTexture);
	//�w�i
	schapter_bg.Draw(pDevice3D, chapter_bg.pTexture);
}

