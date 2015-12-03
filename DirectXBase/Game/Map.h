#pragma once
#include"../Global.h"
#include"../Direct3D/Xfile.h"
#include"../Direct3D/texture.h"
//#include"../Enemy/Enemy.h"
struct BoundingBox
{
	D3DXVECTOR3 minv;	//�ŏ����_
	D3DXVECTOR3 maxv;	//�ő咸�_
};



class Map : public X_FILE
{
private:
	//Texture�̃C���X�^���X����
	Texture ttfloor;
	Texture tpanelSky[4];
	Texture tSky;
	Texture tpanelSun;
	Texture tBuil[4];
	//Xfile�̃C���X�^���X����
	X_FILE xfloor;
	X_FILE xpanelSky;
	X_FILE xBuil[4];
	X_FILE xSky;
	//Enemy�̃C���X�^���X����
	//Enemy Cem;
	//�����o�ϐ�
	DWORD numv[8], stride[8];
	LPDIRECT3DVERTEXBUFFER9 pvb9;
	BYTE *pvertices;
	HRESULT hr[8];
	D3DXVECTOR3 lminv, lmaxv;


public:
	//�R���X�g���N�^
	Map();
	//�f�X�g���N�^
	~Map();
	
	//�����o�֐�
	HRESULT LoadBuldings();
	void MapRender();
	//�v���C���[�ƒn�`�̂����蔻��
	BOOL HitTikei(D3DXVECTOR3 *pmina,D3DXVECTOR3 *pmaxa);
	//�G�̒n�`�Ƃ̂����蔻��
	BOOL HitETikei(D3DXVECTOR3 *emina, D3DXVECTOR3 *emaxa);
	//�J�����ƒn�`�̂����蔻��
	BOOL HitCTikei(D3DXVECTOR3 *cmina, D3DXVECTOR3 *cmaxa);

protected:
	int i = 0;

	static BoundingBox buildingsbox[8];
};