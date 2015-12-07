#include"Enemy.h"

EnemyBox Enemy::em[31];
Score Enemy::dscore;
bool Enemy::isEnemyDestroy[31];
//コンストラクタ
Enemy::Enemy()
{
	
}




//デストラクタ
Enemy::~Enemy()
{

}


void Enemy::Initialize()
{

	//テクスチャとXファイルの読み込み
	t_Enemy.Load("texture/zombie-tex.jpg");
	x_Enemy.XfileLoader(L"xfile/zombie-nobone.X");
	//WAVEの読み込み
	wave[0].Load(_T("BGM/z_koe.wav"));
	wave[1].Load(_T("BGM/z_koe.wav"));
	//行列の初期化
	D3DXMatrixIdentity(&d3dMat);
	//敵が動き続ける時間
	EnemyMoveFrame = 0;
	//敵が動くフラグ
	SearcherFrame = 0;

	//敵初期値ポジションの設定
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		PlayerEnemyDistance[i] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		AutoMove[i] = 0.0f;
		
		while (EnemyPos[i].x > -10 && EnemyPos[i].x<10 && EnemyPos[i].z>-10 && EnemyPos[i].z < 10)
		{
			//-60から60の座標間でランダム生成
			EnemyPos[i] = D3DXVECTOR3(Random(-40.0f, 40.0f), 0.1f, Random(-60.0f, 60.0f));
		}
		//敵が一番最初向いている角度
		EnemyAngle[i] = D3DXVECTOR3(0.0f - (D3DX_PI / 2.0f), 0.0f, 0.0f);
		MapHit[i] = false;
		if (i <= 29)
		{
			TransformEnemy[i] = false;
			EnemyMoveFlag[i] = true;
			SearcherFlag[i] = false;
		}
		else
		{
			//追跡者にするために行動関数はすべてfalse
			TransformEnemy[30] = false;
			EnemyMoveFlag[30] = false;
			SearcherFlag[30] = true;
		}


	}


}


void Enemy::Update(D3DXVECTOR3 pPos)
{
	//敵が動き続けるフレーム数
	EnemyMoveFrame++;
	
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if(isEnemyDestroy[i]==false)
		{


		AutoMove[i] = EnemySearch(pPos);
		if (SearcherFlag[i] == false)
		{

			if (pPos.x - EnemyPos[i].x <= 5.0f &&pPos.x - EnemyPos[i].x >= -5.0f || pPos.z - EnemyPos[i].z <= 5.0f &&pPos.z - EnemyPos[i].z >= -5.0f)
			{
				//AutoMove[i] = EnemySearch(pPos);
				TransformEnemy[i] = true;
				EnemyMoveFlag[i] = false;
			}
			else
			{
				TransformEnemy[i] = false;
			}

			//もし敵の行動フラグが立っていたら
			if (EnemyMoveFlag[i] == true)
			{
				//敵の行動フラグをfalseにする
				EnemyMoveFlag[i] = false;
				//敵の行動関数
				EnemyMove();
				TransformEnemy[i] = false;
			}
			//もし敵が180f(3s)動き続けたら
			if (EnemyMoveFrame >= 180 && TransformEnemy[i] == false)
			{
				//新しい行動を入れるためのフラグをtrueへ
				EnemyMoveFlag[i] = true;
				//フレームを初期値に戻す
				EnemyMoveFrame = 0;
			}
			else if (TransformEnemy[i] == true)
			{
				if (AutoMove[i] != 0)
				{
					if (PlayerEnemyDistance[i].x >= 0 && PlayerEnemyDistance[i].x < 5.0f && PlayerEnemyDistance[i].z >= 0 && PlayerEnemyDistance[i].z < 5.0f)
					{
						EnemyPos[i].x += 0.1f;
						EnemyPos[i].z += 0.1f;
					}
					else if (PlayerEnemyDistance[i].x < 0 && PlayerEnemyDistance[i].x > -5.0f && PlayerEnemyDistance[i].z > 0 && PlayerEnemyDistance[i].z < 5.0f)
					{
						EnemyPos[i].x -= 0.1f;
						EnemyPos[i].z += 0.1f;
					}
					else if (PlayerEnemyDistance[i].x < 0 && PlayerEnemyDistance[i].x > -5.0f && PlayerEnemyDistance[i].z < 0 && PlayerEnemyDistance[i].z>-5.0f)
					{
						EnemyPos[i].x -= 0.1f;
						EnemyPos[i].z -= 0.1f;
					}
					else if (PlayerEnemyDistance[i].x >= 0 && PlayerEnemyDistance[i].x < 5.0f && PlayerEnemyDistance[i].z < 0 && PlayerEnemyDistance[i].z >-5.0f)
					{
						EnemyPos[i].x += 0.1f;
						EnemyPos[i].z -= 0.1f;
					}
				}
			}

		}
		else if (SearcherFlag[i] == true && MapHit[i] == false)
		{
			SerachMove();
		}

		maxe.x = EnemyPos[i].x + 0.7f;
		maxe.y = EnemyPos[i].y + 0.7f;
		maxe.z = EnemyPos[i].z + 0.7f;
		mine.x = EnemyPos[i].x - 0.7f;
		mine.y = EnemyPos[i].y - 0.7f;
		mine.z = EnemyPos[i].z - 0.7f;


		if (eMap.HitETikei(&mine, &maxe) == TRUE)
		{
			MapHit[i] = true;
		}
		else
		{
			MapHit[i] = false;
		}
		if (TransformEnemy[i] == false)
		{
			//行動関数から得た値を敵のPosにたす
			if (MapHit[i] == false)
			{
				EnemyPos[i] += EMoveSpeed[i];
			}
			EnemyAngle[i] += EnemyMoveAngleSpeed[i];
		}
	
		}//isEnemyDestroy[i]==false
		

	}
	
	SearcherFrame++;
}


