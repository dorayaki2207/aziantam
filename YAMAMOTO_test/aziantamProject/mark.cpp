//mark.cpp
//2020.09.03
//山本美由紀

//stage移動するための印、その印に触れればstage移動ができる。

#include <DxLib.h>
#include <math.h>
#include "main.h"
#include "stage.h"
#include "mark.h"


MARK markMag[STAGE_ID_MAX];
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
	mark[STAGE_ID_START].type = STAGE_ID_START;
	mark[STAGE_ID_MOB].type = STAGE_ID_MOB;
	mark[STAGE_ID_KAPPA].type = STAGE_ID_KAPPA;
	mark[STAGE_ID_ONI].type = STAGE_ID_ONI;


	//StartStage
	LoadDivGraph("char/start_stage.png", 20, 5, 4
		, mark[STAGE_ID_START].size.x
		, mark[STAGE_ID_START].size.y
		, markImage[STAGE_ID_START]);
	//MobStage
	LoadDivGraph("char/mob_stage.png", 20, 5, 4
		, mark[STAGE_ID_MOB].size.x
		, mark[STAGE_ID_MOB].size.y
		, markImage[STAGE_ID_MOB]);

	//OniStage
	LoadDivGraph("char/oni_stage.png", 20, 5, 4
		, mark[STAGE_ID_ONI].size.x
		, mark[STAGE_ID_ONI].size.y
		, markImage[STAGE_ID_ONI]);

	//KappaStage
	LoadDivGraph("char/kappa_stage.png", 20, 5, 4
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
			int x = GetRand(MAP_X);
			int y = GetRand(MAP_Y);
			
			while (map[y][x] != 75)
			{
				x = GetRand(MAP_X);
				y = GetRand(MAP_Y);
			}
			mark[st].pos.x = x * CHIP_SIZE_X;
			mark[st].pos.y = y * CHIP_SIZE_Y;
			
			mark[st].flag = true;
			mark[STAGE_ID_START].flag = false;
		}
		else if(GetMapDate() != STAGE_ID_START)
		{
			int x = rand() % MAP_X;
			int y = rand() % MAP_Y;

			if (GetMapDate() == STAGE_ID_MOB
				|| GetMapDate() == STAGE_ID_KAPPA)
			{
				while (map[y][x] != 75)
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
			mark[STAGE_ID_START].flag = true;
		}
		
		mark[st].aniCnt = 0;
		
	}
	return true;
}
void MarkGameControl(XY pos,int size)
{
	
	if (MarkHitCheck(pos, size))
	{
		if (mark[STAGE_ID_START].flag)
		{
			SetMapData(STAGE_ID_START);
			MarkGameInit();
		}
		else if (mark[STAGE_ID_MOB].flag)
		{
			SetMapData(STAGE_ID_MOB);
			MarkGameInit();
		}
		else if (mark[STAGE_ID_KAPPA].flag)
		{
			SetMapData(STAGE_ID_KAPPA);
			MarkGameInit();
		}
		else if (mark[STAGE_ID_ONI].flag)
		{
			SetMapData(STAGE_ID_ONI);
			MarkGameInit();
		}
	}
	
	
}

bool MarkHitCheck(XY pPos,int size)
{
	for (int m = 0; m < STAGE_ID_MAX; m++)
	{
		if (mark[m].flag)
		{
			if ((mark[m].pos.x - mark[m].size.x / 2) < (pPos.x + size / 2)
				&& (mark[m].pos.x + mark[m].size.x / 2) > (pPos.x - size / 2)
				&& (mark[m].pos.y - mark[m].size.y / 2) < (pPos.y + size / 2)
				&& (mark[m].pos.y + mark[m].size.y / 2) > (pPos.y - size / 2))
			{
				return true;
			}
		}
	}
	return false;
}

void MarkGameDraw(void)
{
	
	for (int m = 0; m < STAGE_ID_MAX; m++)
	{
		if (mark[m].flag)
		{
			mark[m].aniCnt++;
			DrawGraph(mark[m].pos.x + mapPos.x, mark[m].pos.y + mapPos.y, markImage[m][(mark[m].aniCnt % 40) / 5], true);
		}
	}

}