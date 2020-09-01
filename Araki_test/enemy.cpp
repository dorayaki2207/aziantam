#include "DxLib.h"
#include "main.h"
#include "stage.h"
#include "enemy.h"


#define ENEMY_SPAWN_1_X	15
#define ENEMY_SPAWN_1_Y	11
#define ENEMY_SPAWN_2_X	12
#define ENEMY_SPAWN_2_Y	34
#define ENEMY_SPAWN_3_X	33
#define ENEMY_SPAWN_3_Y	24
#define ENEMY_SPAWN_TIME 10

//-----�O���ϐ��錾
//��ފ֘A
CHARACTER enemyMob[ENEMY_MAX];
CHARACTER enemyMobMaster[ENEMY_M_MAX];
int enemyImage[ENEMY_M_MAX][16];
CHARACTER enemyBoss[ENEMY_MAX_B];
CHARACTER enemyBossMaster[ENEMY_B_MAX];
int enemyImage_[ENEMY_B_MAX][16];

bool enMoveFlag;							//�G�p��Flag
int enMoveCnt;								//�G�p�̃J�E���^

int eSpawnCnt;								//�G�p�̃J�E���^(�X�|�[��)
int eSpawnCnt2;								//�G�p�̃J�E���^(�X�|�[���̊Ԋu�p)

void EnemySystemInit(void)
{
	//-----�ϐ��̏�����
	//��
	enemyMobMaster[ENEMY_I_MOB].charType = ENEMY_I_MOB;			//	��а�̎��	�F	���
	enemyMobMaster[ENEMY_I_MOB].moveSpeed = 1;					//	��Ȃ̈ړ���
	enemyMobMaster[ENEMY_I_MOB].lifeMax = 5;					//	��Ȃ̗͍̑ő�l
	enemyMobMaster[ENEMY_I_MOB].point = 1;						//	��Ȃ̓��_
	//�S
	enemyBossMaster[ENEMY_ONI].charType = ENEMY_ONI;			//	��а�̎��	�F	�S
	enemyBossMaster[ENEMY_ONI].moveSpeed = 1;					//	�S�̈ړ���
	enemyBossMaster[ENEMY_ONI].lifeMax = 10;						//	�S�̗͍̑ő�l
	enemyBossMaster[ENEMY_ONI].point = 3;						//	�S�̓��_
	//�ꔽ�ؖ�
	enemyMobMaster[ENEMY_Y_MOB].charType = ENEMY_Y_MOB;			//	��а�̎��	�F	�ꔽ�ؖ�
	enemyMobMaster[ENEMY_Y_MOB].moveSpeed = 1;					//	�ꔽ�ؖȂ̈ړ���
	enemyMobMaster[ENEMY_Y_MOB].lifeMax = 5;					//	�ꔽ�ؖȂ̗͍̑ő�l
	enemyMobMaster[ENEMY_Y_MOB].point = 1;						//	�ꔽ�ؖȂ̓��_
	//�V��
	enemyBossMaster[ENEMY_TENG].charType = ENEMY_TENG;			//	��а�̎��	�F	�V��
	enemyBossMaster[ENEMY_TENG].moveSpeed = 1;					//	�V��̈ړ���
	enemyBossMaster[ENEMY_TENG].lifeMax = 10;					//	�V��̗͍̑ő�l
	enemyBossMaster[ENEMY_TENG].point = 3;						//	�V��̓��_
	//�C�V��
	enemyMobMaster[ENEMY_A_MOB].charType = ENEMY_A_MOB;			//	��а�̎��	�F	�C�V��						
	enemyMobMaster[ENEMY_A_MOB].moveSpeed = 1;					//	�C�V��̈ړ���
	enemyMobMaster[ENEMY_A_MOB].lifeMax = 5;					//	�C�V��̗͍̑ő�l
	enemyMobMaster[ENEMY_A_MOB].point = 1;						//	�C�V��̓��_
	//�͓�
	enemyBossMaster[ENEMY_KAPPA].charType = ENEMY_KAPPA;		//	��а�̎��	�F	�͓�
	enemyBossMaster[ENEMY_KAPPA].moveSpeed = 1;					//	�͓��̈ړ���
	enemyBossMaster[ENEMY_KAPPA].lifeMax = 10;					//	�͓��̗͍̑ő�l
	enemyBossMaster[ENEMY_KAPPA].point = 3;						//	�͓��̓��_
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
	//�{�X���܂Ƃ߂ď���
	for (int b = 0; b < ENEMY_B_MAX; b++)
	{
		enemyBossMaster[b].moveDir = DIR_DOWN;
		enemyBossMaster[b].pos = { 50,50 };
		enemyBossMaster[b].size = { 32,32 };
		enemyBossMaster[b].offsetSize = { enemyBossMaster[b].size.x / 2
			, enemyBossMaster[b].size.y / 2 };
		enemyBossMaster[b].life = enemyBossMaster[b].lifeMax;
		enemyBossMaster[b].animCnt = 0;
	}
	//-----���̨���̓o�^
	//�΋��S��MOB
	LoadDivGraph("char/�d��.png", 16, 4, 4
		, enemyMobMaster[ENEMY_I_MOB].size.x
		, enemyMobMaster[ENEMY_I_MOB].size.y
		, enemyImage[ENEMY_I_MOB]);
	//�S
	LoadDivGraph("char/bossDT.png", 16, 4, 4
		, enemyBossMaster[ENEMY_ONI].size.x
		, enemyBossMaster[ENEMY_ONI].size.y
		, enemyImage_[ENEMY_ONI]);
	//�R�{�S��MOB
	LoadDivGraph("char/wind_mob_enemy1.png", 16, 4, 4
		, enemyMobMaster[ENEMY_Y_MOB].size.x
		, enemyMobMaster[ENEMY_Y_MOB].size.y
		, enemyImage[ENEMY_Y_MOB]);
	//�V��
	LoadDivGraph("char/wind_boss.png", 16, 4, 4
		, enemyBossMaster[ENEMY_TENG].size.x
		, enemyBossMaster[ENEMY_TENG].size.y
		, enemyImage_[ENEMY_TENG]);
	//�r�ؒS��MOB
	LoadDivGraph("char/umi0.png", 16, 4, 4
		, enemyMobMaster[ENEMY_A_MOB].size.x
		, enemyMobMaster[ENEMY_A_MOB].size.y
		, enemyImage[ENEMY_A_MOB]);
	//�͓�
	LoadDivGraph("char/KAPPA_00.png", 16, 4, 4
		, enemyBossMaster[ENEMY_KAPPA].size.x
		, enemyBossMaster[ENEMY_KAPPA].size.y
		, enemyImage_[ENEMY_KAPPA]);

	enMoveFlag = false;
	enMoveCnt = 0;

	eSpawnCnt = 0;
	eSpawnCnt2 = 0;
}