void Enemy::Draw()
{

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (PlayerEnemyDistance[i].x <30.0f &&PlayerEnemyDistance[i].x >-30.0f && PlayerEnemyDistance[i].z > -30.0f && PlayerEnemyDistance[i].z < 30.0f)
		{
			x_Enemy.Render(&EnemyPos[i], &EnemyAngle[i], &D3DXVECTOR3(0.05f, 0.05f, 0.05f), t_Enemy.GetTexture());
		}
			//敵の描画
		/*if (PlayerEnemyDistance[i] < D3DXVECTOR3(30.0f, 0.0f, 30.0f) && PlayerEnemyDistance[i] > D3DXVECTOR3(-30.0f, 0.0f, -30.0f))
		{
			x_Enemy.Render(&EnemyPos[i], &EnemyAngle[i], &D3DXVECTOR3(0.05f, 0.05f, 0.05f), t_Enemy.GetTexture());
		}*/
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
		em[i].minv = EnemyPos[i] - D3DXVECTOR3(2.0f, 1.0f, 2.0f);
		em[i].maxv = EnemyPos[i] + D3DXVECTOR3(2.0f, 1.0f, 2.0f);
		pvb9->Unlock();
	}
}


//衝突判定関数
BOOL Enemy::EneymHit(D3DXVECTOR3 *pmin, D3DXVECTOR3 *pmax)
{
	D3DXVECTOR3 *Emin, *Emax;
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (isEnemyDestroy[i] == false)
		{
			Emin = &em[i].minv;
			Emax = &em[i].maxv;
			if ((pmin->x < Emax->x) && (pmax->x > Emin->x) && (pmin->y <Emax->y) && (pmax->y > Emin->y) && (pmin->z < Emax->z) && (pmax->z > Emin->z))
			{
				return TRUE;
			}
		}
		
	}
	return FALSE;
}

//敵の行動関数
void Enemy::EnemyMove()
{
	
		for (int i = 0; i < 30; i++)
		{
			//0から6の間で値を生成
			int EnemyCheck = (int)Random((int)0, (int)6);
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

		//距離が10以下ならうめき声
		if (AutoMoveSpeed <= 10)
		{
			wave[0].Play(false);
		}

	}

	return AutoMoveSpeed;


}

void Enemy::SerachMove()
{
	if (PlayerEnemyDistance[30].x > 0  && PlayerEnemyDistance[30].z >0 )
	{
		EnemyPos[30].x += 0.05f;
		EnemyPos[30].z += 0.05f;
	}
	else if (PlayerEnemyDistance[30].x < 0 && PlayerEnemyDistance[30].z >0 )
	{
		EnemyPos[30].x -= 0.05f;
		EnemyPos[30].z += 0.05f;
	}
	else if (PlayerEnemyDistance[30].x <0 && PlayerEnemyDistance[30].z <0)
	{
		EnemyPos[30].x -= 0.05f;
		EnemyPos[30].z -= 0.05f;
	}
	else if (PlayerEnemyDistance[30].x > 0  && PlayerEnemyDistance[30].z < 0)
	{
		EnemyPos[30].x += 0.05f;
		EnemyPos[30].z -= 0.05f;
	}


}

int Enemy::score1P()
{
	if (DirectInput::GetInstance().KeyDown(DIK_A))
	{
		dscore.Score1P++;
	}
	return dscore.Score1P;
}

int Enemy::score2P()
{

	if (DirectInput::GetInstance().KeyDown(DIK_L))
	{
		dscore.Score2P++;
	}
	return dscore.Score2P;
}

void Enemy::EnemyDown(D3DXVECTOR3 ballPos)
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (ballPos.x>EnemyPos[i].x-1.0f && ballPos.x<EnemyPos[i].x+1.0f && ballPos.z > EnemyPos[i].z-1.0f && ballPos.z<EnemyPos[i].z+1.0f && ballPos.y<EnemyPos[i].y+10.0f &&ballPos.y>0)
		{
			isEnemyDestroy[i] = true;
		}
		if (isEnemyDestroy[i] == true)
		{
			if (EnemyAngle[i].x<0)
			{
				EnemyAngle[i].x += D3DX_PI / 600;
			}
			if (EnemyAngle[i].x >0)
			{
			
				EnemyPos[i].y -= 0.01f;
			}
		}
	}

}



// 最大と最小の間の値をランダムに返すヘルパー関数
float Enemy::Random(float min, float max)
{
	return ((float)rand() / (float)RAND_MAX) * (max - min) + min;
}
