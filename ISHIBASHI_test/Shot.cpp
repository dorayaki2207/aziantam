#include "DxLib.h"
#include "test.h"
#include "KeyCheck.h"
#include "Item.h"
#include "Player.h"
#include "Shot.h"

#include "Stage.h"

//------ŠO•”•Ï”’è‹`
CHARACTER shot[SHOT_TYPE_MAX - 1];
int shotImage[SHOT_TYPE_MAX - 1][SHOT_ANI];
//int shotFlag[SHOT_TYPE_MAX - 1];


void ShotSystemInit(void)
{
	//-----•Ï”‚Ì‰Šú‰»
	shot[SHOT_TYPE_FIRE].charType = SHOT_TYPE_FIRE;
	shot[SHOT_TYPE_WATER].charType = SHOT_TYPE_WATER;
	shot[SHOT_TYPE_WIND].charType = SHOT_TYPE_WIND;
	for (int sh = 0; sh < SHOT_TYPE_MAX - 1; sh++)
	{
		shot[sh].moveDir = DIR_DOWN;							//	’e‚ÌŒü‚«
		shot[sh].size = { 40,40 };								//	’e‚Ì‰æ‘œ»²½Ş
		shot[sh].offsetSize = { shot[sh].size.x / 2
			,shot[sh].size.y / 2 };			//@’e‚ÌµÌ¾¯Ä
		shot[sh].moveSpeed = 4;									//	’e‚ÌˆÚ“®½Ëß°ÄŞ
		shot[sh].pos = { 0,0 };								//@’e‚Ì’n}ã‚ÌÀ•W

	}

	
	//-----¸Ş×Ì¨¯¸‚Ì“o˜^
	//‰Î
	LoadDivGraph("aitem/fire_soft.png", SHOT_ANI, 8, 8
		, shot[SHOT_TYPE_FIRE].size.x
		, shot[SHOT_TYPE_FIRE].size.y
		, shotImage[SHOT_TYPE_FIRE]);
	//…
	LoadDivGraph("aitem/water_soft.png", SHOT_ANI, 8, 8
		, shot[SHOT_TYPE_WATER].size.x
		, shot[SHOT_TYPE_WATER].size.y
		, shotImage[SHOT_TYPE_WATER]);
	//•—
	LoadDivGraph("aitem/wind_soft.png", SHOT_ANI, 8, 8
		, shot[SHOT_TYPE_WIND].size.x
		, shot[SHOT_TYPE_WIND].size.y
		, shotImage[SHOT_TYPE_WIND]);

}

void ShotGameInit(void)
{
	

	for (int sh = 0; sh < SHOT_TYPE_MAX - 1; sh++)
	{
		shot[sh].lifeMax = SHOT_LIFE_MAX;						//	’e‚Ì‘Ì—ÍÅ‘å’l
		shot[sh].life = 0;						//	’e‚Ì‘Ì—Í
		shot[sh].animCnt = 0;									//	’e‚Ì±ÆÒ°¼®İ
	}
}

void ShotControl(void)
{
	for (int sh = 0; sh < SHOT_TYPE_MAX - 1; sh++)
	{
		//Œ‚‚Á‚Ä‚¢‚é’e‚ğ’T‚·
		if (shot[sh].life > 0)
		{
			
			//’e‚ğˆÚ“®‚³‚¹‚é
			if (shot[sh].moveDir == DIR_RIGHT) shot[sh].pos.x += shot[sh].moveSpeed;
			if (shot[sh].moveDir == DIR_LEFT) shot[sh].pos.x -= shot[sh].moveSpeed;
			if (shot[sh].moveDir == DIR_DOWN) shot[sh].pos.y += shot[sh].moveSpeed;
			if (shot[sh].moveDir == DIR_UP) shot[sh].pos.y -= shot[sh].moveSpeed;
			//õ–½‚ğŒ¸‚ç‚·iË’ö‹——£j
			shot[sh].life--;

		//			DeleteShot(sh);
		}
	}
}



//-----’e•`‰æˆ—
void ShotGameDraw(void)
{
	//-----•`‰æ
	for (int sh = 0; sh < ITEM_TYPE_F_MAX - 1; sh++)
	{
		if (shot[sh].life > 0)
		{
			shot[sh].animCnt++;

			DrawGraph(shot[sh].pos.x - shot[sh].offsetSize.x + mapPos.x
				, shot[sh].pos.y - shot[sh].offsetSize.y + mapPos.y
				, shotImage[shot[sh].charType][shot[sh].animCnt]
				, true);
		}

		DrawBox(shot[sh].pos.x - shot[sh].offsetSize.x + mapPos.x
			, shot[sh].pos.y - shot[sh].offsetSize.y + mapPos.y
			, shot[sh].pos.x - shot[sh].offsetSize.x + shot[sh].size.x + mapPos.x
			, shot[sh].pos.y - shot[sh].offsetSize.y + shot[sh].size.y + mapPos.y
			, 0xFFFFFF, false);
		//-----î•ñˆ—
		DrawFormatString(0, 300, 0xFFFFFF, "shotAni:%d", shot[sh].animCnt);

	}


}


//-----’e‚ğ¶¬‚·‚é
void CreateShot(XY pPos, DIR pDir, SHOT_TYPE ptype/*, ITEM_TYPE_F itype*/)
{

	//’e‚Ì”•ªŒ‚‚Á‚Ä‚¢‚È‚¢’e‚ª‚È‚¢‚©‚ğÁª¯¸‚µA
	//Œ‚‚Á‚Ä‚¢‚È‚¢’e‚ª‚ ‚ê‚Îˆê”­’e‚ğì‚Á‚Ä”­Ë‚·‚éB
	for (int sh = 0; sh < SHOT_TYPE_MAX - 1; sh++)
	{
			//Œ‚‚Á‚Ä‚¢‚È‚¢’e‚ğ’T‚·
			if (shot[sh].life <= 0)
			{
				//ŒäD‚Ì”‚ª0–‡ˆÈã‚Ìê‡‚Ì‚İˆ—‚ğ‚·‚é
			/*	if (itemF[itype].point > 0)
				{*/
					//Œ‚‚Á‚Ä‚¢‚È‚¢’e‚ª‚ ‚Á‚½‚Ì‚Å”­Ë
					shot[sh].charType = ptype;
					shot[sh].pos.x = pPos.x;				//	’e‚ÌêŠ
					shot[sh].pos.y = pPos.y;
					shot[sh].moveDir = pDir;				//	’e‚Ìi‚Ş‚×‚«•ûŒü
					shot[sh].life = shot[sh].lifeMax;		//	’e‚ğŒ‚‚Á‚½‚±‚Æ‚É‚·‚é
					break;
			//	}
		}
	}
}

//-----’e‚ğÁ–Å‚³‚¹‚é
void DeleteShot(int index)
{
	if (shot[index].life < 0)
	{
		shot[index].life = 0;
	}

}

void ShotAniCnt(SHOT_TYPE type)
{
	if (shot[type].animCnt > SHOT_ANI)
	{
		shot[type].animCnt = 0;
	}
}