void EnemyGameInit(void)
{

	for (int ene = 0; ene < ENEMY_MAX; ene++)
	{
		enemyMob[ene] = enemyMobMaster[GetRand(ENEMY_M_MAX - 1)];
		enemyMob[ene].pos.x = GetRand(MAP_X * CHIP_SIZE_X - 1);
		enemyMob[ene].pos.y = GetRand(MAP_Y * CHIP_SIZE_Y - 1);
	}
	for (int eb = 0; eb < ENEMY_MAX_B; eb++)
	{
		enemyBoss[eb] = enemyBossMaster[GetRand(ENEMY_B_MAX - 1)];
		enemyBoss[eb].pos.x = GetRand(MAP_M_X * CHIP_SIZE_X - 1);
		enemyBoss[eb].pos.y = GetRand(MAP_M_Y * CHIP_SIZE_Y - 1);
	}

	enMoveFlag = false;
	enMoveCnt = 0;
}

//�G��X���W����ɓ�����
int MoveEnemyX(CHARACTER* enemy, XY playerPos)
{
	//int diff = playerPos.x - (*enemyPos).x;
	int diff = playerPos.x - (*enemy).pos.x;
	int enemySpeed = (*enemy).moveSpeed;
	//int diff = playerPos.y - enemyPos->y;			//�A���[���Z�q

	if (diff >= 0)
	{
		//�X�s�[�h�̒���������
		enemySpeed = diff < enemySpeed ? diff : enemySpeed;		//�O�����Z�q

		//X���W���Ⴄ�ꍇ�G���ړ�������
		(*enemy).moveDir = DIR_RIGHT;
		(*enemy).pos.x += enemySpeed;
	}
	else
	{
		//�X�s�[�h�̒���������
		enemySpeed = -diff < enemySpeed ? -diff : enemySpeed;	//�O�����Z�q

//X���W���Ⴄ�ꍇ�G���ړ�������
		(*enemy).moveDir = DIR_LEFT;
		(*enemy).pos.x -= enemySpeed;
	}

	return enemySpeed;
}

