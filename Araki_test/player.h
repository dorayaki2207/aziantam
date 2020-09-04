//#pragma once

//定数
#define PLAYER_DEF_SPEED  4		//ﾌﾟﾚｲﾔｰの初期移動量
#define PLAYER_MAX_LIFE  500	//ﾌﾟﾚｲﾔｰの最大体力

#define SCROLL_X_MIN	200		//ｽｸﾛｰﾙ可能頭座標X
#define SCROLL_X_MAX	500		//ｽｸﾛｰﾙ可能頭座標Y
#define SCROLL_Y_MIN	200		//ｽｸﾛｰﾙ可能御尻座標X
#define SCROLL_Y_MAX	500		//ｽｸﾛｰﾙ可能御尻座標Y

enum PLAYER_SPEED
{
	PLAYER_SPEED_LOW = 1,		//遅い
	PLAYER_SPEED_NORMAL = 3,	//通常
	PLAYER_SPEED_HIGH = 7,		//速い
	PLAYER_SPEED_STOP = 0,			//止まる
	PLAYER_SPEED_MAX
};


//プロトタイプ宣言
void PlayerSystemInit(void);	//ﾌﾟﾚｲﾔｰ情報の初期化
void PlayerGameInit(void);		//ﾌﾟﾚｲﾔｰの初期化
XY PlayerControl(void);			//ﾌﾟﾚｲﾔｰの操作
void PlayerGameDraw(void);		//ﾌﾟﾚｲﾔｰの描画
void PlayerEvent(void);
bool PlayerDid(void);
