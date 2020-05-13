//-------------------------
// AsoulQuest = main.cpp
// 2019.09.26
// �R�{���R�I
//-------------------------

#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "effect.h"
#include "stage.h"
#include "player.h"
#include "enemy.h"
#include "shot.h"

//�萔
//---------------------------------------
#define DRAW_ORDER_MAX ENEMY_MAX + SHOT_MAX + 1	 //�v���C���[����1

//��`
//----------------------------------------
//��׸��\�����Ǘ��p
struct  DRAW_ORDER
{
	CHARACTER_TYPE characterType;	//��׸��̎��
	int index;						//��׸��z��̓Y����
	int y;							//��׸��̑���Y���W
};

//�ϐ�
//���������������������������������������
//���ъ֘A
SCENE_ID SceneID;		//���݂̼�݊i�[�p
SCENE_ID ScenePreID;	//�ߋ��̼�݊i�[�p
//int gameCounter;		//gameLoop����m�F�p
int SceneCounter;		//��ݗp�̶����
//���ي֘A
int TitleImage;			//���ى摜�i�[�p
int TitlePosX;			//
int TitlePosY;			//
//�ްѵ��ް�֘A
int GameOverImage;		//�ްѵ��ް�摜�i�[�p
int GameOverPosX;		//
int GameOverPosY;		//
//˯Ľ��ķ��֘A	
int HitStartKeyImage;	//˯Ľ��ķ��摜�i�[�p
int HitStartKeyPosX;	//
int HitStartKeyPosY;	//
//̧�ُ���`
char fileName[] = "asoulquest.dat";	//̧�ق̖��O���`
FILE_DATA fileData;					//���_�Ǘ��p
//��׸��̕\����
int drawOrderCnt;							//�\�����鷬׸���
DRAW_ORDER drawOrDerList[DRAW_ORDER_MAX];	//�\�����鷬׸��̕\�������


//WinMain()
//������������
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//------����������
	if (!SystemInit())
	{
		return -1;
	}
	//�������ް�ٰ��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//��ݶ���ؾ��
		if (SceneID != ScenePreID)
		{
			ScenePreID = SceneID;
			SceneCounter = 0;
		}
		//�\�����̏�����
		drawOrderCnt = 0;
		for (int d = 0; d < DRAW_ORDER_MAX; d++)
		{
			drawOrDerList[d].characterType = CHARACTER_MAX;
			drawOrDerList[d].index = 0;
			drawOrDerList[d].y = 0;
		}

		//���͏��̊m�F
		KeyCheck();

		ClsDrawScreen();	//��ʏ���
		
		//��ݑI��
		//-----------------
		switch (SceneID)
		{
		//������
		case SCENE_ID_INIT:
			InitScene();
			SceneID = SCENE_ID_TITLE;
			break;
		//�^�C�g��
		case SCENE_ID_TITLE:
			//��ʐ؂�ւ��G�t�F�N�g
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {}//�G�t�F�N�g�I����̏���
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					//�G�t�F�N�g�I����̏���
					SceneID = SCENE_ID_GAME;
					fadeIn = true;
				}
			}
			TitleScene();
			break;
		//�Q�[��
		case SCENE_ID_GAME:
			//��ʐ؂�ւ��G�t�F�N�g
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {}//�G�t�F�N�g�I����̏���
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					//�G�t�F�N�g�I����̏���
					SceneID = SCENE_ID_GAMEOVER;
					fadeIn = true;
				}
			}
			GameScene();
			break;
		//�Q�[���I�[�o�[
		case SCENE_ID_GAMEOVER:
			//��ʐ؂�ւ��G�t�F�N�g
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {}//�G�t�F�N�g�I����̏���
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					//�G�t�F�N�g�I����̏���
					SceneID = SCENE_ID_INIT;
					fadeIn = true;
				}
			}
			GameOverScene();
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
	//����������я���
	SetWindowText("191645_�R�{���R�I");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	//���͏��̏�����
	KeyInit();
	//�G�t�F�N�g�̏�����
	EffectInit();

	
	SetTransColor(255, 0, 255);
	StageSystemInit();	//�X�e�[�W���̏�����
	PlayerSystemInit();	//��ڲ԰���̏�����
	EnemySystemInit();	//�G���̏�����
	ShotSystemInit();	//�e���̏�����
	//--------���̨���o�^------------------
	TitleImage = LoadGraph("bmp/title.bmp");
	GameOverImage = LoadGraph("bmp/gameover.png");
	HitStartKeyImage = LoadGraph("bmp/hitstartkey.png");
	
	
	
	//�ϐ��̏�����
	SceneCounter = 0;
	SceneID = SCENE_ID_INIT;
	ScenePreID = SCENE_ID_MAX;
	fadeIn = true;
	fileData.Score = 0;
	fileData.hiScore = 0;
	TitlePosX = (SCREEN_SIZE_X - TITLE_SIZE_X) /2;
	TitlePosY = (SCREEN_SIZE_Y - TITLE_SIZE_Y) /2;
	GameOverPosX = (SCREEN_SIZE_X - GAMEOVER_SIZE_X) /2;
	GameOverPosY = (SCREEN_SIZE_Y - GAMEOVER_SIZE_Y) /2;
	HitStartKeyPosX = (SCREEN_SIZE_X - HITSTARTKEY_SIZE_X) /2;
	HitStartKeyPosY = (SCREEN_SIZE_Y - HITSTARTKEY_SIZE_Y) /2 + (TITLE_SIZE_Y - HITSTARTKEY_SIZE_Y);
	
	return true;
}

