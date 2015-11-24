#include"GameMainTag2P.h"

//コンストラクタ
GameMainTag2P::GameMainTag2P()
{
	Init();
	map2P = new Map();
}

//デストラクタ
GameMainTag2P::~GameMainTag2P()
{
	delete map2P;
}

//初期化
void GameMainTag2P::Init()
{
	camera2P.Camera2P();
	
}

//アップデート
void GameMainTag2P::Update()
{
	camera2P.Camera2PUpdate();
}

//描画
void GameMainTag2P::Draw()
{
	map2P->MapRender();

}