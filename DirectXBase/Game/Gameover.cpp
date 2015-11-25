#include"GameOver.h"

//�R���X�g���N�^
Gameover::Gameover()
	:go_marker_flag(false)
{
	Load();
	wave[0].Play(true);
}

//�f�X�g���N�^
Gameover::~Gameover()
{
	//���I�ȃ������m�ۂȂǂ��Ȃ��̂łȂ�
}

//�e�N�X�`���̃��[�h
void Gameover::Load()
{

	//�w�i
	gameover1.Load(_T("Texture/gameover1.png"));      //�摜�i�Q�[���I�[�o�[�P�j�̓ǂݍ���
	gameoverSprite1.SetSize(GAMEOVER1_SPRITE_SIZE_X, GAMEOVER1_SPRITE_SIZE_Y);
	gameoverSprite1.SetPos(GAMEOVER1_SPRITE_POS_X, GAMEOVER1_SPRITE_POS_Y);

	//�₶�邵
	gameover2.Load(_T("Texture/gameover2.png"));      //�摜�i�Q�[���I�[�o�[�Q�j�̓ǂݍ���
	gameoverSprite2[!go_marker_flag].SetSize(GAMEOVER2_SPRITE_SIZE_X, GAMEOVER2_SPRITE_SIZE_Y);
	gameoverSprite2[!go_marker_flag].SetPos(GAMEOVER2_SPRITE_POS_X, GAMEOVER2_SPRITE_POS_Y);
	gameoverSprite2[go_marker_flag].SetSize(GAMEOVER2_SPRITE_SIZE_X, GAMEOVER2_SPRITE_SIZE_Y);
	gameoverSprite2[go_marker_flag].SetPos(GAMEOVER2_SPRITE_POS_X + 430, GAMEOVER2_SPRITE_POS_Y);

	//����
	//���g���C
	gameover3.Load(_T("Texture/gameover3.png"));      //�摜�i�Q�[���I�[�o�[�R�j�̓ǂݍ���
	gameoverSprite3.SetSize(GAMEOVER3_SPRITE_SIZE_X, GAMEOVER3_SPRITE_SIZE_Y);
	gameoverSprite3.SetPos(GAMEOVER3_SPRITE_POS_X, GAMEOVER3_SPRITE_POS_Y);
	//����Ղ��[��
	gameover4.Load(_T("Texture/gameover4.png"));
	gameoverSprite4.SetSize(GAMEOVER4_SPRITE_SIZE_X, GAMEOVER4_SPRITE_SIZE_Y);
	gameoverSprite4.SetPos(GAMEOVER4_SPRITE_POS_X, GAMEOVER4_SPRITE_POS_Y);

	//wav�t�@�C���ǂݍ���
	wave[0].Load(_T("BGM/gameover.wav"));
	wave[1].Load(_T("BGM/kettei.wav"));
	wave[2].Load(_T("BGM/ka-soruidou.wav"));

}
//�Q�[���̏�����
//�Q�[���J�n�̍ۂɍs������
void Gameover::Update()
{
	//�₶�邵�ړ�
	//�E
	if (DirectInput::GetInstance().KeyDown(DIK_RIGHT))
	{
		wave[2].Play(false);
		go_marker_flag = true;
	}
	//��
	if (DirectInput::GetInstance().KeyDown(DIK_LEFT))
	{
		wave[2].Play(false);
		go_marker_flag = false;
	}

	//��ʑJ��
	//���g���C
	if (DirectInput::GetInstance().KeyDown(DIK_RETURN) && go_marker_flag == false)
	{
		wave[0].Stop();
		wave[1].Play(false);
		delete scenechange;
		scenechange = new GameMainTag();
		return;
	}
	//�`���v�^�[��
	if (DirectInput::GetInstance().KeyDown(DIK_RETURN) && go_marker_flag == true)
	{
		wave[0].Stop();
		wave[1].Play(false);

		delete scenechange;
		scenechange = new Chapter();
		return;
	}

}

void Gameover::Draw()
{
	//�₶�邵
	gameoverSprite2[!go_marker_flag].Draw(pDevice3D, gameover2.pTexture);

	//����
	//���g���C
	gameoverSprite3.Draw(pDevice3D, gameover3.pTexture);
	//�`���v�^�[��
	gameoverSprite4.Draw(pDevice3D, gameover4.pTexture);

	//�w�i
	gameoverSprite1.Draw(pDevice3D, gameover1.pTexture, false);

}
