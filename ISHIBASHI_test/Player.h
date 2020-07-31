//#pragma once


//-----定数定義
#define PLAYER_MAX	4

//-----列挙型
enum PLAYER_SPEED
{
	PLAYER_SPEED_LOW = 2,		//	遅い
	PLAYER_SPEED_NOMAL = 4,		//	通常
	PLATER_SPEED_HIGH = 6,		//	速い
	PLATER_SPEED_MAX
};

//-----関数ﾌﾟﾛﾄﾀｲﾌﾟ宣言
void PlayerSystemInit(void);		//　ﾌﾟﾚｲﾔｰ情報の初期化	
void PlayerGameInit(void);			//						
XY PlayerControl(void);			//	ﾌﾟﾚｲﾔｰの操作(戻り値：ﾌﾟﾚｲﾔｰの座標)
void PlayerGameDraw(void);			//　ﾌﾟﾚｲﾔｰ描画処理