//�G��Y���W����ɓ�����
int MoveEnemyY(CHARACTER* enemy, XY playerPos)
{
	int diff = (playerPos).y - (*enemy).pos.y;
	int enemySpeed = (*enemy).moveSpeed;
	//int diff = playerPos.y - enemyPos->y;			//�A���[���Z�q

	if (diff >= 0)
	{
		//�X�s�[�h�̒���������
		enemySpeed = diff < enemySpeed ? diff : enemySpeed;		//�O�����Z�q

		//Y���W���Ⴄ�ꍇ�G���ړ�������
		(*enemy).moveDir = DIR_DOWN;
		(*enemy).pos.y += enemySpeed;
	}
	else
	{
		//�X�s�[�h�̒���������
		enemySpeed = -diff < enemySpeed ? -diff : enemySpeed;	//�O�����Z�q

		//Y���W���Ⴄ�ꍇ�G���ړ�������
		(*enemy).moveDir = DIR_UP;
		(*enemy).pos.y -= enemySpeed;
	}

	return enemySpeed;

}

//�G��XY���W����ɓ�����
int MoveEnemyXY(CHARACTER* enemy, XY playerPos)
{

	int diffX = playerPos.x - (*enemy).pos.x;
	int diffY = playerPos.y - (*enemy).pos.y;
	int enemySpeed = (*enemy).moveSpeed;

	if (abs(diffX) <= abs(diffY))
	{
		enemySpeed = MoveEnemyY(enemy, playerPos);
	}
	else
	{
		enemySpeed = MoveEnemyX(enemy, playerPos);
	}

	return enemySpeed;
}

