


//////////　エスケープシーケンス　\n
//////////	fgetc 一文字ごと読み込む
//////////	fgets 一行ごと読み込む

#include "DxLib.h"
#include "test.h"



//-----外部変数宣言
int SceneCounter;			//	gameLoop動作確認用
SCENE_ID sceneID;
SCENE_ID preSceneID;

int testImage;
int test1Image;

//-----file情報定義
//char name[] = "0930.txt";


//-----WinMain
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//-----初期化処理
	if (!SystemInit()) return -1;


	//-----ｹﾞｰﾑﾙｰﾌﾟ
	while (ProcessMessage() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		ClsDrawScreen();


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

			//	//ﾀｲﾄﾙｼｰﾝ
			//case SCENE_ID_TITLE:
			//	TitleScene();
			//	break;

			//	//ｾﾚｸﾄｼｰﾝ
			//case SCENE_ID_SELECT:
			//	T_selectScene();
			//	break;

			//	//ﾛｰﾄﾞｼｰﾝ
			//case SCENE_ID_LOAD:
			//	LoadScene();
			//	break;

			//ｹﾞｰﾑｼｰﾝ
		case SCENE_ID_GAME:
			GameScene();
			break;

			//	//ｹﾞｰﾑｵｰﾊﾞｰｼｰﾝ
			//case SCENE_ID_GAMEOVER:
			//	GameOverScene();
			//	break;

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


	testImage = LoadGraph("御札案/御札・火・改1.png");
	test1Image = LoadGraph("御札案/御札・火・改.png");
	//-----変数の初期化
	SceneCounter = 0;





	return retFlag;
}


void InitScene(void)
{
	//-----各ｵﾌﾞｼﾞｪｸﾄ処理
	sceneID = SCENE_ID_GAME;
}

void GameScene(void)
{
	//	
	//	FILE *fp;	// FILE型構造体

	//	fopen_s(&fp, "0930.txt", "r");
	//	if (fp == NULL)
	//	{
	//		printf("%s file not open!\n", name);
	//	
	//	}
	//	else
	//	{
	//		printf("%s file opened!\n", name);
	//	}

	//	fclose(fp);		//	fileを閉じる

	/*
	FILE *file;
	char line[256];
	line[0] = '\0';
	file = fopen("c:\\ノベル風文字列描画 - コピー\\0930.txr", "r");
	if (file == NULL)
	{
	printf("file not open\n");
	exit(1);
	}
	while (fgets(line, 256, file) != NULL)
	{
	printf("%s", line);
	}
	fclose(file);
	*/

	GameDraw();
}


void GameDraw(void)
{

	//-----情報処理
	DrawFormatString(0, 0, 0xFFFFFF, "GameMain : %d", SceneCounter);

	DrawBox(15, SCREEN_SIZE_Y - 220, SCREEN_SIZE_X - 15, SCREEN_SIZE_Y - 5, 0xFF22FF, false);

	DrawGraph(400, (SCREEN_SIZE_Y - (SCREEN_SIZE_Y - 220)) / 2, test1Image, true);
	DrawGraph(10, (SCREEN_SIZE_Y - (SCREEN_SIZE_Y - 220)) / 2, testImage, true);
}


