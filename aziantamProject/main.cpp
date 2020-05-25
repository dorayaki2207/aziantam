#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "effect.h"
#include "player.h"
#include "enemy.h"
#include "shot.h"
#include "item.h"
#include "stage.h"

//-----�ϐ�
//��݊֘A
SCENE SceneID;
SCENE ScenePreID;	//�ߋ��̼�݊i�[�p
int SceneCounter;



//PAUSE
bool paseFlag;
bool iventFlag;

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
	//��ڲ԰
	PlayerSystemInit();
	//�Gmob
	EnemySystemInit();
	//����
	ItemSystmeInit();
	//-----���̨���o�^


	//-----�ϐ��̏�����
	//��݊֘A
	SceneCounter = 0;
	SceneID = SCENE_INIT;
	ScenePreID = SCENE_MAX;
	//PAUSE
	pauseFlag = false;
	//����ă�
	iventFlag = false;
	
	
	return true;
}
//���������
void InitScene(void)
{
	//-----�e��޼ު�ď���
	PlayerGameInit();				//	�v���C���[
	EnemyGameInit();				//	�G
	ItemGameInit();					//	����
	

	//-----��ݑJ��
	SceneID = SCENE_TITLE;
}




/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//���ټ��
void TitleScene(void)
{
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
		PlayerControl();		//�@��ڲ԰
		EnemyControl();			//	�G
		ItemControl();			//	����
	}

	
	//-----�`��
	GameDraw(); 
}


//�ްт̕`��
void GameDraw(void)
{

	//-----�e��޼ު�ĕ`�揈��
	PlayerGameDraw();			//��ڲ԰
	EnemyGameDraw();			//�G
	ItemGameDraw();				//����
	//-----�����؊֘A
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
		SetDrawBright(255, 255, 255);
		DrawBox(100, 100, 700, 600, 0x222222, true);
	}
	
	//-----��񏈗�
	DrawFormatString(0, 0, 0xFFFFFF, "Game:%d", SceneCounter);

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
