#include <DxLib.h>
#include "main.h"
#include "stage.h"
#include "enemy.h"
#include "item.h"
#include "effect.h"
#include "mark.h"


//-----外部変数宣言
//ﾓﾌﾞ関連
CHARACTER enemyMob[ENEMY_MAX];
CHARACTER enemyMobMaster[ENEMY_M_MAX];
int enemyImage[ENEMY_M_MAX][16];
int moveCnt;
int moveFlag;

//それぞれのステージにいる敵の生存確認（true:全滅、false:生存）
bool eFlag_mob;
bool eFlag_oni;
bool eFlag_kappa;



void EnemySystemInit(void)
{
	//-----変数の初期化
	//狐
	enemyMobMaster[ENEMY_I_MOB].charType = ENEMY_I_MOB;			//	ｴﾈﾐｰの種類	：	ｷﾂﾈ
	enemyMobMaster[ENEMY_I_MOB].moveSpeed = 2;					//	ｷﾂﾈの移動量
	enemyMobMaster[ENEMY_I_MOB].lifeMax = 3;					//	ｷﾂﾈの体力最大値
	enemyMobMaster[ENEMY_I_MOB].point = 1;						//	ｷﾂﾈの得点
	//一反木綿
	enemyMobMaster[ENEMY_Y_MOB].charType = ENEMY_Y_MOB;			//	ｴﾈﾐｰの種類	：	一反木綿
	enemyMobMaster[ENEMY_Y_MOB].moveSpeed = 3;					//	一反木綿の移動量
	enemyMobMaster[ENEMY_Y_MOB].lifeMax = 3;					//	一反木綿の体力最大値
	enemyMobMaster[ENEMY_Y_MOB].point = 1;						//	一反木綿の得点
	//海坊主
	enemyMobMaster[ENEMY_A_MOB].charType = ENEMY_A_MOB;			//	ｴﾈﾐｰの種類	：	海坊主						
	enemyMobMaster[ENEMY_A_MOB].moveSpeed = 1;					//	海坊主の移動量
	enemyMobMaster[ENEMY_A_MOB].lifeMax = 3;					//	海坊主の体力最大値
	enemyMobMaster[ENEMY_A_MOB].point = 1;						//	海坊主の得点
	//ﾓﾌﾞまとめて処理
	for (int type = 0; type < ENEMY_M_MAX; type++)
	{
		enemyMobMaster[type].moveDir = DIR_DOWN;
		enemyMobMaster[type].pos = { 50,50 };
		enemyMobMaster[type].size = { 32,32 };					
		enemyMobMaster[type].offsetSize = { enemyMobMaster[type].size.x / 2
			, enemyMobMaster[type].size.y / 2 };
		enemyMobMaster[type].life = enemyMobMaster[type].lifeMax;
		enemyMobMaster[type].animCnt = 0;
		enemyMobMaster[type].stageType = STAGE_ID_MOB;
	}

	moveCnt = 0;
	moveFlag = false;
	
	//-----ｸﾞﾗﾌｨｯｸの登録
	//石橋担当MOB
	LoadDivGraph("char/妖狐.png", 16, 4, 4
		, enemyMobMaster[ENEMY_I_MOB].size.x
		, enemyMobMaster[ENEMY_I_MOB].size.y
		, enemyImage[ENEMY_I_MOB]);
	//山本担当MOB
	LoadDivGraph("char/wind_mob_enemy1.png", 16, 4, 4
		, enemyMobMaster[ENEMY_Y_MOB].size.x
		, enemyMobMaster[ENEMY_Y_MOB].size.y
		, enemyImage[ENEMY_Y_MOB]);
	//荒木担当MOB
	LoadDivGraph("char/umi0.png", 16, 4, 4
		, enemyMobMaster[ENEMY_A_MOB].size.x
		, enemyMobMaster[ENEMY_A_MOB].size.y
		, enemyImage[ENEMY_A_MOB]);


	
}

