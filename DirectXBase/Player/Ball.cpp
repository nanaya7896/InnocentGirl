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

	pb.setPos(D3DXVECTOR3(0.5f, 1.0f, 0.0f));
	
	ballSpeed = 10.0f;
	Bound = -1;
	
	Vel.x = 10.0f;
	Vel.y = 0.0f;
	Vel.z = 10.0f;
	pb.setVelocity(Vel);
	ballStopFram = 30;

	ballpos =pb.getCurPos();
	return ballpos;
}

HRESULT Ball::BallLoad()
{
	ballSpeed = 10.0f;
	G.x = 0.0f;
	G.y = -9.8f;
	G.z = 0.0f;
	Pos.x = 0.5f;
	Pos.y = 1.0f;
	Pos.z = 0.0f;
	Vel.x = 10.0f;
	Vel.y = 0.0f;
	Vel.z = 10.0f;
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
	if (ballStopFram == 0)
	{
		if (pb.getCurPos().y <= 0.1f || pb.getCurPos().y > 1.0f)
		{
			Bound *= -1;
		}
		Pos.y =Bound * cosf(Pos.y);
		ballSpeed--;
	}
	if (ballSpeed< 0)
	{
		ballSpeed = 1;
	}

	Pos.x = playerPos.x + (ballSpeed*sinf(playerAngle.y));
	Pos.z = playerPos.z + (ballSpeed*cosf(playerAngle.y));
	pb.setPos(Pos);
	pb.setAccel(G);
	pb.setVelocity(Vel);
	//	bPos=pb.addPos(bPos,bPos);
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
	return ballStopFram > 0 ? ballStopFram - 1 : 30;
}

