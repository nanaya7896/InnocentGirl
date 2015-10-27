#pragma once
#include"../Global.h"
#include"../DirectInput/directInput.h"
class Player{
private:
	float looptime = 0.0f;
	float speed = 0.5f;
	//90“x/s
	float anglesp = D3DX_PI / 2;
	DirectInput dInput;
public:

	D3DXVECTOR3 PlayerMove(DWORD lasttime, D3DXVECTOR3 pPos);


protected:




};