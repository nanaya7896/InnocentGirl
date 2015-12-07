#include"Enemy.h"

EnemyBox Enemy::em[31];
Score Enemy::dscore;
bool Enemy::isEnemyDestroy[31];
//�R���X�g���N�^
Enemy::Enemy()
{
	
}




//�f�X�g���N�^
Enemy::~Enemy()
{

}


void Enemy::Initialize()
{

	//�e�N�X�`����X�t�@�C���̓ǂݍ���
	t_Enemy.Load("texture/zombie-tex.jpg");
	x_Enemy.XfileLoader(L"xfile/zombie-nobone.X");
	//WAVE�̓ǂݍ���
	wave[0].Load(_T("BGM/z_koe.wav"));
	wave[1].Load(_T("BGM/z_koe.wav"));
	//�s��̏�����
	D3DXMatrixIdentity(&d3dMat);
	//�G�����������鎞��
	EnemyMoveFrame = 0;
	//�G�������t���O
	SearcherFrame = 0;

	//�G�����l�|�W�V�����̐ݒ�
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		PlayerEnemyDistance[i] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		AutoMove[i] = 0.0f;
		
		while (EnemyPos[i].x > -10 && EnemyPos[i].x<10 && EnemyPos[i].z>-10 && EnemyPos[i].z < 10)
		{
			//-60����60�̍��W�ԂŃ����_������
			EnemyPos[i] = D3DXVECTOR3(Random(-40.0f, 40.0f), 0.1f, Random(-60.0f, 60.0f));
		}
		//�G����ԍŏ������Ă���p�x
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
			//�ǐՎ҂ɂ��邽�߂ɍs���֐��͂��ׂ�false
			TransformEnemy[30] = false;
			EnemyMoveFlag[30] = false;
			SearcherFlag[30] = true;
		}


	}


}


void Enemy::Update(D3DXVECTOR3 pPos)
{
	//�G������������t���[����
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

			//�����G�̍s���t���O�������Ă�����
			if (EnemyMoveFlag[i] == true)
			{
				//�G�̍s���t���O��false�ɂ���
				EnemyMoveFlag[i] = false;
				//�G�̍s���֐�
				EnemyMove();
				TransformEnemy[i] = false;
			}
			//�����G��180f(3s)������������
			if (EnemyMoveFrame >= 180 && TransformEnemy[i] == false)
			{
				//�V�����s�������邽�߂̃t���O��true��
				EnemyMoveFlag[i] = true;
				//�t���[���������l�ɖ߂�
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
			//�s���֐����瓾���l��G��Pos�ɂ���
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
			//�G�̕`��
		/*if (PlayerEnemyDistance[i] < D3DXVECTOR3(30.0f, 0.0f, 30.0f) && PlayerEnemyDistance[i] > D3DXVECTOR3(-30.0f, 0.0f, -30.0f))
		{
			x_Enemy.Render(&EnemyPos[i], &EnemyAngle[i], &D3DXVECTOR3(0.05f, 0.05f, 0.05f), t_Enemy.GetTexture());
		}*/
		//���E���{�b�N�X�̐���
		numv[i] = x_Enemy.g_pMesh->GetNumVertices();
		stride[i] = D3DXGetFVFVertexSize(x_Enemy.g_pMesh->GetFVF());
		hr[i] = x_Enemy.g_pMesh->GetVertexBuffer(&pvb9);
		if (FAILED(hr))
		{
			return;
		}
		hr[i] = pvb9->Lock(0, 0, (VOID**)&pvertices, 0);	//���_�o�b�t�@�����b�N
		if (FAILED(hr))
		{
			return;
		}
		hr[i] = D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices, numv[i], stride[i], &lminv, &lmaxv);
		if (FAILED(hr))
		{
			return;
		}
		//���E�{�b�N�X�͈̔͂�ݒ�
		em[i].minv = EnemyPos[i] - D3DXVECTOR3(2.0f, 1.0f, 2.0f);
		em[i].maxv = EnemyPos[i] + D3DXVECTOR3(2.0f, 1.0f, 2.0f);
		pvb9->Unlock();
	}
}


//�Փ˔���֐�
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

//�G�̍s���֐�
void Enemy::EnemyMove()
{
	
		for (int i = 0; i < 30; i++)
		{
			//0����6�̊ԂŒl�𐶐�
			int EnemyCheck = (int)Random((int)0, (int)6);
			//�G�̍s����I��
				switch (EnemyCheck)
				{
				case 0:
					//x����0.01f����
					EnemyMoveAngleSpeed[i].y = 0.0f;
					EMoveSpeed[i].x =0.01f;
					break;
				case 1:
					//x����-0.01f����
					EnemyMoveAngleSpeed[i].y = 0.0f;
					EMoveSpeed[i].x = -0.01f;
					break;
				case 2:
					//z����0.01f����
					EnemyMoveAngleSpeed[i].y = 0.0f;
					EMoveSpeed[i].z = 0.01f;
					break;
				case 3:
					//z����-0.01f����
					EnemyMoveAngleSpeed[i].y = 0.0f;
					EMoveSpeed[i].z = -0.01f;
					break;
				case 4:
					//������ς���
					EnemyMoveAngleSpeed[i].y = -0.01f;
					EMoveSpeed[i].x = 0.0f;
					EMoveSpeed[i].z = 0.0f;
					break;
				case 5:
					//������ς���
					EnemyMoveAngleSpeed[i].y = 0.01f;
					EMoveSpeed[i].x = 0.0f;
					EMoveSpeed[i].z = 0.0f;
					break;
				case 6:
					//�������Ȃ�
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

		//Player�ƓG�Ƃ̋���
		PlayerEnemyDistance[i].x = pPos.x - EnemyPos[i].x;
		PlayerEnemyDistance[i].y = 0.0f;
		PlayerEnemyDistance[i].z = pPos.z - EnemyPos[i].z;

		//�O�����̒藝
		AutoMoveSpeed = sqrtf(pow(PlayerEnemyDistance[i].x,2 )+ pow(PlayerEnemyDistance[i].z,2));

		//������10�ȉ��Ȃ炤�߂���
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



// �ő�ƍŏ��̊Ԃ̒l�������_���ɕԂ��w���p�[�֐�
float Enemy::Random(float min, float max)
{
	return ((float)rand() / (float)RAND_MAX) * (max - min) + min;
}