void EnemyReGameInit()
{
	for (int ene = 0; ene < ENEMY_MAX; ene++)
	{
		int type = rand() % ENEMY_M_MAX;
		enemyMob[ene] = enemyMobMaster[type];

		if (ene >= 0 && ene < ENEMY_MAX / 3)
		{
			enemyMob[ene].stageType = STAGE_ID_MOB;
		}
		else if (ene >= ENEMY_MAX / 3 && ene < ENEMY_MAX - (ENEMY_MAX / 3))
		{
			enemyMob[ene].stageType = STAGE_ID_KAPPA;
		}
		else if (ene >= ENEMY_MAX - (ENEMY_MAX / 3) && ene < ENEMY_MAX)
		{
			enemyMob[ene].stageType = STAGE_ID_ONI;
		}

	}
}

void EnemyGameInit(STAGE_ID stageID)
{
	
	for (int ene = 0; ene < ENEMY_MAX; ene++)
	{

		int x = rand() % MAP_M_X;
		int y = rand() % MAP_M_Y;

		//stageIDがSTAGE_ID_STARTかSTAGE_ID_MOBだった場合
		if ((enemyMob[ene].stageType == STAGE_ID_MOB) && (stageID == STAGE_ID_MOB))
		{
			//75番以外のmap配列になったらrandをやりなおす。
			while (map[y][x] != 75)
			{
				x = rand() % MAP_M_X;
				y = rand() % MAP_M_Y;
			}
		}
		else if ((enemyMob[ene].stageType == STAGE_ID_KAPPA) && (stageID == STAGE_ID_KAPPA))
		{
			while (map[y][x] != 40)
			{
				x = rand() % MAPA_X;
				y = rand() % MAPA_Y;
			}
		}
		//stageIDがSTAGE_ID_ONIだった場合
		else if ((enemyMob[ene].stageType == STAGE_ID_ONI) && (stageID == STAGE_ID_ONI))
		{
			//0番以外のmap配列になったらrandをやりなおす。
			while (map[y][x] != 0)
			{
				x = rand() % MAPI_X;
				y = rand() % MAPI_Y;
			}
		}

		//enemyのposをrandで決めた場所とCHIP_SIZEで計算して配置位置を決める。
		enemyMob[ene].pos.x = x * CHIP_SIZE_X - 1;
		enemyMob[ene].pos.y = y * CHIP_SIZE_Y - 1;

		//上のままだと壁にめり込んだり画面外にはみ出したりするので、
		//enemyのposに18足して位置をずらす。
		enemyMob[ene].pos.x += 18;
		enemyMob[ene].pos.y += 18;
	}
}



//敵がステージごとで全滅したか判断用フラグ専用の初期化
bool EFlagInit(void)
{
	eFlag_mob = false;
	eFlag_oni = false;
	eFlag_kappa = false;
	return true;
}

void EnemyControl(XY pPos)
{
	moveCnt++;
	//敵の種類毎に動作を変更する
	for (int en = 0; en < ENEMY_MAX; en++)
	{
		if (stageID == enemyMob[en].stageType)
		{
			CHARACTER enemyCopy = enemyMob[en];
			XY enemyPosCopy = enemyCopy.pos;

			if ((moveCnt / 60) % 2 == 0) moveFlag = false;
			else moveFlag = true;

			//生きているｴﾈﾐｰのみ表示
			if (enemyMob[en].life > 0)
			{
				if (moveFlag)
				{
					switch (enemyMob[en].charType)
					{
					case ENEMY_I_MOB:
						if (!MoveEnemyX(&enemyCopy, pPos)) MoveEnemyY(&enemyCopy, pPos);
						break;

					case ENEMY_Y_MOB:
						if (!MoveEnemyY(&enemyCopy, pPos)) MoveEnemyX(&enemyCopy, pPos);
						break;

					case ENEMY_A_MOB:
						MoveEnemyXY(&enemyCopy, pPos);
						break;
					case ENEMY_M_MAX:
						break;
					default:
						break;
					}

					switch (enemyCopy.moveDir)
					{
					case DIR_RIGHT:
						enemyPosCopy.x = enemyCopy.pos.x + 18;
						break;
					case DIR_LEFT:
						enemyPosCopy.x = enemyCopy.pos.x - 18;
						break;
					case DIR_UP:
						enemyPosCopy.y = enemyCopy.pos.y - 18;
						break;
					case DIR_DOWN:
						enemyPosCopy.y = enemyCopy.pos.y + 18;
					}

					enemyMob[en].moveDir = enemyCopy.moveDir;

					if (IsPass(enemyPosCopy))
					{
						enemyMob[en].pos = enemyCopy.pos;
					}

					
				}
			}
		}
	}

}

