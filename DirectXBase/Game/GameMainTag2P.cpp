#include"GameMainTag2P.h"

//�R���X�g���N�^
GameMainTag2P::GameMainTag2P()
{
	Init();
	map2P = new Map();
}

//�f�X�g���N�^
GameMainTag2P::~GameMainTag2P()
{
	delete map2P;
}

//������
void GameMainTag2P::Init()
{
	camera2P.Camera2P();
	
}

//�A�b�v�f�[�g
void GameMainTag2P::Update()
{
	camera2P.Camera2PUpdate();
}

//�`��
void GameMainTag2P::Draw()
{
	map2P->MapRender();

}