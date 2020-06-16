//#pragma once

//-----定数定義
#define MAP_X			45
#define MAP_Y			45
#define MAP_MOB_X		30
#define MAP_MOB_Y		30
#define MAP_ONI_X		40
#define MAP_ONI_Y		40

#define MAP_TEST_X		30
#define MAP_TEST_Y		30


#define CHIP_SIZE_X		32
#define CHIP_SIZE_Y		32

#define SCROLL_X_MIN 100
#define SCROLL_X_MAX 400
#define SCROLL_Y_MIN 100
#define SCROLL_Y_MAX 400


//-----列挙型
//ｽﾃｰｼﾞ情報
enum STAGE_ID
{
	STAGE_ID_MOB,				//MOB敵ｽﾃｰｼﾞ
	STAGE_ID_ONI,				//鬼ｽﾃｰｼﾞ
	STAGE_ID_TEST,
	STAGE_ID_TEST2,
	STAGE_ID_MAX
};

//出現可能かどうか
enum PASS_ID
{
	PASS_OK,					//出現可能
	PASS_NON
};


//-----関数ﾌﾟﾛﾄﾀｲﾌﾟ宣言
void StageSystemInit(void);		//ｽﾃｰｼﾞ情報の初期化	
void StageGameInit(void);		//						
void StageGameDraw(void);		//ｽﾃｰｼﾞ用描画処理
void SetMapData(STAGE_ID stage_ID);
XY PosToIndex(XY pos);	        //ﾋﾟｸｾﾙ座標系からﾏｯﾌﾟ配列座標系に変換する
bool IsPass(XY pos);			//指定した座標が通過可能かを返す true:通過できる
//bool IsEnemyPass(XY pos);
PASS_ID Pass(XY pos);
void MapRange();
//-----ｸﾞﾛｰﾊﾞﾙ化
extern XY mapPos;
extern XY mapSize;
extern PASS_ID passID;