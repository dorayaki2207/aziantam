#include <DxLib.h>
#include "main.h"
#include "stage.h"
#include "enemy.h"
#include "item.h"
#include "effect.h"

//-----�O���ϐ��錾
//��ފ֘A
CHARACTER enemyMob[ENEMY_MAX];
CHARACTER enemyMobMaster[ENEMY_M_MAX];
int enemyImage[ENEMY_M_MAX][16];

//���ꂼ��̃X�e�[�W�ɂ���G�̐����m�F�itrue:�S�ŁAfalse:�����j
bool eFlag_1;
bool eFlag_2;
bool eFlag_3;

void EnemySystemInit(void)
{
	//-----�ϐ��̏�����
	//��
	enemyMobMaster[ENEMY_I_MOB].charType = ENEMY_I_MOB;			//	��а�̎��	�F	���
	enemyMobMaster[ENEMY_I_MOB].moveSpeed = 4;					//	��Ȃ̈ړ���
	enemyMobMaster[ENEMY_I_MOB].lifeMax = 3;					//	��Ȃ̗͍̑ő�l
	enemyMobMaster[ENEMY_I_MOB].point = 1;						//	��Ȃ̓��_
	//�ꔽ�ؖ�
	enemyMobMaster[ENEMY_Y_MOB].charType = ENEMY_Y_MOB;			//	��а�̎��	�F	�ꔽ�ؖ�
	enemyMobMaster[ENEMY_Y_MOB].moveSpeed = 4;					//	�ꔽ�ؖȂ̈ړ���
	enemyMobMaster[ENEMY_Y_MOB].lifeMax = 3;					//	�ꔽ�ؖȂ̗͍̑ő�l
	enemyMobMaster[ENEMY_Y_MOB].point = 1;						//	�ꔽ�ؖȂ̓��_
	//�C�V��
	enemyMobMaster[ENEMY_A_MOB].charType = ENEMY_A_MOB;			//	��а�̎��	�F	�C�V��						
	enemyMobMaster[ENEMY_A_MOB].moveSpeed = 4;					//	�C�V��̈ړ���
	enemyMobMaster[ENEMY_A_MOB].lifeMax = 3;					//	�C�V��̗͍̑ő�l
	enemyMobMaster[ENEMY_A_MOB].point = 1;						//	�C�V��̓��_
	//��ނ܂Ƃ߂ď���
	for (int type = 0; type < ENEMY_M_MAX; type++)
	{
		enemyMobMaster[type].moveDir = DIR_DOWN;
		enemyMobMaster[type].pos = { 50,50 };
		enemyMobMaster[type].size = { 32,32 };					
		enemyMobMaster[type].offsetSize = { enemyMobMaster[type].size.x / 2
			, enemyMobMaster[type].size.y / 2 };
		enemyMobMaster[type].life = enemyMobMaster[type].lifeMax;
		enemyMobMaster[type].animCnt = 0;
	}

	//-----���̨���̓o�^
	//�΋��S��MOB
	LoadDivGraph("char/�d��.png", 16, 4, 4
		, enemyMobMaster[ENEMY_I_MOB].size.x
		, enemyMobMaster[ENEMY_I_MOB].size.y
		, enemyImage[ENEMY_I_MOB]);
	//�R�{�S��MOB
	LoadDivGraph("char/wind_mob_enemy1.png", 16, 4, 4
		, enemyMobMaster[ENEMY_Y_MOB].size.x
		, enemyMobMaster[ENEMY_Y_MOB].size.y
		, enemyImage[ENEMY_Y_MOB]);
	//�r�ؒS��MOB
	LoadDivGraph("char/umi0.png", 16, 4, 4
		, enemyMobMaster[ENEMY_A_MOB].size.x
		, enemyMobMaster[ENEMY_A_MOB].size.y
		, enemyImage[ENEMY_A_MOB]);

}

