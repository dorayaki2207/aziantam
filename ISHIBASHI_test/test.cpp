


//////////�@�G�X�P�[�v�V�[�P���X�@\n
//////////	fgetc �ꕶ�����Ɠǂݍ���
//////////	fgets ��s���Ɠǂݍ���
//////////	drawtext
//////////	%s �����𕶎���̃|�C���^�Ƃ��Ĉ����A�����񂩂�"\0"�����o
//////////   ���邩�A���x�Ŏw�肵��������ɒB����܂ŕ������o��
//////////	%c�ꕶ������
//////////	%if �L�[�{�[�h���͂�����������ւ񂩂�H�@double�^�ɕϊ�


#include "DxLib.h"
#include "stdio.h"
#include "test.h"
#include "KeyCheck.h"
#include "Player.h"
#include "Item.h"

//-----�O���ϐ��錾
int SceneCounter;			//	gameLoop����m�F�p
SCENE_ID sceneID;
SCENE_ID preSceneID;
//PAUSE
int pCnt;
bool pauseFlag;
bool iventFlag;
//��D
int hiImage;
int hiCnt;
int mizuImage;
int mizuCnt;
int kazeImage;
int kazeCnt;
int kaifukuImage;
int kaifukuCnt;

//�����蔻��p
XY playerSize;
int testCnt;

//��b�V�X�e��
const char *file;
char words[200];

//�C�x���g��
int totalScrNew;
int totalScr[SCR_MAX];


//-----WinMain
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//-----����������
	if (!SystemInit()) return -1;


	//-----�ް�ٰ��
	while (ProcessMessage() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		ClsDrawScreen();

		//-----���̏�Ԏ擾
		KeyCheck();


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
		
			//���ټ��
		case SCENE_ID_TITLE:
			TitleScene();
			break;

			//�ްѼ��
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

	//-----���я���
	SetWindowText("1916004_ishibashi");							//	����

	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);				//	65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);										//	true : window, false : �ٽ�ذ�
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);


	//-----���͏�񏉊���
	KeyInit();
	//-----�e��޼ު�Ă̏�����
	PlayerSystmeInit();
	ItemSystmeInit();

	//-----���̨���o�^
	hiImage = LoadGraph("��D��/R_small.png");
	mizuImage = LoadGraph("��D��/B_small.png");
	kazeImage = LoadGraph("��D��/G_small.png");
	kaifukuImage = LoadGraph("��D��/P_small.png");


	//-----�ϐ��̏�����
	SceneCounter = 0;
	
	//�����؊֘A
	pCnt = 0;
	iventFlag = false;
	FILE* fp;
	// ̧�ٓǂݍ��ݎ��s�����ꍇ 0�ȊO
	if (fopen_s(&fp, "scr.dat", "w+") != NULL)
	{
		//�د����̏�����
		// �傫���l�����čX�V���Ă���
		for (int j = 0; j < SCR_MAX; j++)
		{
			// ��а�̏�����
			totalScr[j] = 0;

		}
	}
	// ̧�ٓǂݍ��ݐ���
	else
	{
		//�������݂������ڽ�̐擪���ڽ
		fread(
			totalScr,
			sizeof(totalScr[0]),
			SCR_MAX,
			fp
		);
		// ���s���Ă���ꍇ�ēx����K�v���Ȃ����炱�̈ʒu�ŕ���
		fclose(fp);
	}
	//PAUSE�@�\
	pauseFlag = false;
	
	//�����蔻��p
	playerSize = { 20,20 };
	


	file = "dafafile.txt";

	return retFlag;
}