void EnemyControl(XY pPos)
{
	eSpawnCnt++;
	eSpawnCnt2 += ENEMY_SPAWN_TIME;
	enMoveCnt++;

	// �G���ړ������鏈��
	for (int e = 0; e < ENEMY_MAX; e++)
	{
		enemyMob[e].animCnt++;

		if (enMoveCnt / 40 % 3 == 0)
		{
			enMoveFlag = false;
		}
		else
		{
			enMoveFlag = true;
		}

		// Startstage����
		if (stageID == STAGE_ID_START)
		{
			if (enMoveFlag == true)
			{
				if (enemyMob[e].life > 0)
				{
					switch (enemyMob[e].charType)
					{
						// X���W
					case ENEMY_A_MOB:
						if (MoveEnemyX(&enemyMob[e], pPos) == 0)
						{
							MoveEnemyY(&enemyMob[e], pPos);
						}
						break;
					case ENEMY_I_MOB:
						if (MoveEnemyY(&enemyMob[e], pPos) == 0)
						{
							MoveEnemyX(&enemyMob[e], pPos);
						}
						break;
					case ENEMY_Y_MOB:
							MoveEnemyXY(&enemyMob[e], pPos);
						break;

					default:
						break;
					}

					
				}

				//����ł���̂œG�𐶐�
				else
				{
					if (eSpawnCnt2 % 100 == 0)
					{
						enemyMob[e].life = enemyMob[e].lifeMax;
						//�X�|�[���ʒu(�R�p�^�[��)
						if (eSpawnCnt % 3 == 0)
						{

							enemyMob[e].pos = { ENEMY_SPAWN_1_X * CHIP_SIZE_X,ENEMY_SPAWN_1_Y * CHIP_SIZE_Y };
						}
						else if (eSpawnCnt % 3 == 1)
						{

							enemyMob[e].pos = { ENEMY_SPAWN_2_X * CHIP_SIZE_X,ENEMY_SPAWN_2_Y * CHIP_SIZE_Y };
						}
						else if (eSpawnCnt % 3 == 2)
						{

							enemyMob[e].pos = { ENEMY_SPAWN_3_X * CHIP_SIZE_X,ENEMY_SPAWN_3_Y * CHIP_SIZE_Y };
						}
					}
				}
			}
		}
	}

	for (int e = 0; e < ENEMY_MAX_B; e++)
	{
		enemyBoss[e].animCnt++;

		if (enMoveCnt / 40 % 3 == 0)
		{
			enMoveFlag = false;
		}
		else
		{
			enMoveFlag = true;
		}
		//Boss
		if (stageID == STAGE_ID_MOB)
		{
			if (enMoveFlag == true)
			{
				if (enemyBoss[e].life > 0)
				{
					switch (enemyBoss[e].charType)
					{
						//X
					//case ENEMY_ONI:
					//	if (MoveEnemyX(&enemyBoss[e], pPos) == 0)
					//	{
					//		MoveEnemyY(&enemyBoss[e], pPos);
					//	}
					//	break;
					//	//Y
					//case ENEMY_TENG:
					//	if (MoveEnemyY(&enemyBoss[e], pPos) == 0)
					//	{
					//		MoveEnemyX(&enemyBoss[e], pPos);
					//	}
					//	break;
					//	//XY
					//case ENEMY_KAPPA:
					//	MoveEnemyXY(&enemyBoss[e], pPos);
					//	break;

					default:
						break;
					}
				}
				else
				{
					if (eSpawnCnt2 % 100 == 0)
					{
						enemyBoss[e].life = enemyBoss[e].lifeMax;
						//�X�|�[���ʒu(�R�p�^�[��)
						if (eSpawnCnt % 3 == 0)
						{

							enemyBoss[e].pos = { ENEMY_SPAWN_1_X * CHIP_SIZE_X,ENEMY_SPAWN_1_Y * CHIP_SIZE_Y };
						}
						else if (eSpawnCnt % 3 == 1)
						{

							enemyBoss[e].pos = { ENEMY_SPAWN_2_X * CHIP_SIZE_X,ENEMY_SPAWN_2_Y * CHIP_SIZE_Y };
						}
						else if (eSpawnCnt % 3 == 2)
						{

							enemyBoss[e].pos = { ENEMY_SPAWN_3_X * CHIP_SIZE_X,ENEMY_SPAWN_3_Y * CHIP_SIZE_Y };
						}
					}
				}
			}
			
		}
}
	//for (int e = 0; e < ENEMY_MAX_B; e++)
	//{
	//	enemyBoss[e].animCnt++;
	//	if (stageID == STAGE_ID_ONI)
	//	{
	//		
	//		if (enemyBoss[e].life > 0)
	//		{
	//			switch (enemyBoss[e].charType)
	//			{
	//				// X���W
	//			case ENEMY_ONI:
	//				if (MoveEnemyX(&enemyMob[e], pPos) == 0)
	//				{
	//					MoveEnemyY(&enemyMob[e], pPos);
	//				}
	//				break;

	//			default:
	//				break;
	//			}
	//		}
	//	}
	//	if (stageID == STAGE_ID_TENGU)
	//	{
	//		enemyBoss[e].animCnt++;
	//		if (enemyBoss[e].life > 0)
	//		{
	//			switch (enemyBoss[e].charType)
	//			{
	//				// X���W
	//			case ENEMY_TENG:
	//				if (MoveEnemyX(&enemyMob[e], pPos) == 0)
	//				{
	//					MoveEnemyY(&enemyMob[e], pPos);
	//				}
	//				break;

	//			default:
	//				break;
	//			}
	//		}
	//	}
	//	if (stageID == STAGE_ID_KAPPA)
	//	{
	//		enemyBoss[e].animCnt++;
	//		if (enemyBoss[e].life > 0)
	//		{
	//			switch (enemyBoss[e].charType)
	//			{
	//				// X���W
	//			case ENEMY_KAPPA:
	//				if (MoveEnemyX(&enemyMob[e], pPos) == 0)
	//				{
	//					MoveEnemyY(&enemyMob[e], pPos);
	//				}
	//				break;

	//			default:
	//				break;
	//			}
	//		}
	//	}
	//}
		
	
}

