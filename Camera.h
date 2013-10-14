#pragma once

#include "Object.h"
#include "Vector.h"

enum CAMERAKIND {
	CAMERAKIND_APPLYNOW = 0, // �ݒ�シ���K�p
	CAMERAKIND_INTERPOLATION, // ���
	CAMERAKIND_DEFAULT = CAMERAKIND_APPLYNOW,
};

#undef far
#undef near

class Camera : public Object {
public:
	typedef struct LockAtUp {
		VECTOR3 eye, at, up;
		LockAtUp();
		LockAtUp(const LockAtUp* origin);
	}LOCKATUP;
	typedef struct Perspective {
		float fovy, aspect, near, far;
		Perspective();
	}PERSPECTIVE;

	Camera(void);
	~Camera(void);

	/** ������
	*/
	Camera* init();

	/** �X�V
	*/
	void update();

	/**
	* �`��E�E�E����̂��H
	*/
	void draw(){}

	/**
	* LockAtUp�v�f�̐ݒ�
	*/

	void setLockAtUp(const LockAtUp* lock_at_up);

	/**
	* LockAtUp�v�f�̎擾
	*/
	const LockAtUp* getLockAtUp(void);

	/** �����ݒ�
	*/
	void setLength(float length);

	/** �����擾
	*/
	float getLength();

	/**
	 * �����𑊑Βl�ŕύX
	 */
	void changeRelativeLength(float length);

	/** �����ݒ�
	*/
	void setKind(CAMERAKIND kind);

	/** �����擾
	*/
	CAMERAKIND getKind();

	/** �����擾
	*/
	const VECTOR3* getDirection();

	/** ���_�𒆐S�ɉ���]
	*/
	void rotateXEyePivot(float angle);

	/** ���_�𒆐S�ɏc��]
	*/
	void rotateYEyePivot(float angle);

	/** �����_�𒆐S�ɉ���]
	*/
	void rotateXAtPivot(float angle);

	/** �����_�𒆐S�ɏc��]
	*/
	void rotateYAtPivot(float angle);

	/** �J�����̉�]�ʎ擾
	* @return ��]�ʃ|�C���^
	*/
	const VECTOR2* getRotate();

private:
	/**
	* �����̍Čv�Z
	*/
	void calcLength();
	/**
	* �����̍Čv�Z
	*/
	void calcDirection();

	LockAtUp now_lock_at_up;
	LockAtUp target_lock_at_up;
	VECTOR3 m_Direction;
	VECTOR2 m_Rotate;
	float m_Length;
	CAMERAKIND m_Kind;
};
