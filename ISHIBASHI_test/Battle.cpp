#include "DxLib.h"
#include "test.h"
#include "KeyCheck.h"
#include "Item.h"
#include "Battle.h"

int testbkImage;		//ýėp�w�i

CHARACTER boss;
int tBossImage[8];		//�҂���S�ʏ펞
int tBossDImage[2];		//�҂���S��Ұ�ގ�
int BossImage;


void BattleSystmeInit(void)
{
	//-----������
	boss.size = { 400,500 };							//	��׸��̉摜����
	boss.offsetSize = { boss.size.x / 2,boss.size.y / 2 };		//�@��׸��̵̾��
	boss.hitFlag = false;			//�U�����󂯂Ă��邩�ǂ���
	
	//-----���̨���̓o�^
	testbkImage = LoadGraph("aitem/bg.jpg");
	LoadDivGraph("aitem/boss.png", 8, 4, 2, boss.size.x, boss.size.y, tBossImage);
	LoadDivGraph("aitem/bs_D.png", 2, 2, 1, boss.size.x, boss.size.y, tBossDImage);

	BossImage = LoadGraph("aitem/boss2.png");

}

void BattleGameInit(void)
{
	boss.pos = { (SCREEN_SIZE_X - boss.size.x) / 2,(BOX_Y - boss.size.y) / 2 };				//�@��׸��̒n�}��̍��W
	boss.lifeMax = 500;												//	��׸��̗͍̑ő�l
	boss.life = boss.lifeMax;										//	��׸��̗̑�
	boss.animCnt = 0;													//	��׸��̱�Ұ���

}


void BattleScene(void)
{

	if (keyDownTrigger[KEY_ID_SPACE])
	{
		sceneID = SCENE_ID_INIT;
	}
	ItemControl();
	BattleControl();
	//�`�揈��
	BattleGameDraw();
}


void BattleControl(void)
{

	for (int type = 0; type < ITEM_TYPE_F_MAX; type++)
	{
		if (itemF[type].point--)
		{
			boss.hitFlag = true;
		}
	}



}



void BattleGameDraw(void)
{
	//-----�`�揈��
	//�w�i
	DrawGraph(0, 0, testbkImage, true);
	//�G
	if (boss.life > 0)
	{
		boss.animCnt++;
		if (!boss.hitFlag)
		{
			DrawGraph(boss.pos.x, boss.pos.y, tBossImage[(boss.animCnt / 16) % 8], true);
		}
		else if(boss.hitFlag)
		{
			DrawGraph(boss.pos.x, boss.pos.y, tBossDImage[(boss.animCnt / 10) % 2], true);
		}
		//	DrawGraph((SCREEN_SIZE_X - 400) / 2, 0, BossImage, true);
	}
	//-----��񏈗�
	DrawFormatString(0, 0, 0xFFFFFF, "Battle : %d", SceneCounter);

	SetDrawBright(200, 200, 200);
	DrawBox(BOX_X, BOX_Y, BOX_END_X, BOX_END_Y, 0xFFFFFF, true);
	SetDrawBright(255, 255, 255);
	DrawBox(BOX_X, BOX_Y, BOX_END_X, BOX_END_Y, 0xFF22FF, false);


	//����
	ItemB_Draw();

}
