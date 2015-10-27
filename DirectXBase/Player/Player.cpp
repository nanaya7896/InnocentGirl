#include"Player.h"

D3DXVECTOR3 Player::PlayerMove(DWORD lasttime, D3DXVECTOR3 pPos)
{
	dInput.Init();
	dInput.Update();


	DWORD curtime = timeGetTime();
	looptime = ((float)lasttime - curtime) / 1000.0f;

	//��ړ�
	if (dInput.KeyDown(DIK_W))
	{
		pPos.z -= speed*looptime;
	}
	else if (dInput.KeyStatePreview(DIK_W))
	{
		pPos.z -= speed*looptime;
	}

	//���ړ�
	if (dInput.KeyDown(DIK_S))
	{
		pPos.z += speed*looptime;
	}
	else if (dInput.KeyStatePreview(DIK_S))
	{
		pPos.z += speed*looptime;
	}

	//�E�ړ�
	if (dInput.KeyDown(DIK_A))
	{
		pPos.x += anglesp*looptime;
	}
	else if (dInput.KeyStatePreview(DIK_A))
	{
		pPos.x += speed*looptime;
	}

	//���ړ�
	if (dInput.KeyDown(DIK_D))
	{
		pPos.x -= anglesp*looptime;
	}
	else if (dInput.KeyStatePreview(DIK_D))
	{
		pPos.x -= speed*looptime;
	}
	return pPos;
}