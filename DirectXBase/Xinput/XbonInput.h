#pragma once
#include"../Global.h"
const short GAMEPAD_THUMBSTICK_DEADZONE = (short)(0.20f * 0X7FFF);    // default to 20% of range as deadzone
const short GAMEPAD_TRIGGER_DEADZONE = 20;                      // trigger range 0-255
const DWORD MAX_CONTROLLERS = 4;
const DWORD GAMEPAD_DPAD_UP = 0x0001;
const DWORD GAMEPAD_DPAD_DOWN = 0x0002;
const DWORD GAMEPAD_DPAD_LEFT = 0x0004;
const DWORD GAMEPAD_DPAD_RIGHT = 0x0008;
const DWORD GAMEPAD_START_BUTTON = 0x0010;
const DWORD GAMEPAD_BACK_BUTTON = 0x0020;
const DWORD GAMEPAD_LEFT_THUMB = 0x0040;
const DWORD GAMEPAD_RIGHT_THUMB = 0x0080;
const DWORD GAMEPAD_LEFT_SHOULDER = 0x0100;
const DWORD GAMEPAD_RIGHT_SHOULDER = 0x0200;
const DWORD GAMEPAD_A = 0x1000;
const DWORD GAMEPAD_B = 0x2000;
const DWORD GAMEPAD_X = 0x4000;
const DWORD GAMEPAD_Y = 0x8000;

struct ControllerState
{
	XINPUT_STATE        state;
	XINPUT_VIBRATION    vibration;
	float               vibrateTimeLeft;    // mSec
	float               vibrateTimeRight;   // mSec
	bool                connected;
};

class XboxInput
{
private:
	ControllerState controllers[MAX_CONTROLLERS];    // state of controllers
	short thumbstickDeadzone;
	short triggerDeadzone;

public:
	XboxInput();
	virtual ~XboxInput();
	void Initialize();
	// Update connection status of game controllers.
	void checkControllers();

	// Save input from connected game controllers.
	void readControllers();

	// Set thumbstick deadzone
	void setThumbstickDeadzone(short dz) { thumbstickDeadzone = abs(dz); }

	// Set trigger deadzone
	void setTriggerDeadzone(BYTE dz) { triggerDeadzone = dz; }

	// Get thumbstick deadzone
	short getThumbstickDeadzone() { return thumbstickDeadzone; }

	// Get trigger deadzone
	BYTE getTriggerDeadzone() { return static_cast<BYTE>(triggerDeadzone); }

	// Return state of specified game controller.
	const ControllerState* getControllerState(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return &controllers[n];
	}

	// Return connection state of specified game controller
	bool getGamepadConnected(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return controllers[n].connected;
	}

	// Return state of controller n buttons.
	const WORD getGamepadButtons(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return controllers[n].state.Gamepad.wButtons;
	}

	// Return state of controller n D-pad Up
	bool getGamepadDPadUp(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return ((controllers[n].state.Gamepad.wButtons&GAMEPAD_DPAD_UP) != 0);
	}

	// Return state of controller n D-pad Down.
	bool getGamepadDPadDown(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return ((controllers[n].state.Gamepad.wButtons&GAMEPAD_DPAD_DOWN) != 0);
	}

	// Return state of controller n D-pad Left.
	bool getGamepadDPadLeft(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return ((controllers[n].state.Gamepad.wButtons&GAMEPAD_DPAD_LEFT) != 0);
	}

