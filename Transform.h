#pragma once

#include "Vector.h"

typedef struct Transform {
	VECTOR3 locate;
	VECTOR4 rotate;
	VECTOR3 scale;
}TRANSFORM, *LPTRANSFORM;