void EnemyGameInit(void)
{
	
	for (int ene = 0; ene < ENEMY_MAX; ene++)
	{
		//stageID��STAGE_ID_START�̂Ƃ��ɁA�ȉ��̏���������B
		if (GetMapDate() == STAGE_ID_START)
		{
			//���C�t��0�ɂ���B
			enemyMob[ene].life = 0;
		}
		//stageID��STAGE_ID_START�ȊO�̂Ƃ��ɁA�ȉ��̏���������B
		else if(GetMapDate() != STAGE_ID_START)
		{
			int type = rand() % ENEMY_M_MAX;
			enemyMob[ene] = enemyMobMaster[type];

			//���C�t��MAX�ɂ���B
			enemyMob[ene].life = enemyMob[ene].lifeMax;

			int x = rand() % MAP_M_X;
			int y = rand() % MAP_M_Y;

			//stageID��STAGE_ID_START��STAGE_ID_MOB�������ꍇ
			if (GetMapDate() == STAGE_ID_MOB)
			{
				//75�ԈȊO��map�z��ɂȂ�����rand�����Ȃ����B
				while (map[y][x] != 75)
				{
					x = rand() % MAP_M_X;
					y = rand() % MAP_M_Y;
				}
			}
			else if (GetMapDate() == STAGE_ID_KAPPA)
			{
				while (map[y][x] != 40)
				{
					x = rand() % MAPA_X;
					y = rand() % MAPA_Y;
				}
			}
			//stageID��STAGE_ID_ONI�������ꍇ
			else if (GetMapDate() == STAGE_ID_ONI)
			{
				//0�ԈȊO��map�z��ɂȂ�����rand�����Ȃ����B
				while (map[y][x] != 0)
				{
					x = rand() % MAPI_X;
					y = rand() % MAPI_Y;
				}
			}

			//enemy��pos��rand�Ō��߂��ꏊ��CHIP_SIZE�Ōv�Z���Ĕz�u�ʒu�����߂�B
			enemyMob[ene].pos.x = x * CHIP_SIZE_X - 1;
			enemyMob[ene].pos.y = y * CHIP_SIZE_Y - 1;

			//��̂܂܂��ƕǂɂ߂荞�񂾂��ʊO�ɂ͂ݏo�����肷��̂ŁA
			//enemy��pos��18�����Ĉʒu�����炷�B
			enemyMob[ene].pos.x += 18;
			enemyMob[ene].pos.y += 18;
		}
	}

}
//�G���X�e�[�W���ƂőS�ł��������f�p�t���O��p�̏�����
bool EFlagInit(void)
{
	eFlag_1 = false;
	eFlag_2 = false;
	eFlag_3 = false;
	return true;
}
void EnemyControl(XY pPos)
{
}
//���ׂĂ�enemy��|�������̏����itrue:�N���A�V�[���ɑJ�ځAfalse:�܂��|���ĂȂ��j
bool SetEnemyMoment(XY pos)
{
	bool Flag = true;

	//���ׂĂ�enemy�̏�Ԃ��擾
	for (int e = 0; e < ENEMY_MAX; e++)
	{
		//enemy�̃��C�t��0�ȉ��ɂȂ���
		if (enemyMob[e].life <= 0)
		{
			//�G�����S���A1�̂���true��������
			//��������ς����Flag���z��ɂȂ��Ă��āA1�̎��񂾂�true��Ԃ��悤�ȏ���
			//Flag[0] = true;
			Flag &= true;
		}
		else
		{
			//�G���������A1�̂���false��������
			Flag &= false;
		}
	}

	//Flag��true�ɂȂ�����
	if (Flag)
	{
		//stage�����u�̃X�e�[�W��������
		if (GetMapDate() == STAGE_ID_MOB)
		{
			//true�ɂ���
			eFlag_1 = true;
		}
		//stage���S�̃X�e�[�W��������
		else if (GetMapDate() == STAGE_ID_ONI)
		{
			//true�ɂ���
			eFlag_2 = true;
		}
		else if (GetMapDate() == STAGE_ID_KAPPA)
		{
			//true�ɂ���
			eFlag_3 = true;
		}

		//�����̃X�e�[�W�œG���S�ł�����
		if (eFlag_1 && eFlag_2)
		{
			//player������̃}�b�v�`�b�v
			if (GetEvent(pos) == EVENT_ID_SPEEDDOWN)
			{
				//true��Ԃ�
				return true;
			}
		}
		else if (eFlag_1 && eFlag_3)
		{
			if (GetEvent(pos) == EVENT_ID_SPEEDDOWN)
			{
				//true��Ԃ�
				return true;
			}
		}
	}
	return false;
}


