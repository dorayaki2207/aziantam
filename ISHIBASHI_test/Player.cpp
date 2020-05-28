#include "DxLib.h"
#include "test.h"
#include "KeyCheck.h"
#include "Stage.h"
#include "Player.h"

//-----�O���ϐ��錾
//��׸��֘A
CHARACTER player;							//	��ڲ԰�ϐ��i�[�p
int playerImage[DIR_MAX][PLAYER_MAX];		//	��ڲ԰�摜�F�ʏ펞


void PlayerSystemInit(void)
{
	//-----�ϐ��̏�����
	player.moveDir = DIR_DOWN;											//	��׸��̌���
	player.size = { 32,32 };											//	��׸��̉摜����
	player.offsetSize = { player.size.x / 2,player.size.y / 2 };		//�@��׸��̵̾��
	player.moveSpeed = 4;												//	��׸��̈ړ���߰��
	player.hitFlag = false;

	//-----���̨���̓o�^
	//��׸��֘A
	LoadDivGraph("aitem/�d��test.png", DIR_MAX*PLAYER_MAX
		, DIR_MAX, PLAYER_MAX, player.size.x, player.size.y, playerImage[0], true);
}

void PlayerGameInit(void)
{
	player.pos = { 150,150};				//�@��׸��̒n�}��̍��W
	player.lifeMax = 150;												//	��׸��̗͍̑ő�l
	player.life = player.lifeMax;										//	��׸��̗̑�
	player.animCnt = 0;													//	��׸��̱�Ұ���

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
				playerPosOffset.x = playerPosCopy.x + player.offsetSize.x;
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
				playerPosOffset.x = playerPosCopy.x - player.offsetSize.x;
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
				playerPosOffset.y = playerPosCopy.y - player.offsetSize.y;
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

			default:
				break;
			}
			//�߂�l��ݒ�
		//	returnValue = player.pos;

		}
		
		//-----ϯ�߂̐����@�i�ړ��������ɓ�����ϯ�߂�����Ă��܂�
		if (mapPos.x > 0) mapPos.x = 0;
		if (mapPos.x < -CHIP_SIZE_X * MAP_X + SCREEN_SIZE_X) mapPos.x = -CHIP_SIZE_X * MAP_X + SCREEN_SIZE_X;
		if (mapPos.y > 0) mapPos.y = 0;
		if (mapPos.y < -CHIP_SIZE_Y * MAP_Y + SCREEN_SIZE_Y) mapPos.y = -CHIP_SIZE_Y * MAP_Y + SCREEN_SIZE_Y;



		//�@�ړ��͈͏���
		//ϯ�����߂̓����蔻����������Ă��Ȃ��ׁA�ꎞ�I���u
//		if (player.pos.x > CHIP_SIZE_X * MAP_X - player.offsetSize.x) player.pos.x = CHIP_SIZE_X * MAP_X - player.offsetSize.x;     //�E����
//		if (player.pos.x < player.offsetSize.x) player.pos.x = player.offsetSize.x;													//������
//		if (player.pos.y > CHIP_SIZE_Y * MAP_Y - player.offsetSize.y) player.pos.y = CHIP_SIZE_Y * MAP_Y - player.offsetSize.y;		//������
//		if (player.pos.y < player.offsetSize.y) player.pos.y = player.offsetSize.y;													//�㐧��


	}
	return returnValue;
}

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

}

