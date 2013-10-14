#include <Windows.h>
#include <math.h>
#include "Config.h"
#include "Camera.h"
#include "Common.h"

#define DEFAULT_EYE 0, 7, -20
#define DEFAULT_AT 0, 4, 0
#define DEFAULT_UP 0, 1, 0

#define FOVY 60
#define ZNEAR 0.5
#define ZFAR 1000.0

#define INTERPOLATION_PERCENT 0.1f

Camera::LockAtUp::LockAtUp() {
	eye.set(DEFAULT_EYE);
	at.set(DEFAULT_AT);
	up.set(DEFAULT_UP);
}

Camera::Perspective::Perspective() {
	fovy = FOVY;
	const POINT* pWndSize = Config::GetWindowSize();
	aspect = (float)pWndSize->x / (float)pWndSize->y;
	near = ZNEAR;
	far = ZFAR;
}

Camera::Camera(void) : Object("camera") {
}

Camera::~Camera(void) {
}

/** ������
*/
Camera* Camera::init() {
	m_Kind = CAMERAKIND_DEFAULT;
	calcLength();
	calcDirection();

	return this;
}

/** �X�V
*/
void Camera::update() {
	VECTOR3 dif(target_lock_at_up.eye - now_lock_at_up.eye);
	dif *= INTERPOLATION_PERCENT;
	now_lock_at_up.eye += dif;
	dif = (target_lock_at_up.at - now_lock_at_up.at);
	dif *= INTERPOLATION_PERCENT;
	now_lock_at_up.at += dif;
}

void Camera::setLockAtUp(const Camera::LockAtUp* lock_at_up) {
	switch(m_Kind) {
		case CAMERAKIND_APPLYNOW:
			now_lock_at_up = *lock_at_up;
			target_lock_at_up = *lock_at_up;
			break;
		case CAMERAKIND_INTERPOLATION:
			target_lock_at_up = *lock_at_up;
			break;
	}
	calcLength();
	calcDirection();
}

const Camera::LockAtUp* Camera::getLockAtUp(void) {
	return &now_lock_at_up;
}

/** �����ݒ�
*/
void Camera::setLength(float length) {
	m_Length = length;
	if(m_Length < 0.01f) m_Length = 0.01f;
	target_lock_at_up.eye.set((now_lock_at_up.at - m_Direction * m_Length));
	if(m_Kind == CAMERAKIND_APPLYNOW) now_lock_at_up = target_lock_at_up;
}

/** �����擾
*/
float Camera::getLength() {
	return m_Length;
}

/**
 * �����𑊑Βl�ŕύX
 */
void Camera::changeRelativeLength(float length) {
	if(length) setLength(m_Length + length);
}

/** �����ݒ�
*/
void Camera::setKind(CAMERAKIND kind) {
	m_Kind = kind;
}

/** �����擾
*/
CAMERAKIND Camera::getKind() {
	return m_Kind;
}

/** �����擾
*/
const VECTOR3* Camera::getDirection() {
	return &m_Direction;
}

/** ���_�𒆐S�ɉ���]
*/
void Camera::rotateXEyePivot(float angle) {
	m_Rotate.y -= angle;
	float radian = cosf(m_Rotate.x);
	m_Direction = VECTOR3(cosf(m_Rotate.y) * radian, sinf(m_Rotate.x), sinf(m_Rotate.y) * radian);
	target_lock_at_up.at.set((target_lock_at_up.eye + m_Direction * m_Length));
	if(m_Kind == CAMERAKIND_APPLYNOW) now_lock_at_up = target_lock_at_up;
}

/** ���_�𒆐S�ɏc��]
*/
void Camera::rotateYEyePivot(float angle) {
	m_Rotate.x -= angle;
	if(m_Rotate.x > PI*0.49f) m_Rotate.x = PI*0.49f;
	else if(m_Rotate.x < -PI*0.49f) m_Rotate.x = -PI*0.49f;
	float radian = cosf(m_Rotate.x);
	m_Direction = VECTOR3(cosf(m_Rotate.y) * radian, sinf(m_Rotate.x), sinf(m_Rotate.y) * radian);
	target_lock_at_up.at.set((target_lock_at_up.eye + m_Direction * m_Length));
	if(m_Kind == CAMERAKIND_APPLYNOW) now_lock_at_up = target_lock_at_up;
}

/** �����_�𒆐S�ɉ���]
*/
void Camera::rotateXAtPivot(float angle) {
	m_Rotate.y += angle;
	float radian = cosf(m_Rotate.x);
	m_Direction = VECTOR3(cosf(m_Rotate.y) * radian, sinf(m_Rotate.x), sinf(m_Rotate.y) * radian);
	target_lock_at_up.eye.set((target_lock_at_up.at - m_Direction * m_Length));
	if(m_Kind == CAMERAKIND_APPLYNOW) now_lock_at_up = target_lock_at_up;
}

/** �����_�𒆐S�ɏc��]
*/
void Camera::rotateYAtPivot(float angle) {
	m_Rotate.x += angle;
	if(m_Rotate.x > PI/2.5f) m_Rotate.x = PI/2.5f;
	else if(m_Rotate.x < -PI/2.5f) m_Rotate.x = -PI/2.5f;
	float radian = cosf(m_Rotate.x);
	m_Direction = VECTOR3(cosf(m_Rotate.y) * radian, sinf(m_Rotate.x), sinf(m_Rotate.y) * radian);
	target_lock_at_up.eye.set((target_lock_at_up.at - m_Direction * m_Length));
	if(m_Kind == CAMERAKIND_APPLYNOW) now_lock_at_up = target_lock_at_up;
}

/** �J�����̉�]�ʎ擾
* @return ��]�ʃ|�C���^
*/
const VECTOR2* Camera::getRotate() {
	return &m_Rotate;
}

/**
* �����̍Čv�Z
*/
void Camera::calcLength() {
	m_Direction = (now_lock_at_up.at - now_lock_at_up.eye);
	m_Length = Vector3Length(&m_Direction);
}

/**
* �����̍Čv�Z
*/
void Camera::calcDirection() {
	m_Direction = now_lock_at_up.at - now_lock_at_up.eye;
	Vector3Normalize(&m_Direction, &m_Direction);

	VECTOR3 vec(m_Direction.x, 0, m_Direction.z);
	Vector3Normalize(&vec, &vec);
	float dot = Vector3Dot(&VECTOR3(1, 0, 0), &vec);
	m_Rotate.y = acosf((dot > 1) ? 1 : (dot < -1) ? -1 : dot);
	m_Rotate.y *= (Vector3Cross(&VECTOR3(), &VECTOR3(1, 0, 0), &vec)->y > 0) ? -1 : 1;
	vec = VECTOR3(sqrtf(m_Direction.x * m_Direction.x + m_Direction.z * m_Direction.z), m_Direction.y, 0);
	dot = Vector3Dot(&VECTOR3(1, 0, 0), &vec);
	m_Rotate.x = acosf((dot > 1) ? 1 : (dot < -1) ? -1 : dot);
	m_Rotate.x *= (Vector3Cross(&VECTOR3(), &VECTOR3(1, 0, 0), &vec)->x > 0) ? 1 : -1;
}

// end