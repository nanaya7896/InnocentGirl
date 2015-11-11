#pragma once

#include "../Direct3D\texture.h"
#include "../Direct3D\sprite.h"
#include "../Direct3D/direct3d.h"
#include "../DirectInput\directInput.h"
#include"../Player/Player.h"
#include"../Direct3D/Camera.h"
#include "SceneChange.h"
#include"../DirectXAnimation/MyAllocateHierarchy.h"
#include"../DirectXAnimation/AnimateObject.h"
#include"../Direct3D/font.h"
class GameMainTag :public SceneChange,Direct3D
{
private:
	//�v���C���[�C���X�^���X
	Player player;
	//�J�����C���X�^���X
	Camera camera;
	//�A�j���[�V�����C���X�^���X
	MyAllocateHierarchy mah;
	//���b�V���C���X�^���X
	CSkinMesh cskinMesh;
	//�e�L�X�g�C���X�^���X
	DirectXText timeText;
	int time;
	int timeframe;
public:


	//�R���X�g���N�^
	GameMainTag();

	//�f�X�g���N�^
	~GameMainTag();

	void Update();
	void Draw();

	void Load();
protected:
	D3DXVECTOR3 PlayerPos;
	D3DXVECTOR3 PlayerAngle;

};