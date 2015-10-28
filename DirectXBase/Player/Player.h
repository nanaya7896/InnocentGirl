#pragma once
#include"../Global.h"
#include"../DirectInput/directInput.h"
#include"../Direct3D/Xfile.h"
#include"../Direct3D/Texture.h"
class Player
{
private:
	float looptime = 0.0f;
	//プレイヤーの移動速度
	float speed = 0.1f;
	//90度/s
	float anglesp = D3DX_PI / 2;
	DirectInput dInput;
	X_FILE Xplayer;
	Texture Tplayer;
public:
	
	Player();
	~Player();
	//プレイヤー作成
	HRESULT PlayerLoad();
	void PlayerCreate(D3DXVECTOR3 pPos);
	//プレイヤーの移動
	D3DXVECTOR3 PlayerMove(DWORD lasttime, D3DXVECTOR3 pPos);


protected:




};