void EnemyGameDraw()
{
	//-----�`�揈��
	for (int ene = 0; ene < ENEMY_MAX; ene++)
	{
		if (enemyMob[ene].life > 0)
		{
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
		DrawFormatString(0, 200, 0xFFFFFF,"enemyHP:%d", enemyMob[ene].life, true);
	}

}

//-----��а�ƒe�̓����蔻��@(true : ������, false : �͂���)
bool EnemyHitCheck(XY sPos, int sSize, CHARACTER *shot)
{
	auto randam = rand() % 100;
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
				switch (enemyMob[en].charType)
				{
				case ENEMY_I_MOB:
					if ((*shot).charType == MAGIC_TYPE_FIRE) enemyMob[en].life -= DAMAGE_NORMAL;
					if ((*shot).charType == MAGIC_TYPE_WATER) enemyMob[en].life -= DAMAGE_LOW;
					if ((*shot).charType == MAGIC_TYPE_WIND) enemyMob[en].life -= DAMAGE_HIGH;
					
					DamageEffect(enemyMob[en].pos, MAGIC_TYPE_FIRE);

					if (enemyMob[en].life <= 0)
					{
						if (randam > 5)
						{
							ItemDrop(enemyMob[en].pos, MAGIC_TYPE_FIRE);
						}
						else if (randam <= 5)
						{
							ItemDrop(enemyMob[en].pos, MAGIC_TYPE_HEAL);
						}
					}
					break;

				case ENEMY_A_MOB:
					if ((*shot).charType == MAGIC_TYPE_FIRE) enemyMob[en].life -= DAMAGE_HIGH;
					if ((*shot).charType == MAGIC_TYPE_WATER) enemyMob[en].life -= DAMAGE_NORMAL;
					if ((*shot).charType == MAGIC_TYPE_WIND) enemyMob[en].life -= DAMAGE_LOW;
					
					DamageEffect(enemyMob[en].pos, MAGIC_TYPE_WATER);
					
					if (enemyMob[en].life <= 0)
					{
						if (randam > 5)
						{
							ItemDrop(enemyMob[en].pos, MAGIC_TYPE_WATER);
						}
						else if (randam <= 5)
						{
							ItemDrop(enemyMob[en].pos, MAGIC_TYPE_HEAL);
						}
					}
					break;

				case ENEMY_Y_MOB:
					if ((*shot).charType == MAGIC_TYPE_FIRE) enemyMob[en].life -= DAMAGE_LOW;
					if ((*shot).charType == MAGIC_TYPE_WATER) enemyMob[en].life -= DAMAGE_HIGH;
					if ((*shot).charType == MAGIC_TYPE_WIND) enemyMob[en].life -= DAMAGE_NORMAL;
				
					DamageEffect(enemyMob[en].pos, MAGIC_TYPE_WIND);

					if (enemyMob[en].life <= 0)
					{
						if (randam > 5)
						{
							ItemDrop(enemyMob[en].pos, MAGIC_TYPE_WIND);
						}
						else if (randam <= 5)
						{
							ItemDrop(enemyMob[en].pos, MAGIC_TYPE_HEAL);
						}
					}
					break;

				case ENEMY_M_MAX:
					break;
				default:
					break;
				}

				return true;
			}
		}
	}
	//�e���O�ꂽ��
	return false;
}


//�����蔻��
bool PlayerHitCheck(XY sPos, int sSize)
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
				//��������
				return true;
			}
		}
	}
	//�O�ꂽ��
	return false;
}

