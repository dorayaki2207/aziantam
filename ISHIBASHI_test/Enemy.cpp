#include "DxLib.h"
#include "test.h"
#include "Stage.h"
#include "Enemy.h"

//-----�O���ϐ��錾
//��ފ֘A
CHARACTER enemyMob[ENEMY_MAX];				
CHARACTER enemyMobMaster[ENEMY_M_MAX];
int enemyImage[ENEMY_M_MAX][16];

//�޽�֘A

//-----��а���̏�����
void EnemySystemInit(void)
{
	//-----�ϐ��̏�����
	//��
	enemyMobMaster[ENEMY_I_MOB].charType = ENEMY_I_MOB;			//	��а�̎��	�F	���
	enemyMobMaster[ENEMY_I_MOB].moveSpeed = 4;					//	��Ȃ̈ړ���
	enemyMobMaster[ENEMY_I_MOB].lifeMax = 50;					//	��Ȃ̗͍̑ő�l
	enemyMobMaster[ENEMY_I_MOB].point = 1;						//	��Ȃ̓��_
	//�ꔽ�ؖ�
	enemyMobMaster[ENEMY_Y_MOB].charType = ENEMY_Y_MOB;			//	��а�̎��	�F	�ꔽ�ؖ�
	enemyMobMaster[ENEMY_Y_MOB].moveSpeed = 4;					//	�ꔽ�ؖȂ̈ړ���
	enemyMobMaster[ENEMY_Y_MOB].lifeMax = 50;					//	�ꔽ�ؖȂ̗͍̑ő�l
	enemyMobMaster[ENEMY_Y_MOB].point = 1;						//	�ꔽ�ؖȂ̓��_
	//�C�V��
	enemyMobMaster[ENEMY_A_MOB].charType = ENEMY_A_MOB;			//	��а�̎��	�F	�C�V��						
	enemyMobMaster[ENEMY_A_MOB].moveSpeed = 4;					//	�C�V��̈ړ���
	enemyMobMaster[ENEMY_A_MOB].lifeMax = 50;					//	�C�V��̗͍̑ő�l
	enemyMobMaster[ENEMY_A_MOB].point = 1;						//	�C�V��̓��_
	//��ނ܂Ƃ߂ď���
	for (int type = 0; type < ENEMY_M_MAX; type++)
	{
		enemyMobMaster[type].moveDir = DIR_DOWN;
		enemyMobMaster[type].pos = { 150,150 };
		enemyMobMaster[type].size = { 32,32 };
		enemyMobMaster[type].offsetSize = { enemyMobMaster[type].size.x / 2
			, enemyMobMaster[type].size.y / 2 };
		enemyMobMaster[type].life = enemyMobMaster[type].lifeMax;
		enemyMobMaster[type].animCnt = 0;
	}

	//-----���̨���̓o�^
	//�΋��S��MOB
	LoadDivGraph("aitem/�d��.png", 16, 4, 4
		, enemyMobMaster[ENEMY_I_MOB].size.x
		, enemyMobMaster[ENEMY_I_MOB].size.y
		, enemyImage[ENEMY_I_MOB]);
	//�R�{�S��MOB
	LoadDivGraph("aitem/wind_mob_enemy1.png", 16, 4, 4
		, enemyMobMaster[ENEMY_Y_MOB].size.x
		, enemyMobMaster[ENEMY_Y_MOB].size.y
		, enemyImage[ENEMY_Y_MOB]);
	//�r�ؒS��MOB
	LoadDivGraph("aitem/umi0.png", 16, 4, 4
		, enemyMobMaster[ENEMY_A_MOB].size.x
		, enemyMobMaster[ENEMY_A_MOB].size.y
		, enemyImage[ENEMY_A_MOB]);

}

void EnemyGameInit(void)
{
	for (int ene = 0; ene < ENEMY_MAX; ene++)
	{
		enemyMob[ene] = enemyMobMaster[GetRand(ENEMY_M_MAX - 1)];
		if (IsPass(enemyMob[ene].pos))
		{
			enemyMob[ene].pos.x = GetRand(20 * CHIP_SIZE_X - 1);
			enemyMob[ene].pos.y = GetRand(25 * CHIP_SIZE_X - 1);
		}
	}
}

void EnemyControl(XY pPos)
{
}

void EnemyGameDraw(void)
{
	for (int ene = 0; ene < ENEMY_MAX; ene++)
	{

		if (enemyMob[ene].life > 0)
		{
			enemyMob[ene].animCnt++;

			DrawGraph(enemyMob[ene].pos.x - enemyMob[ene].offsetSize.x + mapPos.x
				, enemyMob[ene].pos.y - enemyMob[ene].offsetSize.y + mapPos.y
				, enemyImage[enemyMob[ene].charType][enemyMob[ene].moveDir * 4 + ((enemyMob[ene].animCnt / 40) % 4)]
				, true);


			DrawBox(enemyMob[ene].pos.x - enemyMob[ene].offsetSize.x + mapPos.x
				, enemyMob[ene].pos.y - enemyMob[ene].offsetSize.y + mapPos.y
				, enemyMob[ene].pos.x - enemyMob[ene].offsetSize.x + enemyMob[ene].size.x + mapPos.x
				, enemyMob[ene].pos.y - enemyMob[ene].offsetSize.y + enemyMob[ene].size.y + mapPos.y
				, 0xFF00FF, false);

		}
	}
}

//-----�e�ƓG�̓����蔻��@(true : ������, false : �͂���)
bool EnemyHitCheck(XY sPos, int sSize)
{
	//�S�Ă̓G�ɓ����蔻������{����
	for (int en = 0; en < ENEMY_MAX; en++)
	{
		if (enemyMob[en].life > 0)
		{
			if (((enemyMob[en].pos.x - enemyMob[en].size.x / 2) < (sPos.x + sSize / 2))
				&& ((enemyMob[en].pos.x + enemyMob[en].size.x / 2) > (sPos.x - sSize / 2))
				&& ((enemyMob[en].pos.y - enemyMob[en].size.y / 2) < (sPos.y + sSize / 2))
				&& ((enemyMob[en].pos.y + enemyMob[en].size.y / 2) > (sPos.y - sSize / 2)))
			{
				//�����������A��а�̗̑͂����炷
				enemyMob[en].life--;
				return true;
			}
		}
	}
	//�e���O�ꂽ��
	return false;
}