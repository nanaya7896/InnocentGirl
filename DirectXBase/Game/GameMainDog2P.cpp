#include"GameMainDog2P.h"

//D3DXVECTOR3 viewVecE(0.0f, 0.5f, -1.5f);

extern int SceneRetry;
//コンストラクタ
GameMainDodge2P::GameMainDodge2P(ISceneChanger *changer) : BaseScene(changer)
{
	d_PlayerPos.x = 0.0f;
	d_PlayerPos.y = 0.0f;
	d_PlayerPos.z = 0.0f;
	d_PlayerAngle.x = 0.0f;
	d_PlayerAngle.y = 0.0f;
	d_PlayerAngle.z = 0.0f;
	d_PlayerPos2.x = 0.0f;
	d_PlayerPos2.y = 0.0f;
	d_PlayerPos2.z = 0.0f;
	d_PlayerAngle2.x = 0.0f;
	d_PlayerAngle2.y = 0.0f;
	d_PlayerAngle2.z = 0.0f;
	d_PlayerSpeed.x = 0.0f;
	d_PlayerSpeed.y = 0.0f;
	d_PlayerSpeed.z = 0.0f;
	//ボールのポジション
	BallPos.x = 0.0f;
	BallPos.y = 1.0f;
	BallPos.z = 0.0f;
	BallPos2.x = 0.0f;
	BallPos2.y = 1.0f;
	BallPos2.z = 0.0f;
	Ballthrow = false;
	Ballthrow2 = false;
	time = 90;
	timeframe = 0;
	d_camera = new Camera[2];
	CameraPosition = D3DXVECTOR3(d_PlayerPos.x, d_PlayerPos.y + 1.0f, d_PlayerPos.z - 5.0f);
	CameraPosition2 = D3DXVECTOR3(d_PlayerPos2.x, d_PlayerPos2.y + 1.0f, d_PlayerPos2.z - 5.0f);
	d_camera[0].Camera2P();
	d_camera[1].Camera2P();
}

//デストラクタ
GameMainDodge2P::~GameMainDodge2P()
{
	delete[] d_camera;
}

void GameMainDodge2P::Initialize()
{
	mapDog1P.LoadBuldings();

	d_ball[0].BallLoad();
	d_ball[1].BallLoad();
	//wavファイル読み込み
	wave[0].Load(_T("BGM/game.wav"));
	wave[1].Load(_T("BGM/z_taoreru.wav"));
	dtimeTexture[0].Load("texture/0.png");
	dtimeTexture[1].Load("texture/1.png");
	dtimeTexture[2].Load("texture/2.png");
	dtimeTexture[3].Load("texture/3.png");
	dtimeTexture[4].Load("texture/4.png");
	dtimeTexture[5].Load("texture/5.png");
	dtimeTexture[6].Load("texture/6.png");
	dtimeTexture[7].Load("texture/7.png");
	dtimeTexture[8].Load("texture/8.png");
	dtimeTexture[9].Load("texture/9.png");
	dtimeSprite[0].SetPos(910, 100);
	dtimeSprite[0].SetSize(128, 128);
	dtimeSprite[1].SetPos(850, 100);
	dtimeSprite[1].SetSize(128, 128);
	Dog_Enemy.Initialize();
	Dog_Enemy.Draw();
	wave[0].Play(false);
}

void GameMainDodge2P::Finalize()
{

}

void GameMainDodge2P::Update()
{

	//ビューポートの作成
	d_camera[0].Camera1PUpdate();
	//マップのレンダー
	mapDog1P.MapRender();
	//１Pの作成
	d_player[0].PlayerCreate(d_PlayerPos, d_PlayerAngle);
	//敵の情報の更新
	Dog_Enemy.Update(d_PlayerPos);
	//敵の描画
	Dog_Enemy.Draw();
	d_PlayerAngle = d_player[0].PlayerCameraMove(d_PlayerAngle);
	d_PlayerPos = d_player[0].PlayerMove(d_PlayerPos, d_PlayerAngle);

	CameraPosition.x = d_PlayerPos.x - (5.0f*sinf(d_PlayerAngle.y));
	CameraPosition.z = d_PlayerPos.z - (5.0f*cosf(d_PlayerAngle.y));
	if (DirectInput::GetInstance().KeyDown(DIK_Z))
	{
		//ボールのポジションに現在のポジションを入れる
		BallPos += d_PlayerPos;
		Ballthrow = true;
	}
	if (Ballthrow == true)
	{
		d_ball[1].BallCreate(BallPos);
		BallPos = d_ball[1].BallMove(BallPos, d_PlayerPos, d_PlayerAngle);
	}
	if (DirectInput::GetInstance().KeyDown(DIK_X))
	{
		Ballthrow = false;
		BallPos.x = 0.0f;
		BallPos.y = 1.0f;
		BallPos.z = 0.0f;
		BallPos = d_ball[0].Init(BallPos);

	}

	d_camera[0].View1P(CameraPosition, d_PlayerAngle);

	//ビューポートの作成
	d_camera[1].Camera2PUpdate();
	mapDog1P.MapRender();

	d_player[1].PlayerCreate2P(d_PlayerPos2, d_PlayerAngle2);
	d_PlayerAngle2 = d_player[1].PlayerCameraMove2P(d_PlayerAngle2);
	d_PlayerPos2 = d_player[1].PlayerMove2P(d_PlayerPos2, d_PlayerAngle2);
	//敵の移動判定とかのアップデート
	Dog_Enemy.Update(d_PlayerPos2);


	//制限時間管理用フレーム
	timeframe++;
	//敵にぶつかったときもしくはタイムが９０秒経過したときの処理
	if ((d_player[0].Hit == true && d_player[1].Hit == true) || (tentime == 0 && onetime == 0 && d_player[0].Hit == false && d_player[1].Hit == false))
	{
		SceneRetry = 3;
		wave[0].Stop();
		mSceneChanger->ChangeScene(eScene_GameOver);
	}

	if (Dog_Enemy.EnemyDestroyCount == 30)
	{
		wave[0].Stop();
		mSceneChanger->ChangeScene(eScene_Result);
	}
	//ボールの処理
	//ぞしZキーが押されたら
	if (DirectInput::GetInstance().KeyDown(DIK_M))
	{
		//ボールのポジションに現在のポジションを入れる
		BallPos2 += d_PlayerPos2;
		Ballthrow2 = true;
	}
	if (Ballthrow2 == true)
	{
		d_ball[1].BallCreate(BallPos2);
		BallPos2 = d_ball[1].BallMove(BallPos2, d_PlayerPos2, d_PlayerAngle2);
	}

	Dog_Enemy.EnemyDown(BallPos2);

	if (DirectInput::GetInstance().KeyDown(DIK_P))
	{
		Ballthrow = false;
		BallPos2.x = 0.0f;
		BallPos2.y = 1.0f;
		BallPos2.z = 0.0f;
		BallPos2 = d_ball[1].Init(BallPos2);

	}

	d_camera[1].View2P(CameraPosition2, d_PlayerAngle2);


}

void GameMainDodge2P::Draw()
{
	//ball.BallCreate(BallPos);
	//mapDog1P.MapRender();

//	d_player[0].PlayerCreate(d_PlayerPos, d_PlayerAngle);
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
	dtimeSprite[0].Draw(pDevice3D, dtimeTexture[onetime].pTexture);
	dtimeSprite[1].Draw(pDevice3D, dtimeTexture[tentime].pTexture);


}




