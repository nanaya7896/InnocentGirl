#pragma once

#include"../SceneChanger/ISceneChanger.h"
#include"../SceneChanger/BaseScene.h"
#include "../Direct3D\texture.h"
#include "../Direct3D\sprite.h"
#include "../Direct3D/direct3d.h"
#include "../DirectInput\directInput.h"
#include"../Player/Player.h"
#include"../Direct3D/Camera.h"
#include"Map.h"
#include"../DirectXAnimation/MyAllocateHierarchy.h"
#include"../DirectXAnimation/AnimateObject.h"
#include"../Direct3D/font.h"
#include"../Enemy/Enemy.h"
#include"Title.h"
#include"Result.h"
#include"Gameover.h"
#include"../DirectSound/dxsound.h"

class GameMainTag :public BaseScene, Direct3D
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
	//�}�b�v�̃C���X�^���X
	Map map1P;
	//enemy�̃C���X�^���X
	Enemy gmtEnemy;
	//�T�E���h�̃C���X�^���X
	CSound wave[3];
	//���ԗp�����o�ϐ�
	int time;
	int timeframe;
	//time10�̈�
	int tentime = 6;
	//time1�̈�
	int onetime = 0;

	//�X�R�A���u��
	DirectXText score1;
	DirectXText score2;
	int Score1p;
	int Score2p;
public:
	D3DXVECTOR3 CameraPosition;

	//�R���X�g���N�^
	GameMainTag(ISceneChanger *changer);

	//�f�X�g���N�^
	~GameMainTag();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;



protected:
	D3DXVECTOR3 PlayerPos;
	D3DXVECTOR3 PlayerAngle;
	D3DXVECTOR3 PlayerSpeed;
};