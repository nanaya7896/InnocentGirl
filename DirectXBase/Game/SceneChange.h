#pragma once
#include"../Global.h"

class SceneChange
{
private:


public:
	//コンストラクタ
	SceneChange();
	//デストラクタ
	~SceneChange();

	//仮想関数(たくさん同じ処理を実行するなら使ってみる)
	virtual void Update()=0;
	virtual void Draw()=0;
	static SceneChange* scenechange;

//派生クラスからなら見ることができる
protected:

	




};