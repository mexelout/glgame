#define _CRT_SECURE_NO_WARNINGS

#include <gl/glew.h>
#include "Fade.h"
#include "lodepng.h"

#define FADE_CHENGE_AMOUNT 0.01f

Fade::Fade(void) {
	tex_num = 0;
	alpha = 0;
	rev_alpha = 0;
	state = FADESTATE_NONE;
}

Fade::~Fade(void) {
}

void Fade::init(void) {
	alpha = 1;
	LodePNG_Decoder decoder;
	LodePNG_Decoder_init(&decoder);
	unsigned char* buffer;
	unsigned char* image;
	size_t buffersize, imagesize;
	//ロード
	LodePNG_loadFile(&buffer, &buffersize, "textures/fade.png");
	//デコード
	LodePNG_decode(&decoder, &image, &imagesize, buffer, buffersize);
	//幅,高さ
	int width = decoder.infoPng.width; int height = decoder.infoPng.height;

	glGenTextures(1, (GLuint *)&tex_num);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glBindTexture(GL_TEXTURE_2D, tex_num);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 

	glBindTexture(GL_TEXTURE_2D, tex_num );
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,width, height, 0,GL_RGBA, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	delete image;
	delete buffer;
}

void Fade::update(void) {
	if(rev_alpha != 0) {
		alpha += rev_alpha;
		if(alpha > 1.0f) {
			alpha = 1.f;
			rev_alpha = 0;
			state = FADESTATE_OUT_END;
		}
		if(alpha < 0.0f) {
			alpha = 0.f;
			rev_alpha = 0;
			state = FADESTATE_IN_END;
		}
	} else {
		state = FADESTATE_NONE;
	}
}

void Fade::draw(void) {
	if(alpha > 0) {

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);

		if(tex_num) glBindTexture(GL_TEXTURE_2D, tex_num );
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_ALPHA_TEST);//アルファテスト開始
		glEnable(GL_TEXTURE_2D);//テクスチャ有効

		glColor4f(1, 1, 1, alpha);
		glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0, 0);
		glVertex2f(512, 288);

		glTexCoord2f(1, 0);
		glVertex2f(-512, 288);

		glTexCoord2f(0, 1);
		glVertex2f(512, -288);

		glTexCoord2f(1, 1);
		glVertex2f(-512, -288);
		glEnd();
		glDisable(GL_TEXTURE_2D);//テクスチャ無効

		glColor4f(0, 0, 0, alpha);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(512, 288);
		glVertex2f(-512, 288);
		glVertex2f(512, -288);
		glVertex2f(-512, -288);
		glEnd();
		glColor4f(1, 1, 1, 1);
		glDisable(GL_BLEND);

		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
	}
}

void Fade::release(void) {
	glDeleteTextures(1, &tex_num);
	delete this;
}

void Fade::fadeIn() {
	rev_alpha = -FADE_CHENGE_AMOUNT;
	state = FADESTATE_IN;
}

void Fade::fadeOut() {
	rev_alpha = FADE_CHENGE_AMOUNT;
	state = FADESTATE_OUT;
}

Fade::FADESTATE Fade::getState(void) {
	return state;
}
