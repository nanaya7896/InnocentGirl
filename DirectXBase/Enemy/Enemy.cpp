#include"Enemy.h"

EnemyBox Enemy::em[30];

//コンストラクタ
Enemy::Enemy()
{
	//敵が動き続ける時間
	EnemyMoveFrame = 0;
	//敵が動くフラグ
	EnemyMoveFlag = true;
	//Enemyロード関数
	Load();
	//敵初期値ポジションの設定
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		//-60から60の座標間でランダム生成
		EnemyPos[i] = D3DXVECTOR3(Random(-60.0f, 60.0f), 0.5f, Random(-60.0f, 60.0f));
		//敵が一番最初向いている角度
		EnemyAngle[i] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	
}



//デストラクタ
Enemy::~Enemy()
{
	
}


void Enemy::Update()
{
	//敵が動き続けるフレーム数
	EnemyMoveFrame++;

}


void Enemy::Draw()
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		//EnemySearch();


		//もし敵の行動フラグが立っていたら
		if (EnemyMoveFlag == true)
		{
			//敵の行動フラグをfalseにする
			EnemyMoveFlag = false;
				//敵の行動関数
			
				EnemyMove();
		}
		//もし敵が180f(3s)動き続けたら
		if (EnemyMoveFrame >= 180)
		{
			//新しい行動を入れるためのフラグをtrueへ
			EnemyMoveFlag = true;
			//フレームを初期値に戻す
			EnemyMoveFrame = 0;
		}


		//行動関数から得た値を敵のPosにたす
			EnemyPos[i] += EMoveSpeed[i];
			EnemyAngle[i] += EnemyMoveAngleSpeed[i];
			//敵の描画
		x_Enemy.Render(&EnemyPos[i], &EnemyAngle[i], &D3DXVECTOR3(1.0f, 1.0f, 1.0f), t_Enemy.GetTexture());
		//境界線ボックスの生成
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
		//境界ボックスの範囲を設定
		em[i].minv = EnemyPos[i] - D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		em[i].maxv = EnemyPos[i] + D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		pvb9->Unlock();
	}
}

void Enemy::Load()
{
	//テクスチャとXファイルの読み込み
	t_Enemy.Load("texture/teki1.bmp");
	x_Enemy.XfileLoader(L"xfile/teki1.x");
	//行列の初期化
	D3DXMatrixIdentity(&d3dMat);


}

//衝突判定関数
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

//敵の行動関数
void Enemy::EnemyMove()
{
	
		for (int i = 0; i < MAX_ENEMY; i++)
		{
			//0から4の間で値を生成
			int EnemyCheck = Random(0, 6);
			//敵の行動を選択
				switch (EnemyCheck)
				{
				case 0:
					//x軸に0.01f動く
					EnemyMoveAngleSpeed[i].y = 0.0f;
					EMoveSpeed[i].x =0.01f;
					break;
				case 1:
					//x軸に-0.01f動く
					EnemyMoveAngleSpeed[i].y = 0.0f;
					EMoveSpeed[i].x = -0.01f;
					break;
				case 2:
					//z軸に0.01f動く
					EnemyMoveAngleSpeed[i].y = 0.0f;
					EMoveSpeed[i].z = 0.01f;
					break;
				case 3:
					//z軸に-0.01f動く
					EnemyMoveAngleSpeed[i].y = 0.0f;
					EMoveSpeed[i].z = -0.01f;
					break;
				case 4:
					//向きを変える
					EnemyMoveAngleSpeed[i].y = -0.01f;
					EMoveSpeed[i].x = 0.0f;
					EMoveSpeed[i].z = 0.0f;
					break;
				case 5:
					//向きを変える
					EnemyMoveAngleSpeed[i].y = 0.01f;
					EMoveSpeed[i].x = 0.0f;
					EMoveSpeed[i].z = 0.0f;
					break;
				case 6:
					//何もしない
					EMoveSpeed[i].x = 0.0f;
					EMoveSpeed[i].z = 0.0f;
					EnemyMoveAngleSpeed[i].y = 0.0f;
					break;
				}
			
		

		}
	

}

float Enemy::EnemySearch(D3DXVECTOR3 pPos)
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{

		//Playerと敵との距離
		PlayerEnemyDistance[i].x = pPos.x - EnemyPos[i].x;
		PlayerEnemyDistance[i].y = 0.0f;
		PlayerEnemyDistance[i].z = pPos.z - EnemyPos[i].z;

		//三平方の定理
		AutoMoveSpeed = sqrtf(pow(PlayerEnemyDistance[i].x,2 )+ pow(PlayerEnemyDistance[i].z,2));

	}

	return AutoMoveSpeed;


}


// 最大と最小の間の値をランダムに返すヘルパー関数
float Enemy::Random(float min, float max)
{
	return ((float)rand() / (float)RAND_MAX) * (max - min) + min;
}
