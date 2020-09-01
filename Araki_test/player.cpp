#include "DxLib.h"
#include "main.h"
#include "player.h"
#include "keycheck.h"
#include "stage.h"
#include "shot.h"
#include "enemy.h"

//�ϐ�
int playerImage[16];
CHARACTER player;

int speedCnt;
int lifeCnt;
// �萔
enum PLAYER_SPEED
{
	PLAYER_SPEED_LOW = 1,
	PLAYER_SPEED_NORMAL = 3,
	PLAYER_SPEED_L = 2,
	PLAYER_SPEED_HIGH = 7,
	PLAYER_SPEED_MAX 
};

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
	player.pos = { 160,135 };								//��׸��̒n�}��̍��W

	player.life = player.lifeMax;							//��׸��̗̑�
	speedCnt = 0;
	lifeCnt = 0;
}



//�v���C���[�̑���
XY PlayerControl(void)
{
	bool moveFlag = false;				//�@���삳��Ă��邩���f����
	XY returnValue = player.pos;			//	�֐��̖߂�l�i�[�̈�
	XY playerPosCopy = player.pos;
	XY playerPosOffset = playerPosCopy;
	XY indexPos;							//�@ϯ�ߔz����W

	/*for (int dir = 0; dir < DIR_MAX; dir++)
	{
		if (player.moveDir)
		{
			player.moveDir = (DIR)dir;
		}
	}*/
	if (player.life > 0)
	{
		//-----�ړ�����
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

		//��ڲ԰�̌���
		if (moveFlag)
		{
			player.animCnt += 5;
			switch (player.moveDir)
			{
			case DIR_UP:
				playerPosCopy.y -= player.moveSpeed;
				playerPosOffset.y = playerPosCopy.y - player.size.y;
				indexPos = Pos2Index(playerPosCopy);
				//�w�肵���ꏊ��ʉ߉\��
				if (IsPass(playerPosOffset))
				{
					player.pos = playerPosCopy;
					//��۰ِ���
					if (player.pos.y + mapPos.y < SCROLL_Y_MIN)
					{
						mapPos.y += player.moveSpeed;
					}
				}
				break;
			case DIR_DOWN:
				playerPosCopy.y += player.moveSpeed;
				playerPosOffset.y = playerPosCopy.y + player.size.y/2;				
				indexPos = Pos2Index(playerPosCopy);
				//�w�肵���ꏊ��ʉ߉\��
				if (IsPass(playerPosOffset))
				{
					player.pos = playerPosCopy;
					//��۰ِ���
					if (player.pos.y + mapPos.y > SCROLL_Y_MAX)
					{
						mapPos.y -= player.moveSpeed;
					}
				}
				break;
			case DIR_RIGHT:
				playerPosCopy.x += player.moveSpeed;
				playerPosOffset.x = playerPosCopy.x + player.size.x;
				indexPos = Pos2Index(playerPosCopy);
				//�w�肵���ꏊ��ʉ߉\��
				if (IsPass(playerPosOffset))
				{
					player.pos = playerPosCopy;
					//��۰ِ���
					if (player.pos.x + mapPos.x > SCROLL_X_MAX)
					{
						mapPos.x -= player.moveSpeed;
					}
				}
				break;
			case DIR_LEFT:
				playerPosCopy.x -= player.moveSpeed;
				playerPosOffset.x = playerPosCopy.x - player.size.x;
				indexPos = Pos2Index(playerPosCopy);
				//�w�肵���ꏊ��ʉ߉\��
				if (IsPass(playerPosOffset))
				{
					player.pos = playerPosCopy;
					//��۰ِ���
					if (player.pos.x + mapPos.x < SCROLL_X_MIN)
					{
						mapPos.x += player.moveSpeed;
					}
				}
				break;
			default:
				break;
			}
			//�߂�l��ݒ�
			returnValue = player.pos;

		}


		//-----���ď���
		if (KeyNew[KEY_ID_FIRE])
		{
			CreateShot(player.pos,player.moveDir,MAGIC_TYPE_FIRE);
		}
		if (KeyNew[KEY_ID_WATER])
		{
			CreateShot(player.pos, player.moveDir, MAGIC_TYPE_WATER);
		}
		if (KeyNew[KEY_ID_WIND])
		{
			CreateShot(player.pos, player.moveDir, MAGIC_TYPE_WIND);
		}
		if (KeyNew[KEY_ID_HEAL])
		{
			CreateShot(player.pos, player.moveDir, MAGIC_TYPE_HEAL);
		}

		//-----ϯ�߂̐����@�i�ړ��������ɓ�����ϯ�߂�����Ă��܂�
		// �v���C���[
		if (player.pos.x > mapSize.x * CHIP_SIZE_X - player.offsetSize.x)player.pos.x = mapSize.x * CHIP_SIZE_X - player.offsetSize.x;
		if (player.pos.x < 0 + player.offsetSize.x)player.pos.x = 0 + player.offsetSize.x;
		if (player.pos.y < 0 + player.offsetSize.y)player.pos.y = 0 + player.offsetSize.y;
		if (player.pos.y > mapSize.y * CHIP_SIZE_Y - player.offsetSize.y)player.pos.y = mapSize.y * CHIP_SIZE_Y - player.offsetSize.y;

		// �}�b�v
		/*if (stageID == STAGE_ID_START && STAGE_ID_MOB && STAGE_ID_ONI && STAGE_ID_TENGU && STAGE_ID_KAPPA)
		{*/
			if (mapPos.x < -CHIP_SIZE_X * mapSize.x + SCREEN_SIZE_X) mapPos.x = -CHIP_SIZE_X * mapSize.x + SCREEN_SIZE_X;
			if (mapPos.x > 0) mapPos.x = 0;
			if (mapPos.y > 0) mapPos.y = 0;
			if (mapPos.y < -CHIP_SIZE_Y * mapSize.y + SCREEN_SIZE_Y) mapPos.y = -CHIP_SIZE_Y * mapSize.y + SCREEN_SIZE_Y;
		//}
		/*else
		{
			if (mapPos.x < -CHIP_SIZE_X * MAPB_X + SCREEN_SIZE_X) mapPos.x = -CHIP_SIZE_X * MAPB_X + SCREEN_SIZE_X;
			if (mapPos.x > 0) mapPos.x = 0;
			if (mapPos.y > 0) mapPos.y = 0;
			if (mapPos.y < -CHIP_SIZE_Y * MAPB_Y + SCREEN_SIZE_Y) mapPos.y = -CHIP_SIZE_Y * MAPB_Y + SCREEN_SIZE_Y;
		}*/

		/*if (player.life > 0)
		{
			if ((PlayerHitCheck(player.pos, player.size)) == true)
			{
				if (lifeCnt == 0)
				{
					player.life--;
					lifeCnt = 100;
				}
			}
		}
		if (lifeCnt > 0)
		{
			lifeCnt--;
			if (lifeCnt < 0)
			{
				lifeCnt = 0;
			}
		}*/
	
		if (PlayerHitCheck(player.pos, player.size.x))
		{
			if (lifeCnt == 0)
			{
				player.life--;
				lifeCnt = 100;
			}

		}

		if (lifeCnt > 0)
		{
			lifeCnt--;
			if (lifeCnt < 0)
			{
				lifeCnt = 0;
			}
		}
			// ����ȃ}�b�v�𓥂񂾏ꍇ�̏���
			// ��
			if (GetEvent(player.pos) == EVENT_ID_MIZU)
			{
				speedCnt++;
				if (speedCnt > 100)
				{
					player.moveSpeed = PLAYER_SPEED_HIGH;
					player.life -= 2;
					lifeCnt = 100;
				}
			}
			// ��
			else if (GetEvent(player.pos) == EVENT_ID_DOKU)
			{
				if (speedCnt < 100)
				{
					player.moveSpeed = PLAYER_SPEED_LOW;
					player.life -= 3;
					lifeCnt = 100;
				}
			}
			// �X
			else if (GetEvent(player.pos) == EVENT_ID_MORI)
			{
				if (speedCnt < 50)
				{
					player.moveSpeed = PLAYER_SPEED_NORMAL;
				}
			}
			// ��
			else if (GetEvent(player.pos) == EVENT_ID_HATAKE)
			{
				if (speedCnt < 50)
				{
					player.moveSpeed = PLAYER_SPEED_L;
				}
			}
			// �C�x���g�߂�
			else 
			{
				player.moveSpeed = PLAYER_DEF_SPEED;
			}
		
		
	}
	return returnValue;
}
//�v���C���[�̕`��
void PlayerGameDraw(void)
{
	if (player.life > 0)
	{
		player.animCnt++;
		if (lifeCnt % 10 == 0)
		{
			DrawGraph(player.pos.x - player.offsetSize.x + mapPos.x
				, player.pos.y - player.offsetSize.y + mapPos.y
				, playerImage[(player.moveDir * 4) + (player.animCnt / 30) % 4], true);
		}
		
		DrawBox(SCROLL_X_MIN, SCROLL_Y_MIN, SCROLL_X_MAX, SCROLL_Y_MAX, 0xFFFFFF, false);
	}
	
	DrawFormatString(0, 180, 0xFFFFFF, "playerPos:%d,%d", player.pos.x, player.pos.y);
	DrawFormatString(0, 300, 0xFFFFFF, "playerHp%d", player.life);
	DrawFormatString(0, 350, 0xffffff, "Life:%d", lifeCnt);
	DrawFormatString(0, 370, 0xffffff, "speedCnt:%d", speedCnt);
	XY indexPos;
	indexPos = Pos2Index(player.pos);

}

//�v���C���[�̎�
bool playerDead(void)
{
	if (player.life <= 0)
	{
		return true;
	}
}