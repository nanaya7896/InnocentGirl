#pragma once

#include "../Direct3D\texture.h"
#include "../Direct3D\sprite.h"
#include "../Direct3D/direct3d.h"
#include "../DirectInput\directInput.h"
#include"../Player/Player.h"
#include"../Direct3D/Camera.h"
#include"Map.h"
#include "SceneChange.h"
#include"../DirectXAnimation/MyAllocateHierarchy.h"
#include"../DirectXAnimation/AnimateObject.h"
#include"../Direct3D/font.h"
#include"../Enemy/Enemy.h"
class GameMainTag :public SceneChange,Direct3D
{
private:
	//�e�N�X�`���C���X�^���X
	Texture timeTexture[10];
	//�X�v���C�g�C���X�^���X
	Sprite timeSprite[2];
	//�v���C���[�C���X�^���X
	Player player;
	//�J�����C���X�^���X
	Camera *camera;
	//�A�j���[�V�����C���X�^���X
	MyAllocateHierarchy mah;
	//���b�V���C���X�^���X
	CSkinMesh cskinMesh;
	//�e�L�X�g�C���X�^���X
	DirectXText timeText;
	//enemy�̃C���X�^���X
	Enemy gmtEnemy;
	//���ԗp�����o�ϐ�
	int time;
	int timeframe;
	//time10�̈�
	int tentime=9;
	//time1�̈�
	int onetime=0;
public:
	D3DXVECTOR3 CameraPosition;

	//�R���X�g���N�^
	GameMainTag();

	//�f�X�g���N�^
	~GameMainTag();

	void Update();
	void Draw();

	void Load();

	//�����蔻��֐�
	HRESULT Player_HitBox();
protected:
	D3DXVECTOR3 PlayerPos;
	D3DXVECTOR3 PlayerAngle;

};