#include "DxLib.h"
#include "main.h"
#include "player.h"
#include "keycheck.h"
#include "stage.h"

//�ϐ�
int playerImage[16];
CHARACTER player;

//��ڲ԰���̏�����
void PlayerSystemInit(void)
{
	//player.charType;										//��׸��̎��
	player.size = {32,32};									//��׸��摜�̻���
	player.offsetSize = {player.size.x/2,player.size.y/2};	//��׸��̵̾��
	player.lifeMax = PLAYER_MAX_LIFE;						//��׸��̗͍̑ő�l
	player.moveSpeed = PLAYER_DEF_SPEED;					//��׸��̈ړ���߰��
	player.animCnt = 0;										//��׸��̱�Ұ���

	LoadDivGraph("char/boy_player.png", 16, 4, 4
		, player.size.x, player.size.y, playerImage);
}
//�v���C���[�̏�����
void PlayerGameInit(void)
{
	player.moveDir = DIR_RIGHT;								//��׸��̌���
	player.pos = { 100,100 };									//��׸��̒n�}��̍��W

	player.life = player.lifeMax;							//��׸��̗̑�

}



//�v���C���[�̑���
XY PlayerControl(void)
{
	bool moveFlag = false;				//�@���삳��Ă��邩���f����
	XY returnValue = player.pos;			//	�֐��̖߂�l�i�[�̈�
	XY playerPosCopy = player.pos;
	XY playerPosOffset = playerPosCopy;
	XY indexPos;							//�@ϯ�ߔz����W

	if (player.life > 0)
	{
		if (KeyNew[KEY_ID_UP])
		{
			moveFlag = true;
			player.moveDir = DIR_UP;
		}
		if (KeyNew[KEY_ID_DOWN])
		{
			moveFlag = true;
			player.moveDir = DIR_DOWN;
		}
		if (KeyNew[KEY_ID_RIGHT])
		{
			moveFlag = true;
			player.moveDir = DIR_RIGHT;
		}
		if (KeyNew[KEY_ID_LEFT])
		{
			moveFlag = true;
			player.moveDir = DIR_LEFT;
		}


		if (moveFlag)
		{
			player.animCnt += 5;
			switch (player.moveDir)
			{
			case DIR_UP:
				playerPosCopy.y -= player.moveSpeed;
				playerPosOffset.y = playerPosCopy.y;
				indexPos = Pos2Index(playerPosCopy);
				//�w�肵���ꏊ��ʉ߉\��
				if (IsPass(playerPosOffset))
				{
					player.pos = playerPosCopy;
					//��۰ِ���
					if (player.pos.y  < SCROLL_Y_MIN - mapPos.y)
					{
						if (mapPos.y < 0)
						{

							mapPos.y += player.moveSpeed;
						}
					}
				}
				break;
			case DIR_DOWN:
				playerPosCopy.y += player.moveSpeed;
				playerPosOffset.y = playerPosCopy.y;
				indexPos = Pos2Index(playerPosCopy);
				//�w�肵���ꏊ��ʉ߉\��
				if (IsPass(playerPosOffset))
				{
					player.pos = playerPosCopy;
					//��۰ِ���
					if (player.pos.y > SCROLL_Y_MAX - mapPos.y)
					{
						if (mapPos.y > CHIP_SIZE_Y* -mapSize.y + SCREEN_SIZE_Y)
						{
							mapPos.y -= player.moveSpeed;
						}
					}
				}
				break;
			case DIR_RIGHT:
				playerPosCopy.x += player.moveSpeed;
				playerPosOffset.x = playerPosCopy.x;
				indexPos = Pos2Index(playerPosCopy);
				//�w�肵���ꏊ��ʉ߉\��
				if (IsPass(playerPosOffset))
				{
					player.pos = playerPosCopy;
					//��۰ِ���
					if (player.pos.x > SCROLL_X_MAX - mapPos.x)
					{
						if (mapPos.x > CHIP_SIZE_X* -mapSize.x + SCREEN_SIZE_X)
						{
							mapPos.x -= player.moveSpeed;
						}
					}
				}
				break;
			case DIR_LEFT:
				playerPosCopy.x -= player.moveSpeed;
				playerPosOffset.x = playerPosCopy.x;
				indexPos = Pos2Index(playerPosCopy);
				//�w�肵���ꏊ��ʉ߉\��
				if (IsPass(playerPosOffset))
				{
					player.pos = playerPosCopy;
					//��۰ِ���
					if (player.pos.x < SCROLL_X_MIN - mapPos.x)
					{
						if (mapPos.x < 0)
						{
							mapPos.x += player.moveSpeed;
						}
					}
				}
				break;
			default:
				break;
			}
			//�߂�l��ݒ�
			returnValue = player.pos;

		}
		
	}
<<<<<<< HEAD
	if (mapPos.x < 0)
	{
		mapPos.x = 0;
	}
	if (mapPos.x > CHIP_SIZE_X * MAP_X - SCREEN_SIZE_X)
	{
		mapPos.x = CHIP_SIZE_X * MAP_X - SCREEN_SIZE_X;
	}
	if (mapPos.y < 0)
	{
		mapPos.y = 0;
	}
	if (mapPos.y > CHIP_SIZE_Y * MAP_Y - SCREEN_SIZE_Y)
	{
		mapPos.y = CHIP_SIZE_Y * MAP_Y - SCREEN_SIZE_Y;
	}
=======
	return returnValue;
>>>>>>> 9570c1765eccde647c8cebd2eb7ef975b03ac5ad
}
//�v���C���[�̕`��
void PlayerGameDraw(void)
{
	player.animCnt++;
<<<<<<< HEAD
	DrawGraph(player.pos.x, player.pos.y, playerImage[(player.moveDir * 4) + (player.animCnt / 30) % 4], true);
	/*DrawGraph(player1.pos.x - player1.offsetSize.y - mapPos.x
		, player1.pos.y - player1.offsetSize.y - mapPos.y
		, playerImage[player1.moveDir][player1.animCnt / 10 % 4]
		, true);*/
}
=======
	DrawGraph(player.pos.x - player.offsetSize.x + mapPos.x
		, player.pos.y - player.offsetSize.y + mapPos.y
		, playerImage[(player.moveDir * 4) + (player.animCnt / 30) % 4], true);

	DrawBox(SCROLL_X_MIN, SCROLL_Y_MIN, SCROLL_X_MAX, SCROLL_Y_MAX, 0xFFFFFF, false);
	DrawFormatString(0, 50, 0xFFFFFF, "player:%d,%d", player.pos.x, player.pos.y);
	XY indexPos;
	indexPos = Pos2Index(player.pos);

}
>>>>>>> 9570c1765eccde647c8cebd2eb7ef975b03ac5ad