void InitScene(void)
{
	//-----�e��޼ު�ď���
	ItemGameInit();
	PlayerGameInit();
	
	//��D�����p
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

	
	//-----FILE����
	FILE *fp;
	
	fopen_s(&fp, file, "r");
//	fscanf_s(fp,"%s",words,256);
//	fgets(words, 256, fp);
//	printf("\n", words);	
	fread(words, sizeof(words), size_t(2), fp);
//	fprintf(fp, "HelloWorld!!!!�ނ��������Ȃ�");

	//for (int a = 0; a < words[a]; a++)
	//{
	//	if (CheckHitKey(KEY_INPUT_A))
	//	{
	//		printf("%s\n", words);
	//	}
	//}

	fclose(fp);
	
	
	//-----�����؋@�\
	//������
	if (keyDownTrigger[KEY_ID_IVENT])
	{
		iventFlag = !iventFlag;

	}
	//�׸ޏ���
	if (iventFlag)
	{
		SetDrawBright(128, 128, 128);
		pauseFlag = false;
	}
	
	//-----POSE�@�\
	if (keyDownTrigger[KEY_ID_PAUSE]) pauseFlag = !pauseFlag;
	if (pauseFlag)
	{
		SetDrawBright(128, 128, 128);
		iventFlag = false;
	}
	

	//�ʏ펞����
	if (!iventFlag && !pauseFlag)
	{

		//�e��@�\
		pCnt++;

		playerPos = PlayerControl();
		ItemControl();

		//��ڲ԰�ƴ�а�Ƃ̓����蔻��
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
	//-----�e��޼ު�ĕ`�揈��
	ItemGameDraw();
	PlayerGameDraw();
	
	//-----��񏈗�
	DrawFormatString(0, 0, 0xFFFFFF, "GameMain : %d", SceneCounter);
//	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0x55FF55, true);
	DrawFormatString(0, 200, 0xFF22FF, "%d", testCnt);

	
	DrawBox(15, SCREEN_SIZE_Y - 220, SCREEN_SIZE_X - 15, SCREEN_SIZE_Y - 5, 0xFF22FF, false);

	DrawFormatString(0, 24, 0xFFFFFF, "pCnt : %d", pCnt);
	//-----�����؊֘A
	if (iventFlag)
	{
		SetDrawBright(255, 255, 255);
		DrawBox(100, 100, 700, 600, 0xFFFFFF, true);
//		DrawString((SCREEN_SIZE_X - 9 * 8) / 2, (SCREEN_SIZE_Y - 16) / 2, "PAUSE", 0xFFFFFF);

		//��D
		DrawGraph(350, 250, hiImage, true);
		DrawFormatString(380, 254, 0xFF22FF, "��", true);
		DrawFormatString(410, 253, 0xFF22FF, "%d", itemF[ITEM_TYPE_HI].point);

		DrawGraph(350, 300, mizuImage, true);
		DrawFormatString(380, 304, 0xFF22FF, "��", true);
		DrawFormatString(410, 303, 0xFF22FF, "%d", itemF[ITEM_TYPE_MIZU].point);

		DrawGraph(350, 350, kazeImage, true);
		DrawFormatString(380, 354, 0xFF22FF, "��", true);
		DrawFormatString(410, 353, 0xFF22FF, "%d", itemF[ITEM_TYPE_KAZE].point);

		DrawGraph(350, 400, kaifukuImage, true);
		DrawFormatString(380, 404, 0xFF22FF, "��", true);
		DrawFormatString(410, 403, 0xFF22FF, "%d", itemF[ITEM_TYPE_KAIFUKU].point);


	}
	//-----PAUSE�֘A		
	if (pauseFlag)
	{
		SetDrawBright(255, 255, 255);
		DrawBox(100, 100, 700, 600, 0x222222, true);
	}



	if (!iventFlag && !pauseFlag)
	{
		//�ʏ펞����
		DrawFormatString(0, 32, 0xFFFFFF, "%s\n", words);

		DrawFormatString(0, 150, 0xFF22FF, "%d", itemF[ITEM_TYPE_HI].point);
		DrawFormatString(0, 165, 0xFF22FF, "%d", itemF[ITEM_TYPE_MIZU].point);
		DrawFormatString(0, 177, 0xFF22FF, "%d", itemF[ITEM_TYPE_KAZE].point);
		DrawFormatString(0, 189, 0xFF22FF, "%d", itemF[ITEM_TYPE_KAIFUKU].point);


	}


}



