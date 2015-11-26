#include"Player.h"

Player::Player()
{

	Hit = false;
	mypos.y = 0.1f;
	mypos.x = 0.0f;
	mypos.z = 0.0f;
	RunFrame = 0;
	RunFlag = true;
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
	Xplayer2P.XfileLoader(L"xfile/yukicyan.X");
	Tplayer2P.Load("texture/yukitxture2p.jpg");
	//cskinMesh.Init(pDevice3D,"xfile/Y-runstart-P.X");
	D3DXMatrixIdentity(&d3dMat);
	if (Tplayer.pTexture == NULL)
	{
		return E_FAIL;
	}
	if (Tplayer2P.pTexture == NULL)
	{
		return E_FAIL;
	}
	return S_OK;
}

void Player::PlayerCreate(D3DXVECTOR3 pPos,D3DXVECTOR3 pAng)
{
	
	Xplayer.Render(&D3DXVECTOR3(pPos.x,pPos.y,pPos.z),&D3DXVECTOR3(pAng.x-(D3DX_PI/2.0f),pAng.y,pAng.z),&D3DXVECTOR3(0.02f,0.02f,0.02f), Tplayer.GetTexture());
}

void Player::PlayerCreate2P(D3DXVECTOR3 pPos, D3DXVECTOR3 pAng)
{
	Xplayer2P.Render(&D3DXVECTOR3(pPos.x, pPos.y, pPos.z), &D3DXVECTOR3(pAng.x - (D3DX_PI / 2.0f), pAng.y, pAng.z), &D3DXVECTOR3(0.02f, 0.02f, 0.02f), Tplayer2P.GetTexture());


}

