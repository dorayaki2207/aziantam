#include "DxLib.h"
#include "main.h"
#include "stage.h"
#include "enemy.h"

//-----ŠO•”•Ï”éŒ¾
//ÓÌŞŠÖ˜A
CHARACTER enemyMob[ENEMY_MAX];
CHARACTER enemyMobMaster[ENEMY_M_MAX];
int enemyImage[ENEMY_M_MAX][16];


void EnemySystemInit(void)
{
	//-----•Ï”‚Ì‰Šú‰»
	//ŒÏ
	enemyMobMaster[ENEMY_I_MOB].charType = ENEMY_I_MOB;			//	´ÈĞ°‚Ìí—Ş	F	·ÂÈ
	enemyMobMaster[ENEMY_I_MOB].moveSpeed = 4;					//	·ÂÈ‚ÌˆÚ“®—Ê
	enemyMobMaster[ENEMY_I_MOB].lifeMax = 50;					//	·ÂÈ‚Ì‘Ì—ÍÅ‘å’l
	enemyMobMaster[ENEMY_I_MOB].point = 1;						//	·ÂÈ‚Ì“¾“_
	//ˆê”½–Ø–È
	enemyMobMaster[ENEMY_Y_MOB].charType = ENEMY_Y_MOB;			//	´ÈĞ°‚Ìí—Ş	F	ˆê”½–Ø–È
	enemyMobMaster[ENEMY_Y_MOB].moveSpeed = 4;					//	ˆê”½–Ø–È‚ÌˆÚ“®—Ê
	enemyMobMaster[ENEMY_Y_MOB].lifeMax = 50;					//	ˆê”½–Ø–È‚Ì‘Ì—ÍÅ‘å’l
	enemyMobMaster[ENEMY_Y_MOB].point = 1;						//	ˆê”½–Ø–È‚Ì“¾“_
	//ŠC–Vå
	enemyMobMaster[ENEMY_A_MOB].charType = ENEMY_A_MOB;			//	´ÈĞ°‚Ìí—Ş	F	ŠC–Vå						
	enemyMobMaster[ENEMY_A_MOB].moveSpeed = 4;					//	ŠC–Vå‚ÌˆÚ“®—Ê
	enemyMobMaster[ENEMY_A_MOB].lifeMax = 50;					//	ŠC–Vå‚Ì‘Ì—ÍÅ‘å’l
	enemyMobMaster[ENEMY_A_MOB].point = 1;						//	ŠC–Vå‚Ì“¾“_
	//ÓÌŞ‚Ü‚Æ‚ß‚Äˆ—
	for (int type = 0; type < ENEMY_M_MAX; type++)
	{
		enemyMobMaster[type].moveDir = DIR_DOWN;
		enemyMobMaster[type].pos = { 50,50 };
		enemyMobMaster[type].size = { 32,32 };					
		enemyMobMaster[type].offsetSize = { enemyMobMaster[type].size.x / 2
			, enemyMobMaster[type].size.y / 2 };
		enemyMobMaster[type].life = enemyMobMaster[type].lifeMax;
		enemyMobMaster[type].animCnt = 0;
	}

	//-----¸Ş×Ì¨¯¸‚Ì“o˜^
	//Î‹´’S“–MOB
	LoadDivGraph("char/—dŒÏ.png", 16, 4, 4
		, enemyMobMaster[ENEMY_I_MOB].size.x
		, enemyMobMaster[ENEMY_I_MOB].size.y
		, enemyImage[ENEMY_I_MOB]);
	//R–{’S“–MOB
	LoadDivGraph("char/wind_mob_enemy1.png", 16, 4, 4
		, enemyMobMaster[ENEMY_Y_MOB].size.x
		, enemyMobMaster[ENEMY_Y_MOB].size.y
		, enemyImage[ENEMY_Y_MOB]);
	//r–Ø’S“–MOB
	LoadDivGraph("char/umi0.png", 16, 4, 4
		, enemyMobMaster[ENEMY_A_MOB].size.x
		, enemyMobMaster[ENEMY_A_MOB].size.y
		, enemyImage[ENEMY_A_MOB]);

}

void EnemyGameInit(void)
{

	for (int ene = 0; ene < ENEMY_MAX; ene++)
	{
		enemyMob[ene] = enemyMobMaster[GetRand(ENEMY_M_MAX - 1)];
		enemyMob[ene].pos.x = GetRand(MAP_M_X * CHIP_SIZE_X - 1);
		enemyMob[ene].pos.y = GetRand(MAP_M_X * CHIP_SIZE_X - 1);
	}

}

void EnemyControl(XY pPos)
{
}

void EnemyGameDraw()
{

	for (int ene = 0; ene < ENEMY_MAX; ene++)
	{

		if (enemyMob[ene].life > 0)
		{
	
			DrawGraph(enemyMob[ene].pos.x - enemyMob[ene].offsetSize.x + mapPos.x
				, enemyMob[ene].pos.y - enemyMob[ene].offsetSize.y + mapPos.y
				, enemyImage[enemyMob[ene].charType][enemyMob[ene].moveDir * 4 + ((enemyMob[ene].animCnt / 40) % 4)]
				, true);

		//	DrawBox(enemyMob[ene].pos.x - enemyMob[ene].offsetSize.x - mapPos.x
		//		, enemyMob[ene].pos.y - enemyMob[ene].offsetSize.y - mapPos.y
		//		, enemyMob[ene].pos.x - enemyMob[ene].offsetSize.x + enemyMob[ene].size.x
		//		, enemyMob[ene].pos.y - enemyMob[ene].offsetSize.y + enemyMob[ene].size.y
		//		, 0xFF00FF, false);

		}
	}

}
