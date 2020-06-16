// �^�C�g���V�[���@�Z���N�g�r��:�΋�


#include <DxLib.h>
#include "main.h"
#include "keycheck.h"
#include "effect.h"
#include "stage.h"
#include "player.h"
#include "enemy.h"
#include "shot.h"
#include "item.h"


//-----�ϐ�
//��݊֘A
SCENE SceneID;
SCENE ScenePreID;	//�ߋ��̼�݊i�[�p
int SceneCounter;

//������؊֘A
bool iventFlag;

//PAUSE�֘A
bool paseFlag;
int keyImage;

//���ټ�݊֘A
MSG_STATUS msgStatus[MSG_MAX];
MSG_TYPE msgType;
int rogoImage;
int bgImage;
int msgImage[MSG_MAX];
bool msgCheck[MSG_MAX];
bool msgFlag;
int msgCnt = 0;

//Win�֐�
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	if (!SystemInit())return -1;

	//-----�ް�ٰ��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//key�̏��擾
		KeyCheck();
		//��ݶ���ؾ��
		if (SceneID != ScenePreID)
		{
			ScenePreID = SceneID;
			SceneCounter = 0;
		}
		//-----��ʕ`�揈��
		ClsDrawScreen();	//��ʏ���
		//��ݑI��
		switch (SceneID)
		{
		case SCENE_INIT:
			InitScene();
			break;
		//���ټ��
		case SCENE_TITLE:
			TitleScene();
			break;
		//�ްѼ��
		case SCENE_GAME:
			GameScene();
			break;
		//�ްѵ��ް���
		case SCENE_GAMEOVER:
			GameOverScene();
			break;
		default:
			return -1;
			break;
		}
		SceneCounter++;		
		ScreenFlip();		//����ʂ�\��ʂɏu�Ժ�߰
	}
	
	DxLib_End();			//DXײ���؂̏I������
	return 0;				//������۸��т̏I��

}
//���т̏�����
bool SystemInit(void)
{

	//--------���я���
	SetWindowText("����`�O�̐_��`");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)return false;
	SetDrawScreen(DX_SCREEN_BACK);
	
	//-----key���̏�����
	KeyInit();

	//-----�eӼޭ�ق̏�����
	StageSystemInit();			//�ð��
	PlayerSystemInit();			//��ڲ԰
	EnemySystemInit();			//�Gmob
	ItemSystmeInit();			//����
	ShotSystemInit();			//����
	
	//-----���̨���o�^
	keyImage = LoadGraph("item/�������.png");
	rogoImage = LoadGraph("item/rogo_.png");
	bgImage = LoadGraph("item/bg.png");
	LoadDivGraph(("item/msg.png"), 2, 1, 2, 400, 100, msgImage);
	//-----�ϐ��̏�����
	//��݊֘A
	SceneCounter = 0;
	SceneID = SCENE_INIT;
	ScenePreID = SCENE_MAX;
	//PAUSE
	pauseFlag = false;
	//�����ă�
	iventFlag = false;
	//���ټ��
	for (int i = 0; i < MSG_MAX; i++)
	{
		msgStatus[i] = MSG_STATUS_NON;
		msgCheck[i] = true;
	}
	msgType = MSG_START;
	msgFlag = false;
	
	return true;
}
//���������
void InitScene(void)
{
	//-----�e��޼ު�ď���
	StageGameInit();				//�ð��
	PlayerGameInit();				//��ڲ԰
	EnemyGameInit();				//�G
	ItemGameInit();					//����
	ShotGameInit();					//����

	//-----��ݑJ��
	SceneID = SCENE_TITLE;
}




/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//���ټ��
void TitleScene(void)
{
	//-----��ݑJ��
	//if (KeyDownTrigger[KEY_ID_UP])
	//{
	//	msgStatus[MSG_START] = MSG_STATUS_ALIVE;	
	//	msgType = MSG_START;
	//}
	//if (KeyDownTrigger[KEY_ID_DOWN])
	//{
	//	msgStatus[MSG_LOAD] = MSG_STATUS_ALIVE;
	//	msgType = MSG_LOAD;
	//}

	if (msgType == MSG_START)
	{
		if (KeyDownTrigger[KEY_ID_SPACE])
		{
			SceneID = SCENE_GAME;
		}
	}
	//else if (msgType == MSG_LOAD)
	//{
	//	if (KeyDownTrigger[KEY_ID_SPACE])
	//	{
	//		msgFlag = true;	
	//	}
	//	if (msgCnt > 120)
	//	{
	//		msgCnt = 0;
	//		msgFlag = false;
	//	}
	//}
	
	//-----�`��
	TitleDraw();
}

