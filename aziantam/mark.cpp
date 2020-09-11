//mark.cpp
//2020.09.03
//山本美由紀

//stage移動するための印、その印に触れればstage移動ができる。

#include <DxLib.h>
#include <math.h>
#include "main.h"
#include "stage.h"
#include "mark.h"
#include "enemy.h"

MARK mark[STAGE_ID_MAX];
int markImage[STAGE_ID_MAX][20];

bool MarkSystemInit(void)
{
	for (int st = 0; st < STAGE_ID_MAX; st++)
	{
		mark[st].pos = {0,0};
		mark[st].size = { 40,40 };
		mark[st].aniCnt = 0;
		mark[st].flag = true;
	}


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

	return true;
}

bool MarkGameInit(void)
{
	for (int st = 0; st < STAGE_ID_MAX; st++)
	{
		if (GetMapDate() == STAGE_ID_START)
		{
		/*	int x = GetRand(MAP_X);
			int y = GetRand(MAP_Y);
			
			while (map[y][x] != 75)
			{
				x = GetRand(MAP_X);
				y = GetRand(MAP_Y);
			}
			mark[st].pos.x = x * CHIP_SIZE_X;
			mark[st].pos.y = y * CHIP_SIZE_Y;*/
			
			mark[STAGE_ID_MOB].pos = { 280,1200 };
			mark[STAGE_ID_KAPPA].pos = { 1120,1070 };
			mark[STAGE_ID_ONI].pos = { 920,120 };

			mark[st].flag = true;
			mark[STAGE_ID_START].flag = false;
		}
		else if ((GetMapDate() != STAGE_ID_START) &&(GetMapDate() != STAGE_ID_ONI2))
		{
			int x = rand() % MAP_X;
			int y = rand() % MAP_Y;

			if (GetMapDate() == STAGE_ID_MOB)
			{

				while (map[y][x] != 75)
				{
					x = rand() % MAP_X;
					y = rand() % MAP_Y;
				}
			}
			else if (GetMapDate() == STAGE_ID_KAPPA)
			{
				while (map[y][x] != 40)
				{
					x = rand() % MAP_X;
					y = rand() % MAP_Y;
				}
			}
			else if (GetMapDate() == STAGE_ID_ONI)
			{
				while (map[y][x] != 0)
				{
					x = rand() % MAP_X;
					y = rand() % MAP_Y;
				}
			}
			mark[STAGE_ID_START].pos.x = x * CHIP_SIZE_X;
			mark[STAGE_ID_START].pos.y = y * CHIP_SIZE_Y;

			
			mark[st].flag = false;
		//	mark[STAGE_ID_START].flag = true;
		}
		
		mark[st].aniCnt = 0;
		
	}
	return true;
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
		}
	}

}