#include <DxLib.h>
#include "test.h"
#include "KeyCheck.h"
#include "Stage.h"
#include "Player.h"
#include "Item.h"
#include "Shot.h"
#include "Enemy.h"

//-----�O���ϐ��錾
//��׸��֘A
CHARACTER player;							//	��ڲ԰�ϐ��i�[�p
int playerImage[DIR_MAX][PLAYER_MAX];		//	��ڲ԰�摜�F�ʏ펞

int lifeCheckCnt;
//int testImage[4];
//int test2Image[4];

void PlayerSystemInit(void)
{
	//-----�ϐ��̏�����
	player.moveDir = DIR_DOWN;											//	��׸��̌���
	player.size = { 40,50 };											//	��׸��̉摜����
	player.offsetSize = { player.size.x / 2,player.size.y / 2 };		//�@��׸��̵̾��
	player.moveSpeed = 4;												//	��׸��̈ړ���߰��
	player.hitFlag = false;

	//-----���̨���̓o�^
	//��׸��֘A
	LoadDivGraph("aitem/bossDT3.png", DIR_MAX*PLAYER_MAX
		, DIR_MAX, PLAYER_MAX, player.size.x, player.size.y, playerImage[0], true);


//	LoadDivGraph("aitem/hard.png", 4, 4, 1, 32, 40, testImage);
//	LoadDivGraph("aitem/bb.png", 4, 4, 1, 32, 40, test2Image);
}

void PlayerGameInit(void)
{
	player.pos = { 150,150};										//�@��׸��̒n�}��̍��W
	player.lifeMax = 150;												//	��׸��̗͍̑ő�l
	player.life = player.lifeMax;										//	��׸��̗̑�
	player.animCnt = 0;												//	��׸��̱�Ұ���
	lifeCheckCnt = 0;
}

