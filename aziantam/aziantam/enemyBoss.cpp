#include <DxLib.h>
#include "main.h"
#include "stage.h"
#include "enemyBoss.h"
#include "enemy.h"
#include "item.h"
#include "effect.h"


CHARACTER eBoss[ENEMY_B_MAX];
int eBossImage[ENEMY_B_MAX][16];
int eMoveCnt;
bool eMoveFlag;
bool drawFlag[ENEMY_B_MAX];

void EnemyBossSystemInit(void)
{
	//-----変数の初期化
	//鬼
	eBoss[ENEMY_ONI].charType = ENEMY_ONI;			
	eBoss[ENEMY_ONI].stageType = STAGE_ID_ONI;
	//天狗
	eBoss[ENEMY_TENG].charType = ENEMY_TENG;		
	eBoss[ENEMY_TENG].stageType = STAGE_ID_MOB;
	//河童
	eBoss[ENEMY_KAPPA].charType = ENEMY_KAPPA;		
	eBoss[ENEMY_KAPPA].stageType = STAGE_ID_KAPPA;
	
	//ﾓﾌﾞまとめて処理
	for (int type = 0; type < ENEMY_B_MAX; type++)
	{
		eBoss[type].moveSpeed = 2;					
		eBoss[type].lifeMax = 12;					
		eBoss[type].moveDir = DIR_DOWN;
		eBoss[type].pos = { 0,0 };
		eBoss[type].size = { 32,32 };
		eBoss[type].offsetSize = { eBoss[type].size.x / 2
			, eBoss[type].size.y / 2 };
		eBoss[type].life = eBoss[type].lifeMax;
		eBoss[type].animCnt = 0;
		drawFlag[type] = false;
	}

	eMoveCnt = 0;
	eMoveFlag = false;

	//-----ｸﾞﾗﾌｨｯｸの登録
	//石橋担当MOB
	LoadDivGraph("char/boss.png", 16, 4, 4
		, eBoss[ENEMY_ONI].size.x
		, eBoss[ENEMY_ONI].size.y
		, eBossImage[ENEMY_ONI]);
	//山本担当MOB
	LoadDivGraph("char/wind_boss.png", 16, 4, 4
		, eBoss[ENEMY_TENG].size.x
		, eBoss[ENEMY_TENG].size.y
		, eBossImage[ENEMY_TENG]);
	//荒木担当MOB
	LoadDivGraph("char/KAPPA_00.png", 16, 4, 4
		, eBoss[ENEMY_KAPPA].size.x
		, eBoss[ENEMY_KAPPA].size.y
		, eBossImage[ENEMY_KAPPA]);

}

void EnemyBossGameInit(STAGE_ID stageID)
{
	for (int ene = 0; ene < ENEMY_B_MAX; ene++)
	{
		int x = rand() % MAP_M_X;
		int y = rand() % MAP_M_Y;

		if ((eBoss[ene].stageType == STAGE_ID_MOB) && (stageID == STAGE_ID_MOB))
		{
			//75番以外のmap配列になったらrandをやりなおす。
			while (map[y][x] != 75)
			{
				x = rand() % MAP_M_X;
				y = rand() % MAP_M_Y;
			}
		}
		else if ((eBoss[ene].stageType == STAGE_ID_KAPPA) && (stageID == STAGE_ID_KAPPA))
		{
			while (map[y][x] != 40)
			{
				x = rand() % MAPA_X;
				y = rand() % MAPA_Y;
			}
		}
		//stageIDがSTAGE_ID_ONIだった場合
		else if ((eBoss[ene].stageType == STAGE_ID_ONI) && (stageID == STAGE_ID_ONI))
		{
			//0番以外のmap配列になったらrandをやりなおす。
			while (map[y][x] != 0)
			{
				x = rand() % MAPI_X;
				y = rand() % MAPI_Y;
			}
		}

		//enemyのposをrandで決めた場所とCHIP_SIZEで計算して配置位置を決める。
		eBoss[ene].pos.x = x * CHIP_SIZE_X - 1;
		eBoss[ene].pos.y = y * CHIP_SIZE_Y - 1;

		//上のままだと壁にめり込んだり画面外にはみ出したりするので、
		//enemyのposに18足して位置をずらす。
		eBoss[ene].pos.x += 18;
		eBoss[ene].pos.y += 18;
	}
}

