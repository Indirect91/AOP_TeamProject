#pragma once

#include <SDKDDKVer.h>

//▼Life of PI
#define PI 3.141592f
#define PI2 (PI * 2)
#define PI_2 (PI / 2) //90도
#define PI_4 (PI / 4) //45도
#define PI_8 (PI / 8) //22.5도

#define WIN32_LEAN_AND_MEAN
//▼Windows, C헤더
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>

//▼C++
#include <iostream>

//▼STL
#include <string>
#include <vector>
#include <map>
using namespace std;

//▼User Created headers
#include "commonMacroFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "txtData.h"
#include "sceneManager.h"
#include "CameraClass.h"
#include "soundManager.h"
#include "CollisionClass.h"


#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define CAMERA CameraClass::getInstance()
#define SOUNDMANAGER soundManager::getSingleton()
#define COLLISION CollisionClass::getInstance()


//▼윈도우 
#define WINNAME (LPTSTR)(TEXT(" Adventure of Pip Practice : 2차 묶음 _ 하늘"))
#define WINSTARTX	200
#define WINSTARTY	200
#define WINSIZEX		1366
#define WINSIZEY		768
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#define SAFE_DELETE(p)		{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}
 
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;


#define RelativeCameraRect(RECT) {(RECT).left - CAMERA.getCRc().left, (RECT).top - CAMERA.getCRc().top, (RECT).right - CAMERA.getCRc().left, (RECT).bottom - CAMERA.getCRc().top}
#define RelativeCameraPoint(POINT) {(POINT).x - CAMERA.getCRc().left, (POINT).y - CAMERA.getCRc().top}