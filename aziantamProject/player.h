//#pragma once

//定数
#define PLAYER_DEF_SPEED  5		//プレイヤーの初期移動量
#define PLAYER_MAX_LIFE  100	//プレイヤーの最大体力


//プロトタイプ宣言
void PlayerSystemInit(void);				//ﾌﾟﾚｲﾔｰ情報の初期化
void PlayerGameInit(void);					//プレイヤーの初期化
void PlayerControl(void);					//プレイヤーの操作
void PlayerGameDraw(void);						//プレイヤーの描画
