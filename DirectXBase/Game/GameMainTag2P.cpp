#include"GameMainTag2P.h"

//�R���X�g���N�^
GameMainTag2P::GameMainTag2P()
{

	
	//
	map2P = new Map();
	timeTexture2= new Texture[10];
	//�������Ԃ̉摜�ǂݍ���
	timeTexture2[0].Load("texture/0.png");
	timeTexture2[1].Load("texture/1.png");
	timeTexture2[2].Load("texture/2.png");
	timeTexture2[3].Load("texture/3.png");
	timeTexture2[4].Load("texture/4.png");
	timeTexture2[5].Load("texture/5.png");
	timeTexture2[6].Load("texture/6.png");
	timeTexture2[7].Load("texture/7.png");
	timeTexture2[8].Load("texture/8.png");
	timeTexture2[9].Load("texture/9.png");
	//�������Ԃ̓ǂݍ���
	timeSprite2 = new Sprite[2];
	timeSprite2[0].SetPos(910, 100);
	timeSprite2[0].SetSize(128, 128);
	timeSprite2[1].SetPos(850, 100);
	timeSprite2[1].SetSize(128, 128);
	//�v���C���[�̓ǂݍ���
	player = new Player[2];
	//�J�����̓ǂݍ���
	camera1 = new Camera[2];
	camera1[0].Camera2P();
	camera1[1].Camera2P();
	//�G�̓ǂݍ���
	enemy2 = new Enemy();
	//�������֐��̌Ăяo��
	Init();

	wave[0].Play(false);
	
}

//�f�X�g���N�^
GameMainTag2P::~GameMainTag2P()
{
	//delete map2P;
	delete[] timeTexture2;
	delete[] timeSprite2;
	delete[] player;
	delete[] camera1;
	delete map2P;
}

//������
void GameMainTag2P::Init()
{
	timeframe2 = 0;
	PlayerPos1P.x = 0.0f;
	PlayerPos1P.y = 0.0f;
	PlayerPos1P.z = 0.0f;
	PlayerPos2P.x = 0.0f;
	PlayerPos2P.y = 0.0f;
	PlayerPos2P.z = 00.0f;
	PlayerAngle1P = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	PlayerAngle2P = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pInfo1P.CameraPos1P = D3DXVECTOR3(PlayerPos1P.x, 1.0f, PlayerPos1P.z-3.0f);
	pInfo1P.CameraAngle1P = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pInfo2P.CameraPos2P = D3DXVECTOR3(PlayerPos2P.x, 1.0f, PlayerPos2P.z - 3.0f);
	pInfo2P.CameraAngle2P = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//wav�t�@�C���ǂݍ���
	wave[0].Load(_T("BGM/game.wav"));
	wave[1].Load(_T("BGM/z_taoreru.wav"));
}

//�A�b�v�f�[�g
void GameMainTag2P::Update()
{
	//�r���[�|�[�g�̍쐬
	camera1[0].Camera1PUpdate();
	//�}�b�v�̃����_�[
	map2P->MapRender();
	//�PP�̍쐬
	player[0].PlayerCreate(PlayerPos1P, PlayerAngle1P);
	//�G�̏��̍X�V
	enemy2->Update(PlayerPos1P);
	//�G�̕`��
	enemy2->Draw();
	//1P�̃A���O���ƃ|�W�V�����ړ�
	PlayerAngle1P = player[0].PlayerCameraMove(PlayerAngle1P);
	PlayerPos1P = player[0].PlayerMove(PlayerPos1P, PlayerAngle1P);
	//�J�����̈ړ�
	pInfo1P.CameraPos1P.x = PlayerPos1P.x - (3.0f*sinf(PlayerAngle1P.y));
	pInfo1P.CameraPos1P.z = PlayerPos1P.z - (3.0f*cosf(PlayerAngle1P.y));
	//�B�e
	camera1[1].View2P(pInfo2P.CameraPos2P, PlayerAngle2P);


	//�r���[�|�[�g�̍쐬
	camera1[1].Camera2PUpdate();
	map2P->MapRender();

	player[1].PlayerCreate2P(PlayerPos2P, PlayerAngle2P);
	//�G�̏��̍X�V
	enemy2->Update(PlayerPos2P);
	//�G�̕`��
	enemy2->Draw();

	PlayerAngle2P = player[1].PlayerCameraMove2P(PlayerAngle2P);
	PlayerPos2P = player[1].PlayerMove2P(PlayerPos2P, PlayerAngle2P);
	pInfo2P.CameraPos2P.x = PlayerPos2P.x - (3.0f*sinf(PlayerAngle2P.y));
	pInfo2P.CameraPos2P.z = PlayerPos2P.z - (3.0f*cosf(PlayerAngle2P.y));

	camera1[0].View1P(pInfo1P.CameraPos1P, PlayerAngle1P);
	
	
	if (player[1].Hit == true && player[0].Hit == true)
	{
		wave[0].Stop();
		camera1[0].SetViewPort(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		delete scenechange;
		scenechange = new Gameover();
	}
	//�^�C�����X�O�b�o�߂����Ƃ�
	if (tentime2 == 0 && onetime2 == 0 && (player[0].Hit == false || player[1].Hit == false))
	{
		wave[0].Stop();
		delete scenechange;
		scenechange = new CResult();
	}
	//��������
	if (timeframe2 >= 60)
	{
		if (onetime2 == 0)
		{
			onetime2 = 9;
			tentime2--;
		}
		else
		{
			onetime2--;
		}
		timeframe2 = 0;

	}
	timeframe2++;
}

//�`��
void GameMainTag2P::Draw()
{
	
	//�������Ԃ̕`��
	timeSprite2[0].Draw(pDevice3D, timeTexture2[onetime2].GetTexture());
	timeSprite2[1].Draw(pDevice3D, timeTexture2[tentime2].GetTexture());

}