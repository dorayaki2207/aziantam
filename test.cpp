


//////////�@�G�X�P�[�v�V�[�P���X�@\n
//////////	fgetc �ꕶ�����Ɠǂݍ���
//////////	fgets ��s���Ɠǂݍ���
//////////	drawtext



#include "DxLib.h"
#include "test.h"



//-----�O���ϐ��錾
int SceneCounter;			//	gameLoop����m�F�p
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
	//-----����������
	if (!SystemInit()) return -1;


	//-----�ް�ٰ��
	while (ProcessMessage() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		ClsDrawScreen();


		//-----��ݶ���������
		if (sceneID != preSceneID)
		{
			SceneCounter = 0;
			preSceneID = sceneID;
		}

		//-----��ݑI��
		switch (sceneID)
		{
			//��ݏ�����
		case SCENE_ID_INIT:
			InitScene();
			break;

			//	//���ټ��
			//case SCENE_ID_TITLE:
			//	TitleScene();
			//	break;

			//	//�ڸļ��
			//case SCENE_ID_SELECT:
			//	T_selectScene();
			//	break;

			//	//۰�޼��
			//case SCENE_ID_LOAD:
			//	LoadScene();
			//	break;

			//�ްѼ��
		case SCENE_ID_GAME:
			GameScene();
			break;

			//	//�ްѵ��ް���
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

	//-----���я���
	SetWindowText("1916004_ishibashi");							//	����

	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);				//	65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);										//	true : window, false : �ٽ�ذ�
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	BImage = LoadGraph("��D��/B_small.png");
	RImage = LoadGraph("��D��/R_small.png");
	PImage = LoadGraph("��D��/P_small.png");
	GImage = LoadGraph("��D��/G_small.png");

	BBImage = LoadGraph("��D��/B.png");
	RRImage = LoadGraph("��D��/R.png");
	PPImage = LoadGraph("��D��/P.png");
	GGImage = LoadGraph("��D��/G.png");
	//-----�ϐ��̏�����
	SceneCounter = 0;
	


	return retFlag;
}


void InitScene(void)
{
	//-----�e��޼ު�ď���
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

	//-----��񏈗�
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

