#include"GameMainTag.h"
D3DXVECTOR3 viewVecE(0.0f, 0.5f, -1.5f);


//コンストラクタ
GameMainTag::GameMainTag()
{
	PlayerPos.x = 0.0f;
	PlayerPos.y = 1.0f;
	PlayerPos.z = 0.0f;
	PlayerAngle.x=0.0f;
	PlayerAngle.y=0.0f;
	PlayerAngle.z =0.0f;
	timeText.Create(pDevice3D,64);
	time = 90;
	timeframe = 0;
	Load();
	camera = new Camera();
	CameraPosition = D3DXVECTOR3(PlayerPos.x, PlayerPos.y, PlayerPos.z - 1.5f);
}

//デストラクタ
GameMainTag::~GameMainTag()
{
	delete camera;
}

void GameMainTag::Update()
{

	
	PlayerPos=player.PlayerMove(D3DXVECTOR3(PlayerPos.x, PlayerPos.y, PlayerPos.z));
	PlayerAngle= player.PlayerCameraMove(PlayerAngle);

	CameraPosition.x = PlayerPos.x - 1.5f*sinf(PlayerAngle.y);
	CameraPosition.z = PlayerPos.z - 1.5f*cosf(PlayerAngle.y);


	camera->View(CameraPosition, D3DXVECTOR3(PlayerAngle.x +D3DXToRadian(5), PlayerAngle.y, PlayerAngle.z));
	//制限時間管理用フレーム
	timeframe++;
}

void GameMainTag::Draw()
{

	player.PlayerCreate(D3DXVECTOR3(PlayerPos.x, PlayerPos.y, PlayerPos.z),D3DXVECTOR3(PlayerAngle.x,PlayerAngle.y,PlayerAngle.z));
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

		//カメラの生成
		//camera.Create(D3DXVECTOR3(PlayerPos.x + viewVecE.x, PlayerPos.y + viewVecE.y, PlayerPos.z + viewVecE.z), D3DXVECTOR3(PlayerAngle.x, PlayerAngle.y, PlayerAngle.z));
		
}

HRESULT GameMainTag::Player_HitBox()
{
	/*if ()
	{
		return E_FAIL;
	}*/



	return S_OK;
}