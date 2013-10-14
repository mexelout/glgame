#include "Config.h"

// 4:3�A�X�y�N�g
//#define _4_3_

#ifdef _4_3_
// �E�B���h�E��
#define WND_W 800
// �E�B���h�E����
#define WND_H 600
// �E�B���h�E������
#define WND_HW (400)
// �E�B���h�E��������
#define WND_HH (300)
#else
// �E�B���h�E��
#define WND_W 1024
// �E�B���h�E����
#define WND_H 576
// �E�B���h�E������
#define WND_HW (512)
// �E�B���h�E��������
#define WND_HH (288)
#endif // _4_3_

// PC��ʕ�
#define SCR_W (GetSystemMetrics(SM_CXSCREEN))
// PC��ʍ���
#define SCR_H (GetSystemMetrics(SM_CYSCREEN))
// �E�B���h�EX���W
#define WND_X (SCR_W / 2 - WND_HW)
// �E�B���h�EY���W
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
