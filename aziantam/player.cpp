#include <DxLib.h>
#include "main.h"
#include "stage.h"
#include "item.h"
#include "player.h"
#include "keycheck.h"
#include "shot.h"
#include "enemy.h"
#include "effect.h"
#include "mark.h"

//変数
int playerImage[16];
CHARACTER player;

int lifeCheckCnt;
int healCheckCnt;
int speedCnt;

bool endTextFlag;
int endTexCnt;
int eTextImage;

//ﾌﾟﾚｲﾔｰ情報の初期化
void PlayerSystemInit(void)
{
	//player.charType;										//ｷｬﾗｸﾀの種類
	player.size = {32,32};									//ｷｬﾗｸﾀ画像のｻｲｽﾞ
	player.offsetSize = {player.size.x/2,player.size.y/2};	//ｷｬﾗｸﾀのｵﾌｾｯﾄ
	player.lifeMax = PLAYER_MAX_LIFE;						//ｷｬﾗｸﾀの体力最大値
	player.moveSpeed = PLAYER_DEF_SPEED;					//ｷｬﾗｸﾀの移動ｽﾋﾟｰﾄﾞ
	player.animCnt = 0;										//ｷｬﾗｸﾀのｱﾆﾒｰｼｮﾝ
	player.hitFlag = false;

	endTextFlag = false;
	endTexCnt = 0;

	LoadDivGraph("char/boy_player.png", 16, 4, 4
		, player.size.x, player.size.y, playerImage);

	eTextImage = LoadGraph("item/text.png");
}
//プレイヤーの初期化
void PlayerGameInit(void)
{
	player.moveDir = DIR_DOWN;								//ｷｬﾗｸﾀの向き
	player.pos = { 625,600};								//ｷｬﾗｸﾀの地図上の座標

	player.life = player.lifeMax;							//ｷｬﾗｸﾀの体力
	lifeCheckCnt = 0;
	healCheckCnt = 0;
	speedCnt = 0;

	endTextFlag = false;
	endTexCnt = 0;
}

//死亡確認
bool PlayerDid()
{
	if (player.life <= 0)
	{
		return true;
	}
	return false;
}

bool ClearSet(void)
{
	if (SetEnemyMoment())
	{
		endTextFlag = true;
		
		if ((player.pos.x >= CLEAR_MINI_X && player.pos.x <= CLEAR_MAX_X)
			&& (player.pos.y >= CLEAR_MINI_Y && player.pos.y <= CLEAR_MAX_Y))
		{
			return true;
		}
	}

	return false;
}

//プレイヤーの操作
XY PlayerControl(void)
{
	bool moveFlag = false;				//　操作されているか判断する
	XY returnValue = player.pos;			//	関数の戻り値格納領域
	XY playerPosCopy = player.pos;
	XY playerPosOffset = playerPosCopy;
	XY indexPos;							//　ﾏｯﾌﾟ配列座標

	if (player.life < 0) SceneID = SCENE_GAMEOVER;

	if (player.life > 0)
	{
		

		//-----移動処理
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

		//ﾌﾟﾚｲﾔｰの向き
		if (moveFlag)
		{
			player.animCnt += 5;
			switch (player.moveDir)
			{
			case DIR_UP:
				playerPosCopy.y -= player.moveSpeed;
				playerPosOffset.y = playerPosCopy.y - player.offsetSize.y;
				indexPos = Pos2Index(playerPosCopy);
				//指定した場所を通過可能か
				if (IsPass(playerPosOffset))
				{
					player.pos = playerPosCopy;
					//ｽｸﾛｰﾙ制限
					if (player.pos.y + mapPos.y < SCROLL_Y_MIN)
					{
						mapPos.y += player.moveSpeed;
					}
				}
				break;
			case DIR_DOWN:
				playerPosCopy.y += player.moveSpeed;
				playerPosOffset.y = playerPosCopy.y + player.offsetSize.y;
				indexPos = Pos2Index(playerPosCopy);
				//指定した場所を通過可能か
				if (IsPass(playerPosOffset))
				{
					player.pos = playerPosCopy;
					//ｽｸﾛｰﾙ制限
					if (player.pos.y + mapPos.y > SCROLL_Y_MAX)
					{
						mapPos.y -= player.moveSpeed;
					}
				}
				break;
			case DIR_RIGHT:
				playerPosCopy.x += player.moveSpeed;
				playerPosOffset.x = playerPosCopy.x + player.offsetSize.x;
				indexPos = Pos2Index(playerPosCopy);
				//指定した場所を通過可能か
				if (IsPass(playerPosOffset))
				{
					player.pos = playerPosCopy;
					//ｽｸﾛｰﾙ制限
					if (player.pos.x + mapPos.x > SCROLL_X_MAX)
					{
						mapPos.x -= player.moveSpeed;
					}
				}
				break;
			case DIR_LEFT:
				playerPosCopy.x -= player.moveSpeed;
				playerPosOffset.x = playerPosCopy.x - player.offsetSize.x;
				indexPos = Pos2Index(playerPosCopy);
				//指定した場所を通過可能か
				if (IsPass(playerPosOffset))
				{
					player.pos = playerPosCopy;
					//ｽｸﾛｰﾙ制限
					if (player.pos.x + mapPos.x < SCROLL_X_MIN)
					{
						mapPos.x += player.moveSpeed;
					}
				}
				break;
			default:
				break;
			}
			//戻り値を設定
			returnValue = player.pos;

		}

		

		//-----ｼｮｯﾄ処理
		if (KeyNew[KEY_ID_FIRE])
		{
			CreateShot(player.pos, player.moveDir, MAGIC_TYPE_FIRE);
		}
		if (KeyNew[KEY_ID_WATER])
		{
			CreateShot(player.pos, player.moveDir, MAGIC_TYPE_WATER);
		}
		if (KeyNew[KEY_ID_WIND])
		{
			CreateShot(player.pos, player.moveDir, MAGIC_TYPE_WIND);
		}
		if (player.life != player.lifeMax)
		{
			if (KeyNew[KEY_ID_HEAL])
			{

				if (healCheckCnt == 0)
				{
					CreateShot(player.pos, player.moveDir, MAGIC_TYPE_HEAL);

					healCheckCnt = 100;
					if (player.lifeMax > player.life)
					{
						player.life += 10;
					}
					if (player.life > player.lifeMax)
					{
						player.life = player.lifeMax;
					}
				}
			}
		}

		if (healCheckCnt > 0)
		{
			healCheckCnt--;
			if (healCheckCnt < 0)
			{
				healCheckCnt = 0;
			}
		}

		//スクロール制限
		MapRange();

		//-----ライフ操作
		if (PlayerHitCheck(player.pos, player.size.x))
		{
			if (lifeCheckCnt == 0)
			{
				DamageEffect(player.pos, MAGIC_TYPE_HEAL);
				player.life -= 8;
				if (GameOverSet())
				{
					player.life -= 25;
				}
				lifeCheckCnt = 100;
			}

		}
		
		if (lifeCheckCnt > 0)
		{
			lifeCheckCnt--;
			if (lifeCheckCnt < 0)
			{
				lifeCheckCnt = 0;
			}
		}

		PlayerEvent();
	}

	return returnValue;
}


