#pragma once

#include "Vector.h"

typedef struct Transform {
	VECTOR3 position;
	VECTOR4 rotate;
	VECTOR3 scale;
	Transform();
	Transform(const Transform& t);
	Transform(const VECTOR3& p, const VECTOR4& r, const VECTOR3& s);
}TRANSFORM, *LPTRANSFORM;
