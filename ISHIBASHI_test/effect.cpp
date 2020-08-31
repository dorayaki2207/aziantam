//-------------------------
// effect.cpp
// 2019.09.26
// 山本美由紀
//-------------------------
#include <DxLib.h>
#include "effect.h"
#include "test.h"
#include "Stage.h"

//変数
//---------------------
//画面切り替えエフェクト
int fadeCnt;
bool fadeIn;
bool fadeOut;

//ダメージエフェクト
CHARACTER effectMaster[MAGIC_TYPE_MAX - 1];
CHARACTER effect[EFFECT_MAX];
int DeffectImage[MAGIC_TYPE_MAX - 1][9];

void EffectSystemInit(void)
{
	//-----初期化
	effectMaster[MAGIC_TYPE_FIRE].charType = MAGIC_TYPE_FIRE;
	effectMaster[MAGIC_TYPE_WIND].charType = MAGIC_TYPE_WIND;
	effectMaster[MAGIC_TYPE_WATER].charType = MAGIC_TYPE_WATER;

	for (int type = 0; type < MAGIC_TYPE_MAX; type++)
	{
		effectMaster[type].moveDir = DIR_DOWN;
		effectMaster[type].pos = { 0,0 };
		effectMaster[type].size = { 120,120 };
		effectMaster[type].offsetSize = { effectMaster[type].size.x / 2
			,effectMaster[type].size.y / 2 };
		effectMaster[type].moveSpeed = 4;
		effectMaster[type].lifeMax = EFFECT_LIFE_MAX;
		effectMaster[type].life = effectMaster[type].lifeMax;
		effectMaster[type].animCnt = 0;

		for (int ef = 0; ef < EFFECT_MAX; ef++)
		{
			effect[ef] = effectMaster[type];
			effect[ef].pos = { 0,0 };
			effect[ef].lifeMax = EFFECT_LIFE_MAX;
			effect[ef].life = 0;
			effect[ef].animCnt = 0;
		}

	}

	//-----ｸﾞﾗﾌｨｯｸの登録
	LoadDivGraph("aitem/e_fire.png", EFFECT_ANI, 9, 1
		, effectMaster[MAGIC_TYPE_FIRE].size.x
		, effectMaster[MAGIC_TYPE_FIRE].size.y
		, DeffectImage[MAGIC_TYPE_FIRE]);
	LoadDivGraph("aitem/e_wind.png", EFFECT_ANI, 9, 1
		, effectMaster[MAGIC_TYPE_WIND].size.x
		, effectMaster[MAGIC_TYPE_WIND].size.y
		, DeffectImage[MAGIC_TYPE_WIND]);
	LoadDivGraph("aitem/e_water.png", EFFECT_ANI, 9, 1
		, effectMaster[MAGIC_TYPE_WATER].size.x
		, effectMaster[MAGIC_TYPE_WATER].size.y
		, DeffectImage[MAGIC_TYPE_WATER]);

}

//エフェクトの初期化1111
void EffectInit(void)
{
	for (int ef = 0; ef < EFFECT_MAX; ef++)
	{
		effect[ef].pos = { 50,50 };
		effect[ef].life = 0;
	}

	fadeIn = false;
	fadeOut = false;
	fadeCnt = 0;
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

void EffectControl(void)
{
	for (int ef = 0; ef < EFFECT_MAX; ef++)
	{
		if (CheckHitKey(KEY_INPUT_Q))
		{
			if (effect[ef].charType == MAGIC_TYPE_FIRE)
			{
				effect[ef].pos.x += effect[ef].moveSpeed;
			}
		}
	}
}

void EffectGameDraw(void)
{
	//-----描画処理
	for (int ef = 0; ef < EFFECT_MAX; ef++)
	{
		if (effect[ef].life > 0)
		{
			effect[ef].animCnt++;

			DrawGraph(effect[MAGIC_TYPE_FIRE].pos.x - effect[MAGIC_TYPE_FIRE].offsetSize.x + mapPos.x
				, effect[MAGIC_TYPE_FIRE].pos.y - effect[MAGIC_TYPE_FIRE].offsetSize.y + mapPos.y
				, DeffectImage[effect[MAGIC_TYPE_FIRE].charType][(effect[ef].animCnt / 30) % 9]
				,true);

			DrawBox(effect[ef].pos.x - effect[ef].offsetSize.x + mapPos.x
				, effect[ef].pos.y - effect[ef].offsetSize.y + mapPos.y
				, effect[ef].pos.x - effect[ef].offsetSize.x + effect[ef].size.x + mapPos.x
				, effect[ef].pos.y - effect[ef].offsetSize.y + effect[ef].size.y + mapPos.y
				, 0xFFFFFF, false);
		}
	}

}

//void CreateEffect(XY pPpos, DIR pDir, MAGIC_TYPE ptype)
//{
//}

void DeleteEffect(int index)
{
	effect[index].life = 0;
}