//プレイヤーの描画
void PlayerGameDraw(void)
{
	if (player.life > 0)
	{
		player.animCnt++;
		if (lifeCheckCnt % 5 == 0)
		{
			DrawGraph(player.pos.x - player.offsetSize.x + mapPos.x
				, player.pos.y - player.offsetSize.y + mapPos.y
				, playerImage[(player.moveDir * 4) + (player.animCnt / 30) % 4], true);
		}
	}


//	DrawBox(SCROLL_X_MIN, SCROLL_Y_MIN, SCROLL_X_MAX, SCROLL_Y_MAX, 0xFFFFFF, false);
	XY indexPos;
	indexPos = Pos2Index(player.pos);

	////情報処理
//	DrawFormatString(0, 50, 0xFFFFFF, "player:%d,%d", player.pos.x, player.pos.y);
//	DrawFormatString(0, 300, 0xFFFFFF, "playerHp%d", player.life);
	//DrawFormatString(0, 350, 0xffffff, "LifeCheck:%d", lifeCheckCnt);
	//DrawFormatString(0, 370, 0xffffff, "moveCheck:%d", healCheckCnt);
	//DrawFormatString(0, 370, 0xffffff, "speedCnt:%d", speedCnt);
//	DrawFormatString(0, 0, 0xffffff, "speed:%d", player.moveSpeed);

}

void PlayerDraw(void)
{
	//ライフ描画
	DrawBox(32, 25, 32 + player.lifeMax, 16, GetColor(255, 0, 0), true);
	DrawBox(32, 25, 32 + player.life, 16, GetColor(0, 255, 0), true);
	DrawBox(32, 25, 32 + player.lifeMax, 16, GetColor(255, 255, 0), false);

}

void PlayerTextDraw()
{
	//ライフ描画
	DrawFormatString(200, 310, 0xff22ff, "体力　：　%d", player.life);
	DrawBox(212, 330, 212 + player.lifeMax/2, 340, GetColor(255, 0, 0), true);
	DrawBox(212, 330, 212 + player.life/2, 340, GetColor(0, 255, 0), true);
	DrawBox(212, 330, 212 + player.lifeMax/2, 340, GetColor(255, 255, 0), false);
}

void EndTextDraw(void)
{
	if (endTextFlag)
	{
		DrawGraph((SCREEN_SIZE_X - 400) / 2, 10, eTextImage, true);
	}
}


