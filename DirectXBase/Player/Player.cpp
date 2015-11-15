#include"Player.h"

Player::Player()
{
	mypos.y = 1.0f;
	PlayerLoad();
}
Player::~Player()
{
	
}

HRESULT Player::PlayerLoad()
{
	//Xplayer.XfileLoader(L"xfile/Y-runstart-P.X");
	//Tplayer.Load("texture/yukitxture2.jpg");
	Xplayer.XfileLoader(L"xfile/Tiny.x");
	Tplayer.Load("texture/Tiny_skin.dds");
	//cskinMesh.Init(pDevice3D,"xfile/Tiny.x");
	D3DXMatrixIdentity(&d3dMat);
	if (Tplayer.pTexture == NULL)
	{
		return E_FAIL;
	}
	return S_OK;
}

void Player::PlayerCreate(D3DXVECTOR3 pPos)
{
	Xplayer.Render(&D3DXVECTOR3(pPos.x,pPos.y,pPos.z),&D3DXVECTOR3(200,0,0),&D3DXVECTOR3(0.001f,0.001f,0.001f), Tplayer.GetTexture());
}

D3DXVECTOR3 Player::PlayerMove(D3DXVECTOR3 pPos)
{

	//cskinMesh.Update(d3dMat);
	//cskinMesh.Draw(pDevice3D);
	
	if (DirectInput::GetInstance().KeyDown(DIK_F) || DirectInput::GetInstance().KeyState(DIK_F))
	{
		speed = 0.23f;
	}
	else
	{
		speed = 0.1f;
	}

	
	
	
		//è„à⁄ìÆ
		if (DirectInput::GetInstance().KeyDown(DIK_W))
		{
			mypos.z=pPos.z+ speed;
		}
		else if (DirectInput::GetInstance().KeyStatePreview(DIK_W))
		{
			mypos.z=pPos.z + speed;
		}

		//â∫à⁄ìÆ
		if (DirectInput::GetInstance().KeyDown(DIK_S))
		{
			mypos.z=pPos.z - speed;
		}
		else if (DirectInput::GetInstance().KeyStatePreview(DIK_S))
		{
			mypos.z=pPos.z -speed;
		}

		//âEà⁄ìÆ
		if (DirectInput::GetInstance().KeyDown(DIK_A))
		{
			mypos.x=pPos.x - speed;
		}
		else if (DirectInput::GetInstance().KeyStatePreview(DIK_A))
		{
			mypos.x=pPos.x - speed;
		}

		//ç∂à⁄ìÆ
		if (DirectInput::GetInstance().KeyDown(DIK_D))
		{
			mypos.x=pPos.x + speed;
		}
		else if (DirectInput::GetInstance().KeyStatePreview(DIK_D))
		{
			mypos.x=pPos.x + speed;
		}
		D3DXVECTOR3 mina(pPos.x - 0.5f, pPos.y - 0.5f, pPos.z - 0.5f);
		D3DXVECTOR3 maxa(pPos.x + 0.5f, pPos.y + 0.5f, pPos.z + 0.5f);
		if (HitTikei(&mina, &maxa) == FALSE)
		{
			pPos=mypos;
		}

	
	return pPos;
	
}