	// Return state of controller n D-pad Right.
	bool getGamepadDPadRight(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_DPAD_RIGHT) != 0);
	}

	// Return state of controller n Start button.
	bool getGamepadStart(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_START_BUTTON) != 0);
	}

	// Return state of controller n Back button.
	bool getGamepadBack(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_BACK_BUTTON) != 0);
	}

	// Return state of controller n Left Thumb button.
	bool getGamepadLeftThumb(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_LEFT_THUMB) != 0);
	}

	// Return state of controller n Right Thumb button.
	bool getGamepadRightThumb(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_RIGHT_THUMB) != 0);
	}

	// Return state of controller n Left Shoulder button.
	bool getGamepadLeftShoulder(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_LEFT_SHOULDER) != 0);
	}

	// Return state of controller n Right Shoulder button.
	bool getGamepadRightShoulder(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_RIGHT_SHOULDER) != 0);
	}

	// Return state of controller n A button.
	bool getGamepadA(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_A) != 0);
	}

	// Return state of controller n B button.
	bool getGamepadB(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_B) != 0);
	}

	// Return state of controller n X button.
	bool getGamepadX(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_X) != 0);
	}

	// Return state of controller n Y button.
	bool getGamepadY(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_Y) != 0);
	}

	// Return value of controller n Left Trigger (0 through 255).
	// Trigger movement less than GAMEPAD_TRIGGER_DEADZONE returns 0.
	// Return value is scaled to 0 through 255
	BYTE getGamepadLeftTrigger(UINT n);

	// Return value of controller n Left Trigger (0 through 255).
	// Deadzone is not applied.
	BYTE getGamepadLeftTriggerUndead(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return controllers[n].state.Gamepad.bLeftTrigger;
	}

	// Return value of controller n Right Trigger (0 through 255).
	// Trigger movement less than GAMEPAD_TRIGGER_DEADZONE returns 0.
	// Return value is scaled to 0 through 255
	BYTE getGamepadRightTrigger(UINT n);

	// Return value of controller n Right Trigger (0 through 255).
	// Deadzone is not applied.
	BYTE getGamepadRightTriggerUndead(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return controllers[n].state.Gamepad.bRightTrigger;
	}

	// Return value of controller n Left Thumbstick X (-32767 through 32767).
	// Stick movement less than GAMEPAD_THUMBSTICK_DEADZONE returns 0.
	// Return value is scaled to -32768 through 32767
	SHORT getGamepadThumbLX(UINT n);

	// Return value of controller n Left Thumbstick X (-32767 through 32767).
	// Deadzone is not applied.
	SHORT getGamepadThumbLXUndead(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return controllers[n].state.Gamepad.sThumbLX;
	}

	// Return value of controller n Left Thumbstick Y (-32768 through 32767).
	// Stick movement less than GAMEPAD_THUMBSTICK_DEADZONE returns 0.
	// Return value is scaled to -32768 through 32767
	SHORT getGamepadThumbLY(UINT n);

	// Return value of controller n Left Thumbstick Y (-32768 through 32767).
	// Deadzone is not applied.
	SHORT getGamepadThumbLYUndead(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return controllers[n].state.Gamepad.sThumbLY;
	}

	// Return value of controller n Right Thumbstick X (-32768 through 32767).
	// Stick movement less than GAMEPAD_THUMBSTICK_DEADZONE returns 0.
	// Return value is scaled to -32768 through 32767
	SHORT getGamepadThumbRX(UINT n);

	// Return value of controller n Right Thumbstick X (-32768 through 32767).
	// Deadzone is not applied.
	SHORT getGamepadThumbRXUndead(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)   // if invalid controller number
			n = MAX_CONTROLLERS - 1;    // force valid
		return controllers[n].state.Gamepad.sThumbRX;
	}

	// Return value of controller n Right Thumbstick Y (-32768 through 32767).
	// Stick movement less than GAMEPAD_THUMBSTICK_DEADZONE returns 0.
	// Return value is scaled to -32768 through 32767
	SHORT getGamepadThumbRY(UINT n);

	// Return value of controller n Right Thumbstick Y (-32768 through 32767).
	// Deadzone is not applied.
	SHORT getGamepadThumbRYUndead(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return controllers[n].state.Gamepad.sThumbRY;
	}

	// Vibrate controller n left motor.
	// Left is low frequency vibration.
	// speed 0=off, 65536=100 percent
	// sec is time to vibrate in seconds
	void gamePadVibrateLeft(UINT n, WORD speed, float sec)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		controllers[n].vibration.wLeftMotorSpeed = speed;
		controllers[n].vibrateTimeLeft = sec;
	}

	// Vibrate controller n right motor.
	// Right is high frequency vibration.
	// speed 0=off, 65536=100 percent
	// sec is time to vibrate in seconds
	void gamePadVibrateRight(UINT n, WORD speed, float sec)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		controllers[n].vibration.wRightMotorSpeed = speed;
		controllers[n].vibrateTimeRight = sec;
	}

	// Vibrates the connected controllers for the desired time.
	void vibrateControllers(float frameTime);
};