#include "Image.h"
#include "Common.h"
#include "lodepng.h"

COLOR_FULL Image::color;

Image::Image() : base("image") {
	tex_num = 0;
	buffer = null;
}
Image::~Image() {
}
Image* Image::initWithName(std::string file_name) {
	Image* img = new Image();
	img->load(file_name);
	return img;
}

Image* Image::init() {
	return this;
}
void Image::update() {}
void Image::draw() {}
void Image::release() {
	SAFE_DELETE(buffer);
	glDeleteTextures(1, &tex_num);
	base::release();
}
// png file
void Image::load(std::string file_name) {
	this->file_name = file_name;
	LodePNG_Decoder decoder;
	LodePNG_Decoder_init(&decoder);
	unsigned char* image;
	size_t buffersize, imagesize;
	//ロード
	LodePNG_loadFile(&buffer, &buffersize, file_name.c_str());
	//デコード
	LodePNG_decode(&decoder, &image, &imagesize, buffer, buffersize);
	//幅,高さ
	int width = decoder.infoPng.width; int height = decoder.infoPng.height;
	glGenTextures(1, &tex_num);
	glBindTexture(GL_TEXTURE_2D, tex_num);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,GL_RGBA, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	size.width = (float)width;
	size.height = (float)height;
	delete image;
}
/** ファイル名取得
* @return char* 読み込みしたファイル名
*/
std::string Image::getName() {
	return file_name;
}
/** 画像を座標指定で貼る(画像の大きさそのまま)
* @param pPos 座標
*/
void Image::drawAtPoint(const VECTOR3* pPos) {
	glPushMatrix();
	GLfloat hw = size.width / 2.0f, hh = size.height / 2.0f;
	GLfloat vtx[] = {
		-hw,  hh, 0.0f,
		 hw,  hh, 0.0f,
		-hw, -hh, 0.0f,
		 hw, -hh, 0.0f,
	};
	GLfloat tex[] = {
		0.0f, 0.0,
		1.0f, 0.0,
		0.0f, 1.0,
		1.0f, 1.0,
	};

	glBindTexture(GL_TEXTURE_2D, tex_num);
	glEnable(GL_TEXTURE_2D);

	float m[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		pPos->x, pPos->y, pPos->z, 1,
	};

	glLoadIdentity();
	glLoadMatrixf(m);

	glBegin(GL_TRIANGLE_STRIP);

	glColor4f(color.r, color.g, color.b, color.a);
	glTexCoord2fv(&tex[0]);
	glVertex3fv(&vtx[0]);
	glTexCoord2fv(&tex[2]);
	glVertex3fv(&vtx[3]);
	glTexCoord2fv(&tex[4]);
	glVertex3fv(&vtx[6]);
	glTexCoord2fv(&tex[6]);
	glVertex3fv(&vtx[9]);

	glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
}
/** 画像を座標・大きさ指定で貼る
*/
void Image::drawAtPoint(const VECTOR3* pPos, const VECTOR3* pScl) {
	glPushMatrix();
	GLfloat hw = 0.5f, hh = 0.5f;
	GLfloat vtx[] = {
		-hw,  hh, 0.0f,
		 hw,  hh, 0.0f,
		-hw, -hh, 0.0f,
		 hw, -hh, 0.0f,
	};
	GLfloat tex[] = {
		0.0f, 0.0,
		1.0f, 0.0,
		0.0f, 1.0,
		1.0f, 1.0,
	};

	glBindTexture(GL_TEXTURE_2D, tex_num);
	glEnable(GL_TEXTURE_2D);

	float m[16] = {
		pScl->x, 0, 0, 0,
		0, pScl->y, 0, 0,
		0, 0, pScl->z, 0,
		pPos->x, pPos->y, pPos->z, 1,
	};

	glLoadIdentity();
	glLoadMatrixf(m);

	glBegin(GL_TRIANGLE_STRIP);

	glColor4f(color.r, color.g, color.b, color.a);
	glTexCoord2fv(&tex[0]);
	glVertex3fv(&vtx[0]);
	glTexCoord2fv(&tex[2]);
	glVertex3fv(&vtx[3]);
	glTexCoord2fv(&tex[4]);
	glVertex3fv(&vtx[6]);
	glTexCoord2fv(&tex[6]);
	glVertex3fv(&vtx[9]);

	glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
}
/** 画像を座標・回転量指定で貼る
*/
void Image::drawAtPoint(const VECTOR3* pPos, const VECTOR3* pRotVec, const float angle) {
	glPushMatrix();
	GLfloat hw = size.width / 2.0f, hh = size.height / 2.0f;
	GLfloat vtx[] = {
		-hw,  hh, 0.0f,
		 hw,  hh, 0.0f,
		-hw, -hh, 0.0f,
		 hw, -hh, 0.0f,
	};
	GLfloat tex[] = {
		0.0f, 0.0,
		1.0f, 0.0,
		0.0f, 1.0,
		1.0f, 1.0,
	};

	glBindTexture(GL_TEXTURE_2D, tex_num);
	glEnable(GL_TEXTURE_2D);
	glLoadIdentity();
	glTranslatef(pPos->x, pPos->y, pPos->z);
	glRotatef(angle, pRotVec->x, pRotVec->y, pRotVec->z);

	glBegin(GL_TRIANGLE_STRIP);

	glColor4f(color.r, color.g, color.b, color.a);
	glTexCoord2fv(&tex[0]);
	glVertex3fv(&vtx[0]);
	glTexCoord2fv(&tex[2]);
	glVertex3fv(&vtx[3]);
	glTexCoord2fv(&tex[4]);
	glVertex3fv(&vtx[6]);
	glTexCoord2fv(&tex[6]);
	glVertex3fv(&vtx[9]);

	glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
}
/** 画像を座標・大きさ・回転量指定で貼る
*/
void Image::drawAtPoint(const VECTOR3* pPos, const VECTOR3* pScl, const VECTOR3* pRotVec, const float angle) {
	glPushMatrix();
	GLfloat hw = 0.5f, hh = 0.5f;
	GLfloat vtx[] = {
		-hw,  hh, 0.0f,
		 hw,  hh, 0.0f,
		-hw, -hh, 0.0f,
		 hw, -hh, 0.0f,
	};
	GLfloat tex[] = {
		0.0f, 0.0,
		1.0f, 0.0,
		0.0f, 1.0,
		1.0f, 1.0,
	};

	glBindTexture(GL_TEXTURE_2D, tex_num);
	glEnable(GL_TEXTURE_2D);
	glLoadIdentity();
	glTranslatef(pPos->x, pPos->y, pPos->z);
	glRotatef(angle, pRotVec->x, pRotVec->y, pRotVec->z);
	glScalef(pScl->x, pScl->y, pScl->z);

	glBegin(GL_TRIANGLE_STRIP);

	glColor4f(color.r, color.g, color.b, color.a);
	glTexCoord2fv(&tex[0]);
	glVertex3fv(&vtx[0]);
	glTexCoord2fv(&tex[2]);
	glVertex3fv(&vtx[3]);
	glTexCoord2fv(&tex[4]);
	glVertex3fv(&vtx[6]);
	glTexCoord2fv(&tex[6]);
	glVertex3fv(&vtx[9]);

	glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
}
/** 画像の適用
*/
void Image::apply() {
	glBindTexture(GL_TEXTURE_2D, tex_num);
	glEnable(GL_TEXTURE_2D);
}

/** GL_CLAMP or GL_REPEAT
*/
void Image::setWrap(GLint wrap) {
	glBindTexture(GL_TEXTURE_2D, tex_num);

	// テクスチャ空間 (s, t) の s 軸方向の繰り返しON(GL_REPEAT)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);

	// テクスチャ空間 (s, t) の t 軸方向の繰り返しON(GL_REPEAT)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

	glBindTexture(GL_TEXTURE_2D, 0);
}

/** GL_NEAREST or GL_LINEAR
*/
void Image::setFilter(GLint filter) {
	glBindTexture(GL_TEXTURE_2D, tex_num);

	// テクスチャの補間方法：MAG_FILTER（拡大）をGL_LINEAR（最近傍法）に設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

	// テクスチャの補間方法：MIN_FILTER（縮小）をGL_LINEAR（最近傍法）に設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);

	glBindTexture(GL_TEXTURE_2D, 0);
}

/** ブレンド色
* @param color 色(RGBA)
*/
void Image::blendColor(COLOR_FULL& color) {
	Image::color = color;
}
