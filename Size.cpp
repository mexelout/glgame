#include "Size.h"

SIZE2D::SIZE2D() {
	Zero();
}

SIZE2D::SIZE2D(float width, float height) {
	set(width, height);
}

// assignment operators
SIZE2D& SIZE2D::operator += (const SIZE2D& size) {
	this->width+=size.width;
	this->height+=size.height;
	return *this;
}

SIZE2D& SIZE2D::operator -= (const SIZE2D& size) {
	this->width-=size.width;
	this->height-=size.height;
	return *this;
}

SIZE2D& SIZE2D::operator *= (float val) {
	this->width*=val;
	this->height*=val;
	return *this;
}

SIZE2D& SIZE2D::operator /= (float val) {
	this->width/=val;
	this->height/=val;
	return *this;
}

// binary operators
SIZE2D SIZE2D::operator + (const SIZE2D& size) const {
	SIZE2D work(this->width, this->height);
	work+=size;
	return work;
}

SIZE2D SIZE2D::operator - (const SIZE2D& size) const {
	SIZE2D work(this->width, this->height);
	work-=size;
	return work;
}

SIZE2D SIZE2D::operator * (float val) const {
	SIZE2D work(this->width, this->height);
	work*=val;
	return work;
}

SIZE2D SIZE2D::operator / (float val) const {
	SIZE2D work(this->width, this->height);
	work/=val;
	return work;
}

void SIZE2D::Zero() {
	width = 0;
	height = 0;
}

void SIZE2D::set(const SIZE2D& size) {
	*this = size;
}

void SIZE2D::set(float width, float height) {
	this->width = width;
	this->height = height;
}


SIZE3D::SIZE3D() {
	Zero();
}

SIZE3D::SIZE3D(float width, float height, float depth) {
	set(width, height, depth);
}

// assignment operators
SIZE3D& SIZE3D::operator += (const SIZE3D& size) {
	this->width+=size.width;
	this->height+=size.height;
	this->depth+=size.depth;
	return *this;
}

SIZE3D& SIZE3D::operator -= (const SIZE3D& size) {
	this->width-=size.width;
	this->height-=size.height;
	this->depth-=size.depth;
	return *this;
}

SIZE3D& SIZE3D::operator *= (float val) {
	this->width*=val;
	this->height*=val;
	this->depth*=val;
	return *this;
}

SIZE3D& SIZE3D::operator /= (float val) {
	this->width/=val;
	this->height/=val;
	this->depth/=val;
	return *this;
}

// binary operators
SIZE3D SIZE3D::operator + (const SIZE3D& size) const {
	SIZE3D work(this->width, this->height, this->depth);
	work+=size;
	return work;
}

SIZE3D SIZE3D::operator - (const SIZE3D& size) const {
	SIZE3D work(this->width, this->height, this->depth);
	work-=size;
	return work;
}

SIZE3D SIZE3D::operator * (float val) const {
	SIZE3D work(this->width, this->height, this->depth);
	work*=val;
	return work;
}

SIZE3D SIZE3D::operator / (float val) const {
	SIZE3D work(this->width, this->height, this->depth);
	work/=val;
	return work;
}

void SIZE3D::Zero() {
	width = 0;
	height = 0;
	depth = 0;
}

void SIZE3D::set(const SIZE3D& size) {
	*this = size;
}

void SIZE3D::set(float width, float height, float depth) {
	this->width = width;
	this->height = height;
	this->depth = depth;
}
