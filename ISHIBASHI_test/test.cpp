


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
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Battle.h"

//-----�O���ϐ��錾
int SceneCounter;			//	gameLoop����m�F�p
SCENE_ID sceneID;
SCENE_ID preSceneID;
//PAUSE
int pCnt;
bool pauseFlag;
bool iventFlag;
int keyImage;

//�����蔻��p
XY playerSize;
int testCnt;

//��b�V�X�e��
const char *file;
char words[200];

//�C�x���g��


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
			
			//�޽�����ټ��
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

	//-----���я���
	SetWindowText("1916004_ishibashi");							//	����

	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);				//	65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);										//	true : window, false : �ٽ�ذ�
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);


	//-----���͏�񏉊���
	KeyInit();
	//-----�e��޼ު�Ă̏�����
	StageSystemInit();
	PlayerSystemInit();
	EnemySystemInit();
	ItemSystemInit();
	BattleSystemInit();

	//-----���̨���o�^
	keyImage = LoadGraph("aitem/�}2.png");


	//-----�ϐ��̏�����
	SceneCounter = 0;
	sceneID = SCENE_ID_INIT;
	preSceneID = SCENE_ID_MAX;

	//�����؊֘A
	pCnt = 0;
	iventFlag = false;
	
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
	StageGameInit();
	ItemGameInit();
	PlayerGameInit();
	EnemyGameInit();
	BattleGameInit();
	//��D�����p
	testCnt = 0;


	

	sceneID = SCENE_ID_TITLE;
}


void TitleScene()
{

	if (keyDownTrigger[KEY_ID_SPACE])
	{
		sceneID = SCENE_ID_GAME;
	}

	DrawFormatString(0, 0, 0xFFFFFF, "Title:%d", SceneCounter);
}


void GameScene()
{
	XY playerPos;


	if (keyDownTrigger[KEY_ID_SPACE])
	{
		sceneID = SCENE_ID_BATTLE;
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
		

		//��ڲ԰�ƴ�а�Ƃ̓����蔻��
		if (ItemHitCheck(playerPos, playerSize.x))
		{
			testCnt++;
		}
		
	}

	GameDraw();
	

}


void GameDraw()
{
	//-----�e��޼ު�ĕ`�揈��
	StageGameDraw();
	ItemGameDraw();
	PlayerGameDraw();
	EnemyGameDraw();
	//-----��񏈗�
	DrawFormatString(0, 0, 0xFFFFFF, "GameMain : %d", SceneCounter);
//	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0x55FF55, true);
	DrawFormatString(0, 200, 0xFF22FF, "%d", testCnt);

	

	DrawFormatString(0, 24, 0xFFFFFF, "pCnt : %d", pCnt);
	//-----������؊֘A
	if (iventFlag)
	{
		SetDrawBright(255, 255, 255);
		DrawBox(100, 100, 700, 600, 0xFFFFFF, true);
//		DrawString((SCREEN_SIZE_X - 9 * 8) / 2, (SCREEN_SIZE_Y - 16) / 2, "PAUSE", 0xFFFFFF);
		
		//��D
		ItemI_Draw();

	}
	//-----PAUSE�֘A		
	if (pauseFlag)
	{
		SetDrawBright(255, 255, 255);									//	�Â�����
		DrawBox(50, 50, 750, 600, 0x222222, true);						//	�g
		DrawGraph((SCREEN_SIZE_X - 650) / 2, 180, keyImage, true);		//	�׽�
		DrawString(100, 100, "KEY�������", 0xFFFFFF, true);			//	����
		DrawString(99, 110, "------------", 0xFFFFFF, true);			//	���ĉ���
		
		DrawString(150, 430, "Z : �΂̍U��", 0xFFFFFF, true);
		DrawString(150, 460, "X : ���̍U��", 0xFFFFFF, true);
		DrawString(150, 490, "C : ���̍U��", 0xFFFFFF, true);
		DrawString(150, 520, "V : ��", 0xFFFFFF, true);
		DrawString(400, 430, "M : ���j���[���", 0xFFFFFF, true);
		DrawString(400, 460, "I : �A�C�e�����j���[", 0xFFFFFF, true);

	}



	if (!iventFlag && !pauseFlag)
	{

		//�����؂��߰�ދ@�\���g�p����Ă���Ƃ��͕\������Ȃ�
		DrawFormatString(0, 32, 0xFFFFFF, "%s\n", words);

		DrawFormatString(0, 150, 0xFF22FF, "%d", itemF[ITEM_TYPE_HI].point);
		DrawFormatString(0, 165, 0xFF22FF, "%d", itemF[ITEM_TYPE_MIZU].point);
		DrawFormatString(0, 177, 0xFF22FF, "%d", itemF[ITEM_TYPE_KAZE].point);
		DrawFormatString(0, 189, 0xFF22FF, "%d", itemF[ITEM_TYPE_KAIFUKU].point);


	}


}



