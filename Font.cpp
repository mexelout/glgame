#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Common.h"
#include "Font.h"

GLFONT* font = null;

//�R���X�g���N�^�@�t�H���g�쐬
GLFONT::GLFONT() {
	Hfont = CreateFontW(
	32,					//�t�H���g����
	0,						//������
	0,						//�e�L�X�g�̊p�x
	0,						//�x�[�X���C���Ƃ����Ƃ̊p�x
	FW_REGULAR,				//�t�H���g�̑���
	FALSE,					//�C�^���b�N��
	FALSE,					//�A���_�[���C��
	FALSE,					//�ł�������
	SHIFTJIS_CHARSET,		//�����Z�b�g
	OUT_DEFAULT_PRECIS,		//�o�͐��x
	CLIP_DEFAULT_PRECIS,	//�N���b�s���O���x
	ANTIALIASED_QUALITY,	//�o�͕i��
	FIXED_PITCH | FF_MODERN,//�s�b�`�ƃt�@�~���[
	L"MS Gothic");				//���̖�

	Hdc = wglGetCurrentDC();
	SelectObject(Hdc, Hfont);
}

GLFONT::~GLFONT() {
}

void GLFONT::init() {
	font = new GLFONT();
}

//���C�h������̕`��
void GLFONT::drawString(int x,int y,wchar_t *format, ...) {
	wchar_t buf[256];
	va_list ap;
	int Length=0;
	int list=0;

	//�|�C���^��NULL�̏ꍇ�͏I��
	if(format == NULL) return;

	//������ϊ�
	va_start(ap, format);
	vswprintf_s(buf, format, ap);
	va_end(ap);

	Length = wcslen(buf);
	list = glGenLists(Length);

	for( int i=0; i<Length; i++ ) {
		wglUseFontBitmapsW(font->Hdc, buf[i], 1, list + (DWORD)i);
	}

	glDisable(GL_LIGHTING);
	glRasterPos2i(x, y);
	//�f�B�X�v���C���X�g�ŕ`��
	for( int i=0; i<Length; i++ ) {
		glCallList(list + i);
	}
	//�f�B�X�v���C���X�g�j��
	glDeleteLists(list, Length);
	list = 0;
	Length = 0;
	glEnable(GL_LIGHTING);
}

void GLFONT::release() {
	if(font) {delete font;font=null;}
}