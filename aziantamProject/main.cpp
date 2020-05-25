#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "effect.h"
#include "player.h"
#include "enemy.h"
#include "shot.h"
#include "item.h"
#include "stage.h"

//-----変数
//ｼｰﾝ関連
SCENE SceneID;
SCENE ScenePreID;	//過去のｼｰﾝ格納用
int SceneCounter;



//PAUSE
bool paseFlag;
bool iventFlag;

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
	//ﾌﾟﾚｲﾔｰ
	PlayerSystemInit();
	//敵mob
	EnemySystemInit();
	//ｱｲﾃﾑ
	ItemSystmeInit();
	//-----ｸﾞﾗﾌｨｯｸ登録


	//-----変数の初期化
	//ｼｰﾝ関連
	SceneCounter = 0;
	SceneID = SCENE_INIT;
	ScenePreID = SCENE_MAX;
	//PAUSE
	pauseFlag = false;
	//ｲﾍﾞﾝﾄリ
	iventFlag = false;
	
	
	return true;
}
//初期化ｼｰﾝ
void InitScene(void)
{
	//-----各ｵﾌﾞｼﾞｪｸﾄ処理
	PlayerGameInit();				//	プレイヤー
	EnemyGameInit();				//	敵
	ItemGameInit();					//	ｱｲﾃﾑ
	

	//-----ｼｰﾝ遷移
	SceneID = SCENE_TITLE;
}




/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//ﾀｲﾄﾙｼｰﾝ
void TitleScene(void)
{
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
	//ｼｰﾝ遷移
	if (KeyDownTrigger[KEY_ID_SPACE]) SceneID = SCENE_GAMEOVER;



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
		PlayerControl();		//　ﾌﾟﾚｲﾔｰ
		EnemyControl();			//	敵
		ItemControl();			//	ｱｲﾃﾑ
	}

	
	//-----描画
	GameDraw(); 
}


//ｹﾞｰﾑの描画
void GameDraw(void)
{

	//-----各ｵﾌﾞｼﾞｪｸﾄ描画処理
	PlayerGameDraw();			//ﾌﾟﾚｲﾔｰ
	EnemyGameDraw();			//敵
	ItemGameDraw();				//ｱｲﾃﾑ
	//-----ｲﾍﾞﾝﾄﾘ関連
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
		SetDrawBright(255, 255, 255);
		DrawBox(100, 100, 700, 600, 0x222222, true);
	}
	
	//-----情報処理
	DrawFormatString(0, 0, 0xFFFFFF, "Game:%d", SceneCounter);

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
