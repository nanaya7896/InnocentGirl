#include"GameOver.h"

//�R���X�g���N�^
Gameover::Gameover()
{
	Load();
}

//�f�X�g���N�^
Gameover::~Gameover()
{
	//���I�ȃ������m�ۂȂǂ��Ȃ��̂łȂ�
}

//�C���X�^���X�̏�����
void Gameover::Load()
{
	//�e�N�X�`���@�X�v���C�g�̏���

	gameover1.Load(_T("Texture/gameover1.png"));      //�摜�i�Q�[���I�[�o�[�P�j�̓ǂݍ���
	gameover2.Load(_T("Texture/gameover2.png"));      //�摜�i�Q�[���I�[�o�[�Q�j�̓ǂݍ���
	gameover3.Load(_T("Texture/gameover3.png"));      //�摜�i�Q�[���I�[�o�[�R�j�̓ǂݍ���
	gameover4.Load(_T("Texture/gameover4.png"));      //�摜�i�Q�[���I�[�o�[�S�j�̓ǂݍ���

	gameoverSprite1.SetSize(GAMEOVER1_SPRITE_SIZE_X, GAMEOVER1_SPRITE_SIZE_Y);//�X�v���C�g�̃T�C�Y�ݒ�
	gameoverSprite2.SetSize(GAMEOVER2_SPRITE_SIZE_X, GAMEOVER2_SPRITE_SIZE_Y);//�X�v���C�g�̃T�C�Y�ݒ�
	gameoverSprite3.SetSize(GAMEOVER3_SPRITE_SIZE_X, GAMEOVER3_SPRITE_SIZE_Y);//�X�v���C�g�̃T�C�Y�ݒ�
	gameoverSprite4.SetSize(GAMEOVER4_SPRITE_SIZE_X, GAMEOVER4_SPRITE_SIZE_Y);//�X�v���C�g�̃T�C�Y�ݒ�
}
//�Q�[���̏�����
//�Q�[���J�n�̍ۂɍs������
void Gameover::Update()
{
	if (DirectInput::GetInstance().KeyDown(DIK_RETURN))
	{
		delete scenechange;
		scenechange = new Title();
	}
}

void Gameover::Draw()
{
	gameoverSprite1.SetPos(GAMEOVER1_SPRITE_POS_X, GAMEOVER1_SPRITE_POS_Y);
	gameoverSprite1.Draw(pDevice3D, gameover1.pTexture, false);

	gameoverSprite2.SetPos(GAMEOVER2_SPRITE_POS_X, GAMEOVER2_SPRITE_POS_Y);
	gameoverSprite2.Draw(pDevice3D, gameover2.pTexture);

	gameoverSprite3.SetPos(GAMEOVER3_SPRITE_POS_X, GAMEOVER3_SPRITE_POS_Y);
	gameoverSprite3.Draw(pDevice3D, gameover3.pTexture);

	gameoverSprite4.SetPos(GAMEOVER4_SPRITE_POS_X, GAMEOVER4_SPRITE_POS_Y);
	gameoverSprite4.Draw(pDevice3D, gameover4.pTexture);


}
