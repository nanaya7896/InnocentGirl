#pragma once
#include"../Global.h"
#include"../Direct3D/direct3d.h"
#include"../Direct3D/Xfile.h"
#include"../Direct3D/texture.h"
#include"../Game/Map.h"
#include"../DirectSound/dxsound.h"

struct EnemyBox{
	D3DXVECTOR3 minv;
	D3DXVECTOR3 maxv;
};
struct Score
{
	int Score1P;
	int Score2P;
};



class Enemy : public Direct3D
{
private:
	Texture t_Enemy;
	X_FILE x_Enemy;
	Map eMap;


	//���E�{�b�N�X�����p�ϐ�
	LPDIRECT3DVERTEXBUFFER9 pvb9;
	BYTE *pvertices;
	HRESULT hr[31];
	D3DXVECTOR3 lminv, lmaxv;
	//�����o�ϐ�
	DWORD numv[31], stride[31];
	//�G�̏ꏊ
	D3DXVECTOR3 EnemyPos[31];
	//�G�̌����Ă������
	D3DXVECTOR3 EnemyAngle[31];
	//�G�̈ړ��X�s�[�h
	D3DXVECTOR3 EMoveSpeed[31];
	//�G�̌�����ς���X�s�[�h�֐�
	D3DXVECTOR3 EnemyMoveAngleSpeed[31];
	//�G�̍ő�o����
	const int MAX_ENEMY = 31;

	
	
	//�v���C���[�ƃ��L�����̋����̍���ۑ�����
	D3DXVECTOR3 PlayerEnemyDistance[31];
	//�O�����̒藝�ŋ��߂��Ώە��Ƃ̋�����
	float AutoMoveSpeed;
	//�s������ی��𔻒f����֐�
	float AutoMove[31];
	//�G�̈ړ�����p�t���[��
	int EnemyMoveFrame;
	bool MapHit[31];

	//�ǐՎ҃t���O
	bool SearcherFlag[31];
	//�ǐՎ҈ړ�����t���[��
	int SearcherFrame;
	//�G�l�~�[�̎����ړ����v���C���[�ǂ������邩�̔���
	bool TransformEnemy[31];

	bool EnemyMoveFlag[31];
	D3DXVECTOR3 maxe;//(mypos.x + 0.5f, mypos.y + 0.5f, mypos.z + 0.5f);
	D3DXVECTOR3 mine;// (mypos.x - 0.5f, mypos.y - 0.5f, mypos.z - 0.5f);
public:

	


	//�R���X�g���N�^
	Enemy();
	//���z���f�X�g���N�^
	virtual ~Enemy();

	void Update(D3DXVECTOR3 pPos);

	void Draw();

	void Load();

	float EnemySearch(D3DXVECTOR3 pPos);

	BOOL EneymHit(D3DXVECTOR3 *pmin,D3DXVECTOR3 *pmax);

	void EnemyMove();

	//�ǐՎ҂̈ړ��֐�
	void SerachMove();
	//�����_���Œl�𐶐�����w���p�[�֐�
	float Random(float min, float max);
	//�X�R�A
	int score1P();
	int score2P();

	//Wave�t�@�C��
	CSound wave[2];

protected:
	static EnemyBox em[31];
	static Score dscore;


};

