//mark.cpp
//2020.09.03
//山本美由紀

//stage移動するための印、その印に触れればstage移動ができる。

#include <DxLib.h>
#include <math.h>
#include <cmath>
#include "main.h"
#include "stage.h"
#include "mark.h"
#include "enemy.h"

MARK mark[STAGE_ID_MAX];
MARK markClear[STAGE_ID_MAX];
MARK zingi[ITEM_TYPE_B_MAX];

int markImage[STAGE_ID_MAX][20];
int markClearImage[STAGE_ID_MAX][10];
int zingiImage[2][ITEM_TYPE_B_MAX];
int clearHitFlag;
int frame;

bool MarkSystemInit(void)
{
	//移動用オブジェクト
	for (int st = 0; st < STAGE_ID_MAX; st++)
	{
		mark[st].pos = { 0,0 };
		mark[st].size = { 40,40 };
		mark[st].aniCnt = 0;
		mark[st].flag = true;

		markClear[st].pos = { 0,0 };
		markClear[st].size = { 80,80 };
		markClear[st].aniCnt = 0;
		markClear[st].flag = false;
	//	markClear[STAGE_ID_START].flag = false;
	}
	markClear[STAGE_ID_MOB].type = STAGE_ID_MOB;
	markClear[STAGE_ID_KAPPA].type = STAGE_ID_KAPPA;
	markClear[STAGE_ID_ONI].type = STAGE_ID_ONI;

	//StartStage
	LoadDivGraph("item/stageGate/start_stage.png", 20, 5, 4
		, mark[STAGE_ID_START].size.x
		, mark[STAGE_ID_START].size.y
		, markImage[STAGE_ID_START]);
	//MobStage
	LoadDivGraph("item/stageGate/tengu_stage.png", 20, 5, 4
		, mark[STAGE_ID_MOB].size.x
		, mark[STAGE_ID_MOB].size.y
		, markImage[STAGE_ID_MOB]);

	//OniStage
	LoadDivGraph("item/stageGate/oni_stage.png", 20, 5, 4
		, mark[STAGE_ID_ONI].size.x
		, mark[STAGE_ID_ONI].size.y
		, markImage[STAGE_ID_ONI]);

	//KappaStage
	LoadDivGraph("item/stageGate/kappa_stage.png", 20, 5, 4
		, mark[STAGE_ID_KAPPA].size.x
		, mark[STAGE_ID_KAPPA].size.y
		, markImage[STAGE_ID_KAPPA]);

	//ClearEffect
	for (int s = 0; s < STAGE_ID_MAX; s++)
	{
		LoadDivGraph("item/stageGate/Effect_Clear.png", 10, 5, 2
			, markClear[s].size.x, markClear[s].size.y, markClearImage[s]);
	}


	//神器
	zingi[ITEM_TYPE_KEN].type = ITEM_TYPE_KEN;
	zingi[ITEM_TYPE_KEN].pos = { 550, 510 };
	zingi[ITEM_TYPE_KAGAMI].type = ITEM_TYPE_KAGAMI;
	zingi[ITEM_TYPE_KAGAMI].pos = { 600, 510 };
	zingi[ITEM_TYPE_MAGATAMA].type = ITEM_TYPE_MAGATAMA;
	zingi[ITEM_TYPE_MAGATAMA].pos = { 650, 510 };
	for (int type = 0; type < ITEM_TYPE_B_MAX; type++)
	{
		zingi[type].size = { 50,50 };
		zingi[type].aniCnt = 0;
		zingi[type].flag = false;
	}

	LoadDivGraph("item/zingi_low.png", 3, 3, 1
		, zingi[ITEM_TYPE_KEN].size.x
		, zingi[ITEM_TYPE_KEN].size.y
		, zingiImage[ZINGI_OLD]);
	LoadDivGraph("item/zingi.png", 3, 3, 1
		, zingi[ITEM_TYPE_KEN].size.x
		, zingi[ITEM_TYPE_KEN].size.y
		, zingiImage[ZINGI_NEW]);

	clearHitFlag = false;
	frame = 0;

	return true;
}

void MarkReGameInit()
{
	for (int st = 0; st < STAGE_ID_MAX; st++)
	{
		mark[st].aniCnt = 0;
		mark[st].flag = true;

		markClear[st].aniCnt = 0;
		markClear[st].flag = false;
		//	markClear[STAGE_ID_START].flag = false;
	}
	for (int type = 0; type < ITEM_TYPE_B_MAX; type++)
	{
		zingi[type].aniCnt = 0;
		zingi[type].flag = false;
	}
	clearHitFlag = false;
	frame = 0;
}

