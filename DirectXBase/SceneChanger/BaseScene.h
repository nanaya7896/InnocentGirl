#pragma once

#include"Task.h"
#include"ISceneChanger.h"
#include"../Direct3D//direct3d.h"
#include"../DirectInput/directInput.h"

//�V�[���̊��N���X
class BaseScene : public Task
{
protected:
	//�N���X���L���ɃV�[���؂�ւ���`����C���^�[�t�F�C�X
	ISceneChanger* mSceneChanger;

public:
	BaseScene(ISceneChanger* changer);
	virtual ~BaseScene(){}
	virtual void Initialize() = 0;   //�������������I�[�o�[���C�h�B
	virtual void Finalize() = 0;       //�I���������I�[�o�[���C�h�B
	virtual void Update() = 0;        //�X�V�������I�[�o�[���C�h�B
	virtual void Draw() = 0;            //�`�揈�����I�[�o�[���C�h�B


};