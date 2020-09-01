#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "effect.h"
#include "stage.h"
#include "player.h"
#include "enemy.h"
#include "shot.h"
#include "item.h"
#include <time.h>


//-----�ϐ�
//��݊֘A
SCENE SceneID;
SCENE ScenePreID;	//�ߋ��̼�݊i�[�p
int SceneCounter;
int GameOverCnt;

//������؊֘A
bool iventFlag;

//PAUSE�֘A
bool paseFlag;
int keyImage;

MSG_TYPE msgType;
int titleCounter;

int msgImage[MSG_MAX];
bool msgCheck[MSG_MAX];
bool msgFlag;
int msgCnt;
int rogoImage;
int bgImage;
int msgID;

//�����蔻��p
XY playerSize;

//���ިݸފ֘A
int clearImage;
int overImage;

//Win�֐�
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{

	if (!SystemInit()) return -1;

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
	if (DxLib_Init() == -1) return false;
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
	clearImage = LoadGraph("item/clear.png");
	overImage = LoadGraph("item/over.png");
	LoadDivGraph(("item/msg.png"), MSG_MAX, 1, MSG_MAX, 400, 100, msgImage);


	//-----�ϐ��̏�����
	//��݊֘A
	SceneCounter = 0;
	GameOverCnt = 0;
	SceneID = SCENE_INIT;
	ScenePreID = SCENE_MAX;
	//PAUSE
	pauseFlag = false;
	//�����ă�
	iventFlag = false;
	
	msgType = MSG_START;
	msgFlag = 0;
	for (int m = 0; m < MSG_MAX; m++)
	{
		msgCheck[m] = 0;
	}
	msgCnt = 0;
	titleCounter = 0;
	msgID = 0;
	playerSize = { 20,20 };

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
	titleCounter++;

	if (msgType == MSG_START)
	{
		//-----��ݑJ��
		if (KeyDownTrigger[KEY_ID_SPACE]) SceneID = SCENE_GAME;
	}
	else if (msgType == MSG_LOAD)
	{
		if (KeyDownTrigger[KEY_ID_SPACE]) msgFlag = true;
		if ((msgCnt > 250) || KeyDownTrigger[KEY_ID_ENTER])
		{
			msgCnt = 0;
			msgFlag = false;
		}
	}

	

	//-----�`��
	TitleDraw();

}
//���ق̕`��
void TitleDraw(void)
{
	for (int i = 0; i < MSG_MAX; i++)
	{
		if (!msgCheck[i])
		{
			switch (msgType)
			{
			case MSG_START:
				msgCheck[MSG_START] = true;
				msgCheck[MSG_LOAD] = false;
				break;
			case MSG_LOAD:
				msgCheck[MSG_LOAD] = true;
				msgCheck[MSG_START] = false;
				break;
			case MSG_MAX:
				break;
			default:
				break;
			}
		}
	}

	if (KeyDownTrigger[KEY_ID_UP])
	{
		msgID--;
		if (msgID < 0) msgID = MSG_MAX - 1;
		//	msgType = MSG_START;
	}

	if (KeyDownTrigger[KEY_ID_DOWN])
	{
		msgID++;
		if (msgID > MSG_MAX - 1) msgID = 0;
	}

	if (msgID == 0)
	{
		msgType = MSG_START;
	}
	else if (msgID == 1)
	{
		msgType = MSG_LOAD;
	}

	//-----�`�揈��
	DrawGraph(0, 0, bgImage, true);
	DrawGraph((SCREEN_SIZE_X - 400) / 2, 10, rogoImage, true);

	for (int i = 0; i < MSG_MAX; i++)							//ү����
	{
		//�I����
		if (msgCheck[i])
		{
			if (msgType == MSG_START)
			{
				if ((titleCounter / 30) % 2 == 0)
				{
					DrawGraph((SCREEN_SIZE_X - 400) / 2, 400, msgImage[MSG_START], true);
				}

			}
			else if (msgType == MSG_LOAD)
			{
				if ((titleCounter / 30) % 2 == 0)
				{
					DrawGraph((SCREEN_SIZE_X - 400) / 2, 500, msgImage[MSG_LOAD], true);

				}
			}
		}
		//���I����
		else
		{
			DrawGraph((SCREEN_SIZE_X - 400) / 2, 400 + 100 * i, msgImage[i], true);
		}
	}

	//�Â����炷��A��I����������ү����
	if (msgFlag)
	{
		msgCnt++;
		DrawBox(250, 200, 550, 450, 0xFFFFFF, true);
		SetFontSize(16);
		DrawString(295, 240,
			"�@�@ �@�@������\n�Z�[�u�f�[�^�����݂��܂���\n\n�@�@���͂��߂����遄\n\n  ��I�юn�߂Ă�������",
			0x000000);
		SetFontSize(12);
		DrawString(255, 410, "�����̉�ʂ�ENTER KEY\n�@���́A���Ԍo�߂ŕ��܂�", 0x000000);
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
	if (KeyDownTrigger[KEY_ID_SPACE]) fadeOut = true;

	/*if (playerDead())
	{
		GameOverCnt++;
		if (GameOverCnt > 100)
		{
			SceneID = SCENE_GAMEOVER;
			GameOverCnt = 0;
		}
	}*/
	// �Q�[���I�[�o�[
	//////////////////////////////////
	/*if (GameOverSet())
	{
		GameOverCnt++;
		if (GameOverCnt > 100)
		{
			SceneID = SCENE_GAMEOVER;
			GameOverCnt = 0;
		}
	}*/
	/////////////////////////////////
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

		// �C�x���g����
		if (GetEvent(playerPos) == EVENT_ID_KAIDAN)
		{
			SetMapData(STAGE_ID_MOB);
		}

		//��а�ƒe�̓����蔻��
		for (int sh = 0; sh < SHOT_MAX; sh++)
		{
			if (shot[sh].life > 0)
			{
				if (EnemyHitCheck(shot[sh].pos, shot[sh].size.x))
				{
					DeleteShot(sh);
				}
			}
		}
		//�A�C�e���ƃv���C���[�̓����蔻��
		if (ItemHitCheck(playerPos, playerSize.x))
		{
			//���тɓ������Ă���
			DeleteItem();
		}
	}


	//-----�`��
	GameDraw(); 

	return;
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
	//DrawFormatString(0, 140, 0xFFFFFF, "GameOver:%d", GameOverCnt);
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
	DrawGraph((SCREEN_SIZE_X - 400) / 2, (SCREEN_SIZE_Y - 200) / 2, overImage, true);

	//-----��񏈗�
	DrawFormatString(0, 0, 0xFFFFFF, "GameOver:%d", SceneCounter);


}

//�ްѸر���
void GameClearScene(void)
{
	if (KeyDownTrigger[KEY_ID_SPACE]) SceneID = SCENE_INIT;

	GameClearDraw();
}

//�ްѸر�̕`��
void GameClearDraw(void)
{
	//-----�`�揈��
	DrawGraph((SCREEN_SIZE_X - 400) / 2, (SCREEN_SIZE_Y - 200) / 2, clearImage, true);


	//-----��񏈗�
	DrawFormatString(0, 0, 0xFFFFFF, "GameClear:%d", SceneCounter);


}

