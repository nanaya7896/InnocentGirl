#pragma once

typedef enum{
	eScene_Title,		   		 //�^�C�g�����
	eScene_Chapter,				 //�`���v�^�[���
	eScene_GameMainTag1P,		 //�S������1P
	eScene_GameMainTag2P,		 //�S������2P
	eScene_GameMainDodge1P,		 //�h�b�W�{�[��1P
	eScene_GameMainDodge2P,		 //�h�b�W�{�[��2P
	eScene_Result,				 //���U���g
	eScene_GameOver, 			 //�Q�[���I�[�o�[

	eScene_None //����
}eScene;

//�V�[����ύX���邽�߂̃C���^�[�t�F�[�X�N���X
class ISceneChanger
{
public:
	virtual ~ISceneChanger() = 0;
	//�w��̃V�[���ɕύX����
	virtual void ChangeScene(eScene NextScene) = 0;

private:

};