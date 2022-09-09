#include "DxLib.h"
#include "test.h"
#include "KeyCheck.h"
#include "Item.h"
#include "Battle.h"
#include "Player.h"

int testbkImage;		//√Ωƒópîwåi

CHARACTER boss;
int tBossImage[8];		//Ç“Ç¶ÇÒãSí èÌéû
int tBossDImage[2];		//Ç“Ç¶ÇÒãS¿ﬁ“∞ºﬁéû
int BossImage[8];
int BossDImage[2];

void BattleSystemInit(void)
{
	//-----èâä˙âª
	boss.size = { 400,500 };									//	∑¨◊∏¿ÇÃâÊëúª≤Ωﬁ
	boss.offsetSize = { boss.size.x / 2,boss.size.y / 2 };		//Å@∑¨◊∏¿ÇÃµÃæØƒ
	boss.hitFlag = false;										//	çUåÇÇéÛÇØÇƒÇ¢ÇÈÇ©Ç«Ç§Ç©
	
	//-----∏ﬁ◊Ã®Ø∏ÇÃìoò^
	testbkImage = LoadGraph("aitem/bg.jpg");
	LoadDivGraph("aitem/boss.png", 8, 4, 2, boss.size.x, boss.size.y, tBossImage);
	LoadDivGraph("aitem/bs_D.png", 2, 2, 1, boss.size.x, boss.size.y, tBossDImage);

	LoadDivGraph("aitem/boss2.png", 8, 4, 2, boss.size.x, boss.size.y, BossImage);
	LoadDivGraph("aitem/boss2D.png", 2, 2, 1, boss.size.x, boss.size.y, BossDImage);

	

}

void BattleGameInit(void)
{
	boss.pos = { (SCREEN_SIZE_X - boss.size.x) / 2,0};				//Å@∑¨◊∏¿ÇÃínê}è„ÇÃç¿ïW
	boss.lifeMax = 100;												//	∑¨◊∏¿ÇÃëÃóÕç≈ëÂíl
	boss.life = boss.lifeMax;										//	∑¨◊∏¿ÇÃëÃóÕ
	boss.animCnt = 0;													//	∑¨◊∏¿ÇÃ±∆“∞ºÆ›

}


void BattleScene(void)
{

	if (keyDownTrigger[KEY_ID_SPACE])
	{
		sceneID = SCENE_ID_INIT;
	}

	ItemBossControl(&boss);
	BattleControl();


	//ï`âÊèàóù
	BattleGameDraw();
}


void BattleControl(void)
{


}



void BattleGameDraw(void)
{
	//-----ï`âÊèàóù
	//îwåi
	DrawGraph(0, 0, testbkImage, true);
	//ìG
	if (boss.life > 0)
	{
		boss.animCnt++;
		if (!boss.hitFlag)
		{
			DrawGraph(boss.pos.x, boss.pos.y, tBossImage[(boss.animCnt / 16) % 8], true);
		}
		else if(boss.hitFlag)
		{
			DrawGraph(boss.pos.x, boss.pos.y, tBossDImage[(boss.animCnt / 16) % 2], true);
		}
	
		//	DrawGraph((SCREEN_SIZE_X - 400) / 2, 0, BossImage, true);
		DrawBox(100, 20, boss.lifeMax * 7, 50, 0x55FFFF, true);
		DrawBox(100, 20, boss.life * 7, 50, 0xFF55FF, true);

	//	DrawBox(50, 50, 70, boss.lifeMax * 13
	//		, 0x55FFFF, true);
	//	DrawBox(50, 50, 70, boss.life * 13
	//		, 0xFF55FF, true);


	}
	//-----èÓïÒèàóù
	//DrawFormatString(0, 0, 0xFFFFFF, "Battle : %d", SceneCounter);

	
	DrawBox(BOX_X, BOX_Y, BOX_END_X, BOX_END_Y, 0xFFFFFF, true);
	
	DrawBox(BOX_X, BOX_Y, BOX_END_X, BOX_END_Y, 0xFF22FF, false);

	DrawString(352, 500, "âŒ         êÖ         ïó         âÒïú", 0x000000);
	PlayerBattleDraw();

	//±≤√—
	ItemB_Draw();

}
