/**
* �ݒ�N���X
* @author HAL���� �Q�[���w�� �Q�[������w�� ���R���a
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