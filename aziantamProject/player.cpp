//#include "DxLib.h"
//#include "main.h"
//#include "keycheck.h"
//#include "stage.h"
//#include "player.h"
//#include "shot.h"
//#include "enemy.h"
//
//
//CHARACTER player1;
//CHARACTER player2;
//int player1Image[16];
//int player2Image[16];
//int eventCnt;
//int necEXP[LEVEL_MAX];
//
////ÌßÚ²Ô°¼½ÃÑŒn‰Šú‰»
//bool PlayerSystemInit(void)
//{
//	bool rtnFlag = true;
//
//	if (LoadDivGraph("bmp/player.bmp", 16, 4, 4,
//		PLAYER_SIZE_X, PLAYER_SIZE_Y, player1Image) == -1)
//	{
//		AST();
//		rtnFlag = false;
//	}
//	if (LoadDivGraph("bmp/player2.bmp", 16, 4, 4,
//		PLAYER_SIZE_X, PLAYER_SIZE_Y, player2Image) == -1)
//	{
//		AST();
//		rtnFlag = false;
//	}
//	return rtnFlag;
//}
//
////ÌßÚ²Ô°‚Ì‰Šú‰»
//bool PlayerGameInit(void)
//{
//	bool rtnFlag = true;
//
//	player1.lifeMax = 10;
//	player1.life = player1.lifeMax;
//	player1.atk = 2;
//	player1.level = 1;
//	player1.EXP = 0;
//	player1.size.x = PLAYER_SIZE_X;
//	player1.size.y = PLAYER_SIZE_Y;
//	player1.offsetSize = { player1.size.x / 2, player1.size.y / 2 };
//	player1.hitFlag = false;
//	hitCntPL1 = 0;
//
//	player2.lifeMax = 100;
//	player2.life = player2.lifeMax;
//	player2.atk = 20;
//	player2.level = 10;
//	player2.EXP = 45;
//	player2.size.x = PLAYER_SIZE_X;
//	player2.size.y = PLAYER_SIZE_Y;
//	player2.offsetSize = { player2.size.x / 2, player2.size.y / 2 };
//	player2.hitFlag = false;
//	hitCntPL1 = 0;
//
//	return rtnFlag;
//}
//
////ÌßÚ²Ô°½Ã°¼Ş‚Ì‰Šú‰»
//bool PlayerStageInit(void)
//{
//	bool rtnFlag = true;
//
//	player1.animCnt = 0;
//	player1.moveDir = DIR_DOWN;
//	player1.moveSpeed = 4;
//
//	player2.animCnt = 0;
//	player2.moveDir = DIR_DOWN;
//	player2.moveSpeed = 2;
//
//	playerPosBack.x = 0;
//	playerPosBack.y = 0;
//	playerMapPosMax.x = 0;
//	playerMapPosMax.y = 0;
//	playerMapPosMin.x = 0;
//	playerMapPosMin.y = 0;
//	indexPLMax.x = 0;
//	indexPLMax.y = 0;
//	indexPLMin.x = 0;
//	indexPLMin.y = 0;
//
//	eventCnt = 0;
//
//	return rtnFlag;
//}
//
////ÌßÚ²Ô°1ˆÚ“®ˆ—(‰æ–Ê½¸Û°Ù‚ğŠÜ‚Ş)
//XY Player1Ctl(void)
//{
//	PosBack();						//À•W‚ÌÊŞ¯¸±¯Ìß
//
//	//·°Ø½Ä‚Ì”»’è
//	bool moveFlag = false;
//	for (int dir = 0; dir < DIR_MAX; dir++)
//	{
//		if (CheckHitKey(keyList[dir]) == 1)
//		{
//			player1.moveDir = (DIR)dir;
//			if (canMoveFlag) moveFlag = true;
//		}
//	}
//
//	//ÌßÚ²Ô°‚ÌˆÚ“®ˆ—(‰æ–Ê½¸Û°Ù‚ğŠÜ‚Ş)
//	if (moveFlag)
//	{
//		switch (player1.moveDir)
//		{
//		case DIR_UP:
//			player1.pos.y -= player1.moveSpeed;
//			if (mapPos.y < 0)
//			{
//				if (SCROL_Y_MIN - mapPos.y > player1.pos.y)
//				{
//					mapPos.y += player1.moveSpeed;
//				}
//			}
//			break;
//		case DIR_RIGHT:
//			player1.pos.x += player1.moveSpeed;
//			if (mapPos.x > -mapChipCnt.x * CHIP_SIZE_X + SCREEN_SIZE_X)
//			{
//				if (SCROL_X_MAX - mapPos.x < player1.pos.x)
//				{
//					mapPos.x -= player1.moveSpeed;
//				}
//			}
//			break;
//		case DIR_DOWN:
//			player1.pos.y += player1.moveSpeed;
//			if (mapPos.y > -mapChipCnt.y * CHIP_SIZE_Y + SCREEN_SIZE_Y)
//			{
//				if (SCROL_Y_MAX - mapPos.y < player1.pos.y)
//				{
//					mapPos.y -= player1.moveSpeed;
//				}
//			}
//			break;
//		case DIR_LEFT:
//			player1.pos.x -= player1.moveSpeed;
//			if (mapPos.x < 0)
//			{
//				if (SCROL_X_MIN - mapPos.x > player1.pos.x)
//				{
//					mapPos.x += player1.moveSpeed;
//				}
//			}
//			break;
//		default:
//			AST();
//			break;
//		}
//	}
//
//	//ÌßÚ²Ô°‚ÌUŒ‚—Í‘ã“ü
//	GetAtk(player1.atk, player2.atk);
//
//	//“G‚Æ‚Ì“–‚½‚è”»’è‚ª‚Å‚«‚é‚©‚Ç‚¤‚©‚ÌŠÇ——p
//	HitCheckPlayers();
//	player1.animCnt++;
//	CreateShot1(player1.pos, player1.moveDir);
//	return player1.pos;
//}
//
////ÌßÚ²Ô°2ˆÚ“®ˆ—
//void Player2Ctl(void)
//{
//	XY tmpDis;
//	tmpDis.x = player1.pos.x - player2.pos.x;
//	if (tmpDis.x < 0) tmpDis.x = tmpDis.x * (-1);
//	tmpDis.y = player1.pos.y - player2.pos.y;
//	if (tmpDis.y < 0) tmpDis.y = tmpDis.y * (-1);
//	if (((tmpDis.x * tmpDis.x) + (tmpDis.y * tmpDis.y)) > 1000)
//	{
//		if (tmpDis.x > tmpDis.y)
//		{
//			if (player1.pos.x > player2.pos.x)
//			{
//				player2.pos.x += player2.moveSpeed;
//				player2.moveDir = DIR_RIGHT;
//			}
//			else
//			{
//				player2.pos.x -= player2.moveSpeed;
//				player2.moveDir = DIR_LEFT;
//			}
//		}
//		else
//		{
//			if (player1.pos.y > player2.pos.y)
//			{
//				player2.pos.y += player2.moveSpeed;
//				player2.moveDir = DIR_DOWN;
//			}
//			else
//			{
//				player2.pos.y -= player2.moveSpeed;
//				player2.moveDir = DIR_UP;
//			}
//		}
//	}
//	if (((tmpDis.x * tmpDis.x) + (tmpDis.y * tmpDis.y)) > 10000)
//	{
//		player2.moveSpeed = player1.moveSpeed;
//	}
//	else
//	{
//		player2.moveSpeed = 2;
//	}
//	player2.animCnt++;
//	CreateShot2(player2.pos, player2.moveDir);
//}
//
////ÌßÚ²Ô°•`‰æ
//void PlayerDraw(void)
//{
//	//ÌßÚ²Ô°1
//	if (hitCntPL1 / 2 % 2 == 0 && player1.life > 0)
//	{
//		DrawGraph(player1.pos.x - player1.offsetSize.x + mapPos.x,
//			player1.pos.y - player1.offsetSize.y + mapPos.y,
//			player1Image[player1.moveDir * 4 + ((player1.animCnt / 20) % 4)], true);
//	}
//
//	//ÌßÚ²Ô°2
//	if (PL2Flag)
//	{
//		if (hitCntPL2 / 2 % 2 == 0 && player2.life > 0)
//		{
//			DrawGraph(player2.pos.x - player2.offsetSize.x + mapPos.x,
//				player2.pos.y - player2.offsetSize.y + mapPos.y,
//				player2Image[player2.moveDir * 4 + ((player2.animCnt / 20) % 4)], true);
//		}
//	}
//	else
//	{
//		DrawGraph(19 * CHIP_SIZE_X + mapPos.x,
//			69 * CHIP_SIZE_Y + mapPos.y,
//			player2Image[DIR_LEFT * 4], true);
//	}
//
//	//ÌßÚ²Ô°‚Ì²ÍŞİÄ—p
//	if (PL2eventFlag)
//	{
//		eventCnt++;
//		DrawBox(0, 450, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0x000000, true);
//		DrawBox(0, 420, 100, 460, 0x000000, true);
//		DrawBox(650, 360, SCREEN_SIZE_X, 460, 0x000000, true);
//		DrawBox(0 + 5, 450 + 5, SCREEN_SIZE_X - 5, SCREEN_SIZE_Y - 5, 0xFFFFFF, false);
//		DrawBox(0 + 5, 420 + 5, 100 - 5, 460 - 10, 0xFFFFFF, false);
//		DrawBox(650 + 5, 360 + 5, SCREEN_SIZE_X - 5, 460 - 10, 0xFFFFFF, false);
//		if (eventCnt >= 0 && eventCnt < 3)		DrawFormatString(20, 470, 0xFFFFFF, "");
//		if (eventCnt >= 3 && eventCnt < 9)		DrawFormatString(20, 470, 0xFFFFFF, "");
//		if (eventCnt >= 9 && eventCnt < 12)		DrawFormatString(20, 470, 0xFFFFFF, "");
//		
//		if (eventCnt >= 39 && eventCnt < 42)	DrawFormatString(20, 500, 0xFFFFFF, "");
//		if (eventCnt >= 42 && eventCnt < 45)	DrawFormatString(20, 500, 0xFFFFFF, "");
//		if (eventCnt >= 45 && eventCnt < 48)	DrawFormatString(20, 500, 0xFFFFFF, "");
//	
//		
//
//		DrawFormatString(20, 430, 0xFFFFFF, "");
//		if (eventCnt >= 90)
//		{
//			DrawFormatString(700, 380, 0xFFFFFF, "");
//			DrawFormatString(700, 410, 0xFFFFFF, "");
//			if (eventCnt / 20 % 3 != 0)
//			{
//				DrawFormatString(670, 380, 0xFFFFFF, "Y");			//YES
//				DrawFormatString(670, 410, 0xFFFFFF, "N");			//NO
//			}
//		}
//	}
//}
//
////ÌßÚ²Ô°ŠÖŒW‚ÌÒÆ­°‰æ–Ê•`‰æ
//void MenuDrawPL(void)
//{
//
//}
//
////À•WÊŞ¯¸±¯Ìß
//void PosBack(void)
//{
//	playerPosBack = player1.pos;
//}
//
////µÌŞ¼Şª¸Ä‚ÆÌßÚ²Ô°‚Ì“–‚½‚è”»’è
//bool IsHitObjPL(int j)
//{
//	bool hitFlag = false;
//	playerMapPosMax.x = player1.pos.x + player1.offsetSize.x;
//	playerMapPosMax.y = player1.pos.y + player1.offsetSize.y;
//	playerMapPosMin.x = player1.pos.x - player1.offsetSize.x;
//	playerMapPosMin.y = player1.pos.y - player1.offsetSize.y;
//	indexPLMax = PosToIndex(playerMapPosMax);
//	indexPLMin = PosToIndex(playerMapPosMin);
//
//	if (mapData[indexPLMax.y][indexPLMax.x] == j)
//	{
//		hitFlag = true;
//	}
//	else if (mapData[indexPLMin.y][indexPLMin.x] == j)
//	{
//		hitFlag = true;
//	}
//	else if (mapData[indexPLMax.y][indexPLMin.x] == j)
//	{
//		hitFlag = true;
//	}
//	else if (mapData[indexPLMin.y][indexPLMax.x] == j)
//	{
//		hitFlag = true;
//	}
//	else
//	{
//		hitFlag = false;
//	}
//	return hitFlag;
//}
//
////“G‚Ì’e‚ÆÌßÚ²Ô°‚Ì“–‚½‚è”»’è
//bool HitCheckEneShot(XY shotPos, int shotSize, int atk)
//{
//	bool rtnFlag = false;
//	XY distance;
//	if (player1.life > 0 && player1.hitFlag == false)
//	{
//		distance.x = player1.pos.x - shotPos.x;
//		distance.y = player1.pos.y - shotPos.y;
//		if (((distance.x * distance.x) + (distance.y * distance.y)) <=
//			(player1.offsetSize.x + shotSize / 2) * (player1.offsetSize.x + shotSize / 2))
//		{
//			player1.life -= atk;
//			if (player1.life < 0) player1.life = 0;
//			player1.hitFlag = true;
//			rtnFlag = true;
//		}
//	}
//	if (player2.life > 0 && player2.hitFlag == false)
//	{
//		distance.x = player2.pos.x - shotPos.x;
//		distance.y = player2.pos.y - shotPos.y;
//		if (((distance.x * distance.x) + (distance.y * distance.y)) <=
//			(player2.offsetSize.x + shotSize / 2) * (player2.offsetSize.x + shotSize / 2))
//		{
//			player2.life -= atk;
//			if (player2.life < 0) player2.life = 0;
//			player2.hitFlag = true;
//			rtnFlag = true;
//		}
//	}
//	return rtnFlag;
//}
//
////ÌßÚ²Ô°2‚Ì²ÍŞİÄ
//void EventPL2(void)
//{
//	if (CheckHitKey(KEY_INPUT_Y))
//	{
//		PL2eventFlag = false;
//		PL2eventEndFlag = true;
//		PL2Flag = true;
//		player2.pos.x = 19 * CHIP_SIZE_X;
//		player2.pos.y = 69 * CHIP_SIZE_Y;
//	}
//	if (CheckHitKey(KEY_INPUT_N))
//	{
//		PL2eventFlag = false;
//		PL2eventEndFlag = true;
//	}
//}
//
////ÌßÚ²Ô°‚ª“G‚Æ“–‚½‚Á‚½ê‡
//void HitCheckPlayers(void)
//{
//	if (player1.hitFlag)
//	{
//		hitCntPL1++;
//		if (hitCntPL1 >= 100)
//		{
//			hitCntPL1 = 0;
//			player1.hitFlag = false;
//		}
//	}
//	if (player2.hitFlag)
//	{
//		hitCntPL2++;
//		if (hitCntPL2 >= 100)
//		{
//			hitCntPL2 = 0;
//			player2.hitFlag = false;
//		}
//	}
//}
//
////ÌßÚ²Ô°1‚Ìî•ñæ“¾—p
//CHARACTER GetPL1(void)
//{
//	return player1;
//}
//
////ÌßÚ²Ô°2‚Ìî•ñæ“¾—p
//CHARACTER GetPL2(void)
//{
//	return player2;
//}
//