//���������
void InitScene(void)
{
	StageGameInit();
	PlayerInit();	//
	EnemyGameInit();
	ShotGameInit();

}

//���ټ��
void TitleScene(void)
{
	if (KeyDownTrigger[KEY_ID_SPACE])
	{
		//SceneID = SCENE_ID_GAME;
		fadeOut = true;
	}
	TitleDraw();
	
}
//�����������A�����œn���ꂽ�l�𑫂������ʂ�߂�l�ŕԂ��B
int  AddValue ( int a,int b) //�����F�^�ƈ����̕ϐ���ݒ肷��@void:�Ԃ��Ȃ��B
{
	//�֐����̏���������
	int t;
	t = a + b;
	//�֐��̖߂�l������Ζ߂�l��ݒ�@���g��ς���A�h���X�n���B
	return t;

}
//������3����A���߂�2�̈����̒l���v�Z�B���ʂ�3�Ԗڂ̕ϐ��Ɋi�[���ĕԂ��B�֐��̖߂�l�͂Ȃ��B
void AddValue2(int a, int b,int *sum) //�����F�^�ƈ����̕ϐ���ݒ肷��
{
	//�֐����̏���������
	*sum = a + b;

}
//���ټ�݂̕`��p���
void TitleDraw(void)
{
	int c = 5;
	int d = 3;
	int CandDsum;
	CandDsum = AddValue(c,d);

	int e = 3;
	int f = 2;
	int EandFsum = 0;

	AddValue2(e, f,&EandFsum);

	//DrawBox(100, 100, 700, 500, 0x00FF00, true);
	DrawGraph(TitlePosX,TitlePosY,TitleImage,true);
	DrawGraph(HitStartKeyPosX, HitStartKeyPosY,HitStartKeyImage,true);
	DrawFormatString(0, 0, 0xFFFFFF, "TitleScene:%d", SceneCounter);
	DrawFormatString(50, 50, 0xFFFFFF, "%d + %d = %d",c,d, CandDsum);
	DrawFormatString(50, 80, 0xFFFFFF, "%d + %d = %d", e, f,EandFsum);

}
//�ްѼ��
void GameScene(void)
{
	XY playerPos;
	XY enemyPos;
	CHARACTER shot;
	bool MoveFlag = true;

	if (KeyDownTrigger[KEY_ID_SPACE])
	{
		//SceneID = SCENE_ID_GAMEOVER;
		fadeOut = true;
	}
	//Pause�@�\
	if (KeyDownTrigger[KEY_ID_PAUSE])
	{
		pauseFlag = !pauseFlag;
	}
	//Pause��
	if (pauseFlag) SetDrawBright(128, 128, 128);
	//�ʏ퓮��
	else
	{
		//�e�폈��
		playerPos = PlayerControl();	//��ڲ԰�̑���
		enemyPos = EnemyControl(playerPos);	//�G�̑���
		shot = ShotControl();					//�e�̑���
		if (GetEvent(playerPos) == EVENT_ID_KAIDAN)
		{
			EnemyGameInit();
			SetMapData(STAGE_ID_MAZE);
			//playerPos = { 100,100 };
		}
		if (GetEvent(playerPos) == EVENT_ID_KAIDAN)
		{
			EnemyGameInit();
			SetMapData(STAGE_ID_START);

			//playerPos = { 100,100 };
		}
		//�����蔻��̃`�F�b�N
		for (int s = 0; s < SHOT_MAX; s++)
		{
			//���e�ƓG�Ƃ̓����蔻��
			if (EnemyHitCheck(shot))
			{
				//�G�ɂ��e�����������B�e������
//				shot[s].Life = 0;
				DeleteShot(s);
			}
			/*if (PlayerHitCheck(shot, CHARACTER_ENEMY))
			{
				DeleteShot(s);
			}*/
		}
		
		

		//������X�R�A�̃Z�[�u�A���[�h
		//�Z�[�u
		if (KeyDownTrigger[KEY_ID_SAVE])	SaveData();
		//���[�h
		if (KeyDownTrigger[KEY_ID_LOAD])	LoadData();
	}
	//��ʕ`��
	GameDraw();
	//Pause�̃��b�Z�[�W�`��
	if (pauseFlag)
	{
		SetDrawBright(255, 255, 255);
		DrawString((SCREEN_SIZE_X - 9 * 8)/2, (SCREEN_SIZE_Y - 9 * 8)/2, "�o�`�t�r�d",0xFFFFFF);
	}
}
//�ްѼ�݂̕`��p���
void GameDraw(void)
{	
	//DrawBox(100, 100, 700, 500, 0xFF0000, true);
	StageGameDraw();	//�n�}��\��
	
	for (int o = 0; o < drawOrderCnt; o++)
	{
		//�\���Ώۂ��`�F�b�N���ĕ\������
		switch (drawOrDerList[o].characterType)
		{
		case CHARACTER_PLAYER:
			//��ڲ԰�̕\��
			PlayerDraw();
			break;
		case CHARACTER_ENEMY:
			//�G�̕\��(�C���f�b�N�X�Łj
			EnemyGameDrawOrder(drawOrDerList[o].index);
			break;
		case CHARACTER_SHOT:
			//�e��\��
			ShotGameDrawOrder(drawOrDerList[o].index);
			break;
		default:
			break;
		}
		
	}
	EnemyGameDraw();	//�G��\��
	//ShotGameDraw();		//�e��\��
	//PlayerDraw();		//��ڲ԰��\��

	DrawFormatString(0, 0, 0xFFFFFF, "GameScene:%d", SceneCounter);

	DrawBox(200, 0, 600, 16, 0x0, true);
	DrawFormatString(250, 0, 0xFFFFFF, "SCORE:%d", fileData.Score);
	DrawFormatString(450, 0, 0xFFFFFF, "HISCORE:%d", fileData.hiScore);
}
//�ްѵ��ް���
void GameOverScene(void)
{
	//if (KeyDownTrigger[KEY_ID_SPACE])
	//{
		//SceneID = SCENE_ID_INIT;
		fadeOut = true;
	//}
	GameOverDraw();
}
//�ްѵ��ް��݂̕`��p���
void GameOverDraw(void)
{
	//DrawBox(100, 100, 700, 500, 0x0000FF, true);
	DrawGraph(GameOverPosX, GameOverPosY, GameOverImage, true);
	DrawGraph(HitStartKeyPosX, HitStartKeyPosY, HitStartKeyImage, true);
	DrawFormatString(0, 0, 0xFFFFFF, "GameOverScene:%d", SceneCounter);
}
//���_��ǉ�����
void AddScore(int point)
{
	fileData.Score += point;
	if (fileData.hiScore < fileData.Score) fileData.hiScore = fileData.Score;
}
//̧�ق���X�R�A���������݂�����
bool SaveData(void)
{
	FILE *fp;
	fopen_s(&fp, fileName, "wb");
	fwrite(&fileData, sizeof(fileData), 1, fp);
	fclose(fp);
	return true;
}
//̧�ق���X�R�A��ǂݍ���
bool LoadData(void)
{
	FILE *fp;
	fopen_s(&fp, fileName, "rb");
	fread(&fileData, sizeof(fileData), 1, fp);
	fclose(fp);
	return true;
}
//��׸�����drawOrderList�ɒǉ�����
void AddCharOrder(CHARACTER_TYPE characterType, int index, int y)
{
	int insertIndex = drawOrderCnt;		//�}������ꏊ

	//1�A����Y���W���z����̂ǂ̏��Ԃɓ��邩���m�F����
	for (int d = 0; d < drawOrderCnt; d++)
	{
		//�z�����Y���W�ƈ���Y���W���r���Ă����ꏊ�����߂�
		if (drawOrDerList[d].y > y)
		{
			//�}���ꏊ�����܂����B
			insertIndex = d;
			//���[�v�𔲂���B
			break;
		}
	}
	//2�A�����ꏊ�����܂����̂ł��̏ꏊ�ɂ��錳�X�����Ă����f�[�^�����ɂ��炷
		//�����ꏊ��艺�̃f�[�^����i��Ɉڂ��B
	for (int d = drawOrderCnt; d > insertIndex; d--)
	{
		drawOrDerList[d] = drawOrDerList[d - 1];
	}
	//3�A�����̃f�[�^���i�[����
	drawOrDerList[insertIndex].characterType = characterType;
	drawOrDerList[insertIndex].index = index;
	drawOrDerList[insertIndex].y = y;

	drawOrderCnt++;
}