#include <math.h>
#include "Vector.h"

#pragma region VECTOR2
void VECTOR2::Zero() {
	x = 0;
	y = 0;
}

float VECTOR2::Length() {
	return Vector2Length(this);
}

void VECTOR2::set(const VECTOR2& vec) {
	x = vec.x;
	y = vec.y;
}

void VECTOR2::set(float x, float y) {
	this->x = x;
	this->y = y;
}

float Vector2Length(const LPVECTOR2 pVec) {
	return sqrtf(Vector2LengthSq(pVec));
}
float Vector2LengthSq(const LPVECTOR2 pVec) {
	return Vector2Dot(pVec, pVec);
}
LPVECTOR2 Vector2Normalize(LPVECTOR2 pOut, const LPVECTOR2 pIn) {
	float rate = 1.0f / Vector2Length(pIn);
	*pOut = *pIn * rate;
	return pOut;
}
float Vector2Dot(const LPVECTOR2 pVec0, const LPVECTOR2 pVec1) {
	return (pVec0->x * pVec1->x + pVec0->y * pVec1->y);
}
float Vector2Cross(const LPVECTOR2 pVec0, const LPVECTOR2 pVec1) {
	return (pVec0->x * pVec1->y - pVec0->y * pVec1->x);
}

#pragma endregion

#pragma region VECTOR3

void VECTOR3::Zero() {
	x = 0;
	y = 0;
	z = 0;
}

float VECTOR3::Length() {
	return Vector3Length(this);
}

void VECTOR3::set(const VECTOR3& vec) {
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

void VECTOR3::set(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

VECTOR3 VECTOR3::Up() {
	return VECTOR3(0, 1, 0);
}
VECTOR3 VECTOR3::Right() {
	return VECTOR3(1, 0, 0);
}
VECTOR3 VECTOR3::Forward() {
	return VECTOR3(0, 0, 1);
}

float Vector3Length(const LPVECTOR3 pVec) {
	return sqrtf(Vector3LengthSq(pVec));
}
float Vector3LengthSq(const LPVECTOR3 pVec) {
	return Vector3Dot(pVec, pVec);
}
LPVECTOR3 Vector3Normalize(LPVECTOR3 pOut, const LPVECTOR3 pIn) {
	float length = Vector3Length(pIn);
	float rate = 1.0f;
	if(length) rate /= length;
	else rate = 0;
	*pOut = *pIn * rate;
	return pOut;
}
float Vector3Dot(const LPVECTOR3 pVec0, const LPVECTOR3 pVec1) {
	return pVec0->x * pVec1->x + pVec0->y * pVec1->y + pVec0->z * pVec1->z;
}
LPVECTOR3 Vector3Cross(LPVECTOR3 pOut, const LPVECTOR3 pVec0, const LPVECTOR3 pVec1) {
	pOut->x = pVec0->y * pVec1->z - pVec0->z * pVec1->y;
	pOut->y = pVec0->z * pVec1->x - pVec0->x * pVec1->z;
	pOut->z = pVec0->x * pVec1->y - pVec0->y * pVec1->x;
	return pOut;// a2b3-a3b2, a3b1-a1b3, a1b2-a2b1
}

/** 3Dベクトルの外積(X,Z軸からのfloat算出)
* @param v1 調べるベクトル成分1
* @param v2 調べるベクトル成分2
* @return float 計算結果
*/
float Vector3CrossXZ(VECTOR3* v1, VECTOR3* v2) {
	return v1->x * v2->z - v1->z * v2->x;
}

/** 3Dベクトルの内積(X,Z軸からのfloat算出)
* @param v1 調べるベクトル成分1
* @param v2 調べるベクトル成分2
* @return float 計算結果
*/
float Vector3DotXZ(VECTOR3* v1, VECTOR3* v2) {
	return v1->x * v2->x + v1->z * v2->z;
}

/** 3Dベクトルの差分(X,Z軸からの算出)
* @param v1 調べるベクトル成分1
* @param v2 調べるベクトル成分2
* @param out 出力先
* @return Vector3* 計算結果
*/
VECTOR3* Vector3SubXZ(VECTOR3* out, VECTOR3* v1, VECTOR3* v2) {
	out->x = v1->x - v2->x;
	out->y = 0;
	out->z = v1->z - v2->z;
	return out;
}

#pragma endregion

#pragma region VECTOR4

void VECTOR4::Zero() {
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

void VECTOR4::set(const VECTOR4& vec) {
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = vec.w;
}

void VECTOR4::set(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

#pragma endregion
