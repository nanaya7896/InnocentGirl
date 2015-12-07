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
SceneChange::SceneChange() : mNextScene(eScene_None) //���̃V�[���̊Ǘ��ϐ�
{
	mScene = (BaseScene*) new Title(this);
}

//������
void SceneChange::Initialize()
{
	mScene->Initialize();
}

//�I������
void SceneChange::Finalize()
{
	mScene->Finalize();
}

//�X�V
void SceneChange::Update()
{
	if (mNextScene != eScene_None)
	{
		//���̃V�[�����Z�b�g����Ă�����
		mScene->Finalize(); //�I�������̎��s
		delete mScene;
		switch (mNextScene)
		{
			//�V�[����switch�ŕ���
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
		//���̃V�[���̏����N���A
		mNextScene = eScene_None;
		//�V�[����������
		mScene->Initialize();
	}
	//�V�[���̍X�V
	mScene->Update();

}

//�`��
void SceneChange::Draw()
{
	//�V�[���̕`��
	mScene->Draw();
}

//����nextScene�ɕύX����
void SceneChange::ChangeScene(eScene NextScene)
{
	//���̃V�[�����Z�b�g����
	mNextScene = NextScene;
}

void SceneChange::DELETESCENELAST()
{
	if (mScene != NULL)
	{
		delete mScene;
	}
}