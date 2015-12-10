#include"GameMainTag.h"
D3DXVECTOR3 viewVecE(0.0f, 0.5f, -1.5f);

using namespace std;
extern int SceneRetry;

//コンストラクタ
GameMainTag::GameMainTag(ISceneChanger *changer) : BaseScene(changer)
{


	
}

//デストラクタ
GameMainTag::~GameMainTag()
{
	delete camera;
	
}

void GameMainTag::Initialize()
{
	PlayerPos.x = 0.0f;
	PlayerPos.y = 0.0f;
	PlayerPos.z = 0.0f;
	PlayerAngle.x = 0.0f;
	PlayerAngle.y = 0.0f;
	PlayerAngle.z = 0.0f;
	PlayerSpeed.x = 0.0f;
	PlayerSpeed.y = 0.0f;
	PlayerSpeed.z = 0.0f;
	time = 60;
	timeframe = 0;

	camera = new Camera();
	CameraPosition = D3DXVECTOR3(PlayerPos.x, PlayerPos.y + 1.0f, PlayerPos.z - 5.0f);
	player.Hit = false;
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

	//wavファイル読み込み
	wave[0].Load(_T("BGM/game.wav"));
	wave[1].Load(_T("BGM/z_taoreru.wav"));

	//スコア
	score1.Create(pDevice3D, 32);
	score2.Create(pDevice3D, 32);
	wave[0].Play(false);

	
	//スタミナ
	//文字
	//Stamina_bar.Load(_T("texture/stm.png"));
	//白
	Stamina_W.Load(_T("texture/sts.png"));
	sStamina_W.SetPos(1000, 100);
	sStamina_W.SetSize(360, 64);
	//黄
	Stamina_Y.Load(_T("texture/stk.png"));
	sStamina_Y.SetPos(1000, 100);
	//スタミナを初期値を最大値に設定
	currentStamina = MAX_STAMINA;
	//DirectInput::GetInstance().Init();
	gmtEnemy.Initialize();
	gmtEnemy.Draw();
	map1P.LoadBuldings();
}

void GameMainTag::Finalize()
{



}


void GameMainTag::Update()
{
	//現在のスタミナを求める関数
	currentStamina = sta(currentStamina);
	//プレイヤーのポジションを決める関数
	PlayerPos=player.PlayerMove(PlayerPos,PlayerAngle);
	
	//プレイヤーが向きを変える関数
	PlayerAngle = player.PlayerCameraMove(PlayerAngle);
	//カメラをプレイヤー中心に回す
	CameraPosition.x = PlayerPos.x - (5.0f*sinf(PlayerAngle.y));
	CameraPosition.z = PlayerPos.z - (5.0f*cosf(PlayerAngle.y));
	//カメラの視点更新
	camera[0].View(CameraPosition, PlayerAngle);

	//敵の移動判定とかのアップデート
	gmtEnemy.Update(PlayerPos);
	//制限時間管理用フレーム
	timeframe++;
	//敵にぶつかったときの処理
	if (player.Hit == true)
	{
		wave[0].Stop();
		mSceneChanger->ChangeScene(eScene_GameOver);
		SceneRetry = 0;
		return;
	}
	//タイムが９０秒経過したとき
	if (tentime == 0 && onetime == 0 && player.Hit==false)
	{
		wave[0].Stop();
		mSceneChanger->ChangeScene(eScene_Result);
		return;
	}
	//スコア保持用関数にアクセス
	Score1p=gmtEnemy.score1P();
	Score2p = gmtEnemy.score2P();

	
	//現在のスタミナが上限か下限か確かめる関数
	currentStamina = sta_clamp(currentStamina, LOS_STAMINA, MAX_STAMINA);
}

void GameMainTag::Draw()
{

	
	map1P.MapRender();
	player.PlayerCreate(PlayerPos,PlayerAngle);
	//黄
	
	sStamina_Y.SetSize(currentStamina, 64);
	sStamina_Y.Draw_Stamina(pDevice3D, Stamina_Y.pTexture);
	//白
	sStamina_W.Draw_Stamina(pDevice3D, Stamina_W.pTexture);

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

	//score1.Draw(D3DXCOLOR(10.0f, 255.0f, 255.0f, 255.0f), 10, 10, "%d", Score1p);
	//score1.Draw(D3DXCOLOR(10.0f, 255.0f, 255.0f, 255.0f), 100, 10, "%d", Score2p);
}


int GameMainTag::sta(int currentstamina)
{
	return (DirectInput::GetInstance().KeyDown(DIK_F) || DirectInput::GetInstance().KeyState(DIK_F) )? currentStamina-2 : currentStamina+2;
}

int GameMainTag::sta_clamp(int currentstamina, int low, int high)
{
	assert(low <= high);
	
	return min(max(currentstamina,low),high);

}