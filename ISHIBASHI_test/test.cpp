


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

int maImage;
int ma20Image;
int kaImage;
int ka20Image;
int keImage;
int ke20Image;

int ke_vImage;
int ke_v20Image;
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

	maImage = LoadGraph("aitem/勾玉.png");
	ma20Image = LoadGraph("aitam/勾玉20.png");
	kaImage = LoadGraph("aitem/鏡.png");
	ka20Image = LoadGraph("aitam/鏡20.png");
	keImage = LoadGraph("aitem/剣.png");
	ke20Image = LoadGraph("aitam/剣20.png");
	
	ke_vImage = LoadGraph("aitem/剣version2.png");
	ke_v20Image = LoadGraph("aitam/剣version20.png");
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

	DrawGraph(30, 110, maImage, true);
	DrawGraph(30, 150, ma20Image, true);
	DrawGraph(60, 110, kaImage, true);
	DrawGraph(60, 150, ka20Image, true);
	DrawGraph(90, 110, keImage, true);
	DrawGraph(90, 150, ke20Image, true);

	DrawGraph(120, 110, ke_vImage, true);
	DrawGraph(120, 150, ke_v20Image, true);

}

