#pragma once

#include"../Global.h"
#include"../Direct3D/Camera.h"
#include"../SceneChanger/ISceneChanger.h"
#include"../SceneChanger/BaseScene.h"
#include"../Game/Map.h"
#include"../Enemy/Enemy.h"
#include"../Player/Player.h"
#include"Result.h"
#include "../Direct3D/texture.h"
#include "../Direct3D/sprite.h"


struct pCameraInfo1P{
	D3DXVECTOR3 CameraPos1P;
	D3DXVECTOR3 CameraAngle1P;
};

struct pCameraInfo2P{
	D3DXVECTOR3 CameraPos2P;
	D3DXVECTOR3 CameraAngle2P;
};

class GameMainTag2P :public BaseScene,Direct3D
{
private:
	//Camera camera2P;
	//Camera camera1P;
	Camera *camera1;
	Map map2P;
	//�e�N�X�`���C���X�^���X
	Texture timeTexture2[10];
	//�X�v���C�g�C���X�^���X
	Sprite timeSprite2[2];
	//�v���C���[�C���X�^���X
	Player player[2];
	//enemy�̃C���X�^���X
	Enemy enemy2;
	//�PP�̍\����
	pCameraInfo1P pInfo1P;
	//�QP�̍\����
	pCameraInfo2P pInfo2P;
	//wave�ǂݍ���
	CSound wave[2];
	//���ԗp�����o�ϐ�
	int timeframe2;
	//time10�̈�
	int tentime2 = 6;
	//time1�̈�
	int onetime2 = 0;
public:

	//�f�t�H���g�R���X�g���N�^
	GameMainTag2P(ISceneChanger *changer);
	//�f�X�g���N�^
	~GameMainTag2P();
	//������
	void Initialize() override;
	void Finalize() override;
	//�A�b�v�f�[�g
	void  Update() override;
	//�`��
	void Draw() override;


protected:
	D3DXVECTOR3 PlayerPos1P;
	D3DXVECTOR3 PlayerPos2P;
	D3DXVECTOR3 PlayerAngle1P;
	D3DXVECTOR3 PlayerAngle2P;


};