bool MarkGameInit(void)
{
	for (int st = 0; st < STAGE_ID_MAX; st++)
	{
		if (GetMapDate() == STAGE_ID_START)
		{

			mark[STAGE_ID_MOB].pos = { 283,1200 };
			mark[STAGE_ID_KAPPA].pos = { 1120,1070 };
			mark[STAGE_ID_ONI].pos = { 923,120 };

			mark[st].flag = true;
			mark[STAGE_ID_START].flag = false;
		}
		else if ((GetMapDate() != STAGE_ID_START) &&(GetMapDate() != STAGE_ID_ONI2))
		{
			int x = rand() % MAP_X;
			int y = rand() % MAP_Y;


			if ((GetMapDate() == STAGE_ID_MOB))
			{

				while (map[y][x] != 75)
				{
					x = rand() % MAP_M_X;
					y = rand() % MAP_M_Y;
				}
			}
			else if ((GetMapDate() == STAGE_ID_KAPPA))
			{
				while (map[y][x] != 40)
				{
					x = rand() % MAPA_X;
					y = rand() % MAPA_Y;
				}
			}
			else if ((GetMapDate() == STAGE_ID_ONI))
			{
				while (map[y][x] != 0)
				{
					x = rand() % MAPI_X;
 					y = rand() % MAPI_Y;
				}
			}
			mark[STAGE_ID_START].pos.x = x * CHIP_SIZE_X;
			mark[STAGE_ID_START].pos.y = y * CHIP_SIZE_Y;

			mark[st].flag = false;
			
		}
		
		mark[st].aniCnt = 0;
		
	}

	for (int type = 0; type < ITEM_TYPE_B_MAX; type++)
	{
		zingi[type].aniCnt = 0;
		zingi[type].flag = false;
	}

	return true;
}


void MarkControl()
{
	frame++;
	for (int stage = 0; stage < STAGE_ID_MAX; stage++)
	{
		if (GetMapDate() == STAGE_ID_START)
		{
			if ((eFlag_mob) && (markClear[stage].type == STAGE_ID_MOB))
			{
				markClear[STAGE_ID_MOB].pos = { 283,1200 };

				markClear[STAGE_ID_MOB].flag = true;
				zingi[ITEM_TYPE_MAGATAMA].flag = true;
			}
			if ((eFlag_oni) && (markClear[stage].type == STAGE_ID_ONI))
			{
				markClear[STAGE_ID_ONI].pos = { 923,120 };

				markClear[STAGE_ID_ONI].flag = true;
				zingi[ITEM_TYPE_KEN].flag = true;

			}
			if ((eFlag_kappa) && (markClear[stage].type == STAGE_ID_KAPPA))
			{
				markClear[STAGE_ID_KAPPA].pos = { 1120,1070 };

				markClear[STAGE_ID_KAPPA].flag = true;
				zingi[ITEM_TYPE_KAGAMI].flag = true;
			}
		}
		else if ((GetMapDate() != STAGE_ID_START) && (GetMapDate() != STAGE_ID_ONI2))
		{
			markClear[stage].flag = false;
		}
	}

		if (zingi[ITEM_TYPE_KEN].flag && zingi[ITEM_TYPE_KAGAMI].flag && zingi[ITEM_TYPE_MAGATAMA].flag)
		{
			clearHitFlag = true;
		}
}

bool MarkHitCheck(STAGE_ID Id,XY pPos,XY size)
{
	if (mark[Id].flag)
	{
		if ((mark[Id].pos.x - mark[Id].size.x / 2) < (pPos.x + size.x / 2)
			&& (mark[Id].pos.x + mark[Id].size.x / 2) > (pPos.x - size.x / 2)
			&& (mark[Id].pos.y - mark[Id].size.y / 2) < (pPos.y + size.y / 2)
			&& (mark[Id].pos.y + mark[Id].size.y / 2) > (pPos.y - size.y / 2))
		{
			return true;
		}
	}
	return false;
}

void MarkGameDraw(void)
{
	for (int m = 0; m < STAGE_ID_MAX; m++)
	{
		if (GetMapDate() != STAGE_ID_ONI2)
		{
			if (mark[m].flag)
			{
				mark[m].aniCnt++;
				DrawGraph(mark[m].pos.x + mapPos.x, mark[m].pos.y + mapPos.y, markImage[m][(mark[m].aniCnt % 40) / 5], true);
			}
			if (markClear[m].flag)
			{
				markClear[m].aniCnt++;
				DrawGraph(markClear[m].pos.x - 20 + mapPos.x, markClear[m].pos.y - 20 + mapPos.y, markClearImage[m][(markClear[m].aniCnt % 20) / 3], true);
			}
		}
	}


	int itemStatus;
	int itemImage;
	
	for (int i = 0; i < ITEM_TYPE_B_MAX; i++)
	{
		if (stageID == STAGE_ID_START)
		{
			itemStatus = (zingi[i].flag) ? ZINGI_NEW : ZINGI_OLD;
			itemImage = zingiImage[itemStatus][i];

			DrawGraph(zingi[i].pos.x + mapPos.x
				, zingi[i].pos.y + mapPos.y
				, itemImage, true);


			zingi[i].aniCnt++;
			if (clearHitFlag)
			{
				if ((zingi[i].aniCnt / 30) % 2 == 0)
				{
					DrawBox(CLEAR_MINI_X + mapPos.x
						, CLEAR_MINI_Y + mapPos.y
						, CLEAR_MAX_X + mapPos.x
						, CLEAR_MAX_Y + mapPos.y
						, 0xffff22, true);
				}
			}
		}

		if (stageID == STAGE_ID_START)
		{
			
			zingi[i].aniCnt++;
			if (clearHitFlag)
			{
				if ((zingi[i].aniCnt / 30) % 2 == 0)
				{
					DrawBox(CLEAR_MINI_X + mapPos.x
						, CLEAR_MINI_Y + mapPos.y
						, CLEAR_MAX_X + mapPos.x
						, CLEAR_MAX_Y + mapPos.y
						, 0xffff22, true);
				}
			}
		}
	}

	
}