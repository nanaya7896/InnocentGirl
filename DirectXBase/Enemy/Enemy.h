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

	//�����o�ϐ�
	DWORD numv, stride;
	LPDIRECT3DVERTEXBUFFER9 pvb9;
	BYTE *pvertices;
	HRESULT hr;
	D3DXVECTOR3 lminv, lmaxv;
	
public:
	//�R���X�g���N�^
	Enemy();
	//���z���f�X�g���N�^
	virtual ~Enemy();

	void Update();

	void Draw();

	void Load();

	BOOL EneymHit(D3DXVECTOR3 *pmin,D3DXVECTOR3 *pmax);

protected:
	static EnemyBox em;




};

