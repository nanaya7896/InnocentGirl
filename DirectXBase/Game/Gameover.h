#pragma once

#include"../Global.h"
#include"../Direct3D/direct3d.h"
#include"../Direct3D/sprite.h"
#include"../Direct3D/texture.h"
#include"../DirectInput/directInput.h"
#include"SceneChange.h"
#include"GameMainTag.h"
#include"Title.h"


#define GAMEOVER1_SPRITE_SIZE_X 1600   //�Q�[���I�[�o�[�P�i�w�i�j�̃T�C�Y�i�w�j
#define GAMEOVER1_SPRITE_SIZE_Y 900    //�Q�[���I�[�o�[�P�i�w�i�j�̃T�C�Y�i�x�j

#define GAMEOVER2_SPRITE_SIZE_X 70    //�Q�[���I�[�o�[�Q�i�₶�邵�j�̃T�C�Y�i�w�j
#define GAMEOVER2_SPRITE_SIZE_Y 70    //�Q�[���I�[�o�[�Q�i�₶�邵�j�̃T�C�Y�i�x�j

#define GAMEOVER3_SPRITE_SIZE_X 210   //�Q�[���I�[�o�[�R�i���g���C�j�̃T�C�Y�i�w�j
#define GAMEOVER3_SPRITE_SIZE_Y 70    //�Q�[���I�[�o�[�R�i���g���C�j�̃T�C�Y�i�x�j

#define GAMEOVER4_SPRITE_SIZE_X 490   //�Q�[���I�[�o�[�S�i�`���v�^�[�ցj�̃T�C�Y�i�w�j
#define GAMEOVER4_SPRITE_SIZE_Y 70    //�Q�[���I�[�o�[�S�i�`���v�^�[�ցj�̃T�C�Y�i�x�j

#define GAMEOVER1_SPRITE_POS_X 800     //�Q�[���I�[�o�[�P�i�w�i�j�̈ʒu�i�w�j
#define GAMEOVER1_SPRITE_POS_Y 450     //�Q�[���I�[�o�[�P�i�w�i�j�̈ʒu�i�x�j

#define GAMEOVER2_SPRITE_POS_X 370     //�Q�[���I�[�o�[�Q�i�₶�邵�j�̈ʒu�i�w�j
#define GAMEOVER2_SPRITE_POS_Y 700     //�Q�[���I�[�o�[�Q�i�₶�邵�j�̈ʒu�i�x�j

#define GAMEOVER3_SPRITE_POS_X 500     //�Q�[���I�[�o�[�R�i���g���C�j�̈ʒu�i�w�j
#define GAMEOVER3_SPRITE_POS_Y 700     //�Q�[���I�[�o�[�R�i���g���C�j�̈ʒu�i�x�j

#define GAMEOVER4_SPRITE_POS_X 1100     //�Q�[���I�[�o�[�S�i�`���v�^�[�ցj�̈ʒu�i�w�j
#define GAMEOVER4_SPRITE_POS_Y 700     //�Q�[���I�[�o�[�S�i�`���v�^�[�ցj�̈ʒu�i�x�j



class Gameover :public SceneChange,Direct3D
{
private:
	//�e�N�X�`���ƃX�v���C�g
	Texture gameover1;
	Sprite gameoverSprite1;

	Texture gameover2;
	Sprite gameoverSprite2;

	Texture gameover3;
	Sprite gameoverSprite3;

	Texture gameover4;
	Sprite gameoverSprite4;


public:

	//�R���X�g���N�^�@�f�X�g���N�^
	Gameover();
	~Gameover();

	void Load();
	//update
	void Update();

	//draw
	void Draw();

};