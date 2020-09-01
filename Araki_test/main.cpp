#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "effect.h"
#include "stage.h"
#include "player.h"
#include "enemy.h"
#include "shot.h"
#include "item.h"
#include <time.h>


//-----変数
//ｼｰﾝ関連
SCENE SceneID;
SCENE ScenePreID;	//過去のｼｰﾝ格納用
int SceneCounter;
int GameOverCnt;

//ｲﾝﾍﾞﾝﾄﾘ関連
bool iventFlag;

//PAUSE関連
bool paseFlag;
int keyImage;

MSG_TYPE msgType;
int titleCounter;

int msgImage[MSG_MAX];
bool msgCheck[MSG_MAX];
bool msgFlag;
int msgCnt;
int rogoImage;
int bgImage;
int msgID;

//当たり判定用
XY playerSize;

//ｴﾝﾃﾞｨﾝｸﾞ関連
int clearImage;
int overImage;

//Win関数
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{

	if (!SystemInit()) return -1;

	//-----ｹﾞｰﾑﾙｰﾌﾟ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//keyの情報取得
		KeyCheck();

		//ｼｰﾝｶｳﾝﾄﾘｾｯﾄ
		if (SceneID != ScenePreID)
		{
			ScenePreID = SceneID;
			SceneCounter = 0;
		}
		//-----画面描画処理
		ClsDrawScreen();	//画面消去
		//ｼｰﾝ選択
		switch (SceneID)
		{
		case SCENE_INIT:
			InitScene();
			break;
		//ﾀｲﾄﾙｼｰﾝ
		case SCENE_TITLE:
			TitleScene();
			break;
		//ｹﾞｰﾑｼｰﾝ
		case SCENE_GAME:
			GameScene();
			break;
		//ｹﾞｰﾑｵｰﾊﾞｰｼｰﾝ
		case SCENE_GAMEOVER:
			GameOverScene();
			break;
		default:
			return -1;
			break;
		}
		SceneCounter++;		
		ScreenFlip();		//裏画面を表画面に瞬間ｺﾋﾟｰ
	}
	
	DxLib_End();			//DXﾗｲﾌﾞﾗﾘの終了処理
	return 0;				//このﾌﾟﾛｸﾞﾗﾑの終了

}
//ｼｽﾃﾑの初期化
bool SystemInit(void)
{

	//--------ｼｽﾃﾑ処理
	SetWindowText("月夜～三つの神宝～");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1) return false;
	SetDrawScreen(DX_SCREEN_BACK);
	
	
	//-----key情報の初期化
	KeyInit();

	//-----各ﾓｼﾞｭｰﾙの初期化
	StageSystemInit();			//ｽﾃｰｼﾞ
	PlayerSystemInit();			//ﾌﾟﾚｲﾔｰ
	EnemySystemInit();			//敵mob
	ItemSystmeInit();			//ｱｲﾃﾑ
	ShotSystemInit();			//ｼｮｯﾄ
	
	//-----ｸﾞﾗﾌｨｯｸ登録
	keyImage = LoadGraph("item/操作説明.png");
	rogoImage = LoadGraph("item/rogo_.png");
	bgImage = LoadGraph("item/bg.png");
	clearImage = LoadGraph("item/clear.png");
	overImage = LoadGraph("item/over.png");
	LoadDivGraph(("item/msg.png"), MSG_MAX, 1, MSG_MAX, 400, 100, msgImage);


	//-----変数の初期化
	//ｼｰﾝ関連
	SceneCounter = 0;
	GameOverCnt = 0;
	SceneID = SCENE_INIT;
	ScenePreID = SCENE_MAX;
	//PAUSE
	pauseFlag = false;
	//ｲﾝﾍﾞﾝﾄリ
	iventFlag = false;
	
	msgType = MSG_START;
	msgFlag = 0;
	for (int m = 0; m < MSG_MAX; m++)
	{
		msgCheck[m] = 0;
	}
	msgCnt = 0;
	titleCounter = 0;
	msgID = 0;
	playerSize = { 20,20 };

	return true;
}
//初期化ｼｰﾝ
void InitScene(void)
{
	//-----各ｵﾌﾞｼﾞｪｸﾄ処理
	StageGameInit();				//ｽﾃｰｼﾞ
	PlayerGameInit();				//ﾌﾟﾚｲﾔｰ
	EnemyGameInit();				//敵
	ItemGameInit();					//ｱｲﾃﾑ
	ShotGameInit();					//ｼｮｯﾄ

	//-----ｼｰﾝ遷移
	SceneID = SCENE_TITLE;
}




