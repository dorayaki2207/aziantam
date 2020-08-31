//#pragma once
//-------------------------
// effect.h
// 2019.09.26
// 山本美由紀
//-------------------------

//-----定数定義
#define EFFECT_MAX		 20
#define EFFECT_LIFE_MAX  10
#define EFFECT_ANI		  9

//プロトタイプ宣言
//---------------
void EffectSystemInit(void);
void EffectInit(void);					//エフェクトの初期化
bool FadeInScreen(int fadeStep);		//ﾌｪｰﾄﾞｲﾝの処理
bool FadeOutScreen(int fadeStep);		//ﾌｪｰﾄﾞｱｳﾄの処理
//ﾀﾞﾒｰｼﾞｴﾌｪｸﾄ
void EffectControl(void);
void EffectGameDraw(void);
//void CreateEffect(XY pPpos, DIR pDir, MAGIC_TYPE ptype);
void DeleteEffect(int index);


//extern宣言
//---------------
//画面切り替えエフェクト
extern int fadeCnt;
extern bool fadeIn;
extern bool fadeOut;
