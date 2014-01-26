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

	// 横頂点数(計算に使用)
	int nVtxWNum = nWidth + 1;
	int nVtxHNum = nHeight + 1;
	// 全頂点数
	vtxNum = (nVtxWNum * nVtxHNum);
	// 全インデックス数
	idxNum = (((nVtxWNum * 2) * nHeight) + ((nHeight - 1) * 2));
	// テクスコード数
	texNum = vtxNum;
	// 法線数
	norNum = vtxNum;
	// プリミティブ数
	prmNum = ((nWidth * 2 * nHeight) + ((nHeight - 1) * 4))+2;
	// 頂点配列確保
	vtx = new VECTOR3[vtxNum];
	// インデックス配列確保
	idx = new int[idxNum];
	// テクスコード配列確保
	tex = new VECTOR2[texNum];
	// 法線配列確保
	nor = new VECTOR3[norNum];

	// 数えるのに使用
	int nNum = 0;

	// 座標とかに
	float x = 0, y = 0, z = 0;
	float u = 0, v = 0;

	// 半分
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

	// 頂点情報の計算
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

	// 法線を求める
	initNormalVector(nWidth, nHeight);

	// ワーク初期化
	nNum = 0;
	// インデックスの計算
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
	int nPolyParWidth = PAR_Y * 2;// 横ポリゴン数
	int pos_x_num = 0, pos_z_num = 0;

	// 横ポリゴン数
	for(int i = 0; i < PAR_X; i++) {
		// 指定範囲内に居るかX値で判定
		if(vtx[i].x <= pos.x && pos.x <= vtx[i+1].x) {
			// みーつけた
			pos_x_num = i;
			break;
		}
	}
	// 縦ポリゴン数
	for(int i = 0; i < PAR_Y; i++) {
		// 指定範囲内に居るかZ値で判定
		int nShiftVertexNum = nVertexWidthNum * i;
		if(vtx[nShiftVertexNum+nVertexWidthNum].z <= pos.z && pos.z <= vtx[nShiftVertexNum].z) {
			// みーつけた
			pos_z_num = i;
			break;
		}
	}
	nCnt = pos_x_num + pos_z_num * nVertexWidthNum;
	nNum = pos_x_num * 2 + pos_z_num * nPolyParWidth;
	int nVer0 = nCnt;//カウンタのまま                                ┌
	int nVer1 = nCnt + nVertexWidthNum;//カウンタ+横頂点数           └
	int nVer2 = nCnt + 1;//カウンタ+1                                ┐
	int nVer3 = nCnt + nVertexWidthNum + 1;//カウンタ+横頂点数+1     ┘
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
	// 面の法線ベクトル生成

	int nPolyParWidth = nWidth * 2;// 横ポリゴン数
	int nPolyParHeight = nHeight;// 縦ポリゴン数
	int nVertexWidthNum = nWidth + 1; // 横頂点数
	int nVertexHeightNum = nHeight + 1;// 縦頂点数
	int nPolyNormalNum = nPolyParWidth * nPolyParHeight;// 総ポリゴン数
	int nVertexNum = nVertexWidthNum * nVertexHeightNum;// 頂点数
	faceNum = nPolyNormalNum;
	faceNor = new VECTOR3[nPolyNormalNum];
	// ワークベクター
	VECTOR3 vec0, vec1;

	// 面の法線
	int nCnt = 0;

	int nNum = 0;
	// 面の法線を全て求め終わるまで返ってくるな！
	while(nNum < nPolyNormalNum) {
		int nVer0 = nCnt;//カウンタのまま
		int nVer1 = nCnt + nVertexWidthNum;//カウンタ+横頂点数
		int nVer2 = nCnt + nVertexWidthNum + 1;//カウンタ+横頂点数+1
		int nVer3 = nCnt + 1;/*カウンタ+1*/

		// 左
		vec0 = vtx[nVer0] - vtx[nVer1];
		vec1 = vtx[nVer2] - vtx[nVer1];
		Vector3Cross(&faceNor[nNum], &vec0, &vec1);
		Vector3Normalize(&faceNor[nNum], &faceNor[nNum]);

		// 右
		vec0 = vtx[nVer2] - vtx[nVer3];
		vec1 = vtx[nVer0] - vtx[nVer3];
		Vector3Cross(&faceNor[nNum + 1], &vec0, &vec1);
		Vector3Normalize(&faceNor[nNum + 1], &faceNor[nNum + 1]);

		// 面法線カウンタを+2
		nNum += 2;
		// 頂点カウンタをインクリメント
		nCnt++;
		// もし次の行に移っていたら
		if(nNum % nPolyParWidth == 0) {
			// もっかいインクリメント
			nCnt++;
		}
	}

	// 頂点の法線を求める

	// 左下の頂点番号
	int nVertexLeftBottomNum = nVertexNum - 1 - nWidth;
	// 右下の頂点番号
	int nVertexRightBottomNum = nVertexNum - 1;

	nCnt = 0;
	int nCnt2 = 0;
	for(nNum = 0; nNum < nVertexNum; nNum++) {
		// 左上
		if(nNum == 0) {
			nor[nNum] = (faceNor[nCnt] + faceNor[nCnt + 1]) / 2;
			nCnt++;
			continue;
		}
		// 右下
		if(nNum == nVertexRightBottomNum) {
			nor[nNum] = (faceNor[nCnt2] + faceNor[nCnt2 + 1]) / 2;
			continue;
		}

		// 右上又
		if(nNum == nWidth) {
			nor[nNum] = faceNor[nCnt];
			nCnt++;
			continue;
		}
		// 左下
		if(nNum == nVertexLeftBottomNum) {
			nor[nNum] = faceNor[nCnt2];
			continue;
		}

		// 上内側
		if(nNum > 0 && nNum < nWidth) {
			nor[nNum] = (faceNor[nCnt] + faceNor[nCnt + 1] + faceNor[nCnt + 2]) / 3;
			nCnt += 2;
			continue;
		}

		// 下心
		if(nNum > nVertexLeftBottomNum && nNum < nVertexRightBottomNum) {
			nor[nNum] = (faceNor[nCnt2] + faceNor[nCnt2 + 1] + faceNor[nCnt2 + 2]) / 3;
			nCnt2 += 2;
			continue;
		}

		// 左内側
		if(nNum % nVertexWidthNum == 0) {
			nor[nNum] = (faceNor[nCnt] + faceNor[nCnt + 1] + faceNor[nCnt2]) / 3;
			nCnt++;
			continue;
		}

		// 右内側
		if(nNum % nVertexWidthNum == nWidth) {
			nor[nNum] = (faceNor[nCnt2] + faceNor[nCnt2 + 1] + faceNor[nCnt]) / 3;
			nCnt++;
			nCnt2+=2;
			continue;
		}
		// 内側
		nor[nNum] = (faceNor[nCnt] + faceNor[nCnt + 1] + faceNor[nCnt + 2] + faceNor[nCnt2] + faceNor[nCnt2 + 1] + faceNor[nCnt2 + 2]) / 6;
		nCnt += 2;
		nCnt2 += 2;
	}
}
/** 座標の高さ取得
* @param pPos 調べる座標
* @return float 調べた際の高さ(範囲外は-100(上空へリスボーン位置))
*/
float Ground::getHeight(const VECTOR3* pPos) {
	VECTOR3 pos(*pPos);
	int nCnt = 0, nNum = 0;
	int nVertexWidthNum = PAR_X + 1;
	int nPolyParWidth = PAR_Y * 2;// 横ポリゴン数
	int pos_x_num = 0, pos_z_num = 0;

	// 横ポリゴン数
	for(int i = 0; i < PAR_X; i++) {
		// 指定範囲内に居るかX値で判定
		if(vtx[i].x <= pos.x && pos.x <= vtx[i+1].x) {
			// みーつけた
			pos_x_num = i;
			break;
		}
	}
	// 縦ポリゴン数
	for(int i = 0; i < PAR_Y; i++) {
		// 指定範囲内に居るかZ値で判定
		int nShiftVertexNum = nVertexWidthNum * i;
		if(vtx[nShiftVertexNum+nVertexWidthNum].z <= pos.z && pos.z <= vtx[nShiftVertexNum].z) {
			// みーつけた
			pos_z_num = i;
			break;
		}
	}

	nCnt = pos_x_num + pos_z_num * nVertexWidthNum;
	nNum = pos_x_num * 2 + pos_z_num * nPolyParWidth;

	int nVer0 = nCnt;//カウンタのまま                                ┌
	int nVer1 = nCnt + nVertexWidthNum;//カウンタ+横頂点数           └
	int nVer2 = nCnt + 1;//カウンタ+1                                ┐
	int nVer3 = nCnt + nVertexWidthNum + 1;//カウンタ+横頂点数+1     ┘

	// 大きな左と右を調べる
	if(HavePosition(&vtx[nVer0], &vtx[nVer3], &vtx[nVer1], &pos)) {
		// 左側にいる
		pos.y = ((-((pos.x - vtx[nVer1].x) * faceNor[nNum].x) - ((pos.z - vtx[nVer1].z) * faceNor[nNum].z)) / faceNor[nNum].y) + vtx[nVer1].y;
	} else if(HavePosition(&vtx[nVer2], &vtx[nVer3], &vtx[nVer0], &pos)) {
		// 右側にいる
		pos.y = ((-((pos.x - vtx[nVer3].x) * faceNor[nNum + 1].x) - ((pos.z - vtx[nVer3].z) * faceNor[nNum + 1].z)) / faceNor[nNum + 1].y) + vtx[nVer3].y;
	} else {
		// それ以外
		pos.y = 0;
	}
	return pos.y;
}
