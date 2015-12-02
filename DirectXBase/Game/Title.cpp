#include"Title.h"


//�R���X�g���N�^
Title::Title(ISceneChanger* changer) : BaseScene(changer)
{
	
}

//�f�X�g���N�^
Title::~Title()
{
	
}

void Title::Initialize()
{

	//�w�i�̓ǂݍ���
	title_Background.Load(_T("texture/taitoru.png"));
	//�摜�̏ꏊ�w��
	stitle.SetPos(800, 450);
	//�摜�̏c���̃T�C�Y�w��
	stitle.SetSize(1600, 900);
	//press button�̕`��
	title_bar1.Load(_T("texture/start.png"));
	//�����摜�̕`��
	title_bar2.Load(_T("texture/aho.png"));
	stitle_bar.SetPos(800, 700);
	stitle_bar.SetSize(720, 200);

	TitleBlink = false;
	//wav�t�@�C���ǂݍ���
	wave[0].Load(_T("BGM/taitoru.wav"));
	wave[1].Load(_T("BGM/kettei.wav"));
	wave[0].Play(true);

}

void Title::Finalize()
{


}



void Title::Update()
{
	xboxInput.checkControllers();
	xboxInput.readControllers();
	//press button�̓_�ŏ���
	//�t���[�����Z
	frame++;
	//�����t���[�����R�O�Ŋ���؂ꂽ�ꍇ
	if (frame % 30 == 0)
	{
		//�_��ON/OFF�t���O�𔽓]
		TitleBlink = !TitleBlink;
		//�����t���[����60�𒴂�����
		if (frame >=60)
		{
			//�t���[����������
			frame = 0;
		}
	}
	//�������^�[���L�[�������ꂽ�ꍇ
	if (xboxInput.getGamepadButtons(0)|| DirectInput::GetInstance().KeyDown(DIK_RETURN) == true)
	{

		wave[0].Stop();
		//�r�d�u���艹�v
		wave[1].Play(false);
		//�V�[�����`���v�^�[�֕ύX
		mSceneChanger->ChangeScene(eScene_Chapter);
	}

}

//�^�C�g�����
void Title::Draw()
{
	


	if (TitleBlink==true)
	{
		//�^�C�g���`�揈��
		stitle_bar.Draw(pDevice3D,title_bar1.GetTexture());
	}
	else if(TitleBlink==false)
	{
		//�^�C�g���ɔ����摜���d�˂�
		stitle_bar.Draw(pDevice3D,title_bar2.GetTexture());
	}
	//�w�i�̕`��
	stitle.Draw(pDevice3D, title_Background.pTexture);
	

}

