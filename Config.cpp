#include "Config.h"

// 4:3アスペクト
//#define _4_3_

#ifdef _4_3_
// ウィンドウ幅
#define WND_W 800
// ウィンドウ高さ
#define WND_H 600
// ウィンドウ幅半分
#define WND_HW (400)
// ウィンドウ高さ半分
#define WND_HH (300)
#else
// ウィンドウ幅
#define WND_W 1024
// ウィンドウ高さ
#define WND_H 576
// ウィンドウ幅半分
#define WND_HW (512)
// ウィンドウ高さ半分
#define WND_HH (288)
#endif // _4_3_

// PC画面幅
#define SCR_W (GetSystemMetrics(SM_CXSCREEN))
// PC画面高さ
#define SCR_H (GetSystemMetrics(SM_CYSCREEN))
// ウィンドウX座標
#define WND_X (SCR_W / 2 - WND_HW)
// ウィンドウY座標
#define WND_Y (SCR_H / 2 - WND_HH)

#define TITLE "Re:Hal Magic Festival Locus of memories"

char Config::m_WindowName[128] = TITLE;

POINT Config::m_ScreenSize = {
	SCR_W, SCR_H
};

POINT Config::m_WindowSize = {
	WND_W, WND_H
};

POINT Config::m_WindowPos = {
	WND_X, WND_Y
};

const POINT* Config::GetWindowSize( void ) {
	return &m_WindowSize;
}

const POINT* Config::GetWindowPos( void ) {
	return &m_WindowPos;
}

const POINT* Config::GetScreenSize( void ) {
	return &m_ScreenSize;
}

const char* Config::GetWindowName( void ) {
	return m_WindowName;
}
