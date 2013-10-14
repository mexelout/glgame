#ifndef _COMMON_H_
#define _COMMON_H_

// オーバーライドの警告抑止
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
* sprintfを使用した四捨五入関数
* @param num 四捨五入する元の数値
* @param precision 四捨五入する桁
* @return 四捨五入した結果
*/
float roundprecision(float num, int precision);

/** 外積判定用関数\n
* pVtx0とpVtx1のベクトルとpVtx0とpPosのベクトルを外積計算し、その結果を返す
* @param Vector3* pVtx0 2本のベクトルの開始点
* @param Vector3* pVtx1 基準となるベクトルの終了点
* @param Vector3* pPos 調べるベクトルの終了点
* @return float 基準のベクトルよりpPosが右側なら正の値を、左側なら腐┌(^o^┐)┐{ﾎﾓｫ…の値を返す
*/
float TestCross(const VECTOR3* pVtx0, const VECTOR3* pVtx1, const VECTOR3* pPos);
/** 外積を使用した3頂点内にポジションがあるかどうか調べる関数\n
* 3つの頂点内に調べたいポジションがあるかどうか調べる右回りにそれぞれの頂点を送る
* @param pVtx0 頂点0
* @param pVtx1 頂点1
* @param pVtx2 頂点1
* @param pPos 調べる頂点(プレイヤーとかエネミーとか)
* @return BOOL いるなら返事しろー
*/
bool HavePosition(VECTOR3* pVtx0, VECTOR3* pVtx1, VECTOR3* pVtx2, VECTOR3* pPos);

/**
 * デバッグ出力
 * @param str 出力文字(この関数を呼ぶと自動で改行)
 */
void debug(const char* str);

/**
 * 数値を文字に変換
 * @param value 変換したい文字列
 * @return 共有バッファ
 */
char* to_s(int value);

/**
 * 数値を文字に変換
 * @param value 変換したい文字列
 * @return 共有バッファ
 */
char* to_s(float value);

/**
 * 共有スタッククリーン
 */
void cleanString();

/**
 * 共有スタック文字列に連結
 * @param str1, str2 連結したい文字
 * @return 共有バッファ
 */
char* attachString(char* str1, char* str2);

/**
 * バウンドボックス
 * @param lt 左上
 @ @param rb 右下
 * @param p 調べる座標
 * @return true : in false : out
 */
bool boundBox(const VECTOR2& lt, const VECTOR2& rb, const VECTOR2& p);

#endif // _COMMON_H_