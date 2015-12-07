#include"GameMainDog.h"

//D3DXVECTOR3 viewVecE(0.0f, 0.5f, -1.5f);


//コンストラクタ
GameMainDodge::GameMainDodge(ISceneChanger *changer) : BaseScene(changer)
{
	d_PlayerPos.x = 0.0f;
	d_PlayerPos.y = 0.0f;
	d_PlayerPos.z = 0.0f;
	d_PlayerAngle.x = 0.0f;
	d_PlayerAngle.y = 0.0f;
	d_PlayerAngle.z = 0.0f;
	d_PlayerSpeed.x = 0.0f;
	d_PlayerSpeed.y = 0.0f;
	d_PlayerSpeed.z = 0.0f;
	//ボールのポジション
	BallPos.x = 0.0f;
	BallPos.y = 1.0f;
	BallPos.z = 0.0f;
	Ballthrow = false;
	time = 90;
	timeframe = 0;

	camera = new Camera();
	CameraPosition = D3DXVECTOR3(d_PlayerPos.x, d_PlayerPos.y+1.0f, d_PlayerPos.z - 5.0f);
}

//デストラクタ
GameMainDodge::~GameMainDodge()
{
	delete camera;
	
}

void GameMainDodge::Initialize()
{
	mapDog1P.LoadBuldings();

	ball.BallLoad();
	//wavファイル読み込み
	wave[0].Load(_T("BGM/game.wav"));
	wave[1].Load(_T("BGM/z_taoreru.wav"));
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
	timeSprite[0].SetPos(830, 100);
	timeSprite[0].SetSize(128, 128);
	//10の位
	timeSprite[1].SetPos(770, 100);
	timeSprite[1].SetSize(128, 128);
	Dog_Enemy.Initialize();
	Dog_Enemy.Draw();
	wave[0].Play(false);
}

void GameMainDodge::Finalize()
{

}

void GameMainDodge::Update()
{
	d_PlayerAngle = d_player.PlayerCameraMove(d_PlayerAngle);
	d_PlayerPos = d_player.PlayerMove(d_PlayerPos, d_PlayerAngle);

	CameraPosition.x = d_PlayerPos.x - (5.0f*sinf(d_PlayerAngle.y));
	CameraPosition.z = d_PlayerPos.z - (5.0f*cosf(d_PlayerAngle.y));


	camera->View(CameraPosition, d_PlayerAngle);
	
	//敵の移動判定とかのアップデート
	Dog_Enemy.Update(d_PlayerPos);
	
	//制限時間管理用フレーム
	timeframe++;
	//敵にぶつかったときの処理
	if (d_player.Hit == true)
	{
		wave[0].Stop();
		mSceneChanger->ChangeScene(eScene_GameOver);
	}
	//タイムが９０秒経過したとき
	if (tentime == 0 && onetime == 0 && d_player.Hit == false)
	{
		wave[0].Stop();
		mSceneChanger->ChangeScene(eScene_Result);
	}
	//ボールの処理
	//ぞしZキーが押されたら
	if (DirectInput::GetInstance().KeyDown(DIK_Z))
	{
		//ボールのポジションに現在のポジションを入れる
		BallPos += d_PlayerPos;
		Ballthrow = true;

	}
	if (Ballthrow == true)
	{
		ball.BallCreate(BallPos);
		BallPos = ball.BallMove(BallPos, d_PlayerPos, d_PlayerAngle);
	}

	Dog_Enemy.EnemyDown(BallPos);

	if (DirectInput::GetInstance().KeyDown(DIK_P))
	{
		Ballthrow = false;
		BallPos.x = 0.0f;
		BallPos.y = 1.0f;
		BallPos.z = 0.0f;
		BallPos=ball.Init(BallPos);
	
	}

	

}

void GameMainDodge::Draw()
{
	//ball.BallCreate(BallPos);
	mapDog1P.MapRender();
	
	d_player.PlayerCreate(d_PlayerPos, d_PlayerAngle);
	Dog_Enemy.Draw();
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




