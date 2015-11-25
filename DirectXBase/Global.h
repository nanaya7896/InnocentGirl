#pragma once

#define DIRECTSOUND_VERSION 0x800
#define DIRECTINPUT_VERSION 0x800

//シンボル定義およびマクロ
#define SAFE_DELETE_ARRAY(p){if(p){delete[] (p);(p)=NULL;}}
#define SAFE_DELETE(p)		{if(p){delete(p);(p)=NULL;}}
#define SAFE_RELEASE(p)		{if(p){(p)->Release();(p)=NULL;}}
//FPS(1秒 = 1000/FPSミリ秒)
#define FPS 60
#define GameFPS 60
//アニメーションコントローラーのスピード
#define SKIN_ANIME_SPEED 60.0f / 4800.0f




//ウィンドウサイズ
const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 900;

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3dxof.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib,"dsound.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"xinput.lib ")

//C++
#include <Windows.h>
#include <comdef.h>
#include <dsound.h>
#include <mmsystem.h>
#include <tchar.h>
#include <vector>
#include <strsafe.h>
#include<string.h>
#include<XInput.h>
#include<math.h>
#include<map>
#include<string>
#include<list>
#include<iostream>
#include<sstream>
#include <complex>
#include <XInput.h>
#include <algorithm>
//Direct3D
#include <d3d9.h>
#include <d3dx9.h>
#include<d3dx9anim.h>
#include <dinput.h>

//ライブラリの読み込み
//#include"LMath.h"

