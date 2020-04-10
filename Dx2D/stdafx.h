// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <assert.h>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <time.h>
#include <stack>
#include <list>

using namespace std;

// 전역 변수:
extern HINSTANCE	g_hInst;                    // 현재 인스턴스입니다.
extern HWND			g_hWnd;						// 윈도우 핸들
extern POINT		g_ptMouse;

// 전역 디파인
#define WINSIZEX (1920)
#define WINSIZEY 1080
#define HALFSIZEX (WINSIZEX * 0.5f)
#define HALFSIZEY (WINSIZEY * 0.5f)
#define GAMESCREEN_X 3200
#define GAMESCREEN_Y 1800

#define SAFE_DELETE(p)			{ if(p) { delete(p); (p) = NULL; } }
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p); (p) = NULL; } }
#define SAFE_RELEASE(p)			{ if(p) { p->Release(); (p) = NULL; } }

#define GRAVITY (9.8f * 60.0f)

#define GAMESCREEN_X_RATIO 10
#define GAMESCREEN_Y_RATIO 8

/*
속성 -> C/C++ -> 추가 포함 디렉터리 : ../../_Libraries
속성 -> 링커 -> 추가 라이브러리 디렉터리 : ../../_Libraries
*/

// Dx 라이브러리
#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>
#include <D3DX10math.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

// IMGui : Immediate Mode GUI
#include <IMGui/IMGui.h>
#include <IMGui/IMGuiDx11.h>
#pragma comment(lib, "IMGui/IMGui.lib")


// 매니져 클래스
#include "KeyManager.h"
#include "TimeManager.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "FileManager.h"
#include "ShaderManager.h"

// 전역 헤더파일
#include "iGameNode.h"
#include "DxComponent.h"
#include "Shader.h"
#include "Sprite.h"
#include "Rect.h"
#include "Circle.h"
#include "Utility.h"
#include "Clip.h"
#include "Animation.h"
#include "ProgressBar.h"

// 매니져 클래스
#include "Camera.h"
#include "TextManager.h"
#include "SceneManager.h"
#include "LoadManager.h"