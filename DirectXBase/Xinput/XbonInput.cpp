#include"XbonInput.h"


//=====================================================================
//関数名:XboxInout
//引数:なし
//説明:コンストラクタ
//		
//=====================================================================
XboxInput::XboxInput()
{
	//つないであるコントローラーの数初期値を指定
	for (int i = 0; i<MAX_CONTROLLERS; i++)
	{
		controllers[i].vibrateTimeLeft = 0;
		controllers[i].vibrateTimeRight = 0;
	}
	thumbstickDeadzone = GAMEPAD_THUMBSTICK_DEADZONE;    // default
	triggerDeadzone = GAMEPAD_TRIGGER_DEADZONE;          // default
}


//=====================================================================
//関数名:~XboxInout
//引数:なし
//説明:デストラクタ
//		
//=====================================================================
XboxInput::~XboxInput()
{


}

//=====================================================================
//関数名:checkControllers
//引数:なし
//説明:実機につないであるコントローラーの個数を調べる
//		
//=====================================================================

void XboxInput::checkControllers()
{
	DWORD result;
	for (DWORD i = 0; i <MAX_CONTROLLERS; i++)
	{
		result = XInputGetState(i, &controllers[i].state);
		if (result == ERROR_SUCCESS)
			controllers[i].connected = true;
		else
			controllers[i].connected = false;
	}
}

//=====================================================================
//関数名:readControllers
//引数:なし
//説明:接続されているコントローラーの状態を取得
//		
//=====================================================================
void XboxInput::readControllers()
{
	DWORD result;
	for (DWORD i = 0; i <MAX_CONTROLLERS; i++)
	{
		if (controllers[i].connected)
		{
			result = XInputGetState(i, &controllers[i].state);
			if (result == ERROR_DEVICE_NOT_CONNECTED)    // if controller disconnected
				controllers[i].connected = false;
		}
	}
}

//右トリガーが押されているかの判定
BYTE XboxInput::getGamepadRightTrigger(UINT n)
{
	BYTE value = getGamepadRightTriggerUndead(n);
	if (value > triggerDeadzone)    // if > dead zone
		//adjust magnitude relative to the end of the dead zone
		value = (value - triggerDeadzone) * 255 /
		(255 - triggerDeadzone);
	else                                    // else, < dead zone
		value = 0;
	return value;
}
//=====================================================================
//関数名:getGamepadThumbLX
//引数:コントローラーの番号
//説明:引数で渡されたコントローラーのＬスティックのＸ軸の傾きを
//		みる関数
//=====================================================================
SHORT XboxInput::getGamepadThumbLX(UINT n)
{
	int x = getGamepadThumbLXUndead(n);
	if (x > thumbstickDeadzone) // if +x outside dead zone
		//adjust x relative to the deadzone and scale to 0 through 32767
		x = (x - thumbstickDeadzone) * 32767 /
		(32767 - thumbstickDeadzone);
	else if (x < -thumbstickDeadzone)   // if -x outside dead zone
		//adjust y relative to the deadzone and scale to 0 through -32767
		x = (x + thumbstickDeadzone) * 32767 /
		(32767 - thumbstickDeadzone);
	else        // else, x inside dead zone
		x = 0;  // return 0
	return static_cast<SHORT>(x);
}

SHORT XboxInput::getGamepadThumbLY(UINT n)
{
	int y = getGamepadThumbLYUndead(n);
	if (y > thumbstickDeadzone) // if +y outside dead zone
		//adjust magnitude relative to the end of the dead zone
		y = (y - thumbstickDeadzone) * 32767 /
		(32767 - thumbstickDeadzone);
	else if (y < -thumbstickDeadzone)   // if -y outside dead zone
		//adjust magnitude relative to the end of the dead zone
		y = (y + thumbstickDeadzone) * 32767 /
		(32767 - thumbstickDeadzone);
	else        // else, y inside dead zone
		y = 0;  // return 0
	return static_cast<SHORT>(y);
}

SHORT XboxInput::getGamepadThumbRX(UINT n)
{
	int x = getGamepadThumbRXUndead(n);
	if (x > thumbstickDeadzone) // if +x outside dead zone
		//adjust magnitude relative to the end of the dead zone
		x = (x - thumbstickDeadzone) * 32767 /
		(32767 - thumbstickDeadzone);
	else if (x < -thumbstickDeadzone)   // if -x outside dead zone
		//adjust magnitude relative to the end of the dead zone
		x = (x + thumbstickDeadzone) * 32767 /
		(32767 - thumbstickDeadzone);
	else        // else, x inside dead zone
		x = 0;  // return 0
	return static_cast<SHORT>(x);
}

SHORT XboxInput::getGamepadThumbRY(UINT n)
{
	int y = getGamepadThumbRYUndead(n);
	if (y > thumbstickDeadzone) // if +y outside dead zone
		//adjust magnitude relative to the end of the dead zone
		y = (y - thumbstickDeadzone) * 32767 /
		(32767 - thumbstickDeadzone);
	else if (y < -thumbstickDeadzone)   // if -y outside dead zone
		//adjust magnitude relative to the end of the dead zone
		y = (y + thumbstickDeadzone) * 32767 /
		(32767 - thumbstickDeadzone);
	else        // else, y inside dead zone
		y = 0;  // return 0
	return static_cast<SHORT>(y);
}


void XboxInput::vibrateControllers(float frameTime)
{
	for (int i = 0; i < MAX_CONTROLLERS; i++)
	{
		if (controllers[i].connected)
		{
			controllers[i].vibrateTimeLeft -= frameTime;
			if (controllers[i].vibrateTimeLeft < 0)
			{
				controllers[i].vibrateTimeLeft = 0;
				controllers[i].vibration.wLeftMotorSpeed = 0;
			}
			controllers[i].vibrateTimeRight -= frameTime;
			if (controllers[i].vibrateTimeRight < 0)
			{
				controllers[i].vibrateTimeRight = 0;
				controllers[i].vibration.wRightMotorSpeed = 0;
			}
			XInputSetState(i, &controllers[i].vibration);
		}
	}
}