//すべてのenemyを倒した時の処理（true:クリアシーンに遷移、false:まだ倒せてない）
bool SetEnemyMoment()
{
	bool Flag = true;

	//すべてのenemyの状態を取得
	for (int e = 0; e < ENEMY_MAX; e++)
	{
		if (enemyMob[e].stageType == stageID)
		{			//敵が死亡時、1体ずつにtrueを代入する

		//enemyのライフが0以下になって
			if (enemyMob[e].life <= 0)
			{
				//言い方を変えるとFlagが配列になっていて、1体死んだらtrueを返すような処理
				//Flag[0] = true;
				Flag &= true;
			}
			else
			{
				//敵が生存時、1体ずつにfalseを代入する
				Flag &= false;
			}
		}
	}

	//Flagがtrueになったら
		if (Flag)
		{
			//stageがモブのステージだったら
			if (GetMapDate() == STAGE_ID_MOB)
			{
				//trueにする
				eFlag_mob = true;
				mark[STAGE_ID_START].flag = true;
				
			}
			//stageが鬼のステージだったら
			else if (GetMapDate() == STAGE_ID_ONI)
			{
					//trueにする
				eFlag_oni = true;
				mark[STAGE_ID_START].flag = true;
			}
			else if (GetMapDate() == STAGE_ID_KAPPA)
			{
				//trueにする
				eFlag_kappa = true;
				mark[STAGE_ID_START].flag = true;
			}
		}
		//両方のステージで敵が全滅したら

		if (GetMapDate() == STAGE_ID_START)
		{
			if (eFlag_mob && eFlag_oni && eFlag_kappa)
			{
				
				return true;
			}
		}

	return false;
}


void EnemyGameDraw()
{
	//-----描画処理
	for (int ene = 0; ene < ENEMY_MAX; ene++)
	{
		if (stageID == enemyMob[ene].stageType)
		{
		
			if (enemyMob[ene].life > 0)
			{
				enemyMob[ene].animCnt++;

				DrawGraph(enemyMob[ene].pos.x - enemyMob[ene].offsetSize.x + mapPos.x
					, enemyMob[ene].pos.y - enemyMob[ene].offsetSize.y + mapPos.y
					, enemyImage[enemyMob[ene].charType][enemyMob[ene].moveDir * 4 + ((enemyMob[ene].animCnt / 40) % 4)]
					, true);
			}
			//DrawFormatString(0, 200, 0xFFFFFF,"enemyHP:%d", enemyMob[ene].life, true);
		}
	}
}

int MoveEnemyX(CHARACTER* enemy, XY playerPos)
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

int MoveEnemyY(CHARACTER* enemy, XY playerPos)
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

int MoveEnemyXY(CHARACTER* enemy, XY playerPos)
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

