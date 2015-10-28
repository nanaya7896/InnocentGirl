#include "directInput.h"

DirectInput & DirectInput::GetInstance()
{
	static DirectInput directInput;

	return directInput;

}

//�R���X�g���N�^
DirectInput::DirectInput()
{
	pDInput			= NULL;
	pKeyDevice		= NULL;
	pMouseDevice	= NULL;

	//�\���̂̏����� �S�Ă�0�ŏ�����
	ZeroMemory(&keyInput,sizeof(int)*INPUT_BUFFER_SIZE);
	ZeroMemory(&keyInputPreview, sizeof(int)*INPUT_BUFFER_SIZE);
	ZeroMemory(&mouseInput, sizeof(DIMOUSESTATE2));
	ZeroMemory(&mouseInputPreview, sizeof(DIMOUSESTATE2));

	for (int i = 0; i < 8; i++)
	{
		mouseButtonCounter[i] = 0;
	}

	mousePos.Set(0, 0);
	mousePosDelta.Set(0, 0);
	mousePosPreview.Set(0, 0);

}

//�f�X�g���N�^
DirectInput::~DirectInput()
{
	Release();
}

//������
HRESULT DirectInput::Init()
{


	//DirectInput�I�u�W�F�N�g�̍쐬
	//hresult�ɂ�FAILED/SUCCEEDED���Ő^�U���m���߂�̂Ɏg������
	HRESULT hresult = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, NULL);
	if (FAILED(hresult))
	{
		return hresult;
	}

	//�L�[�{�[�h����������
	hresult = InitKey();
	if (FAILED(hresult))
	{
		return hresult;
	}

	//�}�E�X������
	hresult = InitMouse();
	if (FAILED(hresult))
	{
		return hresult;
	}

	return S_OK;
	
}

//�L�[�z�񏉊���
HRESULT DirectInput::InitKey()
{
	HRESULT hresult;

	//�f�o�C�X�I�u�W�F�N�g�̍쐬
	hresult = pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, NULL);	
	if (FAILED(hresult))
	{
		return hresult;
	}

	//�f�[�^�t�H�[�}�b�g�ݒ�
	hresult = pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hresult))
	{
		return hresult;
	}

	//�������[�h��ݒ�t���O	����
	//DISCL_NONEXCLUSIVE
	//	DISCL_BACKGROUND	�f�t�H���g�ݒ�
	//	DISCL_NONEXCLUSIVE
	//	DISCL_FOREGROUND
	//	DISCL_EXCLUSIVE
	//	DISCL_FOREGROUND
	//	DISCL_EXCLUSIVE	�L�[�{�[�h�܂��̓}�E�X�ɂ͖���
	//	DISCL_BACKGROUND
	//���̃v���O�����Ƃ̊֘A���݂����Ȃ��̂�ݒ肷��K�v������܂��B�E�B���h�E���A�N�e�B�u�ȂƂ��̂ݓ��͂��擾���邩�A����Ƃ��o�O�O���E���h�Ɉړ����Ă���Ƃ����擾���邩�A�Ȃǂ̐ݒ�
	hresult = pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	if (FAILED(hresult))
	{
		return hresult;
	}

	pKeyDevice->Acquire();

	return S_OK;
}

//�}�E�X��Ԃ��Ǘ�����N���X�C���X�^���X��������
HRESULT DirectInput::InitMouse()
{
	HRESULT hresult;

	hresult = pDInput->CreateDevice(GUID_SysMouse, &pMouseDevice, NULL);
	//�f�o�C�X�I�u�W�F�N�g�̍쐬
	if (FAILED(hresult))
	{
		return hresult;
	}

	//�f�[�^�t�H�[�}�b�g���쐬
	hresult = pMouseDevice->SetDataFormat(&c_dfDIMouse2);
	if (FAILED(hresult))
	{
		return hresult;
	}
	//�������[�h��ݒ�
	hresult = pMouseDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	if (FAILED(hresult))
	{
		return hresult;
	}

	//�����[�h��ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	//����
	//diprop.dwData = DIPROPAXISMODE_ABS;//���

	hresult = pMouseDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph);
	if (FAILED(hresult))
	{
		return hresult;
	}

	pMouseDevice->Acquire();

	return S_OK;
}


