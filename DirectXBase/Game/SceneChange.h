#pragma once
#include"../Global.h"

class SceneChange
{
private:


public:
	//�R���X�g���N�^
	SceneChange();
	//�f�X�g���N�^
	~SceneChange();

	//���z�֐�(�������񓯂����������s����Ȃ�g���Ă݂�)
	virtual void Update()=0;
	virtual void Draw()=0;
	static SceneChange* scenechange;

//�h���N���X����Ȃ猩�邱�Ƃ��ł���
protected:

	




};