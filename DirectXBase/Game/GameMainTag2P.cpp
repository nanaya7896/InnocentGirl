#include"GameMainTag2P.h"

//コンストラクタ
GameMainTag2P::GameMainTag2P()
{

	timeframe2 = 0;
	
	map2P = new Map();
	timeTexture2= new Texture[10];
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
	timeSprite2 = new Sprite[2];
	timeSprite2[0].SetPos(910, 100);
	timeSprite2[0].SetSize(128, 128);
	timeSprite2[1].SetPos(850, 100);
	timeSprite2[1].SetSize(128, 128);
	player = new Player[2];
	camera1 = new Camera[2];
	camera1[0].Camera2P();
	camera1[1].Camera2P();
	Init();
	
}

//デストラクタ
GameMainTag2P::~GameMainTag2P()
{
	//delete map2P;
	delete[] timeTexture2;
	delete[] timeSprite2;
	delete[] player;
	delete[] camera1;
}

//初期化
void GameMainTag2P::Init()
{
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

	//camera2P.Camera2P();
	//timeTexture2[0]->Load("texture/0.png");
	//timeTexture2[1]->Load("texture/1.png");
	//timeTexture2[2]->Load("texture/2.png");
	//timeTexture2[3]->Load("texture/3.png");
	//timeTexture2[4]->Load("texture/4.png");
	//timeTexture2[5]->Load("texture/5.png");
	//timeTexture2[6]->Load("texture/6.png");
	//timeTexture2[7]->Load("texture/7.png");
	//timeTexture2[8]->Load("texture/8.png");
	//timeTexture2[9]->Load("texture/9.png");
	////1の位
	//timeSprite2[0]->SetPos(830, 100);
	//timeSprite2[0]->SetSize(128, 128);
	////10の位
	//timeSprite2[1]->SetPos(770, 100);
	//timeSprite2[1]->SetSize(128, 128);
}

//アップデート
void GameMainTag2P::Update()
{
	
	camera1[0].Camera1PUpdate();
	
	map2P->MapRender();
	player[0].PlayerCreate(PlayerPos1P, PlayerAngle1P);

	
	PlayerAngle1P = player[0].PlayerCameraMove(PlayerAngle1P);
	PlayerPos1P = player[0].PlayerMove(PlayerPos1P, PlayerAngle1P);


	pInfo1P.CameraPos1P.x = PlayerPos1P.x - (3.0f*sinf(PlayerAngle1P.y));
	pInfo1P.CameraPos1P.z = PlayerPos1P.z - (3.0f*cosf(PlayerAngle1P.y));
	

	camera1[1].View2P(pInfo2P.CameraPos2P, PlayerAngle2P);
	camera1[1].Camera2PUpdate();
	map2P->MapRender();
	//camera1P.View1P(pInfo1P.CameraPos1P, PlayerAngle1P);
	player[1].PlayerCreate2P(PlayerPos2P, PlayerAngle2P);
	
	PlayerAngle2P = player[1].PlayerCameraMove2P(PlayerAngle2P);
	PlayerPos2P = player[1].PlayerMove2P(PlayerPos2P, PlayerAngle2P);
	pInfo2P.CameraPos2P.x = PlayerPos2P.x - (3.0f*sinf(PlayerAngle2P.y));
	pInfo2P.CameraPos2P.z = PlayerPos2P.z - (3.0f*cosf(PlayerAngle2P.y));

	//	camera1P.Camera1PUpdate();
	

	
	camera1[0].View1P(pInfo1P.CameraPos1P, PlayerAngle1P);
	

//	camera2P.Camera2PUpdate();

	
//	camera2P.View2P(pInfo2P.CameraPos2P, PlayerAngle2P);
	
	

	
	//制限時間
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

//描画
void GameMainTag2P::Draw()
{


	timeSprite2[0].Draw(pDevice3D, timeTexture2[onetime2].GetTexture());
	timeSprite2[1].Draw(pDevice3D, timeTexture2[tentime2].GetTexture());

	
	

}