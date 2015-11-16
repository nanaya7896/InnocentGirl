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
	//プレイヤーの移動速度
	float speed = 0.1f;
	//90度/s
	float anglesp = D3DX_PI / 2;
	X_FILE Xplayer;
	Texture Tplayer;
	Enemy pEnemy;
	MyAllocateHierarchy mah;
	CSkinMesh cskinMesh;
	//プレイヤーのヨー回転(y軸中心)
	double ridianYaw =  0.0f;
public:
	
	Player();
	~Player();
	//プレイヤー作成
	HRESULT PlayerLoad();
	void PlayerCreate(D3DXVECTOR3 pPos,D3DXVECTOR3 pAng);
	//プレイヤーの移動
	D3DXVECTOR3 PlayerMove(D3DXVECTOR3 pPos);
	//カメラの視点変更
	D3DXVECTOR3 PlayerCameraMove(D3DXVECTOR3 pAng);
	//ラジアンの角度を変える関数
	D3DXVECTOR3 YRotation();
	D3DXVECTOR3 mypos;
	
protected:




};