/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//ﾀｲﾄﾙｼｰﾝ
void TitleScene(void)
{
	titleCounter++;

	if (msgType == MSG_START)
	{
		//-----ｼｰﾝ遷移
		if (KeyDownTrigger[KEY_ID_SPACE]) SceneID = SCENE_GAME;
	}
	else if (msgType == MSG_LOAD)
	{
		if (KeyDownTrigger[KEY_ID_SPACE]) msgFlag = true;
		if ((msgCnt > 250) || KeyDownTrigger[KEY_ID_ENTER])
		{
			msgCnt = 0;
			msgFlag = false;
		}
	}

	

	//-----描画
	TitleDraw();

}
//ﾀｲﾄﾙの描画
void TitleDraw(void)
{
	for (int i = 0; i < MSG_MAX; i++)
	{
		if (!msgCheck[i])
		{
			switch (msgType)
			{
			case MSG_START:
				msgCheck[MSG_START] = true;
				msgCheck[MSG_LOAD] = false;
				break;
			case MSG_LOAD:
				msgCheck[MSG_LOAD] = true;
				msgCheck[MSG_START] = false;
				break;
			case MSG_MAX:
				break;
			default:
				break;
			}
		}
	}

	if (KeyDownTrigger[KEY_ID_UP])
	{
		msgID--;
		if (msgID < 0) msgID = MSG_MAX - 1;
		//	msgType = MSG_START;
	}

	if (KeyDownTrigger[KEY_ID_DOWN])
	{
		msgID++;
		if (msgID > MSG_MAX - 1) msgID = 0;
	}

	if (msgID == 0)
	{
		msgType = MSG_START;
	}
	else if (msgID == 1)
	{
		msgType = MSG_LOAD;
	}

	//-----描画処理
	DrawGraph(0, 0, bgImage, true);
	DrawGraph((SCREEN_SIZE_X - 400) / 2, 10, rogoImage, true);

	for (int i = 0; i < MSG_MAX; i++)							//ﾒｯｾｰｼﾞ
	{
		//選択時
		if (msgCheck[i])
		{
			if (msgType == MSG_START)
			{
				if ((titleCounter / 30) % 2 == 0)
				{
					DrawGraph((SCREEN_SIZE_X - 400) / 2, 400, msgImage[MSG_START], true);
				}

			}
			else if (msgType == MSG_LOAD)
			{
				if ((titleCounter / 30) % 2 == 0)
				{
					DrawGraph((SCREEN_SIZE_X - 400) / 2, 500, msgImage[MSG_LOAD], true);

				}
			}
		}
		//未選択時
		else
		{
			DrawGraph((SCREEN_SIZE_X - 400) / 2, 400 + 100 * i, msgImage[i], true);
		}
	}

	//つづきからする、を選択した時のﾒｯｾｰｼﾞ
	if (msgFlag)
	{
		msgCnt++;
		DrawBox(250, 200, 550, 450, 0xFFFFFF, true);
		SetFontSize(16);
		DrawString(295, 240,
			"　　 　　※※※\nセーブデータが存在しません\n\n　　＜はじめかする＞\n\n  を選び始めてください",
			0x000000);
		SetFontSize(12);
		DrawString(255, 410, "※この画面はENTER KEY\n　又は、時間経過で閉じます", 0x000000);
	}

	//-----情報処理
	DrawFormatString(0, 0, 0xFFFFFF, "Title:%d", SceneCounter);

}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//ｹﾞｰﾑｼｰﾝ
void GameScene(void)
{
	XY playerPos;		//ﾌﾟﾚｲﾔｰの座標格納領域

	//ｼｰﾝ遷移
	if (KeyDownTrigger[KEY_ID_SPACE]) fadeOut = true;

	/*if (playerDead())
	{
		GameOverCnt++;
		if (GameOverCnt > 100)
		{
			SceneID = SCENE_GAMEOVER;
			GameOverCnt = 0;
		}
	}*/
	// ゲームオーバー
	//////////////////////////////////
	/*if (GameOverSet())
	{
		GameOverCnt++;
		if (GameOverCnt > 100)
		{
			SceneID = SCENE_GAMEOVER;
			GameOverCnt = 0;
		}
	}*/
	/////////////////////////////////
	//-----ｲﾍﾞﾝﾄﾘ機能
	//ｷｰ処理
	if (KeyDownTrigger[KEY_ID_IVENT]) iventFlag = !iventFlag;
	//ﾌﾗｸﾞ処理
	if (iventFlag)
	{
		SetDrawBright(128, 128, 128);
		pauseFlag = false;
	}

	//-----PAUSE機能
	if (KeyDownTrigger[KEY_ID_PAUSE]) pauseFlag = !pauseFlag;
	if (pauseFlag)
	{
		SetDrawBright(128, 128, 128);
		iventFlag = false;
	}

	//通常時操作
	if(!iventFlag && !pauseFlag)
	{
		//各種機能
		//-----各ｵﾌﾞｼﾞｪｸﾄ操作
		playerPos = PlayerControl();		//ﾌﾟﾚｲﾔｰ
		EnemyControl(playerPos);			//ｴﾈﾐｰ
		ItemControl();						//ｱｲﾃﾑ
		ShotControl(playerPos);				//ｼｮｯﾄ

		// イベント処理
		if (GetEvent(playerPos) == EVENT_ID_KAIDAN)
		{
			SetMapData(STAGE_ID_MOB);
		}

		//ｴﾈﾐｰと弾の当たり判定
		for (int sh = 0; sh < SHOT_MAX; sh++)
		{
			if (shot[sh].life > 0)
			{
				if (EnemyHitCheck(shot[sh].pos, shot[sh].size.x))
				{
					DeleteShot(sh);
				}
			}
		}
		//アイテムとプレイヤーの当たり判定
		if (ItemHitCheck(playerPos, playerSize.x))
		{
			//ｱｲﾃﾑに当たっている
			DeleteItem();
		}
	}


	//-----描画
	GameDraw(); 

	return;
}