//-----ｴﾈﾐｰと弾の当たり判定　(true : あたり, false : はずれ)
bool EnemyHitCheck(XY sPos, int sSize, CHARACTER *shot)
{
	auto randam = rand() % 100;
	//全ての敵に当たり判定を実施する
	for (int en = 0; en < ENEMY_MAX; en++)
	{
		if (stageID == enemyMob[en].stageType)
		{
			if (enemyMob[en].life > 0)
			{
				if (((enemyMob[en].pos.x - enemyMob[en].size.x / 2) < (sPos.x + sSize / 2))
					&& ((enemyMob[en].pos.x + enemyMob[en].size.x / 2) > (sPos.x - sSize / 2))
					&& ((enemyMob[en].pos.y - enemyMob[en].size.y / 2) < (sPos.y + sSize / 2))
					&& ((enemyMob[en].pos.y + enemyMob[en].size.y / 2) > (sPos.y - sSize / 2)))
				{
					//当たった時、ｴﾈﾐｰの体力を減らす
					switch (enemyMob[en].charType)
					{
					case ENEMY_I_MOB:
						if ((*shot).charType == MAGIC_TYPE_FIRE) enemyMob[en].life -= DAMAGE_NORMAL;
						if ((*shot).charType == MAGIC_TYPE_WATER) enemyMob[en].life -= DAMAGE_LOW;
						if ((*shot).charType == MAGIC_TYPE_WIND) enemyMob[en].life -= DAMAGE_HIGH;

						DamageEffect(enemyMob[en].pos, MAGIC_TYPE_FIRE);

						if (enemyMob[en].life <= 0)
						{
							if (randam > 5)
							{
								ItemDrop(enemyMob[en].pos, MAGIC_TYPE_FIRE);
								break;
							}
							else if (randam <= 5)
							{
								ItemDrop(enemyMob[en].pos, MAGIC_TYPE_HEAL);
								break;
							}
						}
						break;

					case ENEMY_A_MOB:
						if ((*shot).charType == MAGIC_TYPE_FIRE) enemyMob[en].life -= DAMAGE_HIGH;
						if ((*shot).charType == MAGIC_TYPE_WATER) enemyMob[en].life -= DAMAGE_NORMAL;
						if ((*shot).charType == MAGIC_TYPE_WIND) enemyMob[en].life -= DAMAGE_LOW;

						DamageEffect(enemyMob[en].pos, MAGIC_TYPE_WATER);

						if (enemyMob[en].life <= 0)
						{
							if (randam > 5)
							{
								ItemDrop(enemyMob[en].pos, MAGIC_TYPE_WATER);
								break;
							}
							else if (randam <= 5)
							{
								ItemDrop(enemyMob[en].pos, MAGIC_TYPE_HEAL);
								break;
							}
						}
						break;

					case ENEMY_Y_MOB:
						if ((*shot).charType == MAGIC_TYPE_FIRE) enemyMob[en].life -= DAMAGE_LOW;
						if ((*shot).charType == MAGIC_TYPE_WATER) enemyMob[en].life -= DAMAGE_HIGH;
						if ((*shot).charType == MAGIC_TYPE_WIND) enemyMob[en].life -= DAMAGE_NORMAL;

						DamageEffect(enemyMob[en].pos, MAGIC_TYPE_WIND);

						if (enemyMob[en].life <= 0)
						{
							if (randam > 5)
							{
								ItemDrop(enemyMob[en].pos, MAGIC_TYPE_WIND);
								break;
							}
							else if (randam <= 5)
							{
								ItemDrop(enemyMob[en].pos, MAGIC_TYPE_HEAL);
								break;
							}
						}
						break;

					case ENEMY_M_MAX:
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


//当たり判定
bool PlayerHitCheck(XY sPos, int sSize)
{
	//全ての敵に当たり判定を実施する
	for (int en = 0; en < ENEMY_MAX; en++)
	{
		if (stageID == enemyMob[en].stageType)
		{
			if (enemyMob[en].life > 0)
			{
				if (((enemyMob[en].pos.x - enemyMob[en].size.x / 2) < (sPos.x + sSize / 2))
					&& ((enemyMob[en].pos.x + enemyMob[en].size.x / 2) > (sPos.x - sSize / 2))
					&& ((enemyMob[en].pos.y - enemyMob[en].size.y / 2) < (sPos.y + sSize / 2))
					&& ((enemyMob[en].pos.y + enemyMob[en].size.y / 2) > (sPos.y - sSize / 2)))
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

