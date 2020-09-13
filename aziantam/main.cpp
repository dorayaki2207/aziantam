// タイトルシーン　セレクト途中:石橋
//攻撃お札が全て0枚になったら終了。

#include <DxLib.h>
#include "main.h"
#include "keycheck.h"
#include "title.h"
#include "effect.h"
#include "stage.h"
#include "player.h"
#include "enemy.h"
#include "shot.h"
#include "item.h"
#include "mark.h"


//-----変数
//ｼｰﾝ関連
SCENE SceneID;
SCENE ScenePreID;	//過去のｼｰﾝ格納用
int SceneCounter;
int GameOverCnt;
int GameClearCnt;
//ｲﾝﾍﾞﾝﾄﾘ関連
bool iventFlag;
int pIcon;
int magicH;
//PAUSE関連
bool pauseFlag;
int keyImage;

int setImage;
//当たり判定用
XY playerSize;

//ｴﾝﾃﾞｨﾝｸﾞ関連
int clearImage;
int overImage;
int clear_bgImage;
int over_bgImage;


//Win関数
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	if (!SystemInit())return -1;

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
		//ｹﾞｰﾑｸﾘｱｼｰﾝ
		case SCENE_CLEAR:
			GameClearScene();
			break;

		case SCENE_MAX:
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
	if (DxLib_Init() == -1)return false;
	SetDrawScreen(DX_SCREEN_BACK);
	
	//-----key情報の初期化
	KeyInit();

	//-----各ﾓｼﾞｭｰﾙの初期化
	TitleSystemInit();			//ﾀｲﾄﾙ
	StageSystemInit();			//ｽﾃｰｼﾞ
	PlayerSystemInit();			//ﾌﾟﾚｲﾔｰ
	EnemySystemInit();			//敵mob
	ItemSystmeInit();			//ｱｲﾃﾑ
	ShotSystemInit();			//ｼｮｯﾄ
	EffectSystemInit();			//ｴﾌｪｸﾄ
	MarkSystemInit();
	//-----ｸﾞﾗﾌｨｯｸ登録
	keyImage = LoadGraph("item/操作説明.png");
	pIcon = LoadGraph("char/icon.png");
	magicH = LoadGraph("char/type.png");
	clearImage = LoadGraph("item/clear.png");
	overImage = LoadGraph("item/over.png");
	clear_bgImage = LoadGraph("item/bg_clear.png");
	over_bgImage = LoadGraph("item/bg_over.png");
	setImage = LoadGraph("item/set.png");
	//-----変数の初期化
	//ｼｰﾝ関連
	SceneCounter = 0;
	GameOverCnt = 0;
	GameClearCnt = 0;
	SceneID = SCENE_INIT;
	ScenePreID = SCENE_MAX;
	//PAUSE
	pauseFlag = false;
	//ｲﾝﾍﾞﾝﾄリ
	iventFlag = false;
	//当たり判定用
	playerSize = { 20,20 };

	return true;
}
//初期化ｼｰﾝ
void InitScene(void)
{
	//-----各ｵﾌﾞｼﾞｪｸﾄ処理
	StageGameInit();				//ｽﾃｰｼﾞ
	PlayerGameInit();				//ﾌﾟﾚｲﾔｰ
	EnemyReGameInit();				//敵
//	EnemyBossGameInit();
	EFlagInit();					//eFlag専用
	ItemGameInit();					//ｱｲﾃﾑ
	ShotGameInit();					//ｼｮｯﾄ
	EffectGameInit();				//ｴﾌｪｸﾄ
	MarkReGameInit();
	MarkGameInit();
	//-----ｼｰﾝ遷移
	SceneID = SCENE_TITLE;
}




///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//ｹﾞｰﾑｼｰﾝ
void GameScene(void)
{
	XY playerPos;		//ﾌﾟﾚｲﾔｰの座標格納領域

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
		ItemDropControl();					//ｱｲﾃﾑ
		ShotControl(playerPos);			//ｼｮｯﾄ
		EffectControl();					//ｴﾌｪｸﾄ
		MarkControl();
		//ｴﾈﾐｰと弾の当たり判定
		for (int sh = 0; sh < SHOT_MAX; sh++)
		{
			if (shot[sh].life > 0)
			{
				if (EnemyHitCheck(shot[sh].pos, shot[sh].size.x, &shot[sh]))
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

		MapChange();

		//ｼｰﾝ遷移
	//	if (KeyDownTrigger[KEY_ID_SPACE]) SceneID = SCENE_CLEAR;
		if (/*(GameOverSet()) || */(PlayerDid()))
		{
			GameOverCnt++;
			if (GameOverCnt > 100)
			{
				SceneID = SCENE_GAMEOVER;
				GameOverCnt = 0;
			}
		}

		//すべてのenemyを倒した時の処理（true:クリアシーンに遷移、false:まだ倒せてない）
		if (SetEnemyMoment())
		{
			GameClearCnt++;
			if (GameClearCnt > 100)
			{
				SceneID = SCENE_CLEAR;
				GameClearCnt = 0;
			}
		}
	}

	
	

	//-----描画
	GameDraw(); 
}


//ｹﾞｰﾑの描画
void GameDraw(void)
{

	//-----各ｵﾌﾞｼﾞｪｸﾄ描画処理
	StageGameDraw();			//ｽﾃｰｼﾞ
	EnemyGameDraw();			//敵
	PlayerGameDraw();			//ﾌﾟﾚｲﾔｰ
	ItemGameDraw();				//ｱｲﾃﾑ
	ShotGameDraw();				//ｼｮｯﾄ
	EffectGameDraw();			//ｴﾌｪｸﾄ
	MarkGameDraw();

	DrawGraph(0, 0, setImage, true);
	DrawBox(0, 0, 320, 100, 0xffffff, false);
	
	ItemDraw();
	PlayerDraw();


	//-----ｲﾝﾍﾞﾝﾄﾘ関連
	if (iventFlag)
	{
		SetDrawBright(255, 255, 255);
		DrawBox(150, 120, 650, 520, 0xFFFFFF, true);
		//プレイヤー情報
		DrawBox(199, 149, 350 + 1, 300 + 1, 0xff22ff, false);
		DrawGraph(200, 150, pIcon, true);
		DrawGraph(200, 350, magicH, true);
		PlayerTextDraw();
		//御札
		DrawBox(400, 150, 600, 500, 0xff22ff, false);
		DrawFormatString(412, 180, 0xff22ff, "*---*　所持札　*---*",true);
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
	//DrawFormatString(0, 0, 0xFFFFFF, "Game:%d", SceneCounter);
//	DrawFormatString(0, 120, 0xFFFFFF, "map:%d,%d", mapPos.x,mapPos.y);
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
	DrawGraph(0, 0, over_bgImage, true);
	DrawGraph((SCREEN_SIZE_X - 400) / 2, (SCREEN_SIZE_Y - 200) / 3, overImage, true);

	//-----情報処理
//	DrawFormatString(0, 0, 0xFFFFFF, "GameOver:%d", SceneCounter);


}





//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
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
	DrawGraph(0, 0, clear_bgImage, true);
	DrawGraph((SCREEN_SIZE_X - 400) / 2, (SCREEN_SIZE_Y - 200) / 3, clearImage, true);


	//-----情報処理
//	DrawFormatString(0, 0, 0xFFFFFF, "GameClear:%d", SceneCounter);


}