void EnemyBossControl(XY pPos)
{
	eMoveCnt++;
	//敵の種類毎に動作を変更する
	for (int en = 0; en < ENEMY_B_MAX; en++)
	{
		
		if (eBoss[en].stageType == stageID)
		{
			CHARACTER eBossCopy = eBoss[en];
			XY eBossPosCopy = eBossCopy.pos;

			if ((eMoveCnt / 60) % 20 == 0) eMoveFlag = false;
			else eMoveFlag = true;

			//生きているｴﾈﾐｰのみ表示
			if (eBoss[en].life > 0)
			{
				if (eMoveFlag)
				{
					MoveBossXY(&eBossCopy, pPos);

					switch (eBossCopy.moveDir)
					{
					case DIR_RIGHT:
						eBossPosCopy.x = eBossCopy.pos.x + 18;
						break;
					case DIR_LEFT:
						eBossPosCopy.x = eBossCopy.pos.x - 18;
						break;
					case DIR_UP:
						eBossPosCopy.y = eBossCopy.pos.y - 18;
						break;
					case DIR_DOWN:
						eBossPosCopy.y = eBossCopy.pos.y + 18;
					}

					eBoss[en].moveDir = eBossCopy.moveDir;

					if (IsPass(eBossPosCopy))
					{
						eBoss[en].pos = eBossCopy.pos;
					}
				}
			}
		}
	}
}

int MoveBossX(CHARACTER* enemy, XY playerPos)
{
	//-----enemy操作
	int diff = playerPos.x - (*enemy).pos.x;
	int enemySpeed = (*enemy).moveSpeed;
	//X軸
	if (diff >= 0)
	{
		//ｽﾋﾟｰﾄﾞの調整をする
		enemySpeed = diff < enemySpeed ? diff : enemySpeed;

		//X座標が違う場合は敵を移動させる
		(*enemy).moveDir = DIR_RIGHT;
		(*enemy).pos.x += enemySpeed;
	}
	else
	{
		enemySpeed = -diff < enemySpeed ? -diff : enemySpeed;

		(*enemy).moveDir = DIR_LEFT;
		(*enemy).pos.x -= enemySpeed;
	}


	return enemySpeed;
}

int MoveBossY(CHARACTER* enemy, XY playerPos)
{
	//-----enemy操作
	int diff = playerPos.y - (*enemy).pos.y;
	int enemySpeed = (*enemy).moveSpeed;
	//Y軸
	if (diff >= 0)
	{
		//ｽﾋﾟｰﾄﾞの調整をする
		enemySpeed = diff < enemySpeed ? diff : enemySpeed;

		//Y座標が違う場合は敵を移動させる
		(*enemy).moveDir = DIR_DOWN;
		(*enemy).pos.y += enemySpeed;
	}
	else
	{
		enemySpeed = -diff < enemySpeed ? -diff : enemySpeed;
		//Y座標が違う場合は敵を移動させる
		(*enemy).moveDir = DIR_UP;
		(*enemy).pos.y -= enemySpeed;
	}

	return enemySpeed;

}

int MoveBossXY(CHARACTER* enemy, XY playerPos)
{
	int diffX = playerPos.x - (*enemy).pos.x;
	int diffY = playerPos.y - (*enemy).pos.y;
	int enemySpeed = (*enemy).moveSpeed;

	if (abs(diffX) <= abs(diffY))
	{
		//ｽﾋﾟｰﾄﾞの調整をする
		enemySpeed = MoveEnemyY(enemy, playerPos);
	}
	else
	{
		enemySpeed = MoveEnemyX(enemy, playerPos);
	}

	return enemySpeed;

}
void EnemyBossGameDraw(void)
{
	//-----描画処理
	for (int ene = 0; ene < ENEMY_B_MAX; ene++)
	{
		if (stageID == eBoss[ene].stageType)
		{
			if (eBoss[ene].life > 0)
			{
				eBoss[ene].animCnt++;


				DrawGraph(eBoss[ene].pos.x - eBoss[ene].offsetSize.x + mapPos.x
					, eBoss[ene].pos.y - eBoss[ene].offsetSize.y + mapPos.y
					, eBossImage[eBoss[ene].charType][eBoss[ene].moveDir * 4 + ((eBoss[ene].animCnt / 40) % 4)]
					, true);

			}
			DrawFormatString(0, 200, 0xFFFFFF,"鬼HP:%d", eBoss[ENEMY_ONI].life, true);
			DrawFormatString(0, 220, 0xFFFFFF, "天狗HP:%d", eBoss[ENEMY_TENG].life, true);
			DrawFormatString(0, 240, 0xFFFFFF, "河童HP:%d", eBoss[ENEMY_KAPPA].life, true);
		}
	}

}

