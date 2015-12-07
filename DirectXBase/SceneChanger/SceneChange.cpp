#include "../Game//Title.h"
#include "../Game/Chapter.h"
#include"../Game/GameMainTag.h"
#include"../Game/GameMainTag2P.h"
#include"../Game/Gameover.h"
#include"../Game/Result.h"
#include "SceneChange.h"
#include "../Direct3D/direct3d.h"
#include "../DirectInput/directinput.h"
#include"../Game/GameMainDog.h"
SceneChange::SceneChange() : mNextScene(eScene_None) //次のシーンの管理変数
{
	mScene = (BaseScene*) new Title(this);
}

//初期化
void SceneChange::Initialize()
{
	mScene->Initialize();
}

//終了処理
void SceneChange::Finalize()
{
	mScene->Finalize();
}

//更新
void SceneChange::Update()
{
	if (mNextScene != eScene_None)
	{
		//次のシーンがセットされていたら
		mScene->Finalize(); //終了処理の実行
		delete mScene;
		switch (mNextScene)
		{
			//シーンをswitchで分岐
		case eScene_Title:
			mScene = (BaseScene*) new Title(this);
			break;
		case eScene_Chapter :
			mScene = (BaseScene*) new Chapter(this);
			break;
		case eScene_GameMainTag1P :
			mScene = (BaseScene*) new GameMainTag(this);
			break;
		case eScene_GameMainTag2P :
			mScene = (BaseScene*) new GameMainTag2P(this);
			break;
		case eScene_GameMainDodge1P :
			mScene = (BaseScene*) new GameMainDodge(this);
			break;
			//case eScene_GameMainDodge2P :
			//	mScene = (BaseScene*) new GameMainDodge2P(this);
			//break;
		case eScene_Result :
			mScene = (BaseScene*) new CResult(this);

		case eScene_GameOver :
			mScene = (BaseScene*) new Gameover(this);
		}
		//次のシーンの情報をクリア
		mNextScene = eScene_None;
		//シーンを初期化
		mScene->Initialize();
	}
	//シーンの更新
	mScene->Update();

}

//描画
void SceneChange::Draw()
{
	//シーンの描画
	mScene->Draw();
}

//引数nextSceneに変更する
void SceneChange::ChangeScene(eScene NextScene)
{
	//次のシーンをセットする
	mNextScene = NextScene;
}

void SceneChange::DELETESCENELAST()
{
	if (mScene != NULL)
	{
		delete mScene;
	}
}