#pragma once

#ifndef _DEFINE_VECTOR2_
#define _DEFINE_VECTOR2_
typedef struct VECTOR2 {
	VECTOR2() {Zero();}// zero clear
	VECTOR2(const VECTOR2& vec) {set(vec);}
	VECTOR2(float x, float y) {set(x, y);}// assignment initialize

	// assignment operators
	VECTOR2& operator += (const VECTOR2& vec) {this->x+=vec.x;this->y+=vec.y;return *this;}
	VECTOR2& operator -= (const VECTOR2& vec) {this->x-=vec.x;this->y-=vec.y;return *this;}
	VECTOR2& operator *= (float val) {this->x*=val;this->y*=val;return *this;}
	VECTOR2& operator /= (float val) {if(this->x)this->x/=val;if(this->y)this->y/=val;return *this;}

	// binary operators
	VECTOR2 operator + (const VECTOR2& vec) const {VECTOR2 work(this->x, this->y);work+=vec;return work;}
	VECTOR2 operator - (const VECTOR2& vec) const {VECTOR2 work(this->x, this->y);work-=vec;return work;}
	VECTOR2 operator * (float val) const {VECTOR2 work(this->x, this->y);work*=val;return work;}
	VECTOR2 operator / (float val) const {VECTOR2 work(this->x, this->y);work/=val;return work;}

	void Zero();
	float Length();
	void set(const VECTOR2& vec);
	void set(float x, float y);

	float x, y;
}VECTOR2, *LPVECTOR2;

float Vector2Length(const LPVECTOR2 pVec);
float Vector2LengthSq(const LPVECTOR2 pVec);
LPVECTOR2 Vector2Normalize(LPVECTOR2 pOut, const LPVECTOR2 pIn);
float Vector2Dot(const LPVECTOR2 pVec0, const LPVECTOR2 pVec1);
float Vector2Cross(const LPVECTOR2 pVec0, const LPVECTOR2 pVec1);

#endif // _DEFINE_VECTOR2_

#ifndef _DEFINE_VECTOR3_ // VECTOR3構造体定義したよー！ってフラグ
typedef struct VECTOR3 {
	VECTOR3() {Zero();}// zero clear
	VECTOR3(const VECTOR3& vec) {set(vec);}
	VECTOR3(float x, float y, float z) {set(x, y, z);}// assignment initialize

	// assignment operators
	VECTOR3& operator += (const VECTOR3& vec) {this->x+=vec.x;this->y+=vec.y;this->z+=vec.z;return *this;}
	VECTOR3& operator -= (const VECTOR3& vec) {this->x-=vec.x;this->y-=vec.y;this->z-=vec.z;return *this;}
	VECTOR3& operator *= (float val) {this->x*=val;this->y*=val;this->z*=val;return *this;}
	VECTOR3& operator /= (float val) {if(this->x)this->x/=val;if(this->y)this->y/=val;if(this->z)this->z/=val;return *this;}

	// binary operators
	VECTOR3 operator + (const VECTOR3& vec) const {VECTOR3 work(this->x, this->y, this->z);work+=vec;return work;}
	VECTOR3 operator - (const VECTOR3& vec) const {VECTOR3 work(this->x, this->y, this->z);work-=vec;return work;}
	VECTOR3 operator * (float val) const {VECTOR3 work(this->x, this->y, this->z);work*=val;return work;}
	VECTOR3 operator / (float val) const {VECTOR3 work(this->x, this->y, this->z);work/=val;return work;}

	void Zero();
	float Length();
	void set(const VECTOR3& vec);
	void set(float x, float y, float z);

	static VECTOR3 Up();
	static VECTOR3 Right();
	static VECTOR3 Forward();

	float x, y, z;// member number
}VECTOR3, *LPVECTOR3;
float Vector3Length(const LPVECTOR3 pVec);
float Vector3LengthSq(const LPVECTOR3 pVec);
LPVECTOR3 Vector3Normalize(LPVECTOR3 pOut, const LPVECTOR3 pIn);
float Vector3Dot(const LPVECTOR3 pVec0, const LPVECTOR3 pVec1);
LPVECTOR3 Vector3Cross(LPVECTOR3 pOut, const LPVECTOR3 pVec0, const LPVECTOR3 pVec1);

/** 3Dベクトルの外積(X,Z軸からのfloat算出)
* @param v1 調べるベクトル成分1
* @param v2 調べるベクトル成分2
* @return float 計算結果
*/
float Vector3CrossXZ(VECTOR3* v1, VECTOR3* v2);

/** 3Dベクトルの内積(X,Z軸からのfloat算出)
* @param v1 調べるベクトル成分1
* @param v2 調べるベクトル成分2
* @return float 計算結果
*/
float Vector3DotXZ(VECTOR3* v1, VECTOR3* v2);

/** 3Dベクトルの差分(X,Z軸からの算出)
* @param v1 調べるベクトル成分1
* @param v2 調べるベクトル成分2
* @param out 出力先
* @return Vector3* 計算結果
*/
VECTOR3* Vector3SubXZ(VECTOR3* out, VECTOR3* v1, VECTOR3* v2);

#define _DEFINE_VECTOR3_
#endif // _DEFINE_VECTOR3_

#ifndef _DEFINE_VECTOR4_ // VECTOR3構造体定義したよー！ってフラグ
typedef struct VECTOR4 {
	VECTOR4() {Zero();}// zero clear
	VECTOR4(const VECTOR4& vec) {set(vec);}
	VECTOR4(float x, float y, float z, float w) {set(x, y, z, w);}// assignment initialize

	// assignment operators
	VECTOR4& operator += (const VECTOR4& vec) {this->x+=vec.x;this->y+=vec.y;this->z+=vec.z;this->w+=vec.w;return *this;}
	VECTOR4& operator -= (const VECTOR4& vec) {this->x-=vec.x;this->y-=vec.y;this->z-=vec.z;this->w-=vec.w;return *this;}
	VECTOR4& operator *= (float val) {this->x*=val;this->y*=val;this->z*=val;this->w*=val;return *this;}
	VECTOR4& operator /= (float val) {if(this->x)this->x/=val;if(this->y)this->y/=val;if(this->z)this->z/=val;if(this->w)this->w/=val;return *this;}

	// binary operators
	VECTOR4 operator + (const VECTOR4& vec) const {VECTOR4 work(this->x, this->y, this->z, this->w);work+=vec;return work;}
	VECTOR4 operator - (const VECTOR4& vec) const {VECTOR4 work(this->x, this->y, this->z, this->w);work-=vec;return work;}
	VECTOR4 operator * (float val) const {VECTOR4 work(this->x, this->y, this->z, this->w);work*=val;return work;}
	VECTOR4 operator / (float val) const {VECTOR4 work(this->x, this->y, this->z, this->w);work/=val;return work;}

	void Zero();
	void set(const VECTOR3& vec);
	void set(const VECTOR4& vec);
	void set(float x, float y, float z, float w);

	float x, y, z, w;// member number
}VECTOR4, *LPVECTOR4;

#define _DEFINE_VECTOR4_
#endif // _DEFINE_VECTOR4_

