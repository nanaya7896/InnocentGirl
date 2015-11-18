#pragma once

#include"../Global.h"
#include "../Direct3D\texture.h"
#include "../Direct3D\sprite.h"
#include "../Direct3D/direct3d.h"
#include "../DirectInput\directInput.h"
#include"Chapter_GameOfTag.h"
#include "SceneChange.h"

//�h���N���X:Chapter ���N���X:SceneChange,Direct3D
class Chapter :public SceneChange,Direct3D
{
private:
	//�}�[�J�[
	float y = 300.0f;

public:
	Texture chapter_texture_onigo;
	Texture chapter_texture_dodge;
	Texture chapter_texture_marker;
	Sprite chapter_sprite_onigo;
	Sprite chapter_sprite_dodge;
	Sprite chapter_sprite_marker;

	//�w�i�e�N�X�`���A�X�v���C�g�ǂݍ���
	Texture t_bgChapter;
	Sprite s_bgChapter;
	bool chapter_flag;

	//�R���X�g���N�^
	Chapter();
	//�f�X�g���N�^
	~Chapter();

	void Update();
	void Draw();

	void Load();
};