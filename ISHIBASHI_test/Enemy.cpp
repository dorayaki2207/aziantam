#include "DxLib.h"
#include "test.h"
#include "Stage.h"
#include "Enemy.h"
#include "Item.h"

//-----ŠO•”•Ï”éŒ¾
//ÓÌŞŠÖ˜A
CHARACTER enemyMob[ENEMY_MAX];				
CHARACTER enemyMobMaster[ENEMY_M_MAX];
int enemyImage[ENEMY_M_MAX][16];

//ÎŞ½ŠÖ˜A

//-----´ÈĞ°î•ñ‚Ì‰Šú‰»
void EnemySystemInit(void)
{
	//-----•Ï”‚Ì‰Šú‰»

	//ŒÏ
	enemyMobMaster[ENEMY_I_MOB].charType = ENEMY_I_MOB;			//	´ÈĞ°‚Ìí—Ş	F	·ÂÈ
	enemyMobMaster[ENEMY_I_MOB].moveSpeed = 2;					//	·ÂÈ‚ÌˆÚ“®—Ê
	enemyMobMaster[ENEMY_I_MOB].lifeMax = 3;					//	·ÂÈ‚Ì‘Ì—ÍÅ‘å’l
	enemyMobMaster[ENEMY_I_MOB].point = 1;						//	·ÂÈ‚Ì“¾“_
	//ˆê”½–Ø–È
	enemyMobMaster[ENEMY_Y_MOB].charType = ENEMY_Y_MOB;			//	´ÈĞ°‚Ìí—Ş	F	ˆê”½–Ø–È
	enemyMobMaster[ENEMY_Y_MOB].moveSpeed = 2;					//	ˆê”½–Ø–È‚ÌˆÚ“®—Ê
	enemyMobMaster[ENEMY_Y_MOB].lifeMax = 3;					//	ˆê”½–Ø–È‚Ì‘Ì—ÍÅ‘å’l
	enemyMobMaster[ENEMY_Y_MOB].point = 1;						//	ˆê”½–Ø–È‚Ì“¾“_
	//ŠC–Vå
	enemyMobMaster[ENEMY_A_MOB].charType = ENEMY_A_MOB;			//	´ÈĞ°‚Ìí—Ş	F	ŠC–Vå						
	enemyMobMaster[ENEMY_A_MOB].moveSpeed = 2;					//	ŠC–Vå‚ÌˆÚ“®—Ê
	enemyMobMaster[ENEMY_A_MOB].lifeMax = 3;					//	ŠC–Vå‚Ì‘Ì—ÍÅ‘å’l
	enemyMobMaster[ENEMY_A_MOB].point = 1;						//	ŠC–Vå‚Ì“¾“_
	//ÓÌŞ‚Ü‚Æ‚ß‚Äˆ—
	for (int type = 0; type < ENEMY_M_MAX; type++)
	{
		enemyMobMaster[type].moveDir = DIR_DOWN;
		enemyMobMaster[type].pos = { 150,150 };
		enemyMobMaster[type].size = { 32,32 };
		enemyMobMaster[type].offsetSize = { enemyMobMaster[type].size.x / 2
			, enemyMobMaster[type].size.y / 2 };
		enemyMobMaster[type].life = enemyMobMaster[type].lifeMax;
		enemyMobMaster[type].animCnt = 0;
	}

	//-----¸Ş×Ì¨¯¸‚Ì“o˜^
	//Î‹´’S“–MOB
	LoadDivGraph("aitem/—dŒÏ.png", 16, 4, 4
		, enemyMobMaster[ENEMY_I_MOB].size.x
		, enemyMobMaster[ENEMY_I_MOB].size.y
		, enemyImage[ENEMY_I_MOB]);
	//R–{’S“–MOB
	LoadDivGraph("aitem/wind_mob_enemy1.png", 16, 4, 4
		, enemyMobMaster[ENEMY_Y_MOB].size.x
		, enemyMobMaster[ENEMY_Y_MOB].size.y
		, enemyImage[ENEMY_Y_MOB]);
	//r–Ø’S“–MOB
	LoadDivGraph("aitem/umi0.png", 16, 4, 4
		, enemyMobMaster[ENEMY_A_MOB].size.x
		, enemyMobMaster[ENEMY_A_MOB].size.y
		, enemyImage[ENEMY_A_MOB]);

}

void EnemyGameInit(void)
{
	for (int ene = 0; ene < ENEMY_MAX; ene++)
	{
		enemyMob[ene] = enemyMobMaster[GetRand(ENEMY_M_MAX - 1)];
		if (IsPass(enemyMob[ene].pos))
		{
			enemyMob[ene].pos.x = GetRand(20 * CHIP_SIZE_X - 1);
			enemyMob[ene].pos.y = GetRand(25 * CHIP_SIZE_X - 1);
		}
	}
}

void EnemyControl(XY pPos)
{
	//“G‚Ìí—Ş–ˆ‚É“®ì‚ğ•ÏX‚·‚é
	for (int en = 0; en < ENEMY_MAX; en++)
	{
		CHARACTER enemyCopy = enemyMob[en];

		//¶‚«‚Ä‚¢‚é´ÈĞ°‚Ì‚İ•\¦
		if (enemyMob[en].life > 0)
		{
			/*switch (enemyMob[en].charType)
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

			default:
				break;
			}*/

			enemyMob[en].moveDir = enemyCopy.moveDir;
			if (IsPass(enemyCopy.pos))
			{
				enemyMob[en].pos = enemyCopy.pos;
			}
			//€‚ñ‚Å‚¢‚éˆ×A“G‚ğ¶¬
			else
			{
				enemyMob[en].life = enemyMob[en].lifeMax;
				enemyMob[en].pos = { 50,50 };
			}

		}
	}

}

