//-------------------------
// AsoulQuest = main.cpp
// 2019.09.26
// 山本美由紀
//-------------------------

#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "effect.h"
#include "stage.h"
#include "player.h"
#include "enemy.h"
#include "shot.h"

//定数
//---------------------------------------
#define DRAW_ORDER_MAX ENEMY_MAX + SHOT_MAX + 1	 //プレイヤー数が1

//定義
//----------------------------------------
//ｷｬﾗｸﾀ表示順管理用
struct  DRAW_ORDER
{
	CHARACTER_TYPE characterType;	//ｷｬﾗｸﾀの種類
	int index;						//ｷｬﾗｸﾀ配列の添え字
	int y;							//ｷｬﾗｸﾀの足元Y座標
};

//変数
//ｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰ
//ｼｽﾃﾑ関連
SCENE_ID SceneID;		//現在のｼｰﾝ格納用
SCENE_ID ScenePreID;	//過去のｼｰﾝ格納用
//int gameCounter;		//gameLoop動作確認用
int SceneCounter;		//ｼｰﾝ用のｶｳﾝﾀｰ
//ﾀｲﾄﾙ関連
int TitleImage;			//ﾀｲﾄﾙ画像格納用
int TitlePosX;			//
int TitlePosY;			//
//ｹﾞｰﾑｵｰﾊﾞｰ関連
int GameOverImage;		//ｹﾞｰﾑｵｰﾊﾞｰ画像格納用
int GameOverPosX;		//
int GameOverPosY;		//
//ﾋｯﾄｽﾀｰﾄｷｰ関連	
int HitStartKeyImage;	//ﾋｯﾄｽﾀｰﾄｷｰ画像格納用
int HitStartKeyPosX;	//
int HitStartKeyPosY;	//
//ﾌｧｲﾙ情報定義
char fileName[] = "asoulquest.dat";	//ﾌｧｲﾙの名前を定義
FILE_DATA fileData;					//得点管理用
//ｷｬﾗｸﾀの表示順
int drawOrderCnt;							//表示するｷｬﾗｸﾀ数
DRAW_ORDER drawOrDerList[DRAW_ORDER_MAX];	//表示するｷｬﾗｸﾀの表示順情報


//WinMain()
//ｰｰｰｰｰｰｰｰｰｰｰｰ
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//------初期化処理
	if (!SystemInit())
	{
		return -1;
	}
	//ｰｰｰｰｰｰｹﾞｰﾑﾙｰﾌﾟ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//ｼｰﾝｶｳﾝﾄﾘｾｯﾄ
		if (SceneID != ScenePreID)
		{
			ScenePreID = SceneID;
			SceneCounter = 0;
		}
		//表示順の初期化
		drawOrderCnt = 0;
		for (int d = 0; d < DRAW_ORDER_MAX; d++)
		{
			drawOrDerList[d].characterType = CHARACTER_MAX;
			drawOrDerList[d].index = 0;
			drawOrDerList[d].y = 0;
		}

		//入力情報の確認
		KeyCheck();

		ClsDrawScreen();	//画面消去
		
		//ｼｰﾝ選択
		//-----------------
		switch (SceneID)
		{
		//初期化
		case SCENE_ID_INIT:
			InitScene();
			SceneID = SCENE_ID_TITLE;
			break;
		//タイトル
		case SCENE_ID_TITLE:
			//画面切り替えエフェクト
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {}//エフェクト終了後の処理
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					//エフェクト終了後の処理
					SceneID = SCENE_ID_GAME;
					fadeIn = true;
				}
			}
			TitleScene();
			break;
		//ゲーム
		case SCENE_ID_GAME:
			//画面切り替えエフェクト
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {}//エフェクト終了後の処理
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					//エフェクト終了後の処理
					SceneID = SCENE_ID_GAMEOVER;
					fadeIn = true;
				}
			}
			GameScene();
			break;
		//ゲームオーバー
		case SCENE_ID_GAMEOVER:
			//画面切り替えエフェクト
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {}//エフェクト終了後の処理
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					//エフェクト終了後の処理
					SceneID = SCENE_ID_INIT;
					fadeIn = true;
				}
			}
			GameOverScene();
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
	//ｰｰｰｰｰｰｰｼｽﾃﾑ処理
	SetWindowText("191645_山本美由紀");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	//入力情報の初期化
	KeyInit();
	//エフェクトの初期化
	EffectInit();

	
	SetTransColor(255, 0, 255);
	StageSystemInit();	//ステージ情報の初期化
	PlayerSystemInit();	//ﾌﾟﾚｲﾔｰ情報の初期化
	EnemySystemInit();	//敵情報の初期化
	ShotSystemInit();	//弾情報の初期化
	//--------ｸﾞﾗﾌｨｯｸ登録------------------
	TitleImage = LoadGraph("bmp/title.bmp");
	GameOverImage = LoadGraph("bmp/gameover.png");
	HitStartKeyImage = LoadGraph("bmp/hitstartkey.png");
	
	
	
	//変数の初期化
	SceneCounter = 0;
	SceneID = SCENE_ID_INIT;
	ScenePreID = SCENE_ID_MAX;
	fadeIn = true;
	fileData.Score = 0;
	fileData.hiScore = 0;
	TitlePosX = (SCREEN_SIZE_X - TITLE_SIZE_X) /2;
	TitlePosY = (SCREEN_SIZE_Y - TITLE_SIZE_Y) /2;
	GameOverPosX = (SCREEN_SIZE_X - GAMEOVER_SIZE_X) /2;
	GameOverPosY = (SCREEN_SIZE_Y - GAMEOVER_SIZE_Y) /2;
	HitStartKeyPosX = (SCREEN_SIZE_X - HITSTARTKEY_SIZE_X) /2;
	HitStartKeyPosY = (SCREEN_SIZE_Y - HITSTARTKEY_SIZE_Y) /2 + (TITLE_SIZE_Y - HITSTARTKEY_SIZE_Y);
	
	return true;
}

