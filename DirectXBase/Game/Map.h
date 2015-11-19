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
	Texture tfloor[8];
	Texture tfloorGround[11];
	Texture tpanelSky[4];
	Texture tpanelSun;
	Texture tBuil[4];
	//Xfile�̃C���X�^���X����
	X_FILE xfloor;
	X_FILE xpanelSky;
	X_FILE xBuil[4];
	//Enemy�̃C���X�^���X����
	//Enemy Cem;
	//�����o�ϐ�
	DWORD numv[150], stride[150];
	LPDIRECT3DVERTEXBUFFER9 pvb9;
	BYTE *pvertices;
	HRESULT hr[150];
	D3DXVECTOR3 lminv, lmaxv;


public:
	//�R���X�g���N�^
	Map();
	//�f�X�g���N�^
	~Map();
	
	//�����o�֐�
	HRESULT LoadBuldings();
	void MapRender();
	BOOL HitTikei(D3DXVECTOR3 *pmina,D3DXVECTOR3 *pmaxa);

	BOOL HitETikei(D3DXVECTOR3 *emina, D3DXVECTOR3 *emaxa);
	

protected:
	int i = 0;

	static BoundingBox buildingsbox[150];
};