#pragma once

#include "ISceneChanger.h"
#include "BaseScene.h"

class SceneChange : public ISceneChanger,Task
{
public:
	//�R���X�g���N�^
	SceneChange();

	void Initialize() override;//������
	void Finalize() override;//�I������
	void Update() override;//�X�V
	void Draw() override;//�`��

	void DELETESCENELAST();

	// ���� nextScene �ɃV�[����ύX����
	void ChangeScene(eScene NextScene) override;

private:
	//�V�[���Ǘ��ϐ�
	BaseScene* mScene;
	//���̃V�[���̊Ǘ��ϐ�
	eScene mNextScene;
	//���g���C���̃V�[���ύX�p�ϐ�

};