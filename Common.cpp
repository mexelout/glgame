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
* sprintfを使用した四捨五入関数
* @param num 四捨五入する元の数値
* @param precision 四捨五入する桁
* @return 四捨五入した結果
*/
float roundprecision(float num, int precision) {
	char s[256] = {0};
	sprintf(s, "%.*f", precision-1, num);
	return (float)atof(s);
}

/** 外積判定用関数\n
* pVtx0とpVtx1のベクトルとpVtx0とpPosのベクトルを外積計算し、その結果を返す
* @param pVtx0 2本のベクトルの開始点
* @param pVtx1 基準となるベクトルの終了点
* @param pPos 調べるベクトルの終了点
* @return float 基準のベクトルよりpPosが右側なら正の値を、左側なら腐┌(^o^┐)┐{ﾎﾓｫ…の値を返す
*/
float TestCross(const VECTOR3* pVtx0, const VECTOR3* pVtx1, const VECTOR3* pPos) {
	VECTOR3 vec0, vec1;

	vec0 = *pVtx1 - *pVtx0;
	vec1 = *pPos - *pVtx0;

	return (vec0.z * vec1.x - vec0.x * vec1.z);
}

/** 外積を使用した3頂点内にポジションがあるかどうか調べる関数\n
* 3つの頂点内に調べたいポジションがあるかどうか調べる左回りにそれぞれの頂点を送る
* @param pVtx0 頂点0
* @param pVtx1 頂点1
* @param pVtx2 頂点1
* @param pPos 調べる頂点(プレイヤーとかエネミーとか)
* @return BOOL いるなら返事しろー
*/
bool HavePosition(VECTOR3* pVtx0, VECTOR3* pVtx1, VECTOR3* pVtx2, VECTOR3* pPos) {
	return (TestCross(pVtx0, pVtx1, pPos) >= 0 && TestCross(pVtx1, pVtx2, pPos) >= 0 && TestCross(pVtx2, pVtx0, pPos) >= 0) ? true : false;
}

/**
 * デバッグ出力
 * @param str 出力する文字列
 */
void debug(const char* str) {
	char out[512] = {0};
	strcat(out, str);
	strcat(out, "\n");
	OutputDebugStringA(out);
}

/**
 * 数値を文字に変換(int)
 * @param value 文字にする数値
 * @return char* 変換した文字列
 */
char* to_s(int value) {
	memset(buffer, 0, sizeof(buffer));
	itoa(value, buffer, 256);
	return buffer;
}

/**
 * 数値を文字に変換(float)
 * @param value 文字にする数値
 * @return char* 変換した文字列
 */
char* to_s(float value) {
	memset(buffer, 0, sizeof(buffer));
	sprintf(buffer, "%f", value);
	return buffer;
}

/**
 * 共有スタッククリーン
 */
void cleanString() {
	memset(attach, 0, sizeof(attach));
}

/**
 * 共有スタック文字列に連結
 * @param str1 連結左側文字列
 * @param str2 連結右側文字列
 * @return char* 連結された文字列
 */
char* attachString(char* str1, char* str2) {
	if(attach != str1) strcat(attach, str1);
	strcat(attach, str2);
	return attach;
}

/**
 * バウンドボックス
 * @param lt 左上
 @ @param rb 右下
 * @param p 調べる座標
 * @return true : in false : out
 */
bool boundBox(const VECTOR2& lt, const VECTOR2& rb, const VECTOR2& p) {
	if(lt.x < p.x && lt.y > p.y && rb.x > p.x && rb.y < p.y) {
			return true;
	}
	return false;
}

/**
 * OpenGL系の関数を楽にするやつ(めんどくささ回避)
 * @param callback 呼び出すOpenGL描画メソッド(3つ固定)
 * @param v 出力するベクトル
 */
void dm(void (__stdcall *callback)(float, float, float), const VECTOR3& v) {
	callback(v.x, v.y, v.z);
}
