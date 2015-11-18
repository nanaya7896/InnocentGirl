#pragma once

#include "../Direct3D/direct3d.h"
#include "../Direct3D/sprite.h"
#include "../Direct3D/texture.h"
#include"../Global.h"
#include "../DirectInput/directInput.h"
#include"SceneChange.h"
#include"GameMainTag.h"
#include"Title.h"

#define YUKI_SPRITE_SIZE_X 450          //���L�����̃T�C�Y�i�w�j
#define YUKI_SPRITE_SIZE_Y 900          //���L�����̃T�C�Y�i�x�j

#define GAMECLEAR1_SPRITE_SIZE_X 1600   //�Q�[���N���A�P�̃T�C�Y�i�w�j
#define GAMECLEAR1_SPRITE_SIZE_Y 900    //�Q�[���N���A�P�̃T�C�Y�i�x�j

#define GAMECLEAR2_SPRITE_SIZE_X 950    //�Q�[���N���A�Q�̃T�C�Y�i�w�j
#define GAMECLEAR2_SPRITE_SIZE_Y 100    //�Q�[���N���A�Q�̃T�C�Y�i�x�j

#define GAMECLEAR3_SPRITE_SIZE_X 1100   //�Q�[���N���A�R�̃T�C�Y�i�w�j
#define GAMECLEAR3_SPRITE_SIZE_Y 220    //�Q�[���N���A�R�̃T�C�Y�i�x�j

#define YUKI_SPRITE_POS_X 1420         //���L�����̈ʒu�i�w�j
#define YUKI_SPRITE_POS_Y 450          //���L�����̈ʒu�i�x�j

#define GAMECLEAR1_SPRITE_POS_X 800     //�Q�[���N���A�P�̈ʒu�i�w�j
#define GAMECLEAR1_SPRITE_POS_Y 450     //�Q�[���N���A�P�́i�x�j

#define GAMECLEAR2_SPRITE_POS_X 700     //�Q�[���N���A�Q�̈ʒu�i�w�j
#define GAMECLEAR2_SPRITE_POS_Y 550     //�Q�[���N���A�Q�̈ʒu�i�x�j

#define GAMECLEAR3_SPRITE_POS_X 680     //�Q�[���N���A�R�̈ʒu�i�w�j
#define GAMECLEAR3_SPRITE_POS_Y 400     //�Q�[���N���A�R�̈ʒu�i�x�j



class CResult :public SceneChange,Direct3D
{
private:
	//�e�N�X�`���ƃX�v���C�g
	Texture yukiR1Tex;
	Sprite yukiR1Sprite;

	Texture yukiR2Tex;
	Sprite yukiR2Sprite;

	Texture yukiR3Tex;
	Sprite yukiR3Sprite;

	Texture gameclear1;
	Sprite gameclearSprite1;

	Texture gameclear2;
	Sprite gameclearSprite2;

	Texture gameclear3;
	Sprite gameclearSprite3;

	int randomNum;    //�����_���ϐ��i�[�p
public:

	//�R���X�g���N�^�@�f�X�g���N�^
	CResult();
	~CResult();


	void Load();

	//update
	void Update();

	//draw
	void Draw();

	// �ő�ƍŏ��̊Ԃ̒l�������_���ɕԂ��w���p�[�֐�
	float Random(float min, float max);

};