bool EnemyBossHitCheck(XY sPos, int sSize, CHARACTER* shot)
{
	//全ての敵に当たり判定を実施する
	for (int en = 0; en < ENEMY_B_MAX; en++)
	{
		if(stageID == eBoss[en].stageType)
		{
			if (eBoss[en].life > 0)
			{
				if (((eBoss[en].pos.x - eBoss[en].size.x / 2) < (sPos.x + sSize / 2))
					&& ((eBoss[en].pos.x + eBoss[en].size.x / 2) > (sPos.x - sSize / 2))
					&& ((eBoss[en].pos.y - eBoss[en].size.y / 2) < (sPos.y + sSize / 2))
					&& ((eBoss[en].pos.y + eBoss[en].size.y / 2) > (sPos.y - sSize / 2)))
				{
					//当たった時、ｴﾈﾐｰの体力を減らす
					switch (eBoss[en].charType)
					{
					case ENEMY_ONI:
						if ((*shot).charType == MAGIC_TYPE_FIRE) eBoss[en].life -= DAMAGE_NORMAL;
						if ((*shot).charType == MAGIC_TYPE_WATER) eBoss[en].life -= DAMAGE_LOW;
						if ((*shot).charType == MAGIC_TYPE_WIND) eBoss[en].life -= DAMAGE_HIGH;

						DamageEffect(eBoss[en].pos, MAGIC_TYPE_FIRE);

						break;
					case ENEMY_KAPPA:
						if ((*shot).charType == MAGIC_TYPE_FIRE) eBoss[en].life -= DAMAGE_HIGH;
						if ((*shot).charType == MAGIC_TYPE_WATER) eBoss[en].life -= DAMAGE_NORMAL;
						if ((*shot).charType == MAGIC_TYPE_WIND) eBoss[en].life -= DAMAGE_LOW;

						DamageEffect(eBoss[en].pos, MAGIC_TYPE_WATER);

						break;

					case ENEMY_TENG:
						if ((*shot).charType == MAGIC_TYPE_FIRE) eBoss[en].life -= DAMAGE_LOW;
						if ((*shot).charType == MAGIC_TYPE_WATER) eBoss[en].life -= DAMAGE_HIGH;
						if ((*shot).charType == MAGIC_TYPE_WIND) eBoss[en].life -= DAMAGE_NORMAL;

						DamageEffect(eBoss[en].pos, MAGIC_TYPE_WIND);

						break;

					case ENEMY_B_MAX:
						break;
					default:
						break;
					}

					return true;
				}
			}
		}
	}
	//弾が外れた時
	return false;
}

bool Player_BHitCheck(XY sPos, int sSize)
{
	//全ての敵に当たり判定を実施する
	for (int en = 0; en < ENEMY_B_MAX; en++)
	{
		if (stageID == eBoss[en].stageType) 
		{
			if (eBoss[en].life > 0)
			{
				if (((eBoss[en].pos.x - eBoss[en].size.x / 2) < (sPos.x + sSize / 2))
					&& ((eBoss[en].pos.x + eBoss[en].size.x / 2) > (sPos.x - sSize / 2))
					&& ((eBoss[en].pos.y - eBoss[en].size.y / 2) < (sPos.y + sSize / 2))
					&& ((eBoss[en].pos.y + eBoss[en].size.y / 2) > (sPos.y - sSize / 2)))
				{
					//当たった
					return true;
				}
			}
		}
	}
	//外れた時
	return false;
}
