#include "DxLib.h"
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

void char_disp(int White, int y)
{
	DrawString(150, y, "��", White);
	DrawString(170, 100, "NEW_GAME", White);
	DrawString(170, 120, "ONI", White);
	DrawString(170, 140, "TENGU", White);
	DrawString(170, 160, "KAPPA", White);
	DrawString(170, 200, "LOG_OUT", White);
}

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
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {}//�G�t�F�N�g�I���㏈��
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					//�G�t�F�N�g�I���㏈��
					SceneID = SCENE_GAME;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);

				}
			}
			TitleScene();
			break;
		//�ްѼ��
		case SCENE_GAME:
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {}//�G�t�F�N�g�I���㏈��
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					//�G�t�F�N�g�I���㏈��
					SceneID = SCENE_GAMEOVER;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);

				}
			}
			GameScene();
			break;
		//�ްѵ��ް���
		case SCENE_GAMEOVER:
			if (fadeIn)
			{
				if (!FadeInScreen(5))
				{
					fadeOut = false;
				}//�G�t�F�N�g�I���㏈��
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					//�G�t�F�N�g�I���㏈��
					SceneID = SCENE_INIT;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);

				}
			}
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

	StageSystemInit();			//�ð��

	//-----�ϐ��̏�����
	//��݊֘A
	SceneCounter = 0;
	SceneID = SCENE_INIT;
	ScenePreID = SCENE_MAX;
	//PAUSE
	pauseFlag = false;
	//�����ă�
	iventFlag = false;
	
	
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
	int White = GetColor(255, 255, 255);
	int y = 100;

	char_disp(White, y);

	// ���j���[���ڗv�f
	MenuElement_t Menuelement[5] = {
		{350,150,"�`�f�������r���������`"},
	{350,200,"�`���܂��`"},
	{350,250,"�`�g�������`"},
	{350,300,"�`�Q�[���I���`"},
	{350,350,"�`�k�`�m�j�`"},
	};
	int SelectNum = 0;

	// 
	if (KeyDownTrigger[KEY_ID_DOWN] == 1 || (KeyDownTrigger[KEY_ID_DOWN]%5 == 0 && KeyDownTrigger[KEY_ID_DOWN]>30))
	{
		y += 20;
		if (y == 260)
		{
			y = 100;
		}
		SelectNum = (SelectNum + 1) % 5;

		for (int i = 0; i < 5; i++)
		{
			if (i == SelectNum)
			{
				Menuelement[i].x = 80;
			}
			else
			{
				Menuelement[i].x = 100;
			}
		}
		//SceneID = SCENE_GAME;
	}

	// 
	for (int i = 0; i < 5; i++)
	{
		DrawFormatString(Menuelement[i].x-20, Menuelement[i].y, GetColor(255, 255, 255), Menuelement[i].name);
	}

	//-----��ݑJ��
	if (KeyDownTrigger[KEY_ID_SPACE]) SceneID = SCENE_GAME;

	//-----�`��
	TitleDraw();

}
//���ق̕`��
void TitleDraw(void)
{
	//-----�`�揈��

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


		////�ꎞ�I����
		//if (GetEvent(playerPos) == EVENT_ID_KAIDAN)
		//{
		//	stageID = STAGE_ID_START;
		//	SetMapData(STAGE_ID_MOB);
		//	mapPos.x = 0;
		//	mapPos.y = 0;
		//}
		//
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
