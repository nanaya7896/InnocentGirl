#pragma once

#include"../Global.h"
#include"../Direct3D/Camera.h"
#include"SceneChange.h"
#include"Chapter_GameOfTag.h"
#include"../Game/Map.h"
#include"../Enemy/Enemy.h"
#include"../Player/Player.h"


class GameMainTag2P :public SceneChange,Direct3D
{
private:
	Camera camera2P;
	Map *map2P;

public:

	//�f�t�H���g�R���X�g���N�^
	GameMainTag2P();
	//�f�X�g���N�^
	~GameMainTag2P();
	//������
	void Init();
	//�A�b�v�f�[�g
	void  Update();
	//�`��
	void Draw();


protected:


};