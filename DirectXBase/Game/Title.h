#pragma once

#include "../SceneChanger/BaseScene.h"
#include "../SceneChanger/ISceneChanger.h"
#include"../Direct3D/direct3d.h"
#include"../Direct3D/Texture.h"
#include"../Direct3D/sprite.h"
#include"../DirectInput/directInput.h"
#include"Chapter.h"
#include"Result.h"
#include"../Xinput/XbonInput.h"


//�h���N���X:�^�C�g��	���N���X:SceneChange�@
class Title : public BaseScene,Direct3D
{
private:
	//�����_�ŗp�t���[��
	unsigned long frame = 0;
	//�p����
	XboxInput xboxInput;
public:
	//�����o�ϐ�
	Texture title_Background;
	Texture title_bar1;
	Texture title_bar2;
	Sprite stitle_bar;
	Sprite stitle;
	//�T�E���h�ǂݍ���
	CSound wave[2];
	bool TitleBlink;

	//�R���X�g���N�^
	Title(ISceneChanger *changer);
	//�f�X�g���N�^
	~Title();
	
	void Initialize() override;    //�������������I�[�o�[���C�h�B
	void Finalize() override;        //�I���������I�[�o�[���C�h
	void Update() override;
	void Draw() override;


protected:

	

};