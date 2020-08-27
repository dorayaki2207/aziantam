#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "effect.h"
#include "stage.h"
#include "player.h"
#include "enemy.h"
#include "shot.h"
#include "item.h"


//-----変数
//ｼｰﾝ関連
SCENE SceneID;
SCENE ScenePreID;	//過去のｼｰﾝ格納用
int SceneCounter;

//ｲﾝﾍﾞﾝﾄﾘ関連
bool iventFlag;

//PAUSE関連
bool paseFlag;
int keyImage;

void char_disp(int White, int y)
{
	DrawString(150, y, "■", White);
	DrawString(170, 100, "NEW_GAME", White);
	DrawString(170, 120, "ONI", White);
	DrawString(170, 140, "TENGU", White);
	DrawString(170, 160, "KAPPA", White);
	DrawString(170, 200, "LOG_OUT", White);
}

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
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {}//エフェクト終了後処理
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					//エフェクト終了後処理
					SceneID = SCENE_GAME;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);

				}
			}
			TitleScene();
			break;
		//ｹﾞｰﾑｼｰﾝ
		case SCENE_GAME:
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {}//エフェクト終了後処理
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					//エフェクト終了後処理
					SceneID = SCENE_GAMEOVER;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);

				}
			}
			GameScene();
			break;
		//ｹﾞｰﾑｵｰﾊﾞｰｼｰﾝ
		case SCENE_GAMEOVER:
			if (fadeIn)
			{
				if (!FadeInScreen(5))
				{
					fadeOut = false;
				}//エフェクト終了後処理
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					//エフェクト終了後処理
					SceneID = SCENE_INIT;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);

				}
			}
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

	StageSystemInit();			//ｽﾃｰｼﾞ

	//-----変数の初期化
	//ｼｰﾝ関連
	SceneCounter = 0;
	SceneID = SCENE_INIT;
	ScenePreID = SCENE_MAX;
	//PAUSE
	pauseFlag = false;
	//ｲﾝﾍﾞﾝﾄリ
	iventFlag = false;
	
	
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
	int White = GetColor(255, 255, 255);
	int y = 100;

	char_disp(White, y);

	// メニュー項目要素
	MenuElement_t Menuelement[5] = {
		{350,150,"～ＧａｍｅＳｔａｒｔ～"},
	{350,200,"～おまけ～"},
	{350,250,"～Ｈｅｌｐ～"},
	{350,300,"～ゲーム終了～"},
	{350,350,"～ＬＡＮＫ～"},
	};
	int SelectNum = 0;

	// 
	if (KeyDownTrigger[KEY_ID_DOWN] == 1 || (KeyDownTrigger[KEY_ID_DOWN]%5 == 0 && KeyDownTrigger[KEY_ID_DOWN]>30))
	{
		y += 20;
		if (y == 260)
		{
			y = 100;
		}
		SelectNum = (SelectNum + 1) % 5;

		for (int i = 0; i < 5; i++)
		{
			if (i == SelectNum)
			{
				Menuelement[i].x = 80;
			}
			else
			{
				Menuelement[i].x = 100;
			}
		}
		//SceneID = SCENE_GAME;
	}

	// 
	for (int i = 0; i < 5; i++)
	{
		DrawFormatString(Menuelement[i].x-20, Menuelement[i].y, GetColor(255, 255, 255), Menuelement[i].name);
	}

	//-----ｼｰﾝ遷移
	if (KeyDownTrigger[KEY_ID_SPACE]) SceneID = SCENE_GAME;

	//-----描画
	TitleDraw();

}
//ﾀｲﾄﾙの描画
void TitleDraw(void)
{
	//-----描画処理

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


		////一時的処理
		//if (GetEvent(playerPos) == EVENT_ID_KAIDAN)
		//{
		//	stageID = STAGE_ID_START;
		//	SetMapData(STAGE_ID_MOB);
		//	mapPos.x = 0;
		//	mapPos.y = 0;
		//}
		//
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

	//-----情報処理
	DrawFormatString(0, 0, 0xFFFFFF, "GameOver:%d", SceneCounter);


}
