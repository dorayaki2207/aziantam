#include "DxLib.h"
#include "test.h"
#include "KeyCheck.h"
#include "Player.h"

//-----外部変数宣言
//ｷｬﾗｸﾀ関連
CHARACTER player;							//	ﾌﾟﾚｲﾔｰ変数格納用
int playerImage[DIR_MAX][PLAYER_MAX];		//	ﾌﾟﾚｲﾔｰ画像：通常時
bool hitFlag;								//	攻撃を受けたかどうか　true :攻撃を受けている


void PlayerSystmeInit(void)
{
	//-----変数の初期化
	player.moveDir = DIR_DOWN;											//	ｷｬﾗｸﾀの向き
	player.size = { 32,32 };											//	ｷｬﾗｸﾀの画像ｻｲｽﾞ
	player.offsetSize = { player.size.x / 2,player.size.y / 2 };		//　ｷｬﾗｸﾀのｵﾌｾｯﾄ
	player.moveSpeed = 4;												//	ｷｬﾗｸﾀの移動ｽﾋﾟｰﾄﾞ
	hitFlag = false;

	//-----ｸﾞﾗﾌｨｯｸの登録
	//ｷｬﾗｸﾀ関連
	LoadDivGraph("aitem/妖狐.png", DIR_MAX*PLAYER_MAX
		, DIR_MAX, PLAYER_MAX, player.size.x, player.size.y, playerImage[0], true);
}

void PlayerGameInit(void)
{
	player.pos = { SCREEN_SIZE_X / 2,SCREEN_SIZE_Y / 2 };				//　ｷｬﾗｸﾀの地図上の座標
	player.lifeMax = 150;												//	ｷｬﾗｸﾀの体力最大値
	player.life = player.lifeMax;										//	ｷｬﾗｸﾀの体力
	player.animCnt = 0;													//	ｷｬﾗｸﾀのｱﾆﾒｰｼｮﾝ

}

XY PlayerControl(void)
{
	bool movedFlag = false;			//　操作されているか判断する
	XY returnValue = player.pos;		// 関数の戻り値格納領域

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
			case DIR_RIGHT:			//	右
				player.pos.x += player.moveSpeed;
				break;

			case DIR_LEFT:			//	左
				player.pos.x -= player.moveSpeed;
				break;

			case DIR_UP:			//	上
				player.pos.y -= player.moveSpeed;
				break;

			case DIR_DOWN:			//	下
				player.pos.y += player.moveSpeed;
				break;

			default:
				break;
			}

		}
	}
	return returnValue;
}

void PlayerGameDraw(void)
{
	//ﾌﾟﾚｲﾔｰの各種値を変更する
	player.animCnt++;
	if (player.life > 0)
	{
		//-----画像描画
		//攻撃を受けていなければ
		if (!hitFlag)
		{
			DrawGraph(player.pos.x - player.offsetSize.x
				, player.pos.y - player.offsetSize.y
				, playerImage[player.moveDir][((player.animCnt / 40) % 4)]
				, true);
		}
	}

}

