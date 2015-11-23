#include"Player.h"

Player::Player()
{
	Hit = false;
	mypos.y = 0.0f;
	RunFrame = 0;
	RunFlag = true;
	//maxa(mypos.x + 0.5f, mypos.y + 0.5f, mypos.z + 0.5f);
	//D3DXVECTOR3 mina(mypos.x - 0.5f, mypos.y - 0.5f, mypos.z - 0.5f);

	PlayerLoad();
}
Player::~Player()
{
	Hit = false;
}

HRESULT Player::PlayerLoad()
{
	//Xplayer.XfileLoader(L"xfile/Y-runstart-P.X");
	Tplayer.Load("texture/yukitxture2.jpg");
	Xplayer.XfileLoader(L"xfile/yukicyan.X");
	//Tplayer.Load("texture/Tiny_skin.dds");
	//cskinMesh.Init(pDevice3D,"xfile/Y-runstart-P.X");
	D3DXMatrixIdentity(&d3dMat);
	if (Tplayer.pTexture == NULL)
	{
		return E_FAIL;
	}
	return S_OK;
}

void Player::PlayerCreate(D3DXVECTOR3 pPos,D3DXVECTOR3 pAng)
{
	
	Xplayer.Render(&D3DXVECTOR3(pPos.x,pPos.y,pPos.z),&D3DXVECTOR3(pAng.x-(D3DX_PI/2.0f),pAng.y,pAng.z),&D3DXVECTOR3(0.02f,0.02f,0.02f), Tplayer.GetTexture());
}

D3DXVECTOR3 Player::PlayerMove(D3DXVECTOR3 pPos)
{

	//cskinMesh.Update(d3dMat);
	//cskinMesh.Draw(pDevice3D);
	if (RunFrame >= 120)
	{
		RunFlag = false;
	}
	if (RunFrame >= 360)
	{
		RunFlag = true;
	}
	

	if (DirectInput::GetInstance().KeyDown(DIK_F) || DirectInput::GetInstance().KeyState(DIK_F))
	{
		if (RunFlag == true)
		{
			speed = 0.15f;
			RunFrame++;
		}
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
		maxa.x = mypos.x + 0.5f;
		maxa.y = mypos.y + 0.5f;
		maxa.z = mypos.z + 0.5f;
		mina.x = mypos.x - 0.5f;
		mina.y = mypos.y - 0.5f;
		mina.z = mypos.z - 0.5f;

		if (HitTikei(&mina, &maxa) == FALSE)
		{
			pPos=mypos;
		}
		if (pEnemy.EneymHit(&mina, &maxa) == TRUE)
		{
			Hit = true;
		}

	
	return pPos;
	
}


D3DXVECTOR3 Player::PlayerCameraMove(D3DXVECTOR3 pAng)
{
	//âEÇå¸Ç≠
	if (DirectInput::GetInstance().KeyDown(DIK_LEFT))
	{
		pAng.y -= 0.1f;
	}
	else if (DirectInput::GetInstance().KeyState(DIK_LEFT))
	{
		pAng.y -= 0.1f;
		
	}
	//ç∂Çå¸Ç≠
	if(DirectInput::GetInstance().KeyDown(DIK_RIGHT))
	{
		pAng.y += 0.1f;
	}
	else if (DirectInput::GetInstance().KeyState(DIK_RIGHT))
	{
		pAng.y += 0.1f;

	}
	

	return pAng;
}