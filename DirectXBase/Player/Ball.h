#pragma once
#include"../Global.h"
#include"../DirectInput/directInput.h"
#include"../Direct3D/Xfile.h"
#include"../Direct3D/Texture.h"
#include"../Game/Map.h"
#include"../PhysicBases/PhysicBase.h"

#include"Player.h"
#include"../Enemy/Enemy.h"
#include"../Xinput/XbonInput.h"




class Ball : public Map
{
private:

	float unitTime;
	//�o���h�����邽�߂̌W��
	float Bound = -1.0f;
	float BoundCoefficient=0.0f;
	//�{�[���̔��a
	float ballR = 0.5f;
	X_FILE Xball;
	X_FILE Xball2P;
	Texture Tball;
	Texture Tball2P;
	PhysicBase pb;
	float ballSpeed;

	

	//�v���C���[�C���X�^���X
	Player bplayer;

	//�R���g���[���[�C���X�^���X
	XboxInput pInput;
public:
	//�{�[���̈ړ����x
	float ballspeed;
	//�d��
	D3DXVECTOR3 G;
	//�����x
	D3DXVECTOR3 Vel;
	//�ꏊ
	D3DXVECTOR3 Pos;

	//�{�[���̃t���O
	bool Ball_flag;
	//�{�[���t���[��
	unsigned long frame = 0;
	//�{�[���ɂ����錸���̗͂��Ǘ�����t���[��
	int ballStopFram = 30;
	//�{�[���̌������Ǘ�����֐�
	int ballStop();
	//�R���X�g���N�^
	Ball();
	//�f�X�g���N�^
	~Ball();
	//�{�[���쐬
	HRESULT BallLoad();
	void BallCreate(D3DXVECTOR3 bPos);
	void BallCreate2P(D3DXVECTOR3 bPos);
	//�{�[���̈ړ�
	D3DXVECTOR3 BallMove(D3DXVECTOR3 bPos,D3DXVECTOR3 playerPos, D3DXVECTOR3 playerAngle);
	D3DXVECTOR3 BallMove2P(D3DXVECTOR3 bPos);

	D3DXVECTOR3 ballpos;
	D3DXVECTOR3 ballmaxa;//(ballpos.x + 0.5f, ballpos.y + 0.5f, ballpos.z + 0.5f);
	D3DXVECTOR3 ballmina;// (ballpos.x - 0.5f, ballpos.y - 0.5f, ballpos.z - 0.5f);
	bool bHit;

	D3DXVECTOR3 Init(D3DXVECTOR3 ballpos);

	
protected:


};