void EnemyGameDraw(void)
{
	for (int ene = 0; ene < ENEMY_MAX; ene++)
	{

		if (enemyMob[ene].life > 0)
		{
			enemyMob[ene].animCnt++;

			DrawGraph(enemyMob[ene].pos.x - enemyMob[ene].offsetSize.x + mapPos.x
				, enemyMob[ene].pos.y - enemyMob[ene].offsetSize.y + mapPos.y
				, enemyImage[enemyMob[ene].charType][enemyMob[ene].moveDir * 4 + ((enemyMob[ene].animCnt / 40) % 4)]
				, true);


			DrawBox(enemyMob[ene].pos.x - enemyMob[ene].offsetSize.x + mapPos.x
				, enemyMob[ene].pos.y - enemyMob[ene].offsetSize.y + mapPos.y
				, enemyMob[ene].pos.x - enemyMob[ene].offsetSize.x + enemyMob[ene].size.x + mapPos.x
				, enemyMob[ene].pos.y - enemyMob[ene].offsetSize.y + enemyMob[ene].size.y + mapPos.y
				, 0xFF00FF, false);

		}
	}
}


int MoveEnemyX(CHARACTER* enemy, XY player1Pos)
{
	//-----enemy‘€ì
	int diff = player1Pos.x - (*enemy).pos.x;
	int enemySpeed = (*enemy).moveSpeed;
	//X²
	if (diff >= 0)
	{
		//½Ëß°ÄŞ‚Ì’²®‚ğ‚·‚é
		enemySpeed = diff < enemySpeed ? diff : enemySpeed;

		//XÀ•W‚ªˆá‚¤ê‡‚Í“G‚ğˆÚ“®‚³‚¹‚é
		(*enemy).pos.x += enemySpeed;
		(*enemy).moveDir = DIR_RIGHT;
	}
	else
	{
		enemySpeed = -diff < enemySpeed ? -diff : enemySpeed;

		(*enemy).pos.x -= enemySpeed;
		(*enemy).moveDir = DIR_LEFT;
	}


	return enemySpeed;

}

//YÀ•W‚É“®‚­
int MoveEnemyY(CHARACTER* enemy, XY player1Pos)
{
	//-----enemy‘€ì
	int diff = player1Pos.y - (*enemy).pos.y;
	int enemySpeed = (*enemy).moveSpeed;
	//Y²
	if (diff >= 0)
	{
		//½Ëß°ÄŞ‚Ì’²®‚ğ‚·‚é
		enemySpeed = diff < enemySpeed ? diff : enemySpeed;

		//YÀ•W‚ªˆá‚¤ê‡‚Í“G‚ğˆÚ“®‚³‚¹‚é
		(*enemy).pos.y += enemySpeed;
		(*enemy).moveDir = DIR_DOWN;
	}
	else
	{
		enemySpeed = -diff < enemySpeed ? -diff : enemySpeed;
		//YÀ•W‚ªˆá‚¤ê‡‚Í“G‚ğˆÚ“®‚³‚¹‚é
		(*enemy).pos.y -= enemySpeed;
		(*enemy).moveDir = DIR_UP;
	}

	return enemySpeed;

}
//Î‚ß‚É“®‚­
int MoveEnemyXY(CHARACTER* enemy, XY player1Pos)		// true : “®‚­A false : “®‚©‚³‚È‚¢
{

	int diffX = player1Pos.x - (*enemy).pos.x;
	int diffY = player1Pos.y - (*enemy).pos.y;
	int enemySpeed = (*enemy).moveSpeed;

	if (abs(diffX) <= abs(diffY))
	{
		//½Ëß°ÄŞ‚Ì’²®‚ğ‚·‚é
		enemySpeed = MoveEnemyY(enemy, player1Pos);
	}
	else
	{
		enemySpeed = MoveEnemyX(enemy, player1Pos);
	}

	return enemySpeed;
}



//-----’e‚Æ“G‚Ì“–‚½‚è”»’è@(true : ‚ ‚½‚è, false : ‚Í‚¸‚ê)
bool EnemyHitCheck(XY sPos, int sSize)
{
	//‘S‚Ä‚Ì“G‚É“–‚½‚è”»’è‚ğÀ{‚·‚é
	for (int en = 0; en < ENEMY_MAX; en++)
	{
		if (enemyMob[en].life > 0)
		{
			if (((enemyMob[en].pos.x - enemyMob[en].size.x / 2) < (sPos.x + sSize / 2))
				&& ((enemyMob[en].pos.x + enemyMob[en].size.x / 2) > (sPos.x - sSize / 2))
				&& ((enemyMob[en].pos.y - enemyMob[en].size.y / 2) < (sPos.y + sSize / 2))
				&& ((enemyMob[en].pos.y + enemyMob[en].size.y / 2) > (sPos.y - sSize / 2)))
			{
				//“–‚½‚Á‚½A´ÈĞ°‚Ì‘Ì—Í‚ğŒ¸‚ç‚·
				enemyMob[en].life--;
				return true;
			}
		}
	}
	//’e‚ªŠO‚ê‚½
	return false;
}


bool EnemyLife(int index)
{
	for (int en = 0; en < ENEMY_MAX; en++)
	{
		enemyMob[en].life == 0;	
	}
	return true;
}