#pragma once

#define DIRECTSOUND_VERSION 0x800
#define DIRECTINPUT_VERSION 0x800
//ウィンドウサイズ
#define WINDOW_WIDTH  1600
#define WINDOW_HEIGHT  900
//delete用
#define SAFE_DELETE_ARRAY(p){if(p){delete[] (p);(p)=NULL;}}


#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3dxof.lib")
#pragma comment(lib, "dxguid.lib")
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
#include<string.h>
#include<XInput.h>
//Direct3D
#include <d3d9.h>
#include <d3dx9.h>
#include<d3dx9anim.h>
#include <dinput.h>

//ライブラリの読み込み
#include"LMath.h"