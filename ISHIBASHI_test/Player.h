//#pragma once


//-----定数定義
#define PLAYER_MAX	4


//-----関数ﾌﾟﾛﾄﾀｲﾌﾟ宣言
void PlayerSystmeInit(void);		//　ﾌﾟﾚｲﾔｰ情報の初期化	
void PlayerGameInit(void);			//						
XY PlayerControl(void);			//	ﾌﾟﾚｲﾔｰの操作(戻り値：ﾌﾟﾚｲﾔｰの座標)
void PlayerGameDraw(void);			//　ﾌﾟﾚｲﾔｰ描画処理
