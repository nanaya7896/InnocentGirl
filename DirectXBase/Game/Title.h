#pragma once

#include"SceneChange.h"
#include"../Direct3D/direct3d.h"
#include"../Direct3D/Texture.h"
#include"../Direct3D/sprite.h"
#include"../DirectInput/directInput.h"
#include"Chapter.h"
//�h���N���X:�^�C�g��	���N���X:SceneChange�@
class Title : public SceneChange,Direct3D
{
private:
	//�����_�ŗp�t���[��
	unsigned long frame = 0;


public:
	//�����o�ϐ�
	Texture title_Background;
	Texture title_bar[2];
	Sprite stitle_bar;
	Sprite stitle;

	bool TitleBlink;

	//�R���X�g���N�^
	Title();
	//�f�X�g���N�^
	~Title();

	//�����o�֐�
	void Update();
	void Draw();
	void Load();

protected:



};