

#pragma once
#include"../Global.h"

#ifndef STRICT
#define STRICT
#endif

inline void JoypadEnable(bool enable){ XInputEnable(enable); }

//�N���X
class Joypad
{
public:
	//�{�^���N���X
	enum class Button
	{
		A = XINPUT_GAMEPAD_A,	//A�{�^��
		B = XINPUT_GAMEPAD_B,	//B�{�^��
		X = XINPUT_GAMEPAD_X,	//X�{�^��
		Y = XINPUT_GAMEPAD_Y,	//Y�{�^��
		Start = XINPUT_GAMEPAD_START,	//START�{�^��
		Back = XINPUT_GAMEPAD_BACK,	//BACK�{�^��
		Up = XINPUT_GAMEPAD_DPAD_UP,
		Down = XINPUT_GAMEPAD_DPAD_DOWN,
		Left = XINPUT_GAMEPAD_DPAD_LEFT,
		Right = XINPUT_GAMEPAD_DPAD_RIGHT,
		LThumb = XINPUT_GAMEPAD_LEFT_THUMB,
		RThumb = XINPUT_GAMEPAD_RIGHT_THUMB,
		LShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
		RShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,

	};

	Joypad(int userIndex) : m_UserIndex(userIndex) {}

	bool update();
	bool isPushed(Button button);
	bool vibrate(double leftMotorSpeedByPercent, double rightMotorSpeedByPercent);
	bool isConnected();
	double getLTrigger(double thresholdByPercent = XINPUT_GAMEPAD_TRIGGER_THRESHOLD / (double)TriggerMax);
	double getRTrigger(double thresholdByPercent = XINPUT_GAMEPAD_TRIGGER_THRESHOLD / (double)TriggerMax);
	std::complex<double> getLStick(double thresholdByPercent = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE / (double)StickMax);
	std::complex<double> getRStick(double thresholdByPercent = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE / (double)StickMax);
	int getUserIndex();

private:
	static const long TriggerMax = 255;
	static const long MotorSpeedMax = 65535;
	static const long StickMax = 32767;

	int m_UserIndex;
	XINPUT_STATE m_State;
	bool m_Connected;

};




