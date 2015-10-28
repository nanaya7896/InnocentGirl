#pragma once 

#define D3D_DEBUG_INFO	//Direct3Dデバッグフラグ


#define MOUSE_BUTTON_LEFT 0
#define MOUSE_BUTTON_RIGHT 1
#define MOUSE_BUTTON_MIDDLE 2
#define INPUT_BUFFER_SIZE 256


#include"../Global.h"
#include "../other/MyVector.h"




class DirectInput
{

	LPDIRECTINPUT8		 pDInput;			//directinput オブジェクト
	LPDIRECTINPUTDEVICE8 pKeyDevice;		//キーボード用デバイス
	LPDIRECTINPUTDEVICE8 pMouseDevice;		//マウス用デバイス

	//キーボード情報
	int keyInput[INPUT_BUFFER_SIZE];
	int keyInputPreview[INPUT_BUFFER_SIZE];
	

	//マウス情報
	DIMOUSESTATE2 mouseInput;
	DIMOUSESTATE2 mouseInputPreview;
	int mouseButtonCounter[8];

	Vector2 mousePos;
	Vector2 mousePosPreview;
	Vector2 mousePosDelta;
	
	HWND		  hWnd;

private:

	HRESULT InitKey();//キーボードの初期化
	HRESULT InitMouse();
	//コンストラクタデストラクタ
	DirectInput();
	~DirectInput();
public:

	static DirectInput & GetInstance();

	//初期化処理
	HRESULT Init();

	//キー状態の更新処理
	HRESULT Update();

	//解放処理
	HRESULT Release();	


	//値取得関数

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
