#pragma once
#include"../Global.h"
#include"../DirectInput/directInput.h"
#include"../Direct3D/Xfile.h"
#include"../Direct3D/Texture.h"
#include"../DirectXAnimation/MyAllocateHierarchy.h"
#include"../DirectXAnimation/AnimateObject.h"


class Player : public Direct3D
{
private:
	float looptime = 0.0f;
	//�v���C���[�̈ړ����x
	float speed = 0.1f;
	//90�x/s
	float anglesp = D3DX_PI / 2;
	X_FILE Xplayer;
	Texture Tplayer;

	MyAllocateHierarchy mah;
	CSkinMesh cskinMesh;
public:
	
	Player();
	~Player();
	//�v���C���[�쐬
	HRESULT PlayerLoad();
	void PlayerCreate(D3DXVECTOR3 pPos);
	//�v���C���[�̈ړ�
	D3DXVECTOR3 PlayerMove(D3DXVECTOR3 pPos);


protected:




};