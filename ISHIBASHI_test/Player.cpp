#include <DxLib.h>
#include "test.h"
#include "KeyCheck.h"
#include "Stage.h"
#include "Player.h"
#include "Item.h"
#include "Shot.h"
#include "Enemy.h"

//-----外部変数宣言
//ｷｬﾗｸﾀ関連
CHARACTER player;							//	ﾌﾟﾚｲﾔｰ変数格納用
int playerImage[DIR_MAX][PLAYER_MAX];		//	ﾌﾟﾚｲﾔｰ画像：通常時

int lifeCheckCnt;
//int testImage[4];
//int test2Image[4];

void PlayerSystemInit(void)
{
	//-----変数の初期化
	player.moveDir = DIR_DOWN;											//	ｷｬﾗｸﾀの向き
	player.size = { 40,50 };											//	ｷｬﾗｸﾀの画像ｻｲｽﾞ
	player.offsetSize = { player.size.x / 2,player.size.y / 2 };		//　ｷｬﾗｸﾀのｵﾌｾｯﾄ
	player.moveSpeed = 4;												//	ｷｬﾗｸﾀの移動ｽﾋﾟｰﾄﾞ
	player.hitFlag = false;

	//-----ｸﾞﾗﾌｨｯｸの登録
	//ｷｬﾗｸﾀ関連
	LoadDivGraph("aitem/bossDT3.png", DIR_MAX*PLAYER_MAX
		, DIR_MAX, PLAYER_MAX, player.size.x, player.size.y, playerImage[0], true);


//	LoadDivGraph("aitem/hard.png", 4, 4, 1, 32, 40, testImage);
//	LoadDivGraph("aitem/bb.png", 4, 4, 1, 32, 40, test2Image);
}

void PlayerGameInit(void)
{
	player.pos = { 150,150};										//　ｷｬﾗｸﾀの地図上の座標
	player.lifeMax = 150;												//	ｷｬﾗｸﾀの体力最大値
	player.life = player.lifeMax;										//	ｷｬﾗｸﾀの体力
	player.animCnt = 0;												//	ｷｬﾗｸﾀのｱﾆﾒｰｼｮﾝ
	lifeCheckCnt = 0;
}