void PlayerEvent(void)
{
	if ((stageID == STAGE_ID_START) || (stageID == STAGE_ID_MOB) || (stageID == STAGE_ID_KAPPA))
	{
		// 特殊なマップを踏んだ場合の処理
		// 毒
		//動きが遅くなる
		if (GetEvent(player.pos) == EVENT_ID_SPEEDDOWN)
		{
			player.moveSpeed = PLAYER_SPEED_LOW;
		}
		//ダメージ
		else if (GetEvent(player.pos) == EVENT_ID_DAMAGE)
		{
			if (lifeCheckCnt == 0)
			{
				player.life -= 5;
				lifeCheckCnt = 100;
			}
		}
		else if (GetEvent(player.pos) == EVENT_ID_KAPPA)
		{
			player.moveSpeed = PLAYER_SPEED_L;
		}
		// イベント戻す
		else
		{
			player.moveSpeed = PLAYER_SPEED_NORMAL;
		}
	}

	if ((stageID == STAGE_ID_ONI) || (stageID == STAGE_ID_ONI2))
	{
		//-----ｲﾍﾞﾝﾄ発生
		//動きが止まる
		if (GetEvent(player.pos) == EVENT_ID_STOP)
		{
			speedCnt++;
			if (speedCnt < 100)
			{
				player.moveSpeed = PLAYER_SPEED_STOP;
			}
			else if (speedCnt >= 100)
			{
				player.moveSpeed = PLAYER_SPEED_NORMAL;
			}
		}
		//動きが遅くなる
		else if (GetEvent(player.pos) == EVENT_ID_SPEEDDOWN)
		{
			player.moveSpeed = PLAYER_SPEED_LOW;
		}
		//ﾀﾞﾒｰｼﾞを受ける
		else if (GetEvent(player.pos) == EVENT_ID_DAMAGE)
		{
			if (lifeCheckCnt == 0)
			{
				player.life -= 5;
				lifeCheckCnt = 100;
			}
		}
		//通常時の移動スピード
		else
		{
			player.moveSpeed = PLAYER_SPEED_NORMAL;
		}

		if (GetEvent(player.pos) != EVENT_ID_STOP)
		{
			speedCnt = 0;
		}
	}
 }


void MapChange(void)
{

	
	
	if (GetMapDate() != STAGE_ID_START)
	{
		if (MarkHitCheck(STAGE_ID_START, player.pos, player.size))
		{
			stageID = STAGE_ID_START;
			SetInitMoment(stageID);
		}
	}
	else
	{
		if (MarkHitCheck(STAGE_ID_MOB, player.pos, player.size))
		{
			stageID = STAGE_ID_MOB;
			SetInitMoment(stageID);
		}
		else if (MarkHitCheck(STAGE_ID_ONI, player.pos, player.size))
		{
			stageID = STAGE_ID_ONI;
			SetInitMoment(stageID);
		}
		else if (MarkHitCheck(STAGE_ID_KAPPA, player.pos, player.size))
		{
			
			stageID = STAGE_ID_KAPPA;
			SetInitMoment(stageID);
			
		}
	}

	if (GetMapDate() == STAGE_ID_ONI)
	{
		if (GetEvent(player.pos) == EVENT_ID_KAIDAN)
		{
			stageID = STAGE_ID_ONI2;
			SetMapData(stageID);
			player.pos = { 240,370 };
		}
		if (GetEvent(player.pos) == EVENT_ID_DOKUTU)
		{
			stageID = STAGE_ID_ONI2;
			SetMapData(stageID);
			player.pos = { 350,600 };
		}
	}
	if (GetMapDate() == STAGE_ID_ONI2)
	{
		if (GetEvent(player.pos) == EVENT_ID_KAIDAN2)
		{
			stageID = STAGE_ID_ONI;
			SetMapData(stageID);
			player.pos = { 280,1155 };
			mapPos = { 0 +(-16),0 + (-630) };
		}

		if ((player.pos.x >= 320 && player.pos.x < 350) && (player.pos.y >= 580 && player.pos.y <590))
		{
			stageID = STAGE_ID_ONI;
			SetMapData(stageID);
			player.pos = { 240,360 };
		}
	}

}

//ステージ移動時専用の初期化関数
void SetInitMoment(STAGE_ID stageID)
{
	mapPos = { 0,0 };
	SetMapData(stageID);
	MarkGameInit();
	PlayerPosInit();
	EnemyGameInit(stageID);
}

//playerの座標（向き含む）専用の初期化関数
bool PlayerPosInit(void)
{
	if (GetMapDate() == STAGE_ID_START)
	{
		player.moveDir = DIR_RIGHT;								//ｷｬﾗｸﾀの向き
		player.pos = { 160,135 };								//ｷｬﾗｸﾀの地図上の座標
	}
	else if (GetMapDate() == STAGE_ID_MOB)
	{
		player.moveDir = DIR_RIGHT;								//ｷｬﾗｸﾀの向き
		player.pos = { 160,135 };								//ｷｬﾗｸﾀの地図上の座標
	}
	else if (GetMapDate() == STAGE_ID_ONI)
	{
		player.moveDir = DIR_RIGHT;								//ｷｬﾗｸﾀの向き
		player.pos = { 160,135 };								//ｷｬﾗｸﾀの地図上の座標
	}
	else if (GetMapDate() == STAGE_ID_KAPPA)
	{
		player.moveDir = DIR_RIGHT;								//ｷｬﾗｸﾀの向き
		player.pos = { 160,135 };								//ｷｬﾗｸﾀの地図上の座標
	}
	return true;
}