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
	//プレイヤーの移動速度
	float speed = 0.1f;
	//90度/s
	float anglesp = D3DX_PI / 2;
	X_FILE Xplayer;
	Texture Tplayer;

	MyAllocateHierarchy mah;
	CSkinMesh cskinMesh;
public:
	
	Player();
	~Player();
	//プレイヤー作成
	HRESULT PlayerLoad();
	void PlayerCreate(D3DXVECTOR3 pPos);
	//プレイヤーの移動
	D3DXVECTOR3 PlayerMove(D3DXVECTOR3 pPos);


protected:




};