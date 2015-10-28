#pragma once 

#define D3D_DEBUG_INFO	//Direct3D�f�o�b�O�t���O


#define MOUSE_BUTTON_LEFT 0
#define MOUSE_BUTTON_RIGHT 1
#define MOUSE_BUTTON_MIDDLE 2
#define INPUT_BUFFER_SIZE 256


#include"../Global.h"
#include "../other/MyVector.h"




class DirectInput
{

	LPDIRECTINPUT8		 pDInput;			//directinput �I�u�W�F�N�g
	LPDIRECTINPUTDEVICE8 pKeyDevice;		//�L�[�{�[�h�p�f�o�C�X
	LPDIRECTINPUTDEVICE8 pMouseDevice;		//�}�E�X�p�f�o�C�X

	//�L�[�{�[�h���
	int keyInput[INPUT_BUFFER_SIZE];
	int keyInputPreview[INPUT_BUFFER_SIZE];
	

	//�}�E�X���
	DIMOUSESTATE2 mouseInput;
	DIMOUSESTATE2 mouseInputPreview;
	int mouseButtonCounter[8];

	Vector2 mousePos;
	Vector2 mousePosPreview;
	Vector2 mousePosDelta;
	
	HWND		  hWnd;

private:

	HRESULT InitKey();//�L�[�{�[�h�̏�����
	HRESULT InitMouse();
	//�R���X�g���N�^�f�X�g���N�^
	DirectInput();
	~DirectInput();
public:

	static DirectInput & GetInstance();

	//����������
	HRESULT Init();

	//�L�[��Ԃ̍X�V����
	HRESULT Update();

	//�������
	HRESULT Release();	


	//�l�擾�֐�

	bool KeyState(int code);
	bool KeyStatePreview(int code);
	bool KeyDown(int code);
	bool KeyUp(int code);
	int KeyCount(int code);

	DIMOUSESTATE2 MouseState(){ return  mouseInput; }
	DIMOUSESTATE2 MoouseStatePreview(){ return mouseInputPreview; }

	Vector2 MousePosition(){ return mousePos; }
	Vector2 MousePositionPreview(){ return mousePosPreview; }
	Vector2 MousePositionDelta(){ return mousePosDelta; }

	bool MouseButton(int num);
	bool MouseButtonDown(int num);
	bool MouseButtonUP(int num);
	int MouseButtonCount(int num);
};
