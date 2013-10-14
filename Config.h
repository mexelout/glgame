/**
* 設定クラス
* @author HAL東京 ゲーム学部 ゲーム制作学科 杉山元和
*/
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <Windows.h>

class Config {
public:
	static const POINT* GetWindowSize(void);
	static const POINT* GetWindowPos(void);
	static const POINT* GetScreenSize(void);
	static const char* GetWindowName(void);
private:
	Config(){}
	~Config(){}
	static POINT m_WindowSize;
	static POINT m_WindowPos;
	static POINT m_ScreenSize;
	static char  m_WindowName[128];
};

#endif // _CONFIG_H_