#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "Safe.h"
#include "Common.h"
#include "Central.h"
#include "Ground.h"
#include "Image.h"
#include "Player.h"

#define PAR_X 16
#define PAR_Y 16

//#define _DEBUG_LINE_

Ground::Ground(void) : Object("ground") {
	texture = NULL;
	vtx = NULL;
	idx = NULL;
	nor = NULL;
	tex = NULL;
	faceNor = NULL;
	vtxNum = 0;
	idxNum = 0;
	texNum = 0;
	norNum = 0;
	faceNum = 0;
	prmNum = 0;
}

Ground::~Ground(void) {
}

Ground* Ground::init() {
	texture = Image::initWithName("textures/ground.png");

	int nWidth = PAR_X, nHeight = PAR_Y;

	// �����_��(�v�Z�Ɏg�p)
	int nVtxWNum = nWidth + 1;
	int nVtxHNum = nHeight + 1;
	// �S���_��
	vtxNum = (nVtxWNum * nVtxHNum);
	// �S�C���f�b�N�X��
	idxNum = (((nVtxWNum * 2) * nHeight) + ((nHeight - 1) * 2));
	// �e�N�X�R�[�h��
	texNum = vtxNum;
	// �@����
	norNum = vtxNum;
	// �v���~�e�B�u��
	prmNum = ((nWidth * 2 * nHeight) + ((nHeight - 1) * 4))+2;
	// ���_�z��m��
	vtx = new VECTOR3[vtxNum];
	// �C���f�b�N�X�z��m��
	idx = new int[idxNum];
	// �e�N�X�R�[�h�z��m��
	tex = new VECTOR2[texNum];
	// �@���z��m��
	nor = new VECTOR3[norNum];

	// ������̂Ɏg�p
	int nNum = 0;

	// ���W�Ƃ���
	float x = 0, y = 0, z = 0;
	float u = 0, v = 0;

	// ����
	VECTOR3 one;
	one.x = 5.0f;
	one.y = 5.0f;
	float harf_x = nWidth  * 0.5f * one.x;
	float harf_y = nHeight * 0.5f * one.y;
	int harf_width = nWidth / 2;
	int harf_height = nHeight / 2;

	for(int i = 0; i < vtxNum; i++) {
		vtx[i].set(0, (float)(rand()%100-50)/50.0f, 0);
	}

	// ���_���̌v�Z
	for(z = (float)nVtxHNum-1; z >= 0; z--) {
		for(x = 0; x < nVtxWNum; x++) {
			float hhh = (rand()%1000-500) / 500.0f;
			float top = 0, left = 0, now = vtx[nNum].y;
			if(z < nVtxHNum-1) {
				top = vtx[nNum - nWidth].y;
			}
			if(x > 0) {
				left = vtx[nNum - 1].y;
			}
			now = (top + left + now)/3;
			hhh += now;

			vtx[nNum] = VECTOR3((float)(x * one.x) - harf_x, hhh, (float)(z * one.y) - harf_y);
			tex[nNum] = VECTOR2(u, v);
			nNum++;
			u+=1;
		}
		u = 0;
		v+=1;
	}

	// �@�������߂�
	initNormalVector(nWidth, nHeight);

	// ���[�N������
	nNum = 0;
	// �C���f�b�N�X�̌v�Z
	for(y = 0; y < nHeight; y++) {
		x = 0;
		if(y != 0) {
			idx[nNum] = ((WORD)y * nVtxWNum) + nVtxWNum + (WORD)x;
			nNum++;
		}
		for(x = 0; x < nVtxWNum; x++) {
			idx[nNum] = ((WORD)y * nVtxWNum) + nVtxWNum + (WORD)x;
			nNum++;
			idx[nNum] = ((WORD)y * nVtxWNum) + (WORD)x;
			nNum++;
		}
		x--;
		if(y != (nHeight - 1)) {
			idx[nNum] = ((WORD)y * nVtxWNum) + (WORD)x;
			nNum++;
		}
	}

	return this;
}

