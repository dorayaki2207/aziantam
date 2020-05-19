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
//�G
Enemy* enemyI;		//�΋��S��MOB
Enemy* enemyY;		//�R�{�S��MOB
Enemy* enemyA;		//�r�ؒS��MOB
//����
Item* d_hi;			//�΂̌�D�F��̫��


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
		ScreenFlip();		//����ʂ�\��ʂɏu�Ժ�߰
	}
	//-----�ݽ�ݽ�̉��
	//�G
	delete enemyI;			//�΋��S��MOB
	delete enemyY;			//�R�{�S��MOB
	delete enemyA;			//�r�ؒS��MOB
	//����
	delete d_hi;			//�΂̌�D�F��̫��

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
	
	//-----�ݽ�ݽ�̐���
	//�G
	enemyI = new Enemy(ENEMY_I_MOB			//�΋��S��MOB
		, 100, 100
		, "char/�d��.png", 16
		,4, 4
		,32, 32
	);										
	enemyY = new Enemy(ENEMY_Y_MOB			//�R�{�S��MOB
		, 150, 100
		, "char/wind_mob_enemy1.png", 16
		, 4, 4
		, 32, 32
	);
	enemyA = new Enemy(ENEMY_A_MOB			//�r�ؒS��MOB
		, 200, 100
		, "char/umi0.png", 16
		, 4, 4
		, 32, 32
	);
	//����
	d_hi = new Item(ITEM_M_HI, 150, 150
		, "itam/fuda.png", 8, 4, 2, 20, 20);



	//-----�eӼޭ�ق̏�����
	//�G
	enemyI->SystemInit();	//�΋��S��MOB
	enemyY->SystemInit();	//�R�{�S��MOB
	enemyA->SystemInit();	//�r�ؒS��MOB
	//����
	d_hi->SystemInit();		//�΂̌�D�F��̫��

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
	//�G
	enemyI->GameInit();		//�΋��S��MOB	
	enemyY->GameInit();		//�R�{�S��MOB	
	enemyA->GameInit();		//�r�ؒS��MOB	
	//����
	d_hi->GameInit();			//�΂̌�D�F��̫��

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
	//�G
	enemyI->Control();		//�΋��S��MOB
	enemyY->Control();		//�R�{�S��MOB	
	enemyA->Control();		//�r�ؒS��MOB
	//����
	d_hi->Control();		//�΂̌�D�F��̫��

	//-----�`��
	GameDraw();
}


//�ްт̕`��
void GameDraw(void)
{

	//-----�`�揈��
	//�G
	enemyI->GameDraw();		//�΋��S��MOB
	enemyY->GameDraw();		//�R�{�S��MOB
	enemyA->GameDraw();		//�r�ؒS��MOB
	//����
	d_hi->GameDraw(ITEM_M_HI);		//�΂̌�D�F��̫��
	

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
