#include"Enemy.h"

EnemyBox Enemy::em[30];

//コンストラクタ
Enemy::Enemy()
{
	EnemyMoveFrame = 0;
	Load();
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		EnemyPos[i] = D3DXVECTOR3(Random(-60.0f, 60.0f), 0.5f, Random(-60.0f, 60.0f));
	}
	EnemyAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}



//デストラクタ
Enemy::~Enemy()
{
	
}


void Enemy::Update()
{

	EnemyMoveFrame++;

}


void Enemy::Draw()
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		
		if (EnemyMoveFrame > 10)
	{
			EnemyMove();
			EnemyMoveFrame = 0;
	}
		x_Enemy.Render(&EnemyPos[i], &EnemyAngle, &D3DXVECTOR3(1.0f, 1.0f, 1.0f), t_Enemy.GetTexture());
		numv[i] = x_Enemy.g_pMesh->GetNumVertices();
		stride[i] = D3DXGetFVFVertexSize(x_Enemy.g_pMesh->GetFVF());
		hr[i] = x_Enemy.g_pMesh->GetVertexBuffer(&pvb9);
		if (FAILED(hr))
		{
			return;
		}
		hr[i] = pvb9->Lock(0, 0, (VOID**)&pvertices, 0);	//頂点バッファをロック
		if (FAILED(hr))
		{
			return;
		}
		hr[i] = D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices, numv[i], stride[i], &lminv, &lmaxv);
		if (FAILED(hr))
		{
			return;
		}

		em[i].minv = EnemyPos[i] - D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		em[i].maxv = EnemyPos[i] + D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		pvb9->Unlock();
	}
}

void Enemy::Load()
{
	t_Enemy.Load("texture/teki1.bmp");
	x_Enemy.XfileLoader(L"xfile/teki1.x");
	D3DXMatrixIdentity(&d3dMat);


}

BOOL Enemy::EneymHit(D3DXVECTOR3 *pmin, D3DXVECTOR3 *pmax)
{
	D3DXVECTOR3 *Emin, *Emax;
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		Emin = &em[i].minv;
		Emax = &em[i].maxv;
		if ((pmin->x < Emax->x) && (pmax->x > Emin->x) && (pmin->y <Emax->y) && (pmax->y > Emin->y) && (pmin->z < Emax->z) && (pmax->z > Emin->z))
		{
			return TRUE;
		}
		
	}
	return FALSE;
}

void Enemy::EnemyMove()
{
	
	
	
		for (int i = 0; i < MAX_ENEMY; i++)
		{

			int EnemyCheck = Random(0, 4);
		//	if (TransformEnemy == false)
			//{
				switch (EnemyCheck)
				{
				case 0:
					EMoveSpeed.x = 1.0f;
					break;
				case 1:
					EMoveSpeed.x = -1.0f;
					break;
				case 2:
					EMoveSpeed.z = 1.0f;
					break;
				case 3:
					EMoveSpeed.z = -1.0f;
					break;
				case 4:
					break;
				}
			//}
			EnemyPos[i] += EMoveSpeed;

		}
	

}

BOOL Enemy::EnemyProbe(float *pfoundangley)
{
	//D3DXVECTOR3 probevec1(0.0f, 0.0f, 1.0f);
	//D3DXVECTOR3 probevec2;
	//D3DXMATRIXA16 matWorld;
	//45度の視野を4.5度単位で探索
	/*for (int i = -5; i < 6; i++)
	{
		EnemyAngle.y + D3DX_PI / 40 * i;
		if (D3DXBoxBoundProbe(&mina, &maxa, &EnemyPos, &EnemyAngle) == TRUE)
		{
			*pfoundangley = EnemyAngle.y + D3DX_PI / 40 * i;
			return TRUE;
		}

	}*/
	return FALSE;


}


// 最大と最小の間の値をランダムに返すヘルパー関数
float Enemy::Random(float min, float max)
{
	return ((float)rand() / (float)RAND_MAX) * (max - min) + min;
}
