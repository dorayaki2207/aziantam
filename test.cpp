


//////////　エスケープシーケンス　\n
//////////	fgetc 一文字ごと読み込む
//////////	fgets 一行ごと読み込む
//////////	drawtext



#include "DxLib.h"
#include "test.h"



//-----外部変数宣言
int SceneCounter;			//	gameLoop動作確認用
SCENE_ID sceneID;
SCENE_ID preSceneID;

int BImage;
int RImage;
int PImage;
int GImage;

int BBImage;
int RRImage;
int PPImage;
int GGImage;
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

	BImage = LoadGraph("御札案/B_small.png");
	RImage = LoadGraph("御札案/R_small.png");
	PImage = LoadGraph("御札案/P_small.png");
	GImage = LoadGraph("御札案/G_small.png");

	BBImage = LoadGraph("御札案/B.png");
	RRImage = LoadGraph("御札案/R.png");
	PPImage = LoadGraph("御札案/P.png");
	GGImage = LoadGraph("御札案/G.png");
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

	FILE *fp;
	fopen_s(&fp, "dafafile.txt", "w");
	fprintf(fp, "HelloWorld!!!!");
	//fwrite(&fileData, sizeof(fikeName), size_t(2), fp);

	fclose(fp);

	//FILE *file;
	//file = fopen("test.txt", "w");
	////fprintf(file, "Hello");
	//fclose(file);
	

	GameDraw();
}


void GameDraw(void)
{

	//-----情報処理
	DrawFormatString(0, 0, 0xFFFFFF, "GameMain : %d", SceneCounter);
	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0xFFFFFF, true);

	DrawBox(15, SCREEN_SIZE_Y - 220, SCREEN_SIZE_X - 15, SCREEN_SIZE_Y - 5, 0xFF22FF, false);
	DrawGraph(30, 50, BImage, true);
	DrawGraph(60, 50, RImage, true);
	DrawGraph(90, 50, PImage, true);
	DrawGraph(120, 50, GImage, true);

	DrawGraph(30, 80, BBImage, true);
	DrawGraph(60, 80, RRImage, true);
	DrawGraph(90, 80, PPImage, true);
	DrawGraph(120, 80, GGImage, true);

}