XY PlayerControl(void)
{
	bool movedFlag = false;			//�@���삳��Ă��邩���f����
	XY returnValue = player.pos;		// �֐��̖߂�l�i�[�̈�
	XY playerPosCopy = player.pos;
	XY playerPosOffset = playerPosCopy;
	XY indexPos;						//ϯ�ߔz����W
										
	//��ڲ԰�������Ă���Ƃ�
	if (player.life > 0)
	{

		
		//-----�ړ�����
		if (keyNew[KEY_ID_RIGHT])
		{
			movedFlag = true;
			player.moveDir = DIR_RIGHT;
		}
		if (keyNew[KEY_ID_LEFT])
		{
			movedFlag = true;
			player.moveDir = DIR_LEFT;
		}
		if (keyNew[KEY_ID_UP])
		{
			movedFlag = true;
			player.moveDir = DIR_UP;
		}
		if (keyNew[KEY_ID_DOWN])
		{
			movedFlag = true;
			player.moveDir = DIR_DOWN;
		}

		//��ڲ԰�̌���
		if (movedFlag)
		{
			//��ڲ԰�̊e��l��ύX����
			player.animCnt += 5;


			switch (player.moveDir)
			{
				//�E
			case DIR_RIGHT:			
				playerPosCopy.x += player.moveSpeed;
				playerPosOffset.x = playerPosCopy.x/* + player.offsetSize.x*/+7;
				indexPos = PosToIndex(playerPosCopy);
				//�w�肵���ꏊ��ʉ߉\���ǂ���
				if (IsPass(playerPosOffset))
				{
					player.pos = playerPosCopy;
					//��۰ُ���
					if (player.pos.x + mapPos.x > SCROLL_X_MAX)
					{
						mapPos.x -= player.moveSpeed;
					}
				}
				break;

				//��
			case DIR_LEFT:	
				playerPosCopy.x -= player.moveSpeed;
				playerPosOffset.x = playerPosCopy.x /*- player.offsetSize.x*/-10;
				indexPos = PosToIndex(playerPosCopy);
				//�w�肵���ꏊ��ʉ߉\���ǂ���
				if (IsPass(playerPosOffset))
				{
					player.pos = playerPosCopy;
					//��۰ُ���
					if (player.pos.x + mapPos.x < SCROLL_X_MIN)
					{
						mapPos.x += player.moveSpeed;
					}
				}
				break;

				//��
			case DIR_UP:	
				playerPosCopy.y -= player.moveSpeed;
				playerPosOffset.y = playerPosCopy.y/* - player.offsetSize.y*/;
				indexPos = PosToIndex(playerPosCopy);
				//�w�肵���ꏊ��ʉ߉\���ǂ���
				if (IsPass(playerPosOffset))
				{
					player.pos = playerPosCopy;
					//��۰ُ���
					if (player.pos.y + mapPos.y < SCROLL_Y_MIN)
					{
						mapPos.y += player.moveSpeed;
					}
				}
				break;

				//��
			case DIR_DOWN:
				playerPosCopy.y += player.moveSpeed;
				playerPosOffset.y = playerPosCopy.y + player.offsetSize.y;
				indexPos = PosToIndex(playerPosCopy);
				//�w�肵���ꏊ��ʉ߉\���ǂ���
				if (IsPass(playerPosOffset))
				{
					player.pos = playerPosCopy;
					if (player.pos.y + mapPos.y > SCROLL_Y_MAX)
					{
						mapPos.y -= player.moveSpeed;
					}
				}
				break;

			case DIR_MAX:
				break;
			default:
				break;
			}
			//�߂�l��ݒ�
			returnValue = player.pos;

		}


		//-----���ď���
		if (keyNew[KEY_ID_FIRE])
		{
			CreateShot(player.pos, player.moveDir, MAGIC_TYPE_FIRE);
		}
		if (keyNew[KEY_ID_WATER])
		{
			CreateShot(player.pos, player.moveDir, MAGIC_TYPE_WATER);
		}
		if (keyNew[KEY_ID_WIND])
		{
			CreateShot(player.pos, player.moveDir, MAGIC_TYPE_WIND);
		}
		if (keyNew[KEY_ID_HEAL])
		{
			CreateShot(player.pos, player.moveDir, MAGIC_TYPE_HEAL);
		}
		

		MapRange();
		//�@�ړ��͈͏���
		//ϯ�����߂̓����蔻����������Ă��Ȃ��ׁA�ꎞ�I���u
	//	if (player.pos.x > CHIP_SIZE_X * mapSize.x - player.offsetSize.x) player.pos.x = CHIP_SIZE_X * mapSize.x - player.offsetSize.x;     //�E����
	//	if (player.pos.x < player.offsetSize.x) player.pos.x = player.offsetSize.x;													//������
	//	if (player.pos.y > CHIP_SIZE_Y * mapSize.y - player.offsetSize.y) player.pos.y = CHIP_SIZE_Y * mapSize.y - player.offsetSize.y;		//������
	//	if (player.pos.y < player.offsetSize.y) player.pos.y = player.offsetSize.y;													//�㐧��

		if (PlayerHitCheck(player.pos, player.size.x))
		{
			if (lifeCheckCnt == 0)
			{
				player.life--;
				lifeCheckCnt = 100;
			}
		
		}
		
		if (lifeCheckCnt > 0)
		{
			lifeCheckCnt--;
			if (lifeCheckCnt < 0)
			{
				lifeCheckCnt = 0;
			}
		}
	}



	return returnValue;
}

//-----��ڲ԰�̕`�揈��
void PlayerGameDraw(void)
{
	//-----�摜�`��
	if (player.life > 0)
	{
		//��ڲ԰�̊e��l��ύX����
		player.animCnt++;

		//�U�����󂯂Ă��Ȃ����
		if (!player.hitFlag)
		{
			DrawGraph(player.pos.x - player.offsetSize.x + mapPos.x
				, player.pos.y - player.offsetSize.y + mapPos.y
				, playerImage[player.moveDir][((player.animCnt / 40) % 4)]
				, true);
		}
	}


	// ��۰ِ����̘g
	DrawBox(SCROLL_X_MIN
		, SCROLL_Y_MIN
		, (SCROLL_X_MAX + 1)
		, (SCROLL_Y_MAX + 1)
		, 0x55FF22, false);

	//��񏈗�
	DrawFormatString(0, 180, 0xFFFFFF, "playerPos:%d,%d", player.pos.x, player.pos.y);
	DrawFormatString(0, 300, 0xFFFFFF, "playerHp%d", player.life);
	DrawFormatString(0, 350, 0xffffff, "LifeCheck:%d", lifeCheckCnt);

//	DrawGraph(100, 100, testImage[((player.animCnt / 20) % 4)], true);
//	DrawGraph(150, 100, test2Image[((player.animCnt / 20) % 4)], true);
}