//���ق̕`��
void TitleDraw(void)
{
	//-----�`�揈��
	DrawGraph(0, 0, bgImage, true);
	DrawGraph((SCREEN_SIZE_X - 400)/2, 50, rogoImage, true);
	for (int i = 0; i < MSG_MAX; i++)
	{
		if (msgStatus[i] == MSG_STATUS_NON)
		{

		//	if (msgImage[i] == msgImage[MSG_LOAD])
		//	{
		//		SetDrawBright(50, 50, 50);
		//	}
		}
		//	DrawGraph((SCREEN_SIZE_X - 400) / 2, 400 + 100 * i, msgImage[i], true);
			DrawGraph((SCREEN_SIZE_X - 400) / 2, 400, msgImage[0], true);

			SetDrawBright(255, 255, 255);
		
	}
	if (msgFlag)
	{
		msgCnt++;
		DrawBox(200, 200, 600, 450, 0xFFFFFF, true);
		DrawString(320, 300, "  �I���ł��܂���\n�I�ђ����Ă�������", 0x000000);
	}

	//-----��񏈗�
	DrawFormatString(0, 0, 0xFFFFFF, "Title:%d", SceneCounter);

}



///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//�ްѼ��
void GameScene(void)
{
	XY playerPos;		//��ڲ԰�̍��W�i�[�̈�


	//��ݑJ��
	if (KeyDownTrigger[KEY_ID_SPACE]) SceneID = SCENE_GAMEOVER;



	//-----�����؋@�\
	//������
	if (KeyDownTrigger[KEY_ID_IVENT]) iventFlag = !iventFlag;
	//�׸ޏ���
	if (iventFlag)
	{
		SetDrawBright(128, 128, 128);
		pauseFlag = false;
	}

	//-----PAUSE�@�\
	if (KeyDownTrigger[KEY_ID_PAUSE]) pauseFlag = !pauseFlag;
	if (pauseFlag)
	{
		SetDrawBright(128, 128, 128);
		iventFlag = false;
	}

	//�ʏ펞����
	if(!iventFlag && !pauseFlag)
	{
		//�e��@�\
		//-----�e��޼ު�đ���
		playerPos = PlayerControl();		//��ڲ԰
		EnemyControl(playerPos);			//��а
		ItemControl();						//����
		ShotControl(playerPos);				//����

		//��а�ƒe�̓����蔻��
		for (int sh = 0; sh < SHOT_MAX; sh++)
		{
			if (shot[sh].life > 0)
			{
				if (EnemyHitCheck(shot[sh].pos, shot[sh].size.x, &shot[sh]))
				{
					DeleteShot(sh);
				}
			}
		}


		//�ꎞ�I����
		if (GetEvent(playerPos) == EVENT_ID_ZAKO)
		{
			stageID = STAGE_ID_MOB;
			SetMapData(STAGE_ID_MOB);
			mapPos.x = 0;
			mapPos.y = 0;
		}
		else if (GetEvent(playerPos) == EVENT_ID_KAPPA)
		{
			stageID = STAGE_ID_KAPPA;
			SetMapData(STAGE_ID_KAPPA);
			mapPos.x = 0;
			mapPos.y = 0;
		}
	}

	
	//-----�`��
	GameDraw(); 
}


//�ްт̕`��
void GameDraw(void)
{

	//-----�e��޼ު�ĕ`�揈��
	StageGameDraw();			//�ð��
	PlayerGameDraw();			//��ڲ԰
	EnemyGameDraw();			//�G
	ItemGameDraw();				//����
	ShotGameDraw();				//����
	//-----������؊֘A
	if (iventFlag)
	{
		SetDrawBright(255, 255, 255);
		DrawBox(100, 100, 700, 600, 0xFFFFFF, true);
		//��D
		ItemI_Draw();

	}
	//----PAUSE�֘A
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
	
	//-----��񏈗�
	DrawFormatString(0, 0, 0xFFFFFF, "Game:%d", SceneCounter);
	DrawFormatString(0, 120, 0xFFFFFF, "map:%d,%d", mapPos.x,mapPos.y);

}





//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//�ްѵ��ް���
void GameOverScene(void)
{
	if (KeyDownTrigger[KEY_ID_SPACE]) SceneID = SCENE_INIT;


	GameOverDraw();
}


//�ްѵ��ް�̕`��
void GameOverDraw(void)
{
	//-----�`�揈��

	//-----��񏈗�
	DrawFormatString(0, 0, 0xFFFFFF, "GameOver:%d", SceneCounter);


}
