#include"Enemy.h"

EnemyBox Enemy::em[31];

//�R���X�g���N�^
Enemy::Enemy()
{
	//�G�����������鎞��
	EnemyMoveFrame = 0;
	//�G�������t���O
	SearcherFrame = 0;
	//Enemy���[�h�֐�
	Load();
	//�G�����l�|�W�V�����̐ݒ�
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		PlayerEnemyDistance[i] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		AutoMove[i]=0.0f;
		//-60����60�̍��W�ԂŃ����_������
		EnemyPos[i] = D3DXVECTOR3(Random(-60.0f, 60.0f), 0.5f, Random(-60.0f,60.0f));
		//�G����ԍŏ������Ă���p�x
		EnemyAngle[i] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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



//�f�X�g���N�^
Enemy::~Enemy()
{
	
}


void Enemy::Update(D3DXVECTOR3 pPos)
{
	//�G������������t���[����
	EnemyMoveFrame++;
	
	for (int i = 0; i < MAX_ENEMY; i++)
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
					else if (PlayerEnemyDistance[i].x < 0 && PlayerEnemyDistance[i].x > -5.0f && PlayerEnemyDistance[i].z < 0 && PlayerEnemyDistance[i].z >-5.0f)
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
		else if(SearcherFlag[i]==true)
		{

			
			SerachMove();
				
			
		}
		if (TransformEnemy[i] == false)
		{
			//�s���֐����瓾���l��G��Pos�ɂ���
			EnemyPos[i] += EMoveSpeed[i];
			EnemyAngle[i] += EnemyMoveAngleSpeed[i];
		}
	}
	
	SearcherFrame++;
}


void Enemy::Draw()
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
			//�G�̕`��
		x_Enemy.Render(&EnemyPos[i], &EnemyAngle[i], &D3DXVECTOR3(1.0f, 1.0f, 1.0f), t_Enemy.GetTexture());
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
		em[i].minv = EnemyPos[i] - D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		em[i].maxv = EnemyPos[i] + D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		pvb9->Unlock();
	}
}

void Enemy::Load()
{
	//�e�N�X�`����X�t�@�C���̓ǂݍ���
	t_Enemy.Load("texture/teki1.bmp");
	x_Enemy.XfileLoader(L"xfile/teki1.x");

	//�s��̏�����
	D3DXMatrixIdentity(&d3dMat);


}

//�Փ˔���֐�
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

//�G�̍s���֐�
void Enemy::EnemyMove()
{
	
		for (int i = 0; i < 30; i++)
		{
			//0����4�̊ԂŒl�𐶐�
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


// �ő�ƍŏ��̊Ԃ̒l�������_���ɕԂ��w���p�[�֐�
float Enemy::Random(float min, float max)
{
	return ((float)rand() / (float)RAND_MAX) * (max - min) + min;
}