void EnemyGameDraw()
{
	//-----�`�揈��
	if (stageID == STAGE_ID_START)
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
	
	if (stageID == STAGE_ID_MOB)
	{
		for (int ene = 0; ene < ENEMY_MAX_B; ene++)
		{
			if (enemyBoss[ene].life > 0)
			{
				enemyBoss[ene].animCnt++;
				DrawGraph(enemyBoss[ene].pos.x - enemyBoss[ene].offsetSize.x + mapPos.x
					, enemyBoss[ene].pos.y - enemyBoss[ene].offsetSize.y + mapPos.y
					, enemyImage_[enemyBoss[ene].charType][enemyBoss[ene].moveDir * 4 + ((enemyBoss[ene].animCnt / 40) % 4)]
					, true);

				DrawBox(enemyBoss[ene].pos.x - enemyBoss[ene].offsetSize.x + mapPos.x
					, enemyBoss[ene].pos.y - enemyBoss[ene].offsetSize.y + mapPos.y
					, enemyBoss[ene].pos.x - enemyBoss[ene].offsetSize.x + enemyBoss[ene].size.x + mapPos.x
					, enemyBoss[ene].pos.y - enemyBoss[ene].offsetSize.y + enemyBoss[ene].size.y + mapPos.y
					, 0xFF00FF, false);
			}
		}
	}
	/*if (stageID == STAGE_ID_ONI)
	{
	
			if (enemyBoss[ENEMY_ONI].life > 0)
			{
				DrawGraph(enemyBoss[ENEMY_ONI].pos.x - enemyBoss[ENEMY_ONI].offsetSize.x + mapPos.x
					, enemyBoss[ENEMY_ONI].pos.y - enemyBoss[ENEMY_ONI].offsetSize.y + mapPos.y
					, enemyImage_[enemyBoss[ENEMY_ONI].charType][enemyBoss[ENEMY_ONI].moveDir * 4 + ((enemyBoss[ENEMY_ONI].animCnt / 40) % 4)]
					, true);

				DrawBox(enemyBoss[ENEMY_ONI].pos.x - enemyBoss[ENEMY_ONI].offsetSize.x + mapPos.x
					, enemyBoss[ENEMY_ONI].pos.y - enemyBoss[ENEMY_ONI].offsetSize.y + mapPos.y
					, enemyBoss[ENEMY_ONI].pos.x - enemyBoss[ENEMY_ONI].offsetSize.x + enemyBoss[ENEMY_ONI].size.x + mapPos.x
					, enemyBoss[ENEMY_ONI].pos.y - enemyBoss[ENEMY_ONI].offsetSize.y + enemyBoss[ENEMY_ONI].size.y + mapPos.y
					, 0xFF00FF, false);
			}
		
	}
	if (stageID == STAGE_ID_TENGU)
	{

			if (enemyBoss[ENEMY_TENG].life > 0)
			{
				DrawGraph(enemyBoss[ENEMY_TENG].pos.x - enemyBoss[ENEMY_TENG].offsetSize.x + mapPos.x
					, enemyBoss[ENEMY_TENG].pos.y - enemyBoss[ENEMY_TENG].offsetSize.y + mapPos.y
					, enemyImage_[enemyBoss[ENEMY_TENG].charType][enemyBoss[ENEMY_TENG].moveDir * 4 + ((enemyBoss[ENEMY_TENG].animCnt / 40) % 4)]
					, true);

				DrawBox(enemyBoss[ENEMY_TENG].pos.x - enemyBoss[ENEMY_TENG].offsetSize.x + mapPos.x
					, enemyBoss[ENEMY_TENG].pos.y - enemyBoss[ENEMY_TENG].offsetSize.y + mapPos.y
					, enemyBoss[ENEMY_TENG].pos.x - enemyBoss[ENEMY_TENG].offsetSize.x + enemyBoss[ENEMY_TENG].size.x + mapPos.x
					, enemyBoss[ENEMY_TENG].pos.y - enemyBoss[ENEMY_TENG].offsetSize.y + enemyBoss[ENEMY_TENG].size.y + mapPos.y
					, 0xFF00FF, false);
			}
		
	}
	if (stageID == STAGE_ID_KAPPA)
	{
		
			if (enemyBoss[ENEMY_KAPPA].life > 0)
			{
				DrawGraph(enemyBoss[ENEMY_KAPPA].pos.x - enemyBoss[ENEMY_KAPPA].offsetSize.x + mapPos.x
					, enemyBoss[ENEMY_KAPPA].pos.y - enemyBoss[ENEMY_KAPPA].offsetSize.y + mapPos.y
					, enemyImage_[enemyBoss[ENEMY_KAPPA].charType][enemyBoss[ENEMY_KAPPA].moveDir * 4 + ((enemyBoss[ENEMY_KAPPA].animCnt / 40) % 4)]
					, true);

				DrawBox(enemyBoss[ENEMY_KAPPA].pos.x - enemyBoss[ENEMY_KAPPA].offsetSize.x + mapPos.x
					, enemyBoss[ENEMY_KAPPA].pos.y - enemyBoss[ENEMY_KAPPA].offsetSize.y + mapPos.y
					, enemyBoss[ENEMY_KAPPA].pos.x - enemyBoss[ENEMY_KAPPA].offsetSize.x + enemyBoss[ENEMY_KAPPA].size.x + mapPos.x
					, enemyBoss[ENEMY_KAPPA].pos.y - enemyBoss[ENEMY_KAPPA].offsetSize.y + enemyBoss[ENEMY_KAPPA].size.y + mapPos.y
					, 0xFF00FF, false);
			}
		
	}*/
}

