



#include "DxLib.h"
#include "stdio.h"
#include "test.h"
#include "KeyCheck.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Shot.h"
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

//��b�V�X�e��
const char *file;
char words[200];



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
	if (DxLib_Init() == -1)
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);


	//-----���͏�񏉊���
	KeyInit();
	//-----�e��޼ު�Ă̏�����
	StageSystemInit();			//�ð��
	PlayerSystemInit();			//��ڲ԰
	EnemySystemInit();			//��а
	ItemSystemInit();			//����
	ShotSystemInit();			//����
	BattleSystemInit();			//����

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
	StageGameInit();		//�ð��
	ItemGameInit();			//����
	PlayerGameInit();		//��ڲ԰
	EnemyGameInit();		//��а
	ShotGameInit();			//����
	BattleGameInit();		//����

	
	sceneID = SCENE_ID_GAME;
}

//-----���ټ��
void TitleScene()
{

	if (keyDownTrigger[KEY_ID_SPACE])
	{
		sceneID = SCENE_ID_GAME;
	}

	DrawFormatString(0, 0, 0xFFFFFF, "Title:%d", SceneCounter);
}

//-----�ްѼ��
void GameScene()
{
	XY playerPos;


	if (keyDownTrigger[KEY_ID_SPACE])
	{
		sceneID = SCENE_ID_BATTLE;
	}


	//-----FILE����
//	FILE *fp;
//	
//	fopen_s(&fp, file, "r");
//	fread(words, sizeof(words), size_t(2), fp);
//	fclose(fp);


	//-----�����؋@�\
	//������
	if (keyDownTrigger[KEY_ID_IVENT]) iventFlag = !iventFlag;
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
		EnemyControl(playerPos);
		ShotControl(playerPos);
		itemDropControl();
		
		if (GetEvent(playerPos) == EVENT_ID_DOKUTU)
		{
			SetMapData(STAGE_ID_ONI2);
		}
		if (GetEvent(playerPos) == EVENT_ID_KAIDAN2)
		{
			//�S�X�e�[�W�@�̍Ւd�Ɉړ�������
			SetMapData(STAGE_ID_ONI);
		//	GetPos(playerPos);
		
		}


		//�e�ƴ�а�̓����蔻��
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


	//�ްѼ�ݕ`��
	GameDraw();
	

}

//-----�ްѼ�ݕ`�揈��
void GameDraw()
{
	//-----�e��޼ު�ĕ`�揈��
	StageGameDraw();			//�ð��
	ItemGameDraw();				//����
	PlayerGameDraw();			//��ڲ԰
	ShotGameDraw();				//����
	EnemyGameDraw();			//��а
	
	//-----��񏈗�
	DrawFormatString(0, 0, 0xFFFFFF, "GameMain : %d", SceneCounter);
//	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0x55FF55, true);
	
	

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

		DrawFormatString(0, 215, 0xFF22FF, "%d", itemF[MAGIC_TYPE_FIRE].point);
		DrawFormatString(0, 230, 0xFF22FF, "%d", itemF[MAGIC_TYPE_WATER].point);
		DrawFormatString(0, 245, 0xFF22FF, "%d", itemF[MAGIC_TYPE_WIND].point);
		DrawFormatString(0, 260, 0xFF22FF, "%d", itemF[MAGIC_TYPE_HEAL].point);


	}


}



