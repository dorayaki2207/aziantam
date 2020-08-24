



#include "DxLib.h"
#include "stdio.h"
#include "test.h"
#include "KeyCheck.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Shot.h"
#include "Battle.h"


//-----外部変数宣言
int SceneCounter;			//	gameLoop動作確認用
SCENE_ID sceneID;
SCENE_ID preSceneID;
//PAUSE
int pCnt;
bool pauseFlag;
bool iventFlag;
int keyImage;

//当たり判定用
XY playerSize;

//会話システム
const char *file;
char words[200];



//-----WinMain
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//-----初期化処理
	if (!SystemInit()) return -1;


	//-----ｹﾞｰﾑﾙｰﾌﾟ
	while (ProcessMessage() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		ClsDrawScreen();

		//-----ｷｰの状態取得
		KeyCheck();


		//-----ｼｰﾝｶｳﾝﾀ初期化
		if (sceneID != preSceneID)
		{
			SceneCounter = 0;
			preSceneID = sceneID;
		}

		//-----ｼｰﾝ選択
		switch (sceneID)
		{
			//ｼｰﾝ初期化
		case SCENE_ID_INIT:
			InitScene();
			break;
		
			//ﾀｲﾄﾙｼｰﾝ
		case SCENE_ID_TITLE:
			TitleScene();
			break;

			//ｹﾞｰﾑｼｰﾝ
		case SCENE_ID_GAME:
			GameScene();
			break;
			
			//ﾎﾞｽ戦ﾊﾞﾄﾙｼｰﾝ
		case SCENE_ID_BATTLE:
			BattleScene();
			break;

		default:
			return -1;
			break;
		}

		SceneCounter++;
		ScreenFlip();
	}


	DxLib_End();
	return 0;
}

bool SystemInit(void)
{
	bool retFlag = true;

	//-----ｼｽﾃﾑ処理
	SetWindowText("1916004_ishibashi");							//	ﾀｲﾄﾙ

	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);				//	65536色ﾓｰﾄﾞに設定
	ChangeWindowMode(true);										//	true : window, false : ﾌﾙｽｸﾘｰﾝ
	if (DxLib_Init() == -1)
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);


	//-----入力情報初期化
	KeyInit();
	//-----各ｵﾌﾞｼﾞｪｸﾄの初期化
	StageSystemInit();			//ｽﾃｰｼﾞ
	PlayerSystemInit();			//ﾌﾟﾚｲﾔｰ
	EnemySystemInit();			//ｴﾈﾐｰ
	ItemSystemInit();			//ｱｲﾃﾑ
	ShotSystemInit();			//ｼｮｯﾄ
	BattleSystemInit();			//ﾊﾞﾄﾙ

	//-----ｸﾞﾗﾌｨｯｸ登録
	keyImage = LoadGraph("aitem/図2.png");


	//-----変数の初期化
	SceneCounter = 0;
	sceneID = SCENE_ID_INIT;
	preSceneID = SCENE_ID_MAX;

	//ｲﾍﾞﾝﾄﾘ関連
	pCnt = 0;
	iventFlag = false;
	
	//PAUSE機能
	pauseFlag = false;
	
	//当たり判定用
	playerSize = { 20,20 };
	


	file = "dafafile.txt";

	return retFlag;
}


void InitScene(void)
{
	//-----各ｵﾌﾞｼﾞｪｸﾄ処理
	StageGameInit();		//ｽﾃｰｼﾞ
	ItemGameInit();			//ｱｲﾃﾑ
	PlayerGameInit();		//ﾌﾟﾚｲﾔｰ
	EnemyGameInit();		//ｴﾈﾐｰ
	ShotGameInit();			//ｼｮｯﾄ
	BattleGameInit();		//ﾊﾞﾄﾙ

	
	sceneID = SCENE_ID_GAME;
}

//-----ﾀｲﾄﾙｼｰﾝ
void TitleScene()
{

	if (keyDownTrigger[KEY_ID_SPACE])
	{
		sceneID = SCENE_ID_GAME;
	}

	DrawFormatString(0, 0, 0xFFFFFF, "Title:%d", SceneCounter);
}

