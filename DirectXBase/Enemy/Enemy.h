#pragma once
#include"../Global.h"
#include"../Direct3D/direct3d.h"
#include"../Direct3D/Xfile.h"
#include"../Direct3D/texture.h"



struct EnemyBox{
	D3DXVECTOR3 minv;
	D3DXVECTOR3 maxv;
};

class Enemy : public Direct3D
{
private:
	Texture t_Enemy;
	X_FILE x_Enemy;

	
	//���E�{�b�N�X�����p�ϐ�
	LPDIRECT3DVERTEXBUFFER9 pvb9;
	BYTE *pvertices;
	HRESULT hr[31];
	D3DXVECTOR3 lminv, lmaxv;
	//�����o�ϐ�
	DWORD numv[31], stride[31];
	//�G�̏ꏊ
	D3DXVECTOR3 EnemyPos[30];
	//�G�̌����Ă������
	D3DXVECTOR3 EnemyAngle;
	//�G�̈ړ��X�s�[�h
	D3DXVECTOR3 EMoveSpeed;

	//�G�̍ő�o����
	const int MAX_ENEMY = 30;
	
	//�G�̈ړ�����p�t���[��
	int EnemyMoveFrame;

	//�G�l�~�[�̎����ړ����v���C���[�ǂ������邩�̔���
	bool TransformEnemy[30];

public:

	


	//�R���X�g���N�^
	Enemy();
	//���z���f�X�g���N�^
	virtual ~Enemy();

	void Update();

	void Draw();

	void Load();

	BOOL EnemyProbe(float *pfoundangley);

	BOOL EneymHit(D3DXVECTOR3 *pmin,D3DXVECTOR3 *pmax);

	void EnemyMove();

	//�����_���Œl�𐶐�����w���p�[�֐�
	float Random(float min, float max);

protected:
	static EnemyBox em[30];




};

