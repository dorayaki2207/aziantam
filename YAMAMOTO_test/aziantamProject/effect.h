//#pragma once
//-------------------------
// effect.h
// 2019.09.26
// 山本美由紀
//-------------------------

//extern宣言
//---------------
//画面切り替えエフェクト
extern int fadeCnt;
extern bool fadeIn;
extern bool fadeOut;
//一時停止エフェクト
extern int pauseFlag;

//プロトタイプ宣言
//---------------
void EffectInit(void);					//エフェクトの初期化
bool FadeInScreen(int fadeStep);		//ﾌｪｰﾄﾞｲﾝの処理
bool FadeOutScreen(int fadeStep);		//ﾌｪｰﾄﾞｱｳﾄの処理