//�A�b�v�f�[�g
HRESULT DirectInput::Update()
{
	HRESULT hresult = pKeyDevice->Acquire();

	if ((hresult == DI_OK) || (hresult == S_FALSE))
	{
		//�O��̃L�[���͏���ޔ�
		memcpy(keyInputPreview, keyInput, sizeof(int)*INPUT_BUFFER_SIZE);

		//��ԃ��[�N
		BYTE tKeyInputWork[INPUT_BUFFER_SIZE];

		pKeyDevice->GetDeviceState(sizeof(BYTE)*INPUT_BUFFER_SIZE, &tKeyInputWork);

		for (int i = 0; i < INPUT_BUFFER_SIZE; i++)
		{
			if (tKeyInputWork[i])
			{
				if (keyInput[i] < 2147483647)//int �ő�l�܂�
				{
					keyInput[i]++;
				}				
			}
			else
			{
				keyInput[i] = 0;
			}
		}
	}

	//�}�E�X�̃{�^����Ԃ��擾
	hresult = pMouseDevice->Acquire();
	if (hresult == DI_OK || hresult == S_FALSE)
	{
		//�O��̃}�E�X��Ԃ�ޔ�
		memcpy(&mouseInputPreview, &mouseInput, sizeof(DIMOUSESTATE2));

		pMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &mouseInput);
	
		for (int i = 0; i < 8; i++)
		{
			if (mouseInput.rgbButtons[i])
			{
				if (mouseButtonCounter[i] < 2147483647)//int �ő�l�܂�
				{
					mouseButtonCounter[i]++;
				}
			}
			else
			{
				mouseButtonCounter[i] = 0;
			}
		}
	}

	//�X�N���[�����@�}�E�X���W�擾
	POINT worldPos;
	GetCursorPos(&worldPos);//���[���h���W���擾
	POINT localPos = worldPos;
	ScreenToClient(hWnd,&localPos);//���[���h���W�����[�J�����W�ɕϊ�

	mousePosPreview = mousePos;
	mousePos.Set(localPos.x, localPos.y);
	mousePosDelta = mousePos-mousePosPreview;


	return S_OK;
}

//�������
HRESULT  DirectInput::Release()
{
	int a = 0;
	if (pMouseDevice)
	{
		//���b�N�̉���
		pMouseDevice->Unacquire();
		//�f�o�C�X�̉��
		pMouseDevice->Release();
		//NULL������Ӗ��B�|�C���^�^�ɂO��������Ƃǂ��̃A�h���X�������Ă��Ȃ����ƂɂȂ�
		pMouseDevice = NULL;
	}
	
	if (pKeyDevice)
	{
		pKeyDevice->Unacquire();
		pKeyDevice->Release();
		pKeyDevice = NULL;
	}

	if (pDInput)
	{
		pDInput->Release();
		pDInput = NULL;
	}
	
	return S_OK;
}

//�L�[��������Ă���Ȃ�true
bool DirectInput::KeyState(int code)
{
	if (code >= 0 && code < INPUT_BUFFER_SIZE)
	{
		if (keyInput[code] > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

//1�t���[���O�̃L�[���
bool DirectInput::KeyStatePreview(int code)
{
	if (code >= 0 && code < INPUT_BUFFER_SIZE)
	{
		if (keyInputPreview[code] > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

//�L�[�������ꂽ�u�Ԃ�
bool DirectInput::KeyDown(int code)
{
	if (code >= 0 && code < INPUT_BUFFER_SIZE)
	{
		return  (keyInput[code] >= 1) && (keyInputPreview[code] == 0);
	}
	return false;
}

//�L�[�������ꂽ�u�Ԃ�
bool DirectInput::KeyUp(int code)
{
	if (code >= 0 && code < INPUT_BUFFER_SIZE)
	{
		return   (keyInput[code] == 0) && (keyInputPreview[code] >= 1);
	}
	return false;
}
//�L�[�������ꑱ���Ă���t���[����
int DirectInput::KeyCount(int code)
{
	if (code >= 0 && code < INPUT_BUFFER_SIZE)
	{
		return keyInput[code];
	}
	return 0;
}

//�}�E�X�̃{�^�����
bool DirectInput::MouseButton(int num)
{ 
	if (num >= 0 && num < 8)
	{
		//return ();��bool�^�Ƃ��Ĉ������Ƃ��ł���
		return (mouseInput.rgbButtons[num] >= 1);
	}
	else
	{
		return false;
	}
}

//�}�E�X�̃{�^���������ꂽ�u�Ԃ�
bool DirectInput::MouseButtonDown(int num)
{
	if (num >= 0 && num < 8)
	{
		return (mouseInput.rgbButtons[num] >= 1) && (mouseInputPreview.rgbButtons[num] == 0);
	}
	else
	{
		return false;
	}
}

//�}�E�X�{�^���������ꂽ�u�Ԃ�
bool DirectInput::MouseButtonUP(int num)
{
	if (num >= 0 && num < 8)
	{
		return (mouseInput.rgbButtons[num] ==0) && (mouseInputPreview.rgbButtons[num] >=1);
	}
	else
	{
		return false;
	}
}

//�}�E�X�{�^���������ꑱ���Ă���t���[����
int DirectInput::MouseButtonCount(int num)
{
	if (num >= 0 && num < 8)
	{
		return mouseButtonCounter[num];
	}
	else
	{
		return 0;
	}
}