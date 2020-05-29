//#pragma once

//-----定数定義
#define MAP_X			30
#define MAP_Y			30
#define CHIP_SIZE_X		32
#define CHIP_SIZE_Y		32

#define SCROLL_X_MIN 100
#define SCROLL_X_MAX 400
#define SCROLL_Y_MIN 100
#define SCROLL_Y_MAX 550

//出現可能かどうか
enum PASS_ID
{
	PASS_OK,				//	出現可能
	PASS_NON
};


//-----関数ﾌﾟﾛﾄﾀｲﾌﾟ宣言
void StageSystemInit(void);		//　ｽﾃｰｼﾞ情報の初期化	
void StageGameInit(void);			//						
void StageGameDraw(void);			//　ｽﾃｰｼﾞ用描画処理
XY PosToIndex(XY pos);	           //ﾋﾟｸｾﾙ座標系からﾏｯﾌﾟ配列座標系に変換する
bool IsPass(XY pos);						//指定した座標が通過可能かを返す true:通過できる
//bool IsEnemyPass(XY pos);
PASS_ID Pass(XY pos);
//-----ｸﾞﾛｰﾊﾞﾙ化
extern XY mapPos;
extern PASS_ID passID;