//-----��а�ƒe�̓����蔻��@(true : ������, false : �͂���)
bool EnemyHitCheck(XY sPos, int sSize)
{
	//�S�Ă̓G�ɓ����蔻������{����
	for (int en = 0; en < ENEMY_MAX; en++)
	{
		if (stageID == STAGE_ID_START)
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
		
	}
	//�e���O�ꂽ��
	//return false;

	for (int eb = 0; eb < ENEMY_MAX_B; eb++)
	{
		if (stageID == STAGE_ID_MOB)
		{
			if (enemyBoss[eb].life > 0)
			{
				if (((enemyBoss[eb].pos.x - enemyBoss[eb].size.x / 2) < (sPos.x + sSize / 2))
					&& ((enemyBoss[eb].pos.x + enemyBoss[eb].size.x / 2) > (sPos.x - sSize / 2))
					&& ((enemyBoss[eb].pos.y - enemyBoss[eb].size.y / 2) < (sPos.y + sSize / 2))
					&& ((enemyBoss[eb].pos.y + enemyBoss[eb].size.y / 2) > (sPos.y - sSize / 2)))
				{
					//�����������A��а�̗̑͂����炷
					enemyBoss[eb].life--;


					return true;
				}
			}
		}

	}
	//�e���O�ꂽ��
	return false;
}

// ���@��G�Ƃ̓����蔻��
bool PlayerHitCheck(XY pPos, int pSize)
{
	for (int sn = 0; sn < ENEMY_MAX; sn++)
	{
		if (stageID == STAGE_ID_START)
		{
			if (enemyMob[sn].life > 0)
			{
				if ((enemyMob[sn].pos.x - enemyMob[sn].size.x / 2) < (pPos.x + pSize / 2)
					&& (enemyMob[sn].pos.x + enemyMob[sn].size.x /2) > (pPos.x - pSize /2)
					&& (enemyMob[sn].pos.y - enemyMob[sn].size.y/2)<(pPos.y + pSize /2)
					&& (enemyMob[sn].pos.y + enemyMob[sn].size.y / 2) > (pPos.y - pSize / 2))
				{
					return true;
				}
			}
		}
	}
	//return false;

	for (int sb = 0; sb < ENEMY_MAX_B; sb++)
	{
		if (stageID == STAGE_ID_MOB)
		{
			if (enemyBoss[sb].life > 0)
			{
				if ((enemyBoss[sb].pos.x - enemyBoss[sb].size.x / 2) < (pPos.x + pSize / 2)
					&& (enemyBoss[sb].pos.x + enemyBoss[sb].size.x / 2) > (pPos.x - pSize / 2)
					&& (enemyBoss[sb].pos.y - enemyBoss[sb].size.y / 2) < (pPos.y + pSize / 2)
					&& (enemyBoss[sb].pos.y + enemyBoss[sb].size.y / 2) > (pPos.y - pSize / 2))
				{
					return true;
				}
			}
		}
	}
	return false;
}