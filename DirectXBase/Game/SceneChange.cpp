#include"SceneChange.h"


SceneChange* SceneChange::scenechange = nullptr;

//�R���X�g���N�^
SceneChange::SceneChange()
{
		pJoypad = new Joypad(0);	
}

//�f�X�g���N�^
SceneChange::~SceneChange()
{
	if (pJoypad != NULL)
	{
		delete pJoypad;
	}

}