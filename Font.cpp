#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Common.h"
#include "Font.h"

GLFONT* font = null;

//コンストラクタ　フォント作成
GLFONT::GLFONT() {
	Hfont = CreateFontW(
	32,					//フォント高さ
	0,						//文字幅
	0,						//テキストの角度
	0,						//ベースラインとｘ軸との角度
	FW_REGULAR,				//フォントの太さ
	FALSE,					//イタリック体
	FALSE,					//アンダーライン
	FALSE,					//打ち消し線
	SHIFTJIS_CHARSET,		//文字セット
	OUT_DEFAULT_PRECIS,		//出力精度
	CLIP_DEFAULT_PRECIS,	//クリッピング精度
	ANTIALIASED_QUALITY,	//出力品質
	FIXED_PITCH | FF_MODERN,//ピッチとファミリー
	L"MS Gothic");				//書体名

	Hdc = wglGetCurrentDC();
	SelectObject(Hdc, Hfont);
}

GLFONT::~GLFONT() {
}

void GLFONT::init() {
	font = new GLFONT();
}

//ワイド文字列の描画
void GLFONT::drawString(int x,int y,wchar_t *format, ...) {
	wchar_t buf[256];
	va_list ap;
	int Length=0;
	int list=0;

	//ポインタがNULLの場合は終了
	if(format == NULL) return;

	//文字列変換
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
	//ディスプレイリストで描画
	for( int i=0; i<Length; i++ ) {
		glCallList(list + i);
	}
	//ディスプレイリスト破棄
	glDeleteLists(list, Length);
	list = 0;
	Length = 0;
	glEnable(GL_LIGHTING);
}

void GLFONT::release() {
	if(font) {delete font;font=null;}
}