//初期化ｼｰﾝ
void InitScene(void)
{
	StageGameInit();
	PlayerInit();	//
	EnemyGameInit();
	ShotGameInit();

}

//ﾀｲﾄﾙｼｰﾝ
void TitleScene(void)
{
	if (KeyDownTrigger[KEY_ID_SPACE])
	{
		//SceneID = SCENE_ID_GAME;
		fadeOut = true;
	}
	TitleDraw();
	
}
//引数を二つもち、引数で渡された値を足した結果を戻り値で返す。
int  AddValue ( int a,int b) //引数：型と引数の変数を設定する　void:返さない。
{
	//関数内の処理を書く
	int t;
	t = a + b;
	//関数の戻り値があれば戻り値を設定　中身を変えるアドレス渡し。
	return t;

}
//引数を3つあり、初めの2つの引数の値を計算。結果を3番目の変数に格納して返す。関数の戻り値はない。
void AddValue2(int a, int b,int *sum) //引数：型と引数の変数を設定する
{
	//関数内の処理を書く
	*sum = a + b;

}
//ﾀｲﾄﾙｼｰﾝの描画用ｼｰﾝ
void TitleDraw(void)
{
	int c = 5;
	int d = 3;
	int CandDsum;
	CandDsum = AddValue(c,d);

	int e = 3;
	int f = 2;
	int EandFsum = 0;

	AddValue2(e, f,&EandFsum);

	//DrawBox(100, 100, 700, 500, 0x00FF00, true);
	DrawGraph(TitlePosX,TitlePosY,TitleImage,true);
	DrawGraph(HitStartKeyPosX, HitStartKeyPosY,HitStartKeyImage,true);
	DrawFormatString(0, 0, 0xFFFFFF, "TitleScene:%d", SceneCounter);
	DrawFormatString(50, 50, 0xFFFFFF, "%d + %d = %d",c,d, CandDsum);
	DrawFormatString(50, 80, 0xFFFFFF, "%d + %d = %d", e, f,EandFsum);

}
//ｹﾞｰﾑｼｰﾝ
void GameScene(void)
{
	XY playerPos;
	XY enemyPos;
	CHARACTER shot;
	bool MoveFlag = true;

	if (KeyDownTrigger[KEY_ID_SPACE])
	{
		//SceneID = SCENE_ID_GAMEOVER;
		fadeOut = true;
	}
	//Pause機能
	if (KeyDownTrigger[KEY_ID_PAUSE])
	{
		pauseFlag = !pauseFlag;
	}
	//Pause時
	if (pauseFlag) SetDrawBright(128, 128, 128);
	//通常動作
	else
	{
		//各種処理
		playerPos = PlayerControl();	//ﾌﾟﾚｲﾔｰの操作
		enemyPos = EnemyControl(playerPos);	//敵の操作
		shot = ShotControl();					//弾の操作
		if (GetEvent(playerPos) == EVENT_ID_KAIDAN)
		{
			EnemyGameInit();
			SetMapData(STAGE_ID_MAZE);
			//playerPos = { 100,100 };
		}
		if (GetEvent(playerPos) == EVENT_ID_KAIDAN)
		{
			EnemyGameInit();
			SetMapData(STAGE_ID_START);

			//playerPos = { 100,100 };
		}
		//当たり判定のチェック
		for (int s = 0; s < SHOT_MAX; s++)
		{
			//ｐ弾と敵との当たり判定
			if (EnemyHitCheck(shot))
			{
				//敵にｐ弾が当たった。弾を消す
//				shot[s].Life = 0;
				DeleteShot(s);
			}
			/*if (PlayerHitCheck(shot, CHARACTER_ENEMY))
			{
				DeleteShot(s);
			}*/
		}
		
		

		//ｰｰｰｰｰスコアのセーブ、ロード
		//セーブ
		if (KeyDownTrigger[KEY_ID_SAVE])	SaveData();
		//ロード
		if (KeyDownTrigger[KEY_ID_LOAD])	LoadData();
	}
	//画面描画
	GameDraw();
	//Pauseのメッセージ描画
	if (pauseFlag)
	{
		SetDrawBright(255, 255, 255);
		DrawString((SCREEN_SIZE_X - 9 * 8)/2, (SCREEN_SIZE_Y - 9 * 8)/2, "ＰＡＵＳＥ",0xFFFFFF);
	}
}
//ｹﾞｰﾑｼｰﾝの描画用ｼｰﾝ
void GameDraw(void)
{	
	//DrawBox(100, 100, 700, 500, 0xFF0000, true);
	StageGameDraw();	//地図を表示
	
	for (int o = 0; o < drawOrderCnt; o++)
	{
		//表示対象をチェックして表示する
		switch (drawOrDerList[o].characterType)
		{
		case CHARACTER_PLAYER:
			//ﾌﾟﾚｲﾔｰの表示
			PlayerDraw();
			break;
		case CHARACTER_ENEMY:
			//敵の表示(インデックス版）
			EnemyGameDrawOrder(drawOrDerList[o].index);
			break;
		case CHARACTER_SHOT:
			//弾を表示
			ShotGameDrawOrder(drawOrDerList[o].index);
			break;
		default:
			break;
		}
		
	}
	EnemyGameDraw();	//敵を表示
	//ShotGameDraw();		//弾を表示
	//PlayerDraw();		//ﾌﾟﾚｲﾔｰを表示

	DrawFormatString(0, 0, 0xFFFFFF, "GameScene:%d", SceneCounter);

	DrawBox(200, 0, 600, 16, 0x0, true);
	DrawFormatString(250, 0, 0xFFFFFF, "SCORE:%d", fileData.Score);
	DrawFormatString(450, 0, 0xFFFFFF, "HISCORE:%d", fileData.hiScore);
}
//ｹﾞｰﾑｵｰﾊﾞｰｼｰﾝ
void GameOverScene(void)
{
	//if (KeyDownTrigger[KEY_ID_SPACE])
	//{
		//SceneID = SCENE_ID_INIT;
		fadeOut = true;
	//}
	GameOverDraw();
}
//ｹﾞｰﾑｵｰﾊﾞｰｼｰﾝの描画用ｼｰﾝ
void GameOverDraw(void)
{
	//DrawBox(100, 100, 700, 500, 0x0000FF, true);
	DrawGraph(GameOverPosX, GameOverPosY, GameOverImage, true);
	DrawGraph(HitStartKeyPosX, HitStartKeyPosY, HitStartKeyImage, true);
	DrawFormatString(0, 0, 0xFFFFFF, "GameOverScene:%d", SceneCounter);
}
//得点を追加する
void AddScore(int point)
{
	fileData.Score += point;
	if (fileData.hiScore < fileData.Score) fileData.hiScore = fileData.Score;
}
//ﾌｧｲﾙからスコアを書き込みをする
bool SaveData(void)
{
	FILE *fp;
	fopen_s(&fp, fileName, "wb");
	fwrite(&fileData, sizeof(fileData), 1, fp);
	fclose(fp);
	return true;
}
//ﾌｧｲﾙからスコアを読み込む
bool LoadData(void)
{
	FILE *fp;
	fopen_s(&fp, fileName, "rb");
	fread(&fileData, sizeof(fileData), 1, fp);
	fclose(fp);
	return true;
}
//ｷｬﾗｸﾀ情報をdrawOrderListに追加する
void AddCharOrder(CHARACTER_TYPE characterType, int index, int y)
{
	int insertIndex = drawOrderCnt;		//挿入する場所

	//1、引数Y座標が配列内のどの順番に入るかを確認する
	for (int d = 0; d < drawOrderCnt; d++)
	{
		//配列内のY座標と引数Y座標を比較していれる場所を決める
		if (drawOrDerList[d].y > y)
		{
			//挿入場所が決まった。
			insertIndex = d;
			//ループを抜ける。
			break;
		}
	}
	//2、入れる場所が決まったのでその場所にある元々入っていたデータを下にずらす
		//入れる場所より下のデータを一段後に移す。
	for (int d = drawOrderCnt; d > insertIndex; d--)
	{
		drawOrDerList[d] = drawOrDerList[d - 1];
	}
	//3、引数のデータを格納する
	drawOrDerList[insertIndex].characterType = characterType;
	drawOrDerList[insertIndex].index = index;
	drawOrDerList[insertIndex].y = y;

	drawOrderCnt++;
}