void Ground::update() {}

void Ground::draw() {
	if(texture) texture->apply();

	glLoadIdentity();

	GLfloat ambient[4] = {0.1f, 0.1f, 0.1f, 1.0f};
	GLfloat diffuse[4] = {0.8f, 0.8f, 0.8f, 1.0f};
	GLfloat specular[4] = {0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat emission[4] = {0.1f, 0.1f, 0.1f, 0.1f};

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.0f);

	glEnable(GL_LIGHTING);

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1.0f, 1.0f, 1.0f);
	for(int i = 0; i < prmNum; i++) {
		glTexCoord2f(tex[idx[i]].x, tex[idx[i]].y);
		glNormal3f(nor[idx[i]].x, nor[idx[i]].y, nor[idx[i]].z);
		glVertex3f(vtx[idx[i]].x, vtx[idx[i]].y, vtx[idx[i]].z);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);

#ifdef _DEBUG_LINE_
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glLineWidth(3);

	Player* player = (Player*)(Central::getInst()->findObject("player"));
	VECTOR3 pos(player->getTransform()->position);
	int nCnt = 0, nNum = 0;
	int nVertexWidthNum = PAR_X + 1;
	int nPolyParWidth = PAR_Y * 2;// ���|���S����
	int pos_x_num = 0, pos_z_num = 0;

	// ���|���S����
	for(int i = 0; i < PAR_X; i++) {
		// �w��͈͓��ɋ��邩X�l�Ŕ���
		if(vtx[i].x <= pos.x && pos.x <= vtx[i+1].x) {
			// �݁[����
			pos_x_num = i;
			break;
		}
	}
	// �c�|���S����
	for(int i = 0; i < PAR_Y; i++) {
		// �w��͈͓��ɋ��邩Z�l�Ŕ���
		int nShiftVertexNum = nVertexWidthNum * i;
		if(vtx[nShiftVertexNum+nVertexWidthNum].z <= pos.z && pos.z <= vtx[nShiftVertexNum].z) {
			// �݁[����
			pos_z_num = i;
			break;
		}
	}
	nCnt = pos_x_num + pos_z_num * nVertexWidthNum;
	nNum = pos_x_num * 2 + pos_z_num * nPolyParWidth;
	int nVer0 = nCnt;//�J�E���^�̂܂�                                ��
	int nVer1 = nCnt + nVertexWidthNum;//�J�E���^+�����_��           ��
	int nVer2 = nCnt + 1;//�J�E���^+1                                ��
	int nVer3 = nCnt + nVertexWidthNum + 1;//�J�E���^+�����_��+1     ��
	int idxs[4] = {nVer0, nVer1, nVer2, nVer3};

	glBegin(GL_LINES);
	VECTOR3 cols[4] = {VECTOR3::Right(), VECTOR3::Up(), VECTOR3::Forward(), VECTOR3(1, 1, 1)};
	for(int i = 0; i < 4; i++) {
		dm(glColor3f, cols[i]);
		dm(glVertex3f, vtx[idxs[i]]);
		dm(glVertex3f, vtx[idxs[i]]+VECTOR3::Up()*5);
	}
	glEnd();
	glEnable(GL_LIGHTING);

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.8f, 0.0f);
	for(int i = 0; i < prmNum; i++) {
		glVertex3f(vtx[idx[i]].x, vtx[idx[i]].y, vtx[idx[i]].z);
	}
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 0);
	for(int i = 0; i < norNum; i++) {
		glVertex3f(vtx[i].x, vtx[i].y, vtx[i].z);
		glVertex3f(vtx[i].x + nor[i].x, vtx[i].y + nor[i].y, vtx[i].z + nor[i].z);
	}
	glEnd();
	glEnable(GL_LIGHTING);
	glLineWidth(1);
