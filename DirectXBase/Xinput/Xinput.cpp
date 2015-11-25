#include "Xinput.h"



//�{�^���������Ă��邩�̔���
bool Joypad::isPushed(Button button)
{
	return isConnected() && (m_State.Gamepad.wButtons & static_cast<int>(button));
}
//�ڑ�����Ă���䐔�̔���
bool Joypad::isConnected()
{
		return m_Connected;	
}

//�L�[�̃A�b�v�f�[�g
bool Joypad::update()
{
	m_Connected = (XInputGetState(m_UserIndex, &m_State) == ERROR_SUCCESS);
	return m_Connected;
}
//�v���C���[�ԍ�
int Joypad::getUserIndex()
{
	return m_UserIndex;
}
//L�X�e�B�b�N�̔���
std::complex<double> Joypad::getLStick(double thresholdByPercent)
{
		if (!isConnected())return std::complex<double>(0, 0);
		auto y_abs = std::abs(m_State.Gamepad.sThumbLY) / (double)StickMax;
		auto y_sign = (m_State.Gamepad.sThumbLY < 0) ? -1 : 1;
		auto x_abs = std::abs(m_State.Gamepad.sThumbLX) / (double)StickMax;
		auto x_sign = (m_State.Gamepad.sThumbLX < 0) ? -1 : 1;

		return std::complex<double>(
			(x_abs < thresholdByPercent) ? 0 : x_abs * x_sign,
			(y_abs < thresholdByPercent) ? 0 : y_abs * y_sign
			);
	
}

//R�X�e�B�b�N�̔���
std::complex<double> Joypad::getRStick(double thresholdByPercent)
{

	if (!isConnected())return std::complex<double>(0, 0);
	auto y_abs = std::abs(m_State.Gamepad.sThumbRY) / (double)StickMax;
	auto y_sign = (m_State.Gamepad.sThumbRY < 0) ? -1 : 1;
	auto x_abs = std::abs(m_State.Gamepad.sThumbRX) / (double)StickMax;
	auto x_sign = (m_State.Gamepad.sThumbRX < 0) ? -1 : 1;

	return std::complex<double>(
		(x_abs < thresholdByPercent) ? 0 : x_abs * x_sign,
		(y_abs < thresholdByPercent) ? 0 : y_abs * y_sign
		);

}

//L�g���K�[�̔���
double Joypad::getLTrigger(double thresholdByPercent)
{
	if (!isConnected()) return 0;
	auto t = m_State.Gamepad.bLeftTrigger / (double)TriggerMax;

	return (t < thresholdByPercent) ? 0 : t;

}

//R�g���K�[�̔���
double Joypad::getRTrigger(double thresholdByPercent)
{
	if (!isConnected()) return 0;
	auto t = m_State.Gamepad.bRightTrigger / (double)TriggerMax;

	return (t < thresholdByPercent) ? 0 : t;

}

bool Joypad::vibrate(double leftMotorSpeedByPercent, double rightMotorSpeedByPercent)
{
	XINPUT_VIBRATION vib;
	vib.wLeftMotorSpeed = leftMotorSpeedByPercent * MotorSpeedMax;
	vib.wRightMotorSpeed = rightMotorSpeedByPercent * MotorSpeedMax;

	return XInputSetState(m_UserIndex, &vib) == ERROR_SUCCESS;

}



