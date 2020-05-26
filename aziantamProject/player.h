//#pragma once

//定数
#define PLAYER_DEF_SPEED  4		//ﾌﾟﾚｲﾔｰの初期移動量
#define PLAYER_MAX_LIFE  100	//ﾌﾟﾚｲﾔｰの最大体力

#define SCROLL_X_MIN	100		//ｽｸﾛｰﾙ可能頭座標X
#define SCROLL_X_MAX	700		//ｽｸﾛｰﾙ可能頭座標Y
#define SCROLL_Y_MIN	100		//ｽｸﾛｰﾙ可能御尻座標X
#define SCROLL_Y_MAX	500		//ｽｸﾛｰﾙ可能御尻座標Y


//プロトタイプ宣言
void PlayerSystemInit(void);	//ﾌﾟﾚｲﾔｰ情報の初期化
void PlayerGameInit(void);		//ﾌﾟﾚｲﾔｰの初期化
XY PlayerControl(void);			//ﾌﾟﾚｲﾔｰの操作
void PlayerGameDraw(void);		//ﾌﾟﾚｲﾔｰの描画
