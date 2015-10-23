#pragma once

#define DIRECTSOUND_VERSION 0x800
#define DIRECTINPUT_VERSION 0x800

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3dxof.lib")
#pragma comment(lib,"d3dxof.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib,"dsound.lib")
#pragma comment(lib, "winmm.lib")


//C++
#include <comdef.h>
#include <dsound.h>
#include <mmsystem.h>
#include <tchar.h>
#include <vector>
#include <strsafe.h>
//Direct3D
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

//ƒ‰ƒCƒuƒ‰ƒŠ‚Ì“Ç‚İ‚İ
#include"LMath.h"