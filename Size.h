#pragma once

typedef struct SIZE2D {
	SIZE2D();
	SIZE2D(float width, float height);

	// assignment operators
	SIZE2D& operator += (const SIZE2D& size);
	SIZE2D& operator -= (const SIZE2D& size);
	SIZE2D& operator *= (float val);
	SIZE2D& operator /= (float val);

	// binary operators
	SIZE2D operator + (const SIZE2D& size) const;
	SIZE2D operator - (const SIZE2D& size) const;
	SIZE2D operator * (float val) const;
	SIZE2D operator / (float val) const;

	void Zero();
	void set(const SIZE2D& size);
	void set(float width, float height);

	float width;
	float height;
}SIZE2D;

typedef struct SIZE3D {
	SIZE3D();
	SIZE3D(float width, float height, float depth);

	// assignment operators
	SIZE3D& operator += (const SIZE3D& size);
	SIZE3D& operator -= (const SIZE3D& size);
	SIZE3D& operator *= (float val);
	SIZE3D& operator /= (float val);

	// binary operators
	SIZE3D operator + (const SIZE3D& size) const;
	SIZE3D operator - (const SIZE3D& size) const;
	SIZE3D operator * (float val) const;
	SIZE3D operator / (float val) const;

	void Zero();
	void set(const SIZE3D& size);
	void set(float width, float height, float depth);

	float width;
	float height;
	float depth;
}SIZE3D;
