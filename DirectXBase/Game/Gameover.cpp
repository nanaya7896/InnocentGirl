#include"GameOver.h"

//�R���X�g���N�^
Gameover::Gameover(ISceneChanger* changer)
	:BaseScene(changer),go_marker_flag(false)
{
	//wave[0].Play(true);
}

//�f�X�g���N�^
Gameover::~Gameover()
{

	//���I�ȃ������m�ۂȂǂ��Ȃ��̂łȂ�
}

//�e�N�X�`���̃��[�h

//�Q�[���̏�����
//�Q�[���J�n�̍ۂɍs������
void Gameover::Initialize()
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
	dGScore.Create(pDevice3D, 32);
	//wav�t�@�C���ǂݍ���
	/*wave[0].Load(_T("BGM/gameover.wav"));
	wave[1].Load(_T("BGM/kettei.wav"));
	wave[2].Load(_T("BGM/ka-soruidou.wav"));
*/
}

void Gameover::Finalize()
{

}

void Gameover::Update()
{
	gInput.checkControllers();
	gInput.readControllers();
	//�₶�邵�ړ�
	//�E
	if (gInput.getGamepadThumbLX(0)>0 ||  DirectInput::GetInstance().KeyDown(DIK_RIGHT))
	{
		//wave[2].Play(false);
		go_marker_flag = true;
	}
	//��
	if (gInput.getGamepadThumbLX(0)<0|| DirectInput::GetInstance().KeyDown(DIK_LEFT))
	{
		//wave[2].Play(false);
		go_marker_flag = false;
	}

	//��ʑJ��
	//���g���C
	if ((gInput.getGamepadB(0) || DirectInput::GetInstance().KeyDown(DIK_RETURN)) && go_marker_flag == false)
	{
		/*wave[0].Stop();
		wave[1].Play(false);*/
		mSceneChanger->ChangeScene(eScene_GameMainTag1P);
		return;
	}
	//�`���v�^�[��
	if ((gInput.getGamepadB(0) || DirectInput::GetInstance().KeyDown(DIK_RETURN)) && go_marker_flag == true)
	{
		/*wave[0].Stop();
		wave[1].Play(false);*/
		mSceneChanger->ChangeScene(eScene_Chapter);
		return;
	}
	//���ۂɃX�R�A���󂯎��
	//a = Gscore.score1P();
}

void Gameover::Draw()
{
	//dGScore.Draw(D3DXCOLOR(10, 255, 255, 255), 10, 100, "%d", a);
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