//ｹﾞｰﾑの描画
void GameDraw(void)
{

	//-----各ｵﾌﾞｼﾞｪｸﾄ描画処理
	StageGameDraw();			//ｽﾃｰｼﾞ
	PlayerGameDraw();			//ﾌﾟﾚｲﾔｰ
	EnemyGameDraw();			//敵
	ItemGameDraw();				//ｱｲﾃﾑ
	ShotGameDraw();				//ｼｮｯﾄ
	//-----ｲﾝﾍﾞﾝﾄﾘ関連
	if (iventFlag)
	{
		SetDrawBright(255, 255, 255);
		DrawBox(100, 100, 700, 600, 0xFFFFFF, true);
		//御札
		ItemI_Draw();

	}
	//----PAUSE関連
	if (pauseFlag)
	{
		SetDrawBright(255, 255, 255);									//	暗くする
		DrawBox(50, 50, 750, 600, 0x222222, true);						//	枠
		DrawGraph((SCREEN_SIZE_X - 650) / 2, 180, keyImage, true);		//	ｲﾗｽﾄ
		DrawString(100, 100, "KEY操作説明", 0xFFFFFF, true);			//	ｺﾒﾝﾄ
		DrawString(99, 110, "------------", 0xFFFFFF, true);			//	ｺﾒﾝﾄ下線

		DrawString(150, 430, "Z : 火の攻撃", 0xFFFFFF, true);
		DrawString(150, 460, "X : 水の攻撃", 0xFFFFFF, true);
		DrawString(150, 490, "C : 風の攻撃", 0xFFFFFF, true);
		DrawString(150, 520, "V : 回復", 0xFFFFFF, true);
		DrawString(400, 430, "M : メニュー画面", 0xFFFFFF, true);
		DrawString(400, 460, "I : アイテムメニュー", 0xFFFFFF, true);

	}
	
	//-----情報処理
	DrawFormatString(0, 0, 0xFFFFFF, "Game:%d", SceneCounter);
	DrawFormatString(0, 120, 0xFFFFFF, "map:%d,%d", mapPos.x,mapPos.y);
	//DrawFormatString(0, 140, 0xFFFFFF, "GameOver:%d", GameOverCnt);
}





//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//ｹﾞｰﾑｵｰﾊﾞｰｼｰﾝ
void GameOverScene(void)
{
	if (KeyDownTrigger[KEY_ID_SPACE]) SceneID = SCENE_INIT;


	GameOverDraw();
}


//ｹﾞｰﾑｵｰﾊﾞｰの描画
void GameOverDraw(void)
{
	//-----描画処理
	DrawGraph((SCREEN_SIZE_X - 400) / 2, (SCREEN_SIZE_Y - 200) / 2, overImage, true);

	//-----情報処理
	DrawFormatString(0, 0, 0xFFFFFF, "GameOver:%d", SceneCounter);


}

//ｹﾞｰﾑｸﾘｱｼｰﾝ
void GameClearScene(void)
{
	if (KeyDownTrigger[KEY_ID_SPACE]) SceneID = SCENE_INIT;

	GameClearDraw();
}

//ｹﾞｰﾑｸﾘｱの描画
void GameClearDraw(void)
{
	//-----描画処理
	DrawGraph((SCREEN_SIZE_X - 400) / 2, (SCREEN_SIZE_Y - 200) / 2, clearImage, true);


	//-----情報処理
	DrawFormatString(0, 0, 0xFFFFFF, "GameClear:%d", SceneCounter);


}

