#include"Player.h"

Player::Player()
{
	PlayerLoad();
}
Player::~Player()
{
	
}

HRESULT Player::PlayerLoad()
{
	Xplayer.XfileLoader(_T("xfile/yukicyan.X"));
	Tplayer.Load(_T("texture/yukitxture2.jpg"));

	if (Tplayer.pTexture == NULL)
	{
		return E_FAIL;
	}
	return S_OK;
}

void Player::PlayerCreate(D3DXVECTOR3 pPos)
{
	Xplayer.Render(&D3DXVECTOR3(pPos.x,pPos.y,pPos.z),&D3DXVECTOR3(200,0,0),&D3DXVECTOR3(0.01f,0.01f,0.01f), Tplayer.GetTexture());
}

D3DXVECTOR3 Player::PlayerMove(DWORD lasttime, D3DXVECTOR3 pPos)
{
	dInput.Init();
	dInput.Update();


	DWORD curtime = timeGetTime();
	looptime = ((float)lasttime - curtime) / 10000.0f;

	//上移動
	if (dInput.KeyDown(DIK_W))
	{
		pPos.z += speed;
	}
	else if (dInput.KeyStatePreview(DIK_W))
	{
		pPos.z += speed;
	}

	//下移動
	if (dInput.KeyDown(DIK_S))
	{
		pPos.z -= speed;
	}
	else if (dInput.KeyStatePreview(DIK_S))
	{
		pPos.z -= speed;
	}

	//右移動
	if (dInput.KeyDown(DIK_A))
	{
		pPos.x -= speed;
	}
	else if (dInput.KeyStatePreview(DIK_A))
	{
		pPos.x -= speed;
	}

	//左移動
	if (dInput.KeyDown(DIK_D))
	{
		pPos.x += speed;
	}
	else if (dInput.KeyStatePreview(DIK_D))
	{
		pPos.x += speed;
	}
	return pPos;
}