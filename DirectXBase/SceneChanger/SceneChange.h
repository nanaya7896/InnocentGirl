#pragma once

#include "ISceneChanger.h"
#include "BaseScene.h"

class SceneChange : public ISceneChanger,Task
{
public:
	//コンストラクタ
	SceneChange();

	void Initialize() override;//初期化
	void Finalize() override;//終了処理
	void Update() override;//更新
	void Draw() override;//描画

	void DELETESCENELAST();

	// 引数 nextScene にシーンを変更する
	void ChangeScene(eScene NextScene) override;

private:
	//シーン管理変数
	BaseScene* mScene;
	//次のシーンの管理変数
	eScene mNextScene;
	//リトライ時のシーン変更用変数

};