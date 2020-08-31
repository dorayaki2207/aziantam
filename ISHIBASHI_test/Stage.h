//#pragma once

//-----定数定義
#define MAP_X		 	45
#define MAP_Y			45
#define MAP_MOB_X		30
#define MAP_MOB_Y		30
#define MAP_ONI_X		40
#define MAP_ONI_Y		40
#define MAP_ONI2_X		25
#define MAP_ONI2_Y		25

#define MAP_START_Y 40	//はじまりの村
#define MAP_START_X 40


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
	STAGE_ID_START,
	STAGE_ID_MOB,				//MOB敵ｽﾃｰｼﾞ
	STAGE_ID_ONI,				//鬼ｽﾃｰｼﾞ
	STAGE_ID_ONI2,				//鬼洞窟
	STAGE_ID_MAX
};
//ｲﾍﾞﾝﾄ情報
enum EVENT_ID
{
	EVENT_ID_NON,			//ｲﾍﾞﾝﾄなし
	EVENT_ID_KAIDAN,		//階段①
	EVENT_ID_KAIDAN2,		//階段②
	EVENT_ID_DOKUTU,
	EVENT_ID_DAMAGE,		//ﾀﾞﾒｰｼﾞ
	EVENT_ID_STOP,			//止まる
	EVENT_ID_SPEEDDOWN,		//動きが遅くなる
	EVENT_ID_MAX
};

enum CHIP_POS
{
	CHIP_POS_KAIDAN,
	CHIP_POS_KAIDAN2,
	CHIP_POS_NON,
	CHIP_POS_MAX
};


//-----関数ﾌﾟﾛﾄﾀｲﾌﾟ宣言
void StageSystemInit(void);		//ｽﾃｰｼﾞ情報の初期化	
void StageGameInit(void);		//						
void StageGameDraw(void);		//ｽﾃｰｼﾞ用描画処理
void SetMapData(STAGE_ID stage_ID);
XY PosToIndex(XY pos);	        //ﾋﾟｸｾﾙ座標系からﾏｯﾌﾟ配列座標系に変換する
bool IsPass(XY pos);			//指定した座標が通過可能かを返す true:通過できる
EVENT_ID GetEvent(XY pos);	    // 指定した座標が特別にｲﾍﾞﾝﾄを起こすかを確認する　戻り値：ｲﾍﾞﾝﾄID
void MapRange();

void GetPos(XY pos);
//-----ｸﾞﾛｰﾊﾞﾙ化
extern XY mapPos;
extern XY mapSize;
