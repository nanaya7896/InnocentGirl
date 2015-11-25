#include"GameMainTag.h"
D3DXVECTOR3 viewVecE(0.0f, 0.5f, -1.5f);


//コンストラクタ
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

//デストラクタ
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
	//敵の移動判定とかのアップデート
	gmtEnemy.Update(PlayerPos);
	//制限時間管理用フレーム
	timeframe++;
	//敵にぶつかったときの処理
	if (player.Hit == true)
	{
		wave[0].Stop();
		delete scenechange;
		scenechange = new Gameover();
	}
	//タイムが９０秒経過したとき
	if (tentime == 0 && onetime == 0 && player.Hit==false)
	{
		wave[0].Stop();
		delete scenechange;
		scenechange =new CResult();
	}

	
}

void GameMainTag::Draw()
{
	map1P->MapRender();
	player.PlayerCreate(PlayerPos,PlayerAngle);
	gmtEnemy.Draw();
	//制限時間
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
		//1の位
		timeSprite[0].SetPos(830,100);
		timeSprite[0].SetSize(128,128);
		//10の位
		timeSprite[1].SetPos(770,100);
		timeSprite[1].SetSize(128,128);

		//wavファイル読み込み
		wave[0].Load(_T("BGM/game.wav"));
		wave[1].Load(_T("BGM/z_taoreru.wav"));
		
}

