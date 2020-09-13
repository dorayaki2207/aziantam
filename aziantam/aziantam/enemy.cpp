#include <DxLib.h>
#include "main.h"
#include "stage.h"
#include "enemy.h"
#include "item.h"
#include "effect.h"
#include "mark.h"


//-----�O���ϐ��錾
//��ފ֘A
CHARACTER enemyMob[ENEMY_MAX];
CHARACTER enemyMobMaster[ENEMY_M_MAX];
int enemyImage[ENEMY_M_MAX][16];
int moveCnt;
int moveFlag;

//���ꂼ��̃X�e�[�W�ɂ���G�̐����m�F�itrue:�S�ŁAfalse:�����j
bool eFlag_mob;
bool eFlag_oni;
bool eFlag_kappa;

void EnemySystemInit(void)
{
	//-----�ϐ��̏�����
	//��
	enemyMobMaster[ENEMY_I_MOB].charType = ENEMY_I_MOB;			//	��а�̎��	�F	���
	enemyMobMaster[ENEMY_I_MOB].moveSpeed = 2;					//	��Ȃ̈ړ���
	enemyMobMaster[ENEMY_I_MOB].lifeMax = 3;					//	��Ȃ̗͍̑ő�l
	enemyMobMaster[ENEMY_I_MOB].point = 1;						//	��Ȃ̓��_
	//�ꔽ�ؖ�
	enemyMobMaster[ENEMY_Y_MOB].charType = ENEMY_Y_MOB;			//	��а�̎��	�F	�ꔽ�ؖ�
	enemyMobMaster[ENEMY_Y_MOB].moveSpeed = 3;					//	�ꔽ�ؖȂ̈ړ���
	enemyMobMaster[ENEMY_Y_MOB].lifeMax = 3;					//	�ꔽ�ؖȂ̗͍̑ő�l
	enemyMobMaster[ENEMY_Y_MOB].point = 1;						//	�ꔽ�ؖȂ̓��_
	//�C�V��
	enemyMobMaster[ENEMY_A_MOB].charType = ENEMY_A_MOB;			//	��а�̎��	�F	�C�V��						
	enemyMobMaster[ENEMY_A_MOB].moveSpeed = 1;					//	�C�V��̈ړ���
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
		enemyMobMaster[type].stageType = STAGE_ID_MOB;
	}

	moveCnt = 0;
	moveFlag = false;
	
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

void EnemyReGameInit()
{
	for (int ene = 0; ene < ENEMY_MAX; ene++)
	{
		int type = rand() % ENEMY_M_MAX;
		enemyMob[ene] = enemyMobMaster[type];

		if (ene >= 0 && ene < ENEMY_MAX / 3)
		{
			enemyMob[ene].stageType = STAGE_ID_MOB;
		}
		else if (ene >= ENEMY_MAX / 3 && ene < ENEMY_MAX - (ENEMY_MAX / 3))
		{
			enemyMob[ene].stageType = STAGE_ID_KAPPA;
		}
		else if (ene >= ENEMY_MAX - (ENEMY_MAX / 3) && ene < ENEMY_MAX)
		{
			enemyMob[ene].stageType = STAGE_ID_ONI;
		}

	}
}

