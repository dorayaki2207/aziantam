


//////////　エスケープシーケンス　\n
//////////	fgetc 一文字ごと読み込む
//////////	fgets 一行ごと読み込む
//////////	drawtext
//////////	%s 引数を文字列のポインタとして扱い、文字列から"\0"を検出
//////////   するか、精度で指定した文字列に達するまで文字を出力
//////////	%c一文字ずつ
//////////	%if キーボード入力した文字列をへんかん？　double型に変換


#include "DxLib.h"
#include "stdio.h"
#include "test.h"
#include "KeyCheck.h"
#include "Player.h"
#include "Item.h"

//-----外部変数宣言
int SceneCounter;			//	gameLoop動作確認用
SCENE_ID sceneID;
SCENE_ID preSceneID;
//PAUSE
int pCnt;
bool pauseFlag;
bool iventFlag;
//御札
int hiImage;
int hiCnt;
int mizuImage;
int mizuCnt;
int kazeImage;
int kazeCnt;
int kaifukuImage;
int kaifukuCnt;

//当たり判定用
XY playerSize;
int testCnt;

//会話システム
const char *file;
char words[200];

//イベントリ
int totalScrNew;
int totalScr[SCR_MAX];


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
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);


	//-----入力情報初期化
	KeyInit();
	//-----各ｵﾌﾞｼﾞｪｸﾄの初期化
	PlayerSystmeInit();
	ItemSystmeInit();

	//-----ｸﾞﾗﾌｨｯｸ登録
	hiImage = LoadGraph("御札案/R_small.png");
	mizuImage = LoadGraph("御札案/B_small.png");
	kazeImage = LoadGraph("御札案/G_small.png");
	kaifukuImage = LoadGraph("御札案/P_small.png");


	//-----変数の初期化
	SceneCounter = 0;
	
	//ｲﾍﾞﾝﾄﾘ関連
	pCnt = 0;
	iventFlag = false;
	FILE* fp;
	// ﾌｧｲﾙ読み込み失敗した場合 0以外
	if (fopen_s(&fp, "scr.dat", "w+") != NULL)
	{
		//ｸﾘｯｸ数の初期化
		// 大きい値を入れて更新していく
		for (int j = 0; j < SCR_MAX; j++)
		{
			// ﾀﾞﾐｰの初期化
			totalScr[j] = 0;

		}
	}
	// ﾌｧｲﾙ読み込み成功
	else
	{
		//書き込みたいｱﾄﾞﾚｽの先頭ｱﾄﾞﾚｽ
		fread(
			totalScr,
			sizeof(totalScr[0]),
			SCR_MAX,
			fp
		);
		// 失敗している場合再度閉じる必要がないからこの位置で閉じる
		fclose(fp);
	}
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
	ItemGameInit();
	PlayerGameInit();
	
	//御札枚数用
	hiCnt = 0;
	mizuCnt = 0;
	kazeCnt = 0;
	kaifukuCnt = 0;

	testCnt = 0;


	

	sceneID = SCENE_ID_TITLE;
}


void TitleScene()
{

	if (keyDownTrigger[KEY_ID_SPACE])
	{
		sceneID = SCENE_ID_GAME;
	}

	DrawFormatString(0, 50, 0xFFFFFF, "Title:%d", SceneCounter);
}