XY PlayerControl(void)
{
	bool movedFlag = false;			//　操作されているか判断する
	XY returnValue = player.pos;		// 関数の戻り値格納領域
	XY playerPosCopy = player.pos;
	XY playerPosOffset = playerPosCopy;
	XY indexPos;						//ﾏｯﾌﾟ配列座標
										
	//ﾌﾟﾚｲﾔｰが生きているとき
	if (player.life > 0)
	{

		
		//-----移動処理
		if (keyNew[KEY_ID_RIGHT])
		{
			movedFlag = true;
			player.moveDir = DIR_RIGHT;
		}
		if (keyNew[KEY_ID_LEFT])
		{
			movedFlag = true;
			player.moveDir = DIR_LEFT;
		}
		if (keyNew[KEY_ID_UP])
		{
			movedFlag = true;
			player.moveDir = DIR_UP;
		}
		if (keyNew[KEY_ID_DOWN])
		{
			movedFlag = true;
			player.moveDir = DIR_DOWN;
		}

		//ﾌﾟﾚｲﾔｰの向き
		if (movedFlag)
		{
			//ﾌﾟﾚｲﾔｰの各種値を変更する
			player.animCnt += 5;


			switch (player.moveDir)
			{
				//右
			case DIR_RIGHT:			
				playerPosCopy.x += player.moveSpeed;
				playerPosOffset.x = playerPosCopy.x/* + player.offsetSize.x*/+7;
				indexPos = PosToIndex(playerPosCopy);
				//指定した場所を通過可能かどうか
				if (IsPass(playerPosOffset))
				{
					player.pos = playerPosCopy;
					//ｽｸﾛｰﾙ処理
					if (player.pos.x + mapPos.x > SCROLL_X_MAX)
					{
						mapPos.x -= player.moveSpeed;
					}
				}
				break;

				//左
			case DIR_LEFT:	
				playerPosCopy.x -= player.moveSpeed;
				playerPosOffset.x = playerPosCopy.x /*- player.offsetSize.x*/-10;
				indexPos = PosToIndex(playerPosCopy);
				//指定した場所を通過可能かどうか
				if (IsPass(playerPosOffset))
				{
					player.pos = playerPosCopy;
					//ｽｸﾛｰﾙ処理
					if (player.pos.x + mapPos.x < SCROLL_X_MIN)
					{
						mapPos.x += player.moveSpeed;
					}
				}
				break;

				//上
			case DIR_UP:	
				playerPosCopy.y -= player.moveSpeed;
				playerPosOffset.y = playerPosCopy.y/* - player.offsetSize.y*/;
				indexPos = PosToIndex(playerPosCopy);
				//指定した場所を通過可能かどうか
				if (IsPass(playerPosOffset))
				{
					player.pos = playerPosCopy;
					//ｽｸﾛｰﾙ処理
					if (player.pos.y + mapPos.y < SCROLL_Y_MIN)
					{
						mapPos.y += player.moveSpeed;
					}
				}
				break;

				//下
			case DIR_DOWN:
				playerPosCopy.y += player.moveSpeed;
				playerPosOffset.y = playerPosCopy.y + player.offsetSize.y;
				indexPos = PosToIndex(playerPosCopy);
				//指定した場所を通過可能かどうか
				if (IsPass(playerPosOffset))
				{
					player.pos = playerPosCopy;
					if (player.pos.y + mapPos.y > SCROLL_Y_MAX)
					{
						mapPos.y -= player.moveSpeed;
					}
				}
				break;

			case DIR_MAX:
				break;
			default:
				break;
			}
			//戻り値を設定
			returnValue = player.pos;

		}


		//-----ｼｮｯﾄ処理
		if (keyNew[KEY_ID_FIRE])
		{
			CreateShot(player.pos, player.moveDir, MAGIC_TYPE_FIRE);
		}
		if (keyNew[KEY_ID_WATER])
		{
			CreateShot(player.pos, player.moveDir, MAGIC_TYPE_WATER);
		}
		if (keyNew[KEY_ID_WIND])
		{
			CreateShot(player.pos, player.moveDir, MAGIC_TYPE_WIND);
		}
		if (keyNew[KEY_ID_HEAL])
		{
			CreateShot(player.pos, player.moveDir, MAGIC_TYPE_HEAL);
		}
		

		MapRange();
		//　移動範囲処理
		//ﾏｯﾌﾟﾁｯﾌﾟの当たり判定を実装していない為、一時的処置
	//	if (player.pos.x > CHIP_SIZE_X * mapSize.x - player.offsetSize.x) player.pos.x = CHIP_SIZE_X * mapSize.x - player.offsetSize.x;     //右制御
	//	if (player.pos.x < player.offsetSize.x) player.pos.x = player.offsetSize.x;													//左制御
	//	if (player.pos.y > CHIP_SIZE_Y * mapSize.y - player.offsetSize.y) player.pos.y = CHIP_SIZE_Y * mapSize.y - player.offsetSize.y;		//下制御
	//	if (player.pos.y < player.offsetSize.y) player.pos.y = player.offsetSize.y;													//上制御

		if (PlayerHitCheck(player.pos, player.size.x))
		{
			if (lifeCheckCnt == 0)
			{
				player.life--;
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
	}



	return returnValue;
}

//-----ﾌﾟﾚｲﾔｰの描画処理
void PlayerGameDraw(void)
{
	//-----画像描画
	if (player.life > 0)
	{
		//ﾌﾟﾚｲﾔｰの各種値を変更する
		player.animCnt++;

		//攻撃を受けていなければ
		if (!player.hitFlag)
		{
			DrawGraph(player.pos.x - player.offsetSize.x + mapPos.x
				, player.pos.y - player.offsetSize.y + mapPos.y
				, playerImage[player.moveDir][((player.animCnt / 40) % 4)]
				, true);
		}
	}


	// ｽｸﾛｰﾙ制限の枠
	DrawBox(SCROLL_X_MIN
		, SCROLL_Y_MIN
		, (SCROLL_X_MAX + 1)
		, (SCROLL_Y_MAX + 1)
		, 0x55FF22, false);

	//情報処理
	DrawFormatString(0, 180, 0xFFFFFF, "playerPos:%d,%d", player.pos.x, player.pos.y);
	DrawFormatString(0, 300, 0xFFFFFF, "playerHp%d", player.life);
	DrawFormatString(0, 350, 0xffffff, "LifeCheck:%d", lifeCheckCnt);

//	DrawGraph(100, 100, testImage[((player.animCnt / 20) % 4)], true);
//	DrawGraph(150, 100, test2Image[((player.animCnt / 20) % 4)], true);
}