void EnemyGameInit(STAGE_ID stageID)
{
	
	for (int ene = 0; ene < ENEMY_MAX; ene++)
	{

		int x = rand() % MAP_M_X;
		int y = rand() % MAP_M_Y;

		//stageID��STAGE_ID_START��STAGE_ID_MOB�������ꍇ
		if ((enemyMob[ene].stageType == STAGE_ID_MOB) && (stageID == STAGE_ID_MOB))
		{
			//75�ԈȊO��map�z��ɂȂ�����rand�����Ȃ����B
			while (map[y][x] != 75)
			{
				x = rand() % MAP_M_X;
				y = rand() % MAP_M_Y;
			}
		}
		else if ((enemyMob[ene].stageType == STAGE_ID_KAPPA) && (stageID == STAGE_ID_KAPPA))
		{
			while (map[y][x] != 40)
			{
				x = rand() % MAPA_X;
				y = rand() % MAPA_Y;
			}
		}
		//stageID��STAGE_ID_ONI�������ꍇ
		else if ((enemyMob[ene].stageType == STAGE_ID_ONI) && (stageID == STAGE_ID_ONI))
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



//�G���X�e�[�W���ƂőS�ł��������f�p�t���O��p�̏�����
bool EFlagInit(void)
{
	eFlag_mob = false;
	eFlag_oni = false;
	eFlag_kappa = false;
	return true;
}

void EnemyControl(XY pPos)
{
	moveCnt++;
	//�G�̎�ޖ��ɓ����ύX����
	for (int en = 0; en < ENEMY_MAX; en++)
	{
		if (stageID == enemyMob[en].stageType)
		{
			CHARACTER enemyCopy = enemyMob[en];
			XY enemyPosCopy = enemyCopy.pos;

			if ((moveCnt / 60) % 2 == 0) moveFlag = false;
			else moveFlag = true;

			//�����Ă����а�̂ݕ\��
			if (enemyMob[en].life > 0)
			{
				if (moveFlag)
				{
					switch (enemyMob[en].charType)
					{
					case ENEMY_I_MOB:
						if (!MoveEnemyX(&enemyCopy, pPos)) MoveEnemyY(&enemyCopy, pPos);
						break;

					case ENEMY_Y_MOB:
						if (!MoveEnemyY(&enemyCopy, pPos)) MoveEnemyX(&enemyCopy, pPos);
						break;

					case ENEMY_A_MOB:
						MoveEnemyXY(&enemyCopy, pPos);
						break;
					case ENEMY_M_MAX:
						break;
					default:
						break;
					}

					switch (enemyCopy.moveDir)
					{
					case DIR_RIGHT:
						enemyPosCopy.x = enemyCopy.pos.x + 18;
						break;
					case DIR_LEFT:
						enemyPosCopy.x = enemyCopy.pos.x - 18;
						break;
					case DIR_UP:
						enemyPosCopy.y = enemyCopy.pos.y - 18;
						break;
					case DIR_DOWN:
						enemyPosCopy.y = enemyCopy.pos.y + 18;
					}

					enemyMob[en].moveDir = enemyCopy.moveDir;

					if (IsPass(enemyPosCopy))
					{
						enemyMob[en].pos = enemyCopy.pos;
					}

					
				}
			}
		}
	}

}

//���ׂĂ�enemy��|�������̏����itrue:�N���A�V�[���ɑJ�ځAfalse:�܂��|���ĂȂ��j
bool SetEnemyMoment()
{
	bool Flag = true;

	//���ׂĂ�enemy�̏�Ԃ��擾
	for (int e = 0; e < ENEMY_MAX; e++)
	{
		if (enemyMob[e].stageType == stageID)
		{			//�G�����S���A1�̂���true��������

		//enemy�̃��C�t��0�ȉ��ɂȂ���
			if (enemyMob[e].life <= 0)
			{
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
	}

	//Flag��true�ɂȂ�����
		if (Flag)
		{
			//stage�����u�̃X�e�[�W��������
			if (GetMapDate() == STAGE_ID_MOB)
			{
				//true�ɂ���
				eFlag_mob = true;
				mark[STAGE_ID_START].flag = true;
				
			}
			//stage���S�̃X�e�[�W��������
			else if (GetMapDate() == STAGE_ID_ONI)
			{
					//true�ɂ���
				eFlag_oni = true;
				mark[STAGE_ID_START].flag = true;
			}
			else if (GetMapDate() == STAGE_ID_KAPPA)
			{
				//true�ɂ���
				eFlag_kappa = true;
				mark[STAGE_ID_START].flag = true;
			}
		}
		//�����̃X�e�[�W�œG���S�ł�����

		if (GetMapDate() == STAGE_ID_START)
		{
			if (eFlag_mob && eFlag_oni && eFlag_kappa)
			{
				return true;

			}
		}

	return false;
}


void EnemyGameDraw()
{
	//-----�`�揈��
	for (int ene = 0; ene < ENEMY_MAX; ene++)
	{
		if (stageID == enemyMob[ene].stageType)
		{
		
			if (enemyMob[ene].life > 0)
			{
				enemyMob[ene].animCnt++;

				DrawGraph(enemyMob[ene].pos.x - enemyMob[ene].offsetSize.x + mapPos.x
					, enemyMob[ene].pos.y - enemyMob[ene].offsetSize.y + mapPos.y
					, enemyImage[enemyMob[ene].charType][enemyMob[ene].moveDir * 4 + ((enemyMob[ene].animCnt / 40) % 4)]
					, true);
			}
			//DrawFormatString(0, 200, 0xFFFFFF,"enemyHP:%d", enemyMob[ene].life, true);
		}
	}
}

int MoveEnemyX(CHARACTER* enemy, XY playerPos)
{
	//-----enemy����
	int diff = playerPos.x - (*enemy).pos.x;
	int enemySpeed = (*enemy).moveSpeed;
	//X��
	if (diff >= 0)
	{
		//��߰�ނ̒���������
		enemySpeed = diff < enemySpeed ? diff : enemySpeed;

		//X���W���Ⴄ�ꍇ�͓G���ړ�������
		(*enemy).moveDir = DIR_RIGHT;
		(*enemy).pos.x += enemySpeed;
	}
	else
	{
		enemySpeed = -diff < enemySpeed ? -diff : enemySpeed;

		(*enemy).moveDir = DIR_LEFT;
		(*enemy).pos.x -= enemySpeed;
	}


	return enemySpeed;
}

int MoveEnemyY(CHARACTER* enemy, XY playerPos)
{
	//-----enemy����
	int diff = playerPos.y - (*enemy).pos.y;
	int enemySpeed = (*enemy).moveSpeed;
	//Y��
	if (diff >= 0)
	{
		//��߰�ނ̒���������
		enemySpeed = diff < enemySpeed ? diff : enemySpeed;

		//Y���W���Ⴄ�ꍇ�͓G���ړ�������
		(*enemy).moveDir = DIR_DOWN;
		(*enemy).pos.y += enemySpeed;
	}
	else
	{
		enemySpeed = -diff < enemySpeed ? -diff : enemySpeed;
		//Y���W���Ⴄ�ꍇ�͓G���ړ�������
		(*enemy).moveDir = DIR_UP;
		(*enemy).pos.y -= enemySpeed;
	}

	return enemySpeed;

}

int MoveEnemyXY(CHARACTER* enemy, XY playerPos)
{
	int diffX = playerPos.x - (*enemy).pos.x;
	int diffY = playerPos.y - (*enemy).pos.y;
	int enemySpeed = (*enemy).moveSpeed;

	if (abs(diffX) <= abs(diffY))
	{
		//��߰�ނ̒���������
		enemySpeed = MoveEnemyY(enemy, playerPos);
	}
	else
	{
		enemySpeed = MoveEnemyX(enemy, playerPos);
	}

	return enemySpeed;

}

//-----��а�ƒe�̓����蔻��@(true : ������, false : �͂���)
bool EnemyHitCheck(XY sPos, int sSize, CHARACTER *shot)
{
	auto randam = rand() % 100;
	//�S�Ă̓G�ɓ����蔻������{����
	for (int en = 0; en < ENEMY_MAX; en++)
	{
		if (stageID == enemyMob[en].stageType)
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
								break;
							}
							else if (randam <= 5)
							{
								ItemDrop(enemyMob[en].pos, MAGIC_TYPE_HEAL);
								break;
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
								break;
							}
							else if (randam <= 5)
							{
								ItemDrop(enemyMob[en].pos, MAGIC_TYPE_HEAL);
								break;
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
								break;
							}
							else if (randam <= 5)
							{
								ItemDrop(enemyMob[en].pos, MAGIC_TYPE_HEAL);
								break;
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
		if (stageID == enemyMob[en].stageType)
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
	}
	//�O�ꂽ��
	return false;
}

