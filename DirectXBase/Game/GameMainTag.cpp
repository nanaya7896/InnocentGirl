#include"GameMainTag.h"
D3DXVECTOR3 viewVecE(0.0f, 0.5f, -1.5f);


//�R���X�g���N�^
GameMainTag::GameMainTag()
{
	PlayerPos.x = 0.0f;
	PlayerPos.y = 0.5f;
	PlayerPos.z = 0.0f;
	PlayerAngle.x=0.0f;
	PlayerAngle.y=0.0f;
	PlayerAngle.z =0.0f;
	PlayerSpeed.x = 0.0f;
	PlayerSpeed.y = 0.0f;
	PlayerSpeed.z = 0.0f;
	time = 90;
	timeframe = 0;
	map1P = new Map();
	Load();

	camera = new Camera();
	CameraPosition = D3DXVECTOR3(PlayerPos.x, PlayerPos.y, PlayerPos.z - 3.0f);

	wave[0].Play(false);
}

//�f�X�g���N�^
GameMainTag::~GameMainTag()
{
	delete camera;
	delete map1P;
}

void GameMainTag::Update()
{
	PlayerAngle = player.PlayerCameraMove(PlayerAngle);
	PlayerPos=player.PlayerMove(PlayerPos,PlayerAngle);
	
	CameraPosition.x = PlayerPos.x - (3.0f*sinf(PlayerAngle.y));
	CameraPosition.z = PlayerPos.z - (3.0f*cosf(PlayerAngle.y));


	camera->View(CameraPosition, PlayerAngle);
	//�G�̈ړ�����Ƃ��̃A�b�v�f�[�g
	gmtEnemy.Update(PlayerPos);
	//�������ԊǗ��p�t���[��
	timeframe++;
	//�G�ɂԂ������Ƃ��̏���
	if (player.Hit == true)
	{
		delete scenechange;
		scenechange = new Gameover();
	}
	//�^�C�����X�O�b�o�߂����Ƃ�
	if (tentime == 0 && onetime == 0 && player.Hit==false)
	{
		delete scenechange;
		scenechange =new CResult();
	}

	
}

void GameMainTag::Draw()
{
	map1P->MapRender();
	player.PlayerCreate(PlayerPos,PlayerAngle);
	gmtEnemy.Draw();
	//��������
	if (timeframe >= 60)
	{
		if (onetime == 0)
		{
			onetime = 9;
			tentime--;
		}
		else
		{
			onetime--;
		}
		timeframe = 0;
	
	}
	timeSprite[0].Draw(pDevice3D, timeTexture[onetime].pTexture);
	timeSprite[1].Draw(pDevice3D, timeTexture[tentime].pTexture);

	
}

void GameMainTag::Load()
{
		timeTexture[0].Load("texture/0.png");
		timeTexture[1].Load("texture/1.png");
		timeTexture[2].Load("texture/2.png");
		timeTexture[3].Load("texture/3.png");
		timeTexture[4].Load("texture/4.png");
		timeTexture[5].Load("texture/5.png");
		timeTexture[6].Load("texture/6.png");
		timeTexture[7].Load("texture/7.png");
		timeTexture[8].Load("texture/8.png");
		timeTexture[9].Load("texture/9.png");
		//1�̈�
		timeSprite[0].SetPos(830,100);
		timeSprite[0].SetSize(128,128);
		//10�̈�
		timeSprite[1].SetPos(770,100);
		timeSprite[1].SetSize(128,128);

		//wav�t�@�C���ǂݍ���
		wave[0].Load(_T("BGM/game.wav"));
		wave[1].Load(_T("BGM/z_taoreru.wav"));
		
}