D3DXVECTOR3 Player::PlayerMove(D3DXVECTOR3 pPos,D3DXVECTOR3 pAng)
{
	if (RunFrame >= 120)
	{
		RunFlag = false;
	}
	if (RunFrame >= 360)
	{
		RunFlag = true;
	}
	//pJoypad->update();

	if ( pJoypad->isPushed(Joypad::Button::A) == true|| DirectInput::GetInstance().KeyDown(DIK_F) || DirectInput::GetInstance().KeyState(DIK_F))
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
		//上移動
	if (pJoypad->getLStick(0.1).imag() >= 0.5 || DirectInput::GetInstance().KeyDown(DIK_W))
		{
			mypos.x = pPos.x + (sin(pAng.y)*speed);
			mypos.z = pPos.z + (cos(pAng.y)*speed);
			
		}
		else if (DirectInput::GetInstance().KeyStatePreview(DIK_W))
		{
			mypos.x = pPos.x + (sin(pAng.y)*speed);
			mypos.z = pPos.z + (cos(pAng.y)*speed);
		}

		//下移動
	if (pJoypad->getLStick(0.1).imag() <= -0.5 || DirectInput::GetInstance().KeyDown(DIK_S))
		{
			//mypos.z=pPos.z - speed;
			mypos.x = pPos.x - (sin(pAng.y)*speed);
			mypos.z = pPos.z - (cos(pAng.y)*speed);
		}
		else if (DirectInput::GetInstance().KeyStatePreview(DIK_S))
		{
			mypos.x = pPos.x - (sin(pAng.y)*speed);
			mypos.z = pPos.z - (cos(pAng.y)*speed);
		}

		//右移動
	if (pJoypad->getLStick(0.1).real() <= -0.5 || DirectInput::GetInstance().KeyDown(DIK_A))
		{
			//mypos.x=pPos.x - speed;
			mypos.x = pPos.x -+ (cos(pAng.y)*speed);
			mypos.z = pPos.z - (sin(pAng.y)*speed);
		}
		else if (DirectInput::GetInstance().KeyStatePreview(DIK_A))
		{
			mypos.x = pPos.x - (cos(pAng.y)*speed);
			mypos.z = pPos.z + (sin(pAng.y)*speed);
		}

		//左移動
	if (pJoypad->getLStick(0.1).real() >= 0.5 || DirectInput::GetInstance().KeyDown(DIK_D))
		{
			mypos.x = pPos.x + (cos(pAng.y)*speed);
			mypos.z = pPos.z - (sin(pAng.y)*speed);
		}
		else if (DirectInput::GetInstance().KeyStatePreview(DIK_D))
		{
			mypos.x = pPos.x + (cos(pAng.y)*speed);
			mypos.z = pPos.z - (sin(pAng.y)*speed);
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

D3DXVECTOR3 Player::PlayerMove2P(D3DXVECTOR3 pPos, D3DXVECTOR3 pAng)
{
	if (RunFrame2P >= 120)
	{
		RunFlag2P = false;
	}
	if (RunFrame2P >= 360)
	{
		RunFlag2P = true;
	}
	//pJoypad->update();

	if (pJoypad->isPushed(Joypad::Button::A) || DirectInput::GetInstance().KeyDown(DIK_H) || DirectInput::GetInstance().KeyState(DIK_H))
	{
		if (RunFlag2P == true)
		{
			speed = 0.15f;
			RunFrame2P++;
		}
	}
	else
	{
		speed = 0.1f;
	}
	//上移動
	if (DirectInput::GetInstance().KeyDown(DIK_O))
	{
		mypos.x = pPos.x + (sin(pAng.y)*speed);
		mypos.z = pPos.z + (cos(pAng.y)*speed);

	}
	else if (DirectInput::GetInstance().KeyStatePreview(DIK_O))
	{
		mypos.x = pPos.x + (sin(pAng.y)*speed);
		mypos.z = pPos.z + (cos(pAng.y)*speed);
	}

	//下移動
	if (pJoypad->getLStick(0.1).imag() >= 0.5 || DirectInput::GetInstance().KeyDown(DIK_K))
	{
		//mypos.z=pPos.z - speed;
		mypos.x = pPos.x - (sin(pAng.y)*speed);
		mypos.z = pPos.z - (cos(pAng.y)*speed);
	}
	else if (DirectInput::GetInstance().KeyStatePreview(DIK_K))
	{
		mypos.x = pPos.x - (sin(pAng.y)*speed);
		mypos.z = pPos.z - (cos(pAng.y)*speed);
	}

	//右移動
	if (pJoypad->getLStick(0.1).imag() <= -0.5 || DirectInput::GetInstance().KeyDown(DIK_J))
	{
		//mypos.x=pPos.x - speed;
		mypos.x = pPos.x - +(cos(pAng.y)*speed);
		mypos.z = pPos.z - (sin(pAng.y)*speed);
	}
	else if (DirectInput::GetInstance().KeyStatePreview(DIK_J))
	{
		mypos.x = pPos.x - (cos(pAng.y)*speed);
		mypos.z = pPos.z + (sin(pAng.y)*speed);
	}

	//左移動
	if (pJoypad->getLStick(0.1).real() >= 0.5 || DirectInput::GetInstance().KeyDown(DIK_L))
	{
		mypos.x = pPos.x + (cos(pAng.y)*speed);
		mypos.z = pPos.z - (sin(pAng.y)*speed);
	}
	else if (DirectInput::GetInstance().KeyStatePreview(DIK_L))
	{
		mypos.x = pPos.x + (cos(pAng.y)*speed);
		mypos.z = pPos.z - (sin(pAng.y)*speed);
	}
	maxa.x = mypos.x + 0.5f;
	maxa.y = mypos.y + 0.5f;
	maxa.z = mypos.z + 0.5f;
	mina.x = mypos.x - 0.5f;
	mina.y = mypos.y - 0.5f;
	mina.z = mypos.z - 0.5f;

	if (HitTikei(&mina, &maxa) == FALSE)
	{
		pPos = mypos;
	}
	if (pEnemy.EneymHit(&mina, &maxa) == TRUE)
	{
		Hit = true;
	}


	return pPos;

}

D3DXVECTOR3 Player::PlayerCameraMove(D3DXVECTOR3 pAng)
{

	//右を向く
	if ( pJoypad->getRStick(0.1).real() <= -0.5 || DirectInput::GetInstance().KeyDown(DIK_Q))
	{
		pAng.y -= 0.1f;
	}
	else if (DirectInput::GetInstance().KeyState(DIK_Q))
	{
		pAng.y -= 0.1f;
		
	}
	//左を向く
	if (pJoypad->getRStick(0.1).real() >= 0.5 || DirectInput::GetInstance().KeyDown(DIK_E))
	{
		pAng.y += 0.1f;
	}
	else if (DirectInput::GetInstance().KeyState(DIK_E))
	{
		pAng.y += 0.1f;

	}
	

	return pAng;
}

D3DXVECTOR3 Player::PlayerCameraMove2P(D3DXVECTOR3 pAng)
{

	//右を向く
	if (pJoypad->getRStick(0.1).real() <= -0.5 || DirectInput::GetInstance().KeyDown(DIK_P))
	{
		pAng.y -= 0.1f;
	}
	else if (DirectInput::GetInstance().KeyState(DIK_P))
	{
		pAng.y -= 0.1f;

	}
	//左を向く
	if (pJoypad->getRStick(0.1).real() >= 0.5 ||DirectInput::GetInstance().KeyDown(DIK_I))
	{
		pAng.y += 0.1f;
	}
	else if (DirectInput::GetInstance().KeyState(DIK_I))
	{
		pAng.y += 0.1f;

	}


	return pAng;
}