#endif // _DEBUG_LINE_
}
void Ground::release() {
	SAFE_RELEASE(texture);
	SAFE_DELETE_ARRAY(vtx);
	SAFE_DELETE_ARRAY(idx);
	SAFE_DELETE_ARRAY(tex);
	SAFE_DELETE_ARRAY(nor);
	SAFE_DELETE_ARRAY(faceNor);
	vtxNum = 0;
	idxNum = 0;
	texNum = 0;
	prmNum = 0;
	delete this;
}

void Ground::initNormalVector(int nWidth, int nHeight) {
	// �ʂ̖@���x�N�g������

	int nPolyParWidth = nWidth * 2;// ���|���S����
	int nPolyParHeight = nHeight;// �c�|���S����
	int nVertexWidthNum = nWidth + 1; // �����_��
	int nVertexHeightNum = nHeight + 1;// �c���_��
	int nPolyNormalNum = nPolyParWidth * nPolyParHeight;// ���|���S����
	int nVertexNum = nVertexWidthNum * nVertexHeightNum;// ���_��
	faceNum = nPolyNormalNum;
	faceNor = new VECTOR3[nPolyNormalNum];
	// ���[�N�x�N�^�[
	VECTOR3 vec0, vec1;

	// �ʂ̖@��
	int nCnt = 0;

	int nNum = 0;
	// �ʂ̖@����S�ċ��ߏI���܂ŕԂ��Ă���ȁI
	while(nNum < nPolyNormalNum) {
		int nVer0 = nCnt;//�J�E���^�̂܂�
		int nVer1 = nCnt + nVertexWidthNum;//�J�E���^+�����_��
		int nVer2 = nCnt + nVertexWidthNum + 1;//�J�E���^+�����_��+1
		int nVer3 = nCnt + 1;/*�J�E���^+1*/

		// ��
		vec0 = vtx[nVer0] - vtx[nVer1];
		vec1 = vtx[nVer2] - vtx[nVer1];
		Vector3Cross(&faceNor[nNum], &vec0, &vec1);
		Vector3Normalize(&faceNor[nNum], &faceNor[nNum]);

		// �E
		vec0 = vtx[nVer2] - vtx[nVer3];
		vec1 = vtx[nVer0] - vtx[nVer3];
		Vector3Cross(&faceNor[nNum + 1], &vec0, &vec1);
		Vector3Normalize(&faceNor[nNum + 1], &faceNor[nNum + 1]);

		// �ʖ@���J�E���^��+2
		nNum += 2;
		// ���_�J�E���^���C���N�������g
		nCnt++;
		// �������̍s�Ɉڂ��Ă�����
		if(nNum % nPolyParWidth == 0) {
			// ���������C���N�������g
			nCnt++;
		}
	}

	// ���_�̖@�������߂�

	// �����̒��_�ԍ�
	int nVertexLeftBottomNum = nVertexNum - 1 - nWidth;
	// �E���̒��_�ԍ�
	int nVertexRightBottomNum = nVertexNum - 1;

	nCnt = 0;
	int nCnt2 = 0;
	for(nNum = 0; nNum < nVertexNum; nNum++) {
		// ����
		if(nNum == 0) {
			nor[nNum] = (faceNor[nCnt] + faceNor[nCnt + 1]) / 2;
			nCnt++;
			continue;
		}
		// �E��
		if(nNum == nVertexRightBottomNum) {
			nor[nNum] = (faceNor[nCnt2] + faceNor[nCnt2 + 1]) / 2;
			continue;
		}

		// �E�㖔
		if(nNum == nWidth) {
			nor[nNum] = faceNor[nCnt];
			nCnt++;
			continue;
		}
		// ����
		if(nNum == nVertexLeftBottomNum) {
			nor[nNum] = faceNor[nCnt2];
			continue;
		}

		// �����
		if(nNum > 0 && nNum < nWidth) {
			nor[nNum] = (faceNor[nCnt] + faceNor[nCnt + 1] + faceNor[nCnt + 2]) / 3;
			nCnt += 2;
			continue;
		}

		// ���S
		if(nNum > nVertexLeftBottomNum && nNum < nVertexRightBottomNum) {
			nor[nNum] = (faceNor[nCnt2] + faceNor[nCnt2 + 1] + faceNor[nCnt2 + 2]) / 3;
			nCnt2 += 2;
			continue;
		}

		// ������
		if(nNum % nVertexWidthNum == 0) {
			nor[nNum] = (faceNor[nCnt] + faceNor[nCnt + 1] + faceNor[nCnt2]) / 3;
			nCnt++;
			continue;
		}

		// �E����
		if(nNum % nVertexWidthNum == nWidth) {
			nor[nNum] = (faceNor[nCnt2] + faceNor[nCnt2 + 1] + faceNor[nCnt]) / 3;
			nCnt++;
			nCnt2+=2;
			continue;
		}
		// ����
		nor[nNum] = (faceNor[nCnt] + faceNor[nCnt + 1] + faceNor[nCnt + 2] + faceNor[nCnt2] + faceNor[nCnt2 + 1] + faceNor[nCnt2 + 2]) / 6;
		nCnt += 2;
		nCnt2 += 2;
	}
}
/** ���W�̍����擾
* @param pPos ���ׂ���W
* @return float ���ׂ��ۂ̍���(�͈͊O��-100(���փ��X�{�[���ʒu))
*/
float Ground::getHeight(const VECTOR3* pPos) {
	VECTOR3 pos(*pPos);
	int nCnt = 0, nNum = 0;
	int nVertexWidthNum = PAR_X + 1;
	int nPolyParWidth = PAR_Y * 2;// ���|���S����
	int pos_x_num = 0, pos_z_num = 0;

	// ���|���S����
	for(int i = 0; i < PAR_X; i++) {
		// �w��͈͓��ɋ��邩X�l�Ŕ���
		if(vtx[i].x <= pos.x && pos.x <= vtx[i+1].x) {
			// �݁[����
			pos_x_num = i;
			break;
		}
	}
	// �c�|���S����
	for(int i = 0; i < PAR_Y; i++) {
		// �w��͈͓��ɋ��邩Z�l�Ŕ���
		int nShiftVertexNum = nVertexWidthNum * i;
		if(vtx[nShiftVertexNum+nVertexWidthNum].z <= pos.z && pos.z <= vtx[nShiftVertexNum].z) {
			// �݁[����
			pos_z_num = i;
			break;
		}
	}

	nCnt = pos_x_num + pos_z_num * nVertexWidthNum;
	nNum = pos_x_num * 2 + pos_z_num * nPolyParWidth;

	int nVer0 = nCnt;//�J�E���^�̂܂�                                ��
	int nVer1 = nCnt + nVertexWidthNum;//�J�E���^+�����_��           ��
	int nVer2 = nCnt + 1;//�J�E���^+1                                ��
	int nVer3 = nCnt + nVertexWidthNum + 1;//�J�E���^+�����_��+1     ��

	// �傫�ȍ��ƉE�𒲂ׂ�
	if(HavePosition(&vtx[nVer0], &vtx[nVer3], &vtx[nVer1], &pos)) {
		// �����ɂ���
		pos.y = ((-((pos.x - vtx[nVer1].x) * faceNor[nNum].x) - ((pos.z - vtx[nVer1].z) * faceNor[nNum].z)) / faceNor[nNum].y) + vtx[nVer1].y;
	} else if(HavePosition(&vtx[nVer2], &vtx[nVer3], &vtx[nVer0], &pos)) {
		// �E���ɂ���
		pos.y = ((-((pos.x - vtx[nVer3].x) * faceNor[nNum + 1].x) - ((pos.z - vtx[nVer3].z) * faceNor[nNum + 1].z)) / faceNor[nNum + 1].y) + vtx[nVer3].y;
	} else {
		// ����ȊO
		pos.y = 0;
	}
	return pos.y;
}
