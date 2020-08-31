//-------------------------
// effect.cpp
// 2019.09.26
// 山本美由紀
//-------------------------
#include <DxLib.h>
#include "effect.h"

//変数
//---------------------
//画面切り替えエフェクト
int fadeCnt;
bool fadeIn;
bool fadeOut;
//一時停止エフェクト
int pauseFlag;

//エフェクトの初期化
void EffectInit(void)
{
	fadeIn = false;
	fadeOut = false;
	fadeCnt = 0;
	pauseFlag = false;
}
//フェードイン処理
bool FadeInScreen(int fadeStep)
{
	fadeCnt += fadeStep;
	if (fadeCnt <= 255)
	{
		SetDrawBright(fadeCnt, fadeCnt, fadeCnt);
		return true;
	}
	else
	{
		SetDrawBright(255, 255, 255);
		fadeCnt = 0;
		fadeIn = false;
		return false;
	}
}
//フェードアウト処理
bool FadeOutScreen(int fadeStep)
{
	fadeCnt += fadeStep;
	if (fadeCnt <= 255)
	{
		SetDrawBright(255 - fadeCnt, 255 - fadeCnt, 255 - fadeCnt);
		return true;
	}
	else
	{
		SetDrawBright(0, 0, 0);
		fadeCnt = 0;
		fadeOut = false;
		return false;
	}
}