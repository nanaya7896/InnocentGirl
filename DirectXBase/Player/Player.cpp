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

D3DXVECTOR3 Player::PlayerMove(D3DXVECTOR3 pPos)
{
	DirectInput::GetInstance().Init();
	DirectInput::GetInstance().Update();




	//è„à⁄ìÆ
	if (DirectInput::GetInstance().KeyDown(DIK_W))
	{
		pPos.z += speed;
	}
	else if (DirectInput::GetInstance().KeyStatePreview(DIK_W))
	{
		pPos.z += speed;
	}

	//â∫à⁄ìÆ
	if (DirectInput::GetInstance().KeyDown(DIK_S))
	{
		pPos.z -= speed;
	}
	else if (DirectInput::GetInstance().KeyStatePreview(DIK_S))
	{
		pPos.z -= speed;
	}

	//âEà⁄ìÆ
	if (DirectInput::GetInstance().KeyDown(DIK_A))
	{
		pPos.x -= speed;
	}
	else if (DirectInput::GetInstance().KeyStatePreview(DIK_A))
	{
		pPos.x -= speed;
	}

	//ç∂à⁄ìÆ
	if (DirectInput::GetInstance().KeyDown(DIK_D))
	{
		pPos.x += speed;
	}
	else if (DirectInput::GetInstance().KeyStatePreview(DIK_D))
	{
		pPos.x += speed;
	}
	return pPos;
}