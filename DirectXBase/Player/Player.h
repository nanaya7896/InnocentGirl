#pragma once
#include"../Global.h"
#include"../DirectInput/directInput.h"
#include"../Direct3D/Xfile.h"
#include"../Direct3D/Texture.h"
#include"../Game/Map.h"
#include"../DirectXAnimation/MyAllocateHierarchy.h"
#include"../DirectXAnimation/AnimateObject.h"
#include"../Enemy/Enemy.h"
#include"../Xinput/XbonInput.h"


class Player : public Map
{
private:
	float looptime = 0.0f;
	
	//�v���C���[�̈ړ����x
	const float SPEED_DASH = 0.2f;
	const float SPEED_NORMAL = 0.1f;
	//90�x/s
	float anglesp = D3DX_PI / 2;
	X_FILE Xplayer;
	X_FILE Xplayer2P;
	Texture Tplayer2P;
	Texture Tplayer;
	Enemy pEnemy;
	MyAllocateHierarchy mah;
	CSkinMesh cskinMesh;
	XboxInput pInput;
	int RunFrame;
	int RunFrame2P;
	bool RunFlag;
	bool RunFlag2P;
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
	//�_�b�V���p�֐�
	bool isDash();
	float speed();
	//�J�����̎��_�ύX
	D3DXVECTOR3 PlayerCameraMove(D3DXVECTOR3 pAng);
	D3DXVECTOR3 PlayerCameraMove2P(D3DXVECTOR3 pAng);
	//���W�A���̊p�x��ς���֐�
	D3DXVECTOR3 YRotation();
	D3DXVECTOR3 mypos;
	D3DXVECTOR3 maxa;
	D3DXVECTOR3 mina;
	bool Hit;
protected:




};