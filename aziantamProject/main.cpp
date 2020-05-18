#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "effect.h"
#include "enemy.h"
#include "shot.h"
#include "item.h"
#include "stage.h"

//�ϐ�
SCENE SceneID;
SCENE ScenePreID;	//�ߋ��̼�݊i�[�p
int SceneCounter;

//�׽����ݽ�ݽ�𐶐�
enemy* enemyI;
enemy* enemyY;
enemy* enemyA;

//Win�֐�
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	if (!SystemInit())return -1;

	//-----�ް�ٰ��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
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
		ScreenFlip();		//�@����ʂ�\��ʂɏu�Ժ�߰
	}
	//�ݽ�ݽ�̉��


	DxLib_End();			// DXײ���؂̏I������
	return 0;				// ������۸��т̏I��

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
	
	//-----�ݽ�ݽ�̐���
	enemyI = new enemy(ENEMY_I_MOB
		, 100, 100
		, "char/�d��.png", 16
		,4, 4
		,32, 32
	);
	enemyY = new enemy(ENEMY_Y_MOB
		, 150, 100
		, "char/wind_mob_enemy1.png", 16
		, 4, 4
		, 32, 32
	);
	enemyA = new enemy(ENEMY_A_MOB
		, 200, 100
		, "char/umi0.png", 16
		, 4, 4
		, 32, 32
	);


	//-----�eӼޭ�ق̏�����
	enemyI->SystemInit();	//�΋��S��MOB
	enemyY->SystemInit();	//�R�{�S��MOB
	enemyA->SystemInit();	//�r�ؒS��MOB

	//���̨���o�^

	//�ϐ��̏�����
	SceneCounter = 0;
	SceneID = SCENE_INIT;
	ScenePreID = SCENE_MAX;

	return true;
}
//���������
void InitScene(void)
{
	//-----�e��޼ު�ď���
	enemyI->GameInit();		//�΋��S��MOB	
	enemyY->GameInit();		//�R�{�S��MOB	
	enemyA->GameInit();		//�r�ؒS��MOB	

	//-----��ݑJ��
	SceneID = SCENE_TITLE;
}




/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//���ټ��
void TitleScene(void)
{
	//-----��ݑJ��
	SceneID = SCENE_GAME;

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
	//-----�e��޼ު�đ���
	enemyI->Control();		//�΋��S��MOB
	enemyY->Control();		//�R�{�S��MOB	
	enemyA->Control();		//�r�ؒS��MOB


	//-----�`��
	GameDraw();
}


//�ްт̕`��
void GameDraw(void)
{

	//-----�`�揈��
	enemyI->GameDraw();		//�΋��S��MOB
	enemyY->GameDraw();		//�R�{�S��MOB
	enemyA->GameDraw();		//�r�ؒS��MOB
	//-----��񏈗�
	DrawFormatString(0, 0, 0xFFFFFF, "Game:%d", SceneCounter);

}





//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//�ްѵ��ް���
void GameOverScene(void)
{
	GameOverDraw();
}


//�ްѵ��ް�̕`��
void GameOverDraw(void)
{
	//-----�`�揈��

	//-----��񏈗�
	DrawFormatString(0, 0, 0xFFFFFF, "GameOver:%d", SceneCounter);


}
