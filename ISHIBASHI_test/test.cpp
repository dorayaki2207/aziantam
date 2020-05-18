


//////////　エスケープシーケンス　\n
//////////	fgetc 一文字ごと読み込む
//////////	fgets 一行ごと読み込む
//////////	drawtext
//////////	%s 引数を文字列のポインタとして扱い、文字列から"\0"を検出
//////////   するか、精度で指定した文字列に達するまで文字を出力


#include "DxLib.h"
#include "test.h"



//-----外部変数宣言
int SceneCounter;			//	gameLoop動作確認用
SCENE_ID sceneID;
SCENE_ID preSceneID;

struct FILE_DATA
{
	int data1;
	int data2;
};
char fileName[] = "data.txt";
struct FILE_DATA fileData;

const char *file;

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


	//-----変数の初期化
	SceneCounter = 0;
	
	fileData.data1 = 256;
	fileData.data2 = 256;

	file = "dafafile.txt";

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
	char words[200];
	fopen_s(&fp, file, "r");
	fscanf(fp,  words,"%s");
//	fgets(&file, sizeof(words), fp);

	//fread(&fileData, sizeof(fileName), size_t(2), fp);
	
	
//	fprintf(fp, "HelloWorld!!!!");
	//fwritez(&fileData, sizeof(fikeName), size_t(2), fp);

	fclose(fp);

	

	GameDraw();
}


void GameDraw(void)
{

	//-----情報処理
	DrawFormatString(0, 0, 0xFFFFFF, "GameMain : %d", SceneCounter);
//	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0xFFFFFF, true);

	DrawBox(15, SCREEN_SIZE_Y - 220, SCREEN_SIZE_X - 15, SCREEN_SIZE_Y - 5, 0xFF22FF, false);
	
}

