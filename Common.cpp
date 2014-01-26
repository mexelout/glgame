#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<typeinfo>
#include "Common.h"

char buffer[256] = {};
char attach[512] = {};

/**
* sprintf���g�p�����l�̌ܓ��֐�
* @param num �l�̌ܓ����錳�̐��l
* @param precision �l�̌ܓ����錅
* @return �l�̌ܓ���������
*/
float roundprecision(float num, int precision) {
	char s[256] = {0};
	sprintf(s, "%.*f", precision-1, num);
	return (float)atof(s);
}

/** �O�ϔ���p�֐�\n
* pVtx0��pVtx1�̃x�N�g����pVtx0��pPos�̃x�N�g�����O�όv�Z���A���̌��ʂ�Ԃ�
* @param pVtx0 2�{�̃x�N�g���̊J�n�_
* @param pVtx1 ��ƂȂ�x�N�g���̏I���_
* @param pPos ���ׂ�x�N�g���̏I���_
* @return float ��̃x�N�g�����pPos���E���Ȃ琳�̒l���A�����Ȃ畅��(^o^��)��{�ӫ�c�̒l��Ԃ�
*/
float TestCross(const VECTOR3* pVtx0, const VECTOR3* pVtx1, const VECTOR3* pPos) {
	VECTOR3 vec0, vec1;

	vec0 = *pVtx1 - *pVtx0;
	vec1 = *pPos - *pVtx0;

	return (vec0.z * vec1.x - vec0.x * vec1.z);
}

/** �O�ς��g�p����3���_���Ƀ|�W�V���������邩�ǂ������ׂ�֐�\n
* 3�̒��_���ɒ��ׂ����|�W�V���������邩�ǂ������ׂ鍶���ɂ��ꂼ��̒��_�𑗂�
* @param pVtx0 ���_0
* @param pVtx1 ���_1
* @param pVtx2 ���_1
* @param pPos ���ׂ钸�_(�v���C���[�Ƃ��G�l�~�[�Ƃ�)
* @return BOOL ����Ȃ�Ԏ�����[
*/
bool HavePosition(VECTOR3* pVtx0, VECTOR3* pVtx1, VECTOR3* pVtx2, VECTOR3* pPos) {
	return (TestCross(pVtx0, pVtx1, pPos) >= 0 && TestCross(pVtx1, pVtx2, pPos) >= 0 && TestCross(pVtx2, pVtx0, pPos) >= 0) ? true : false;
}

/**
 * �f�o�b�O�o��
 * @param str �o�͂��镶����
 */
void debug(const char* str) {
	char out[512] = {0};
	strcat(out, str);
	strcat(out, "\n");
	OutputDebugStringA(out);
}

/**
 * ���l�𕶎��ɕϊ�(int)
 * @param value �����ɂ��鐔�l
 * @return char* �ϊ�����������
 */
char* to_s(int value) {
	memset(buffer, 0, sizeof(buffer));
	itoa(value, buffer, 256);
	return buffer;
}

/**
 * ���l�𕶎��ɕϊ�(float)
 * @param value �����ɂ��鐔�l
 * @return char* �ϊ�����������
 */
char* to_s(float value) {
	memset(buffer, 0, sizeof(buffer));
	sprintf(buffer, "%f", value);
	return buffer;
}

/**
 * ���L�X�^�b�N�N���[��
 */
void cleanString() {
	memset(attach, 0, sizeof(attach));
}

/**
 * ���L�X�^�b�N������ɘA��
 * @param str1 �A������������
 * @param str2 �A���E��������
 * @return char* �A�����ꂽ������
 */
char* attachString(char* str1, char* str2) {
	if(attach != str1) strcat(attach, str1);
	strcat(attach, str2);
	return attach;
}

/**
 * �o�E���h�{�b�N�X
 * @param lt ����
 @ @param rb �E��
 * @param p ���ׂ���W
 * @return true : in false : out
 */
bool boundBox(const VECTOR2& lt, const VECTOR2& rb, const VECTOR2& p) {
	if(lt.x < p.x && lt.y > p.y && rb.x > p.x && rb.y < p.y) {
			return true;
	}
	return false;
}

/**
 * OpenGL�n�̊֐����y�ɂ�����(�߂�ǂ��������)
 * @param callback �Ăяo��OpenGL�`�惁�\�b�h(3�Œ�)
 * @param v �o�͂���x�N�g��
 */
void dm(void (__stdcall *callback)(float, float, float), const VECTOR3& v) {
	callback(v.x, v.y, v.z);
}
