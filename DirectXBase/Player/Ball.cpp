#include "Ball.h"

Ball::Ball()
{
	
	BallLoad();
}


Ball::~Ball()
{

}

D3DXVECTOR3 Ball::Init(D3DXVECTOR3 ballpos)
{

	


	pb.setPos(ballpos);
	
	ballSpeed = 10.0f;
	Bound = -1;
	
	Vel.x = 10.0f;
	Vel.y = 0.0f;
	Vel.z = 10.0f;
	pb.setVelocity(Vel);
	ballStopFram = 30;
	//pb.update(unitTime);
	ballpos =pb.getCurPos();
	return ballpos;
}

HRESULT Ball::BallLoad()
{
	ballSpeed = 5.0f;
	G.x = 0.0f;
	G.y = -9.8f;
	G.z = 0.0f;
	Pos.x = 0.5f;
	Pos.y = 1.0f;
	Pos.z = 0.0f;
	Vel.x = 10.0f*cosf(60/180*D3DX_PI);
	Vel.y = 0.0f;
	Vel.z = 10.0f*sinf(60/180*D3DX_PI);
	unitTime = 1 / 60.0f;

	//現在のボールの座標を取得
	pb.setPos(Pos);
	//現在のボールの速度を取得
	pb.setVelocity(Vel);
	//現在のボールの加速度を取得
	pb.setAccel(G);
	Tball.Load("texture/ball-tex.jpg");
	Xball.XfileLoader(L"xfile/ball.X");
	D3DXMatrixIdentity(&d3dMat);


	


	if (Tball.pTexture == NULL)
	{
		return E_FAIL;
	}
	return S_OK;
}

void Ball::BallCreate(D3DXVECTOR3 bPos)
{
	
	Xball.Render(&D3DXVECTOR3(bPos.x, bPos.y, bPos.z), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0.01f, 0.01f, 0.01f), Tball.GetTexture());
}

void Ball::BallCreate2P(D3DXVECTOR3 bPos)
{
	Xball2P.Render(&D3DXVECTOR3(bPos.x, bPos.y, bPos.z), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0.02f, 0.02f, 0.02f), Tball2P.GetTexture());
}


D3DXVECTOR3 Ball::BallMove(D3DXVECTOR3 bPos, D3DXVECTOR3 playerPos, D3DXVECTOR3 playerAngle)
{

	ballStopFram=ballStop();
	if (pb.getCurPos().y - ballR< 0.0f)
	{
			Bound *= -1.0f;
		//ballSpeed-=0.5f;
	}
	if (BoundCoefficient > 60)
	{
		Vel.y = Bound * cosf(Vel.y);
	}
	BoundCoefficient += 1;

	Vel.x =/* playerPos.x + */(ballSpeed*sinf(playerAngle.y));
	Vel.z =/* playerPos.z + */(ballSpeed*cosf(playerAngle.y));
	//pb.setPos(D3DXVECTOR3(sinf(bPos.x),bPos.y,cosf(bPos.z)));
	pb.setPos(bPos);
	//pb.getPos(bPos, unitTime);
	pb.setAccel(G);
	//pb.getVelocity(Vel, unitTime);
	pb.setVelocity(Vel);
	
	pb.getPos(bPos, unitTime);
	pb.update(unitTime);
	bPos = pb.getCurPos();

	
	

	return bPos;
}

D3DXVECTOR3 Ball::BallMove2P(D3DXVECTOR3 bPos)
{
	return bPos;
}

int Ball::ballStop()
{
	return ballStopFram == BoundCoefficient ? 30 : ballStopFram - 1;
}


