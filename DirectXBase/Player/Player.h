#pragma once
#include"../Global.h"
#include"../DirectInput/directInput.h"
#include"../Direct3D/Xfile.h"
#include"../Direct3D/Texture.h"
#include"../Game/Map.h"
#include"../DirectXAnimation/MyAllocateHierarchy.h"
#include"../DirectXAnimation/AnimateObject.h"
#include"../Enemy/Enemy.h"

class Player : public Map
{
private:
	float looptime = 0.0f;
	//�v���C���[�̈ړ����x
	float speed = 0.1f;
	//90�x/s
	float anglesp = D3DX_PI / 2;
	X_FILE Xplayer;
	X_FILE Xplayer2P;
	Texture Tplayer2P;
	Texture Tplayer;
	Enemy pEnemy;
	MyAllocateHierarchy mah;
	CSkinMesh cskinMesh;

	int RunFrame;
	int RunFrame2P;
	bool RunFlag;
	bool RunFlag2P;

	//�v���C���[�̃��[��](y�����S)
	double ridianYaw =  0.0f;
public:
	
	Player();
	~Player();
	//�v���C���[�쐬
	HRESULT PlayerLoad();
	void PlayerCreate(D3DXVECTOR3 pPos,D3DXVECTOR3 pAng);
	void PlayerCreate2P(D3DXVECTOR3 pPos, D3DXVECTOR3 pAng);
	//�v���C���[�̈ړ�
	D3DXVECTOR3 PlayerMove(D3DXVECTOR3 pPos,D3DXVECTOR3 pAng);
	D3DXVECTOR3 PlayerMove2P(D3DXVECTOR3 pPos, D3DXVECTOR3 pAng);
	//�J�����̎��_�ύX
	D3DXVECTOR3 PlayerCameraMove(D3DXVECTOR3 pAng);
	D3DXVECTOR3 PlayerCameraMove2P(D3DXVECTOR3 pAng);
	//���W�A���̊p�x��ς���֐�
	D3DXVECTOR3 YRotation();
	D3DXVECTOR3 mypos;
	D3DXVECTOR3 maxa;//(mypos.x + 0.5f, mypos.y + 0.5f, mypos.z + 0.5f);
	D3DXVECTOR3 mina;// (mypos.x - 0.5f, mypos.y - 0.5f, mypos.z - 0.5f);
	bool Hit;
protected:




};