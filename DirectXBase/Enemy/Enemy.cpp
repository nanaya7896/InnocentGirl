#include"Enemy.h"

EnemyBox Enemy::em;

//コンストラクタ
Enemy::Enemy()
{
	Load();
}



//デストラクタ
Enemy::~Enemy()
{



}


void Enemy::Update()
{



}


void Enemy::Draw()
{
	x_Enemy.Render(&D3DXVECTOR3(20.0f,1.2f,0.0f),&D3DXVECTOR3(0.0f,0.0f,0.0f),&D3DXVECTOR3(1.0f,1.0f,1.0f),t_Enemy.GetTexture());
	numv = x_Enemy.g_pMesh->GetNumVertices();
	stride = D3DXGetFVFVertexSize(x_Enemy.g_pMesh->GetFVF());
	hr = x_Enemy.g_pMesh->GetVertexBuffer(&pvb9);
	if (FAILED(hr))
	{
		return;
	}
	hr = pvb9->Lock(0, 0, (VOID**)&pvertices, 0);	//頂点バッファをロック
	if (FAILED(hr))
	{
		return;
	}
	hr = D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices, numv, stride, &lminv, &lmaxv);
	if (FAILED(hr))
	{
		return;
	}
	em.minv = D3DXVECTOR3(20.0f, 1.2f, 0.0f) - D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	em.maxv = D3DXVECTOR3(20.0f, 1.2f, 0.0f) + D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	pvb9->Unlock();
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
	Emin = &em.minv;
	Emax = &em.maxv;
	if ((pmin->x < Emax->x) && (pmax->x > Emin->x) && (pmin->y <Emax->y) && (pmax->y > Emin->y) && (pmin->z < Emax->z) && (pmax->z > Emin->z))
	{
		return TRUE;
	}
	return FALSE;

}
