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
	player.animCnt = 0;										//ｷｬﾗｸﾀのｱﾆﾒｰｼｮﾝ

	LoadDivGraph("char/boy_player.png", 16, 4, 4
		, player.size.x, player.size.y, playerImage);
}
//プレイヤーの初期化
void PlayerGameInit(void)
{
	player.moveDir = DIR_RIGHT;								//ｷｬﾗｸﾀの向き
	player.pos = { 100,100 };									//ｷｬﾗｸﾀの地図上の座標
	player.moveSpeed = PLAYER_DEF_SPEED;					//ｷｬﾗｸﾀの移動ｽﾋﾟｰﾄﾞ
	player.life = player.lifeMax;							//ｷｬﾗｸﾀの体力

}
//プレイヤーの操作
void PlayerControl(void)
{
	bool moveFlag = false;

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
			player.pos.y -= player.moveSpeed;
			break;
		case DIR_DOWN:
			player.pos.y += player.moveSpeed;
			break;
		case DIR_RIGHT:
			player.pos.x += player.moveSpeed;
			break;
		case DIR_LEFT:
			player.pos.x -= player.moveSpeed;
			break;
		default:
			break;
		}
	}
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
}
//プレイヤーの描画
void PlayerGameDraw(void)
{
	player.animCnt++;
	DrawGraph(player.pos.x, player.pos.y, playerImage[(player.moveDir * 4) + (player.animCnt / 30) % 4], true);
	/*DrawGraph(player1.pos.x - player1.offsetSize.y - mapPos.x
		, player1.pos.y - player1.offsetSize.y - mapPos.y
		, playerImage[player1.moveDir][player1.animCnt / 10 % 4]
		, true);*/
}