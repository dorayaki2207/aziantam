// �^�C�g���V�[���@�Z���N�g�r��:�΋�
//�U�����D���S��0���ɂȂ�����I���B

#include <DxLib.h>
#include "main.h"
#include "keycheck.h"
#include "title.h"
#include "effect.h"
#include "stage.h"
#include "player.h"
#include "enemy.h"
#include "shot.h"
#include "item.h"
#include "mark.h"


//-----�ϐ�
//��݊֘A
SCENE SceneID;
SCENE ScenePreID;	//�ߋ��̼�݊i�[�p
int SceneCounter;
int GameOverCnt;
//������؊֘A
bool iventFlag;

//PAUSE�֘A
bool pauseFlag;
int keyImage;

//�����蔻��p
XY playerSize;

//���ިݸފ֘A
int clearImage;
int overImage;
int clear_bgImage;
int over_bgImage;


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
		//�ްѸر���
		case SCENE_CLEAR:
			GameClearScene();
			break;

		case SCENE_MAX:
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
	TitleSystemInit();			//����
	StageSystemInit();			//�ð��
	PlayerSystemInit();			//��ڲ԰
	EnemySystemInit();			//�Gmob
	ItemSystmeInit();			//����
	ShotSystemInit();			//����
	EffectSystemInit();			//�̪��
	MarkSystemInit();
	//-----���̨���o�^
	keyImage = LoadGraph("item/�������.png");
	clearImage = LoadGraph("item/clear.png");
	overImage = LoadGraph("item/over.png");
	clear_bgImage = LoadGraph("item/bg_clear.png");
	over_bgImage = LoadGraph("item/bg_over.png");
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
	//�����蔻��p
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
	EFlagInit();					//eFlag��p
	ItemGameInit();					//����
	ShotGameInit();					//����
	EffectGameInit();				//�̪��
	MarkGameInit();
	//-----��ݑJ��
	SceneID = SCENE_TITLE;
}




///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//�ްѼ��
void GameScene(void)
{
	XY playerPos;		//��ڲ԰�̍��W�i�[�̈�


	//��ݑJ��
	if (KeyDownTrigger[KEY_ID_SPACE]) SceneID = SCENE_CLEAR;
	if ((GameOverSet()) || (PlayerDid()))
	{
		GameOverCnt++;
		if (GameOverCnt > 100)
		{
			SceneID = SCENE_GAMEOVER;
			GameOverCnt = 0;
		}
	}

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
		ItemDropControl();					//����
		ShotControl(playerPos);			//����
		EffectControl();					//�̪��
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
		//�A�C�e���ƃv���C���[�̓����蔻��
		if (ItemHitCheck(playerPos, playerSize.x))
		{
			//���тɓ������Ă���
			DeleteItem();
		}

		MapChange();


		//���ׂĂ�enemy��|�������̏����itrue:�N���A�V�[���ɑJ�ځAfalse:�܂��|���ĂȂ��j
		if (SetEnemyMoment(playerPos))
		{
			SceneID = SCENE_CLEAR;
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
	EffectGameDraw();			//�̪��
	MarkGameDraw();

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
	DrawFormatString(0, 140, 0xFFFFFF, "GameOver:%d", GameOverCnt);

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
	DrawGraph(0, 0, over_bgImage, true);
	DrawGraph((SCREEN_SIZE_X - 400) / 2, (SCREEN_SIZE_Y - 200) / 3, overImage, true);

	//-----��񏈗�
	DrawFormatString(0, 0, 0xFFFFFF, "GameOver:%d", SceneCounter);


}





//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
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
	DrawGraph(0, 0, clear_bgImage, true);
	DrawGraph((SCREEN_SIZE_X - 400) / 2, (SCREEN_SIZE_Y - 200) / 3, clearImage, true);


	//-----��񏈗�
	DrawFormatString(0, 0, 0xFFFFFF, "GameClear:%d", SceneCounter);


}
