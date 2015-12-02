#pragma once

#include"Task.h"
#include"ISceneChanger.h"
#include"../Direct3D//direct3d.h"
#include"../DirectInput/directInput.h"

//シーンの基底クラス
class BaseScene : public Task
{
protected:
	//クラス所有元にシーン切り替えを伝えるインターフェイス
	ISceneChanger* mSceneChanger;

public:
	BaseScene(ISceneChanger* changer);
	virtual ~BaseScene(){}
	virtual void Initialize() = 0;   //初期化処理をオーバーライド。
	virtual void Finalize() = 0;       //終了処理をオーバーライド。
	virtual void Update() = 0;        //更新処理をオーバーライド。
	virtual void Draw() = 0;            //描画処理をオーバーライド。


};