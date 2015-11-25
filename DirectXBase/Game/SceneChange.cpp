#include"SceneChange.h"


SceneChange* SceneChange::scenechange = nullptr;

//コンストラクタ
SceneChange::SceneChange()
{
		pJoypad = new Joypad(0);	
}

//デストラクタ
SceneChange::~SceneChange()
{
	if (pJoypad != NULL)
	{
		delete pJoypad;
	}

}