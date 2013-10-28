#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Common.h"
#include "Font.h"

Font* font = null;

//�R���X�g���N�^�@�t�H���g�쐬
Font::Font() {
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

Font::~Font() {
}

void Font::init() {
	font = new Font();
}

//���C�h������̕`��
void Font::drawString(int x,int y, const char* format, ...) {
	//�|�C���^��NULL�̏ꍇ�͏I��
	if(format == NULL) return;

	wchar_t buf[256];
	va_list ap;
	int Length=0;
	int list=0;

	// wchar_t��
	size_t s_t;
	wchar_t fmt_buf[256];
	mbstowcs_s(&s_t, fmt_buf, 256, format, 128);

	//������ϊ�
	va_start(ap, fmt_buf);
	vswprintf_s(buf, fmt_buf, ap);
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
}

void Font::release() {
	if(font) {delete font;font=null;}
}