void GameScene()
{
	XY playerPos;


	if (keyDownTrigger[KEY_ID_SPACE])
	{
		sceneID 
			= SCENE_ID_INIT;
	}

	
	//-----FILE操作
	FILE *fp;
	
	fopen_s(&fp, file, "r");
//	fscanf_s(fp,"%s",words,256);
//	fgets(words, 256, fp);
//	printf("\n", words);	
	fread(words, sizeof(words), size_t(2), fp);
//	fprintf(fp, "HelloWorld!!!!むずかしいなぁ");

	//for (int a = 0; a < words[a]; a++)
	//{
	//	if (CheckHitKey(KEY_INPUT_A))
	//	{
	//		printf("%s\n", words);
	//	}
	//}

	fclose(fp);
	
	
	//-----ｲﾍﾞﾝﾄﾘ機能
	//ｷｰ処理
	if (keyDownTrigger[KEY_ID_IVENT])
	{
		iventFlag = !iventFlag;

	}
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
		ItemControl();

		//ﾌﾟﾚｲﾔｰとｴﾈﾐｰとの当たり判定
		if (ItemHitCheck(playerPos, playerSize.x))
		{
			testCnt++;
		}
		/*if (keyDownTrigger[KEY_ID_UP])hiCnt++;
		if (keyDownTrigger[KEY_ID_RIGHT])mizuCnt++;
		if (keyDownTrigger[KEY_ID_DOWN])kazeCnt++;
		if (keyDownTrigger[KEY_ID_LEFT])kaifukuCnt++;*/

	}

	GameDraw();
	

}


void GameDraw()
{
	//-----各ｵﾌﾞｼﾞｪｸﾄ描画処理
	ItemGameDraw();
	PlayerGameDraw();
	
	//-----情報処理
	DrawFormatString(0, 0, 0xFFFFFF, "GameMain : %d", SceneCounter);
//	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0x55FF55, true);
	DrawFormatString(0, 200, 0xFF22FF, "%d", testCnt);

	
	DrawBox(15, SCREEN_SIZE_Y - 220, SCREEN_SIZE_X - 15, SCREEN_SIZE_Y - 5, 0xFF22FF, false);

	DrawFormatString(0, 24, 0xFFFFFF, "pCnt : %d", pCnt);
	//-----ｲﾍﾞﾝﾄﾘ関連
	if (iventFlag)
	{
		SetDrawBright(255, 255, 255);
		DrawBox(100, 100, 700, 600, 0xFFFFFF, true);
//		DrawString((SCREEN_SIZE_X - 9 * 8) / 2, (SCREEN_SIZE_Y - 16) / 2, "PAUSE", 0xFFFFFF);

		//御札
		DrawGraph(350, 250, hiImage, true);
		DrawFormatString(380, 254, 0xFF22FF, "＠", true);
		DrawFormatString(410, 253, 0xFF22FF, "%d", itemF[ITEM_TYPE_HI].point);

		DrawGraph(350, 300, mizuImage, true);
		DrawFormatString(380, 304, 0xFF22FF, "＠", true);
		DrawFormatString(410, 303, 0xFF22FF, "%d", itemF[ITEM_TYPE_MIZU].point);

		DrawGraph(350, 350, kazeImage, true);
		DrawFormatString(380, 354, 0xFF22FF, "＠", true);
		DrawFormatString(410, 353, 0xFF22FF, "%d", itemF[ITEM_TYPE_KAZE].point);

		DrawGraph(350, 400, kaifukuImage, true);
		DrawFormatString(380, 404, 0xFF22FF, "＠", true);
		DrawFormatString(410, 403, 0xFF22FF, "%d", itemF[ITEM_TYPE_KAIFUKU].point);


	}
	//-----PAUSE関連		
	if (pauseFlag)
	{
		SetDrawBright(255, 255, 255);
		DrawBox(100, 100, 700, 600, 0x222222, true);
	}



	if (!iventFlag && !pauseFlag)
	{
		//通常時動作
		DrawFormatString(0, 32, 0xFFFFFF, "%s\n", words);

		DrawFormatString(0, 150, 0xFF22FF, "%d", itemF[ITEM_TYPE_HI].point);
		DrawFormatString(0, 165, 0xFF22FF, "%d", itemF[ITEM_TYPE_MIZU].point);
		DrawFormatString(0, 177, 0xFF22FF, "%d", itemF[ITEM_TYPE_KAZE].point);
		DrawFormatString(0, 189, 0xFF22FF, "%d", itemF[ITEM_TYPE_KAIFUKU].point);


	}


}



