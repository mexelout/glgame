#include "Image.h"
#include "Common.h"
#include "lodepng.h"

Image::Image() : base("image") {
	tex_num = 0;
	buffer = null;
}
Image::~Image() {
}
Image* Image::init() {
	return this;
}
void Image::update() {}
void Image::draw() {}
void Image::release() {
	if(buffer) delete buffer;
	glDeleteTextures(1, &tex_num);
	base::release();
}
void Image::setTexNum() {
	glBindTexture(GL_TEXTURE_2D, tex_num);
}
// png file
void Image::load(const char* file_name) {
	LodePNG_Decoder decoder;
	LodePNG_Decoder_init(&decoder);
	unsigned char* image;
	size_t buffersize, imagesize;
	//ロード
	LodePNG_loadFile(&buffer, &buffersize, file_name);
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,width, height, 0,GL_RGBA, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	size.width = (float)width;
	size.height = (float)height;
	delete image;
}
