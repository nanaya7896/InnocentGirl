#pragma once

typedef enum{
	eScene_Title,		   		 //タイトル画面
	eScene_Chapter,				 //チャプター画面
	eScene_GameMainTag1P,		 //鬼ごっこ1P
	eScene_GameMainTag2P,		 //鬼ごっこ2P
	eScene_GameMainDodge1P,		 //ドッジボール1P
	eScene_GameMainDodge2P,		 //ドッジボール2P
	eScene_Result,				 //リザルト
	eScene_GameOver, 			 //ゲームオーバー

	eScene_None //無し
}eScene;

//シーンを変更するためのインターフェースクラス
class ISceneChanger
{
public:
	virtual ~ISceneChanger() = 0;
	//指定のシーンに変更する
	virtual void ChangeScene(eScene NextScene) = 0;

private:

};