#include"GameMainTag.h"
D3DXVECTOR3 viewVecE(0.0f, 0.5f, -1.5f);
D3DXVECTOR3 viewVecL(0.0f, 0.0f, 0.0f);

//コンストラクタ
GameMainTag::GameMainTag()
{
	PlayerPos.x = 0.0f;
	PlayerPos.y = 1.0f;
	PlayerPos.z = 0.0f;
	PlayerAngle.x=0.0f;
	PlayerAngle.y=0.0f;
	PlayerAngle.z=0.0f;
}

//デストラクタ
GameMainTag::~GameMainTag()
{


}

void GameMainTag::Update()
{

	
	PlayerPos=player.PlayerMove(D3DXVECTOR3(PlayerPos.x, PlayerPos.y, PlayerPos.z));
	camera.Create(D3DXVECTOR3(PlayerPos.x + viewVecE.x, PlayerPos.y + viewVecE.y, PlayerPos.z + viewVecE.z), D3DXVECTOR3(PlayerAngle.x + viewVecL.x, PlayerAngle.y + viewVecL.y, PlayerAngle.z + viewVecL.z));
	
}

void GameMainTag::Draw()
{
	player.PlayerCreate(D3DXVECTOR3(PlayerPos.x, PlayerPos.y, PlayerPos.z));

}

void GameMainTag::Load()
{


}