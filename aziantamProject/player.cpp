#include "DxLib.h"
#include "main.h"
#include "player.h"
#include "keycheck.h"
#include "stage.h"

//変数
int playerImage[16];
CHARACTER player;

//ﾌﾟﾚｲﾔｰ情報の初期化
void PlayerSystemInit(void)
{
	//player.charType;										//ｷｬﾗｸﾀの種類
	player.size = {32,32};									//ｷｬﾗｸﾀ画像のｻｲｽﾞ
	player.offsetSize = {player.size.x/2,player.size.y/2};	//ｷｬﾗｸﾀのｵﾌｾｯﾄ
	player.lifeMax = PLAYER_MAX_LIFE;						//ｷｬﾗｸﾀの体力最大値
	player.moveSpeed = PLAYER_DEF_SPEED;					//ｷｬﾗｸﾀの移動ｽﾋﾟｰﾄﾞ
	player.animCnt = 0;										//ｷｬﾗｸﾀのｱﾆﾒｰｼｮﾝ

	LoadDivGraph("char/boy_player.png", 16, 4, 4
		, player.size.x, player.size.y, playerImage);
}
//プレイヤーの初期化
void PlayerGameInit(void)
{
	player.moveDir = DIR_RIGHT;								//ｷｬﾗｸﾀの向き
	player.pos = { 100,100 };									//ｷｬﾗｸﾀの地図上の座標

	player.life = player.lifeMax;							//ｷｬﾗｸﾀの体力

}



//プレイヤーの操作
XY PlayerControl(void)
{
	bool moveFlag = false;				//　操作されているか判断する
	XY returnValue = player.pos;			//	関数の戻り値格納領域
	XY playerPosCopy = player.pos;
	XY playerPosOffset = playerPosCopy;
	XY indexPos;							//　ﾏｯﾌﾟ配列座標

	if (player.life > 0)
	{
		if (KeyNew[KEY_ID_UP])
		{
			moveFlag = true;
			player.moveDir = DIR_UP;
		}
		if (KeyNew[KEY_ID_DOWN])
		{
			moveFlag = true;
			player.moveDir = DIR_DOWN;
		}
		if (KeyNew[KEY_ID_RIGHT])
		{
			moveFlag = true;
			player.moveDir = DIR_RIGHT;
		}
		if (KeyNew[KEY_ID_LEFT])
		{
			moveFlag = true;
			player.moveDir = DIR_LEFT;
		}


		if (moveFlag)
		{
			player.animCnt += 5;
			switch (player.moveDir)
			{
			case DIR_UP:
				playerPosCopy.y -= player.moveSpeed;
				playerPosOffset.y = playerPosCopy.y;
				indexPos = Pos2Index(playerPosCopy);
				//指定した場所を通過可能か
				if (IsPass(playerPosOffset))
				{
					player.pos = playerPosCopy;
					//ｽｸﾛｰﾙ制限
					if (player.pos.y  < SCROLL_Y_MIN - mapPos.y)
					{
						if (mapPos.y < 0)
						{

							mapPos.y += player.moveSpeed;
						}
					}
				}
				break;
			case DIR_DOWN:
				playerPosCopy.y += player.moveSpeed;
				playerPosOffset.y = playerPosCopy.y;
				indexPos = Pos2Index(playerPosCopy);
				//指定した場所を通過可能か
				if (IsPass(playerPosOffset))
				{
					player.pos = playerPosCopy;
					//ｽｸﾛｰﾙ制限
					if (player.pos.y > SCROLL_Y_MAX - mapPos.y)
					{
						if (mapPos.y > CHIP_SIZE_Y* -mapSize.y + SCREEN_SIZE_Y)
						{
							mapPos.y -= player.moveSpeed;
						}
					}
				}
				break;
			case DIR_RIGHT:
				playerPosCopy.x += player.moveSpeed;
				playerPosOffset.x = playerPosCopy.x;
				indexPos = Pos2Index(playerPosCopy);
				//指定した場所を通過可能か
				if (IsPass(playerPosOffset))
				{
					player.pos = playerPosCopy;
					//ｽｸﾛｰﾙ制限
					if (player.pos.x > SCROLL_X_MAX - mapPos.x)
					{
						if (mapPos.x > CHIP_SIZE_X* -mapSize.x + SCREEN_SIZE_X)
						{
							mapPos.x -= player.moveSpeed;
						}
					}
				}
				break;
			case DIR_LEFT:
				playerPosCopy.x -= player.moveSpeed;
				playerPosOffset.x = playerPosCopy.x;
				indexPos = Pos2Index(playerPosCopy);
				//指定した場所を通過可能か
				if (IsPass(playerPosOffset))
				{
					player.pos = playerPosCopy;
					//ｽｸﾛｰﾙ制限
					if (player.pos.x < SCROLL_X_MIN - mapPos.x)
					{
						if (mapPos.x < 0)
						{
							mapPos.x += player.moveSpeed;
						}
					}
				}
				break;
			default:
				break;
			}
			//戻り値を設定
			returnValue = player.pos;

		}
		
	}
<<<<<<< HEAD
	if (mapPos.x < 0)
	{
		mapPos.x = 0;
	}
	if (mapPos.x > CHIP_SIZE_X * MAP_X - SCREEN_SIZE_X)
	{
		mapPos.x = CHIP_SIZE_X * MAP_X - SCREEN_SIZE_X;
	}
	if (mapPos.y < 0)
	{
		mapPos.y = 0;
	}
	if (mapPos.y > CHIP_SIZE_Y * MAP_Y - SCREEN_SIZE_Y)
	{
		mapPos.y = CHIP_SIZE_Y * MAP_Y - SCREEN_SIZE_Y;
	}
=======
	return returnValue;
>>>>>>> 9570c1765eccde647c8cebd2eb7ef975b03ac5ad
}
//プレイヤーの描画
void PlayerGameDraw(void)
{
	player.animCnt++;
<<<<<<< HEAD
	DrawGraph(player.pos.x, player.pos.y, playerImage[(player.moveDir * 4) + (player.animCnt / 30) % 4], true);
	/*DrawGraph(player1.pos.x - player1.offsetSize.y - mapPos.x
		, player1.pos.y - player1.offsetSize.y - mapPos.y
		, playerImage[player1.moveDir][player1.animCnt / 10 % 4]
		, true);*/
}
=======
	DrawGraph(player.pos.x - player.offsetSize.x + mapPos.x
		, player.pos.y - player.offsetSize.y + mapPos.y
		, playerImage[(player.moveDir * 4) + (player.animCnt / 30) % 4], true);

	DrawBox(SCROLL_X_MIN, SCROLL_Y_MIN, SCROLL_X_MAX, SCROLL_Y_MAX, 0xFFFFFF, false);
	DrawFormatString(0, 50, 0xFFFFFF, "player:%d,%d", player.pos.x, player.pos.y);
	XY indexPos;
	indexPos = Pos2Index(player.pos);

}
>>>>>>> 9570c1765eccde647c8cebd2eb7ef975b03ac5ad
