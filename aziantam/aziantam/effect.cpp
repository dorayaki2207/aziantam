//-------------------------
// effect.cpp
// 2019.09.26
// �R�{���R�I
//-------------------------
#include <DxLib.h>
#include "main.h"
#include "effect.h"
#include "stage.h"

//�ϐ�
//---------------------
//��ʐ؂�ւ��G�t�F�N�g
int fadeCnt;
bool fadeIn;
bool fadeOut;
//�_���[�W�G�t�F�N�g
CHARACTER effectMaster[MAGIC_TYPE_MAX];
CHARACTER effect[EFFECT_MAX];
int effectImage[MAGIC_TYPE_MAX][EFFECT_ANI];

void EffectSystemInit(void)
{
	//-----������
	effectMaster[MAGIC_TYPE_FIRE].charType = MAGIC_TYPE_FIRE;
	effectMaster[MAGIC_TYPE_WIND].charType = MAGIC_TYPE_WIND;
	effectMaster[MAGIC_TYPE_WATER].charType = MAGIC_TYPE_WATER;
	effectMaster[MAGIC_TYPE_HEAL].charType = MAGIC_TYPE_HEAL;

	for (int type = 0; type < MAGIC_TYPE_MAX; type++)
	{
		effectMaster[type].pos = { 0,0 };
		effectMaster[type].size = { 120,120 };
		effectMaster[type].offsetSize = { effectMaster[type].size.x / 2
			,effectMaster[type].size.y / 2 };
		effectMaster[type].lifeMax = EFFECT_LIFE_MAX;
		effectMaster[type].life = 0;
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

	//-----���̨���̓o�^
	LoadDivGraph("item/e_fire.png", EFFECT_ANI, 9, 1
		, effectMaster[MAGIC_TYPE_FIRE].size.x
		, effectMaster[MAGIC_TYPE_FIRE].size.y
		, effectImage[MAGIC_TYPE_FIRE]);
	LoadDivGraph("item/e_wind.png", EFFECT_ANI, 9, 1
		, effectMaster[MAGIC_TYPE_WIND].size.x
		, effectMaster[MAGIC_TYPE_WIND].size.y
		, effectImage[MAGIC_TYPE_WIND]);
	LoadDivGraph("item/e_water.png", EFFECT_ANI, 9, 1
		, effectMaster[MAGIC_TYPE_WATER].size.x
		, effectMaster[MAGIC_TYPE_WATER].size.y
		, effectImage[MAGIC_TYPE_WATER]);
	LoadDivGraph("item/e_player.png", EFFECT_ANI, 9, 1
		, effectMaster[MAGIC_TYPE_HEAL].size.x
		, effectMaster[MAGIC_TYPE_HEAL].size.y
		, effectImage[MAGIC_TYPE_HEAL]);
}

//�G�t�F�N�g�̏�����
void EffectGameInit(void)
{
	for (int ef = 0; ef < EFFECT_MAX; ef++)
	{
		effect[ef].pos = { 0,0 };
		effect[ef].life = 0;
	}

	fadeIn = false;
	fadeOut = false;
	fadeCnt = 0;
}
//�t�F�[�h�C������
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
//�t�F�[�h�A�E�g����
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

//�G�t�F�N�g����
void EffectControl(void)
{
	for (int ef = 0; ef < EFFECT_MAX; ef++)
	{
		if (effect[ef].animCnt >= EFFECT_ANI)
		{
			effect[ef].life = 0;
			effect[ef].animCnt = 0;
		}
	}
}

//�G�t�F�N�g�`��
void EffectGameDraw(void)
{
	//-----�`�揈��
	for (int ef = 0; ef < EFFECT_MAX; ef++)
	{
		if (effect[ef].life > 0)
		{
			effect[ef].animCnt++;

			DrawGraph(effect[ef].pos.x - effect[ef].offsetSize.x + mapPos.x
				, effect[ef].pos.y - effect[ef].offsetSize.y + mapPos.y
				, effectImage[effect[ef].charType][effect[ef].animCnt]
				, true);
		}
	}
}

void DamageEffect(XY pos, MAGIC_TYPE type)
{
	for (int ef = 0; ef < EFFECT_MAX; ef++)
	{
		if (effect[ef].life <= 0)
		{
			effect[ef].charType = type;
			effect[ef].pos = pos;
			effect[ef].life = effect[ef].lifeMax;
		}
		break;
	}
}
