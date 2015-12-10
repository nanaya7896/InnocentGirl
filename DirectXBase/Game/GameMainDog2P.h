#pragma once

#include"../SceneChanger/ISceneChanger.h"
#include"../SceneChanger/BaseScene.h"
#include "../Direct3D\texture.h"
#include "../Direct3D\sprite.h"
#include "../Direct3D/direct3d.h"
#include "../DirectInput\directInput.h"
#include "../Player/Ball.h"
#include"../Direct3D/Camera.h"
#include"../DirectXAnimation/MyAllocateHierarchy.h"
#include"../DirectXAnimation/AnimateObject.h"
#include"../Direct3D/font.h"
#include"Title.h"
#include"Result.h"
#include"Gameover.h"
#include"../DirectSound/dxsound.h"



class GameMainDodge2P :public BaseScene, Direct3D
{
private:
	//�e�N�X�`���C���X�^���X
	Texture dtimeTexture[10];
	//�X�v���C�g�C���X�^���X
	Sprite dtimeSprite[2];
	//�v���C���[�C���X�^���X
	Player d_player[2];
	//�{�[���C���X�^���X
	Ball d_ball[2];
	//�J�����C���X�^���X
	Camera *d_camera;
	//�A�j���[�V�����C���X�^���X
	MyAllocateHierarchy mah;
	//���b�V���C���X�^���X
	CSkinMesh cskinMesh;
	//�}�b�v�̃C���X�^���X
	Map mapDog1P;
	//enemy�̃C���X�^���X
	Enemy Dog_Enemy;
	//�T�E���h�̃C���X�^���X
	CSound wave[3];
	//���ԗp�����o�ϐ�
	int time;
	int timeframe;
	//time10�̈�
	int tentime = 9;
	//time1�̈�
	int onetime = 0;
	//�X�^�~�i����l
	const int MAX_STAMINA = 360;
	//�X�^�~�i�����l
	const int LOS_STAMINA = 0;

	bool Ballthrow;
	bool Ballthrow2;
public:

	//���݂̃X�^�~�i
	int currentStamina;
	//�X�^�~�i�����߂�֐�
	int sta(int currentStamina);
	//�X�^�~�i�̏���������䂷��֐�
	int sta_clamp(int currentstamina, int low, int high);
	D3DXVECTOR3 CameraPosition;
	D3DXVECTOR3 CameraPosition2;
	//�R���X�g���N�^
	GameMainDodge2P(ISceneChanger *changer);
	//�f�X�g���N�^
	~GameMainDodge2P();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;


protected:
	D3DXVECTOR3 d_PlayerPos;
	D3DXVECTOR3 d_PlayerAngle;
	D3DXVECTOR3 d_PlayerPos2;
	D3DXVECTOR3 d_PlayerAngle2;
	D3DXVECTOR3 d_PlayerSpeed;
	D3DXVECTOR3 BallPos;
	D3DXVECTOR3 BallPos2;
};