//-----ｹﾞｰﾑｼｰﾝ
void GameScene()
{
	XY playerPos;


	if (keyDownTrigger[KEY_ID_SPACE])
	{
		sceneID = SCENE_ID_BATTLE;
	}


	//-----FILE操作
//	FILE *fp;
//	
//	fopen_s(&fp, file, "r");
//	fread(words, sizeof(words), size_t(2), fp);
//	fclose(fp);


	//-----ｲﾍﾞﾝﾄﾘ機能
	//ｷｰ処理
	if (keyDownTrigger[KEY_ID_IVENT]) iventFlag = !iventFlag;
	//ﾌﾗｸﾞ処理
	if (iventFlag)
	{
		SetDrawBright(128, 128, 128);
		pauseFlag = false;
	}

	//-----POSE機能
	if (keyDownTrigger[KEY_ID_PAUSE]) pauseFlag = !pauseFlag;
	if (pauseFlag)
	{
		SetDrawBright(128, 128, 128);
		iventFlag = false;
	}


	//通常時動作
	if (!iventFlag && !pauseFlag)
	{
		//各種機能
		pCnt++;

		playerPos = PlayerControl();
		EnemyControl(playerPos);
		ShotControl(playerPos);
		itemDropControl();
		
		if (GetEvent(playerPos) == EVENT_ID_DOKUTU)
		{
			SetMapData(STAGE_ID_ONI2);
		}
		if (GetEvent(playerPos) == EVENT_ID_KAIDAN2)
		{
			//鬼ステージ①の祭壇に移動させる
			SetMapData(STAGE_ID_ONI);
		//	GetPos(playerPos);
		
		}


		//弾とｴﾈﾐｰの当たり判定
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


	//ｹﾞｰﾑｼｰﾝ描画
	GameDraw();
	

}

//-----ｹﾞｰﾑｼｰﾝ描画処理
void GameDraw()
{
	//-----各ｵﾌﾞｼﾞｪｸﾄ描画処理
	StageGameDraw();			//ｽﾃｰｼﾞ
	ItemGameDraw();				//ｱｲﾃﾑ
	PlayerGameDraw();			//ﾌﾟﾚｲﾔｰ
	ShotGameDraw();				//ｼｮｯﾄ
	EnemyGameDraw();			//ｴﾈﾐｰ
	
	//-----情報処理
	DrawFormatString(0, 0, 0xFFFFFF, "GameMain : %d", SceneCounter);
//	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0x55FF55, true);
	
	

	DrawFormatString(0, 24, 0xFFFFFF, "pCnt : %d", pCnt);
	//-----ｲﾝﾍﾞﾝﾄﾘ関連
	if (iventFlag)
	{
		SetDrawBright(255, 255, 255);
		DrawBox(100, 100, 700, 600, 0xFFFFFF, true);
//		DrawString((SCREEN_SIZE_X - 9 * 8) / 2, (SCREEN_SIZE_Y - 16) / 2, "PAUSE", 0xFFFFFF);
		
		//御札
		ItemI_Draw();

	}
	//-----PAUSE関連		
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



	if (!iventFlag && !pauseFlag)
	{

		//ｲﾍﾞﾝﾄﾘかﾎﾟｰｽﾞ機能が使用されているときは表示されない
		DrawFormatString(0, 32, 0xFFFFFF, "%s\n", words);

		DrawFormatString(0, 215, 0xFF22FF, "%d", itemF[MAGIC_TYPE_FIRE].point);
		DrawFormatString(0, 230, 0xFF22FF, "%d", itemF[MAGIC_TYPE_WATER].point);
		DrawFormatString(0, 245, 0xFF22FF, "%d", itemF[MAGIC_TYPE_WIND].point);
		DrawFormatString(0, 260, 0xFF22FF, "%d", itemF[MAGIC_TYPE_HEAL].point);


	}


}



