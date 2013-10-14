#ifndef _COMMON_H_
#define _COMMON_H_

// �I�[�o�[���C�h�̌x���}�~
#pragma warning(disable: 4996)

#include "Vector.h"

#define PI 3.141592f
#define D2R(degree) (degree * 0.017453f)
#define R2D(radian) (radian / 0.017453f)
#define null 0
#define boolean unsigned char
#define SAFE_METHOD(p, method) {if(p) p->method();}
#define SAFE_RELEASE(p) if(p){p->release();p=null;}

/**
* sprintf���g�p�����l�̌ܓ��֐�
* @param num �l�̌ܓ����錳�̐��l
* @param precision �l�̌ܓ����錅
* @return �l�̌ܓ���������
*/
float roundprecision(float num, int precision);

/** �O�ϔ���p�֐�\n
* pVtx0��pVtx1�̃x�N�g����pVtx0��pPos�̃x�N�g�����O�όv�Z���A���̌��ʂ�Ԃ�
* @param Vector3* pVtx0 2�{�̃x�N�g���̊J�n�_
* @param Vector3* pVtx1 ��ƂȂ�x�N�g���̏I���_
* @param Vector3* pPos ���ׂ�x�N�g���̏I���_
* @return float ��̃x�N�g�����pPos���E���Ȃ琳�̒l���A�����Ȃ畅��(^o^��)��{�ӫ�c�̒l��Ԃ�
*/
float TestCross(const VECTOR3* pVtx0, const VECTOR3* pVtx1, const VECTOR3* pPos);
/** �O�ς��g�p����3���_���Ƀ|�W�V���������邩�ǂ������ׂ�֐�\n
* 3�̒��_���ɒ��ׂ����|�W�V���������邩�ǂ������ׂ�E���ɂ��ꂼ��̒��_�𑗂�
* @param pVtx0 ���_0
* @param pVtx1 ���_1
* @param pVtx2 ���_1
* @param pPos ���ׂ钸�_(�v���C���[�Ƃ��G�l�~�[�Ƃ�)
* @return BOOL ����Ȃ�Ԏ�����[
*/
bool HavePosition(VECTOR3* pVtx0, VECTOR3* pVtx1, VECTOR3* pVtx2, VECTOR3* pPos);

/**
 * �f�o�b�O�o��
 * @param str �o�͕���(���̊֐����ĂԂƎ����ŉ��s)
 */
void debug(const char* str);

/**
 * ���l�𕶎��ɕϊ�
 * @param value �ϊ�������������
 * @return ���L�o�b�t�@
 */
char* to_s(int value);

/**
 * ���l�𕶎��ɕϊ�
 * @param value �ϊ�������������
 * @return ���L�o�b�t�@
 */
char* to_s(float value);

/**
 * ���L�X�^�b�N�N���[��
 */
void cleanString();

/**
 * ���L�X�^�b�N������ɘA��
 * @param str1, str2 �A������������
 * @return ���L�o�b�t�@
 */
char* attachString(char* str1, char* str2);

/**
 * �o�E���h�{�b�N�X
 * @param lt ����
 @ @param rb �E��
 * @param p ���ׂ���W
 * @return true : in false : out
 */
bool boundBox(const VECTOR2& lt, const VECTOR2& rb, const VECTOR2& p);

#endif // _COMMON_H_