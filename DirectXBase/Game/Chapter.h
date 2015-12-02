#pragma once

#include "../Global.h"

#include "../Direct3D\texture.h"
#include "../Direct3D\sprite.h"
#include "../Direct3D/direct3d.h"
#include "../SceneChanger/BaseScene.h"
#include "../SceneChanger/ISceneChanger.h"
#include "../DirectInput\directInput.h"
#include"Title.h"
#include "GameMainTag.h"
#include "GameMainTag2P.h"


#include"../DirectSound/dxsound.h"

#include"../Xinput/XbonInput.h"


//�h���N���X:Chapter ���N���X:SceneChange,Direct3D
class Chapter :public BaseScene, Direct3D
{
public:
	//�w�i
	Texture chapter_bg;
	Sprite schapter_bg;
	//�������
	Texture tContTx;
	Sprite sContTx;
	//�}�[�J�[
	Texture marker;
	Sprite smarker[2];
	//���ɂ�����
	Texture chapter_onigo;
	Sprite schapter_onigo;
	//�h�b�a�{�[��
	Texture chapter_dodge;
	Sprite schapter_dodge;
	//�`���v�^�[
	Texture chapter[2];
	Sprite schapter[2];
	//�Q�[�����
	Texture GameScreen[2];
	Sprite sGameScreen[2];
	//�ЂƂ�
	Texture hitori[2];
	Sprite shitori[2];
	//�Ƃ�����
	Texture tomodati[2];
	Sprite stomodati[2];
	//Coming Soon
	Texture coming;
	Sprite scoming;
	//Wave�t�@�C��
	CSound wave[3];

	XboxInput chaInput;
	//�t���O
	bool chapter_flag;
	bool member_flag;
	bool marker_flag;
	bool ContFlag;

	//�R���X�g���N�^
	Chapter(ISceneChanger *changer);
	//�f�X�g���N�^
	~Chapter();

	void Initialize() override;    //�������������I�[�o�[���C�h�B
	void Finalize() override;        //�I���������I�[�o�[���C�h�B
	void Update() override;
	void Draw() override;
};