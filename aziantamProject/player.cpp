#include <DxLib.h>
#include "main.h"
#include "player.h"
#include "keycheck.h"
#include "stage.h"
#include "shot.h"
#include "enemy.h"
#include "effect.h"

//�ϐ�
int playerImage[16];
CHARACTER player;

int lifeCheckCnt;
int healCheckCnt;
int speedCnt;

//��ڲ԰���̏�����
void PlayerSystemInit(void)
{
	//player.charType;										//��׸��̎��
	player.size = {32,32};									//��׸��摜�̻���
	player.offsetSize = {player.size.x/2,player.size.y/2};	//��׸��̵̾��
	player.lifeMax = PLAYER_MAX_LIFE;						//��׸��̗͍̑ő�l
	player.moveSpeed = PLAYER_DEF_SPEED;					//��׸��̈ړ���߰��
	player.animCnt = 0;										//��׸��̱�Ұ���
	player.hitFlag = false;

	LoadDivGraph("char/boy_player.png", 16, 4, 4
		, player.size.x, player.size.y, playerImage);
}
//�v���C���[�̏�����
void PlayerGameInit(void)
{
	player.moveDir = DIR_RIGHT;								//��׸��̌���
	player.pos = { 160,135};								//��׸��̒n�}��̍��W

	player.life = player.lifeMax;							//��׸��̗̑�
	lifeCheckCnt = 0;
	healCheckCnt = 0;
	speedCnt = 0;
}

bool PlayerDid()
{
	if (player.life <= 0)
	{
		return true;
	}
	return false;
}

//�v���C���[�̑���
XY PlayerControl(void)
{
	bool moveFlag = false;				//�@���삳��Ă��邩���f����
	XY returnValue = player.pos;			//	�֐��̖߂�l�i�[�̈�
	XY playerPosCopy = player.pos;
	XY playerPosOffset = playerPosCopy;
	XY indexPos;							//�@ϯ�ߔz����W

	if (player.life < 0) SceneID = SCENE_GAMEOVER;

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
				playerPosOffset.y = playerPosCopy.y - player.offsetSize.y;
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
				playerPosOffset.y = playerPosCopy.y + player.offsetSize.y;
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
				playerPosOffset.x = playerPosCopy.x + player.offsetSize.x;
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
				playerPosOffset.x = playerPosCopy.x - player.offsetSize.x;
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
			CreateShot(player.pos, player.moveDir, MAGIC_TYPE_FIRE);
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

			if (healCheckCnt == 0)
			{
				CreateShot(player.pos, player.moveDir, MAGIC_TYPE_HEAL);

				healCheckCnt = 100;
				if (player.lifeMax > player.life)
				{
					player.life++;
				}
				if (player.life > player.lifeMax)
				{
					player.life = player.lifeMax;
				}
			}
		}

		if (healCheckCnt > 0)
		{
			healCheckCnt--;
			if (healCheckCnt < 0)
			{
				healCheckCnt = 0;
			}
		}

		//�X�N���[������
		MapRange();

		//-----���C�t����
		if (PlayerHitCheck(player.pos, player.size.x))
		{
			if (lifeCheckCnt == 0)
			{
				DamageEffect(player.pos, MAGIC_TYPE_HEAL);
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

		
		PlayerEvent();
	}

	return returnValue;
}


//�v���C���[�̕`��
void PlayerGameDraw(void)
{
	if (player.life > 0)
	{
		player.animCnt++;
		if (lifeCheckCnt % 10 == 0)
		{
			DrawGraph(player.pos.x - player.offsetSize.x + mapPos.x
				, player.pos.y - player.offsetSize.y + mapPos.y
				, playerImage[(player.moveDir * 4) + (player.animCnt / 30) % 4], true);
		}
	}
	DrawBox(SCROLL_X_MIN, SCROLL_Y_MIN, SCROLL_X_MAX, SCROLL_Y_MAX, 0xFFFFFF, false);
	DrawBox(32, 25, player.lifeMax, 16, GetColor(255, 0, 0), true);
	DrawBox(32, 25, player.life, 16, GetColor(0, 255, 0), true);
	DrawBox(32, 25, player.lifeMax, 16, GetColor(255, 255, 0), false);
	DrawFormatString(0, 50, 0xFFFFFF, "player:%d,%d", player.pos.x, player.pos.y);
	XY indexPos;
	indexPos = Pos2Index(player.pos);

	//��񏈗�
	DrawFormatString(0, 180, 0xFFFFFF, "playerPos:%d,%d", player.pos.x, player.pos.y);
	DrawFormatString(0, 300, 0xFFFFFF, "playerHp%d", player.life);
	DrawFormatString(0, 350, 0xffffff, "LifeCheck:%d", lifeCheckCnt);
	DrawFormatString(0, 370, 0xffffff, "moveCheck:%d", healCheckCnt);
	DrawFormatString(0, 370, 0xffffff, "speedCnt:%d", speedCnt);

}


void PlayerEvent(void)
{
	if ((stageID == STAGE_ID_START) || (stageID == STAGE_ID_MOB) || (stageID == STAGE_ID_KAPPA))
	{
		// ����ȃ}�b�v�𓥂񂾏ꍇ�̏���
		/*if (GetEvent(player.pos) == EVENT_ID_DOKU)
		{
			speedCnt++;
			if (speedCnt < 10)
			{
				player.moveSpeed = PLAYER_SPEED_LOW;
				player.life -= 3;
				lifeCheckCnt = 100;
			}
		}*/
		// ��
		if (GetEvent(player.pos) == EVENT_ID_SPEEDDOWN)
		{
			speedCnt++;
			player.moveSpeed = PLAYER_SPEED_LOW;
		}
		//�_���[�W
		else if (GetEvent(player.pos) == EVENT_ID_DOKU)
		{
			if (lifeCheckCnt == 0)
			{
				player.life -= 5;
				lifeCheckCnt = 10;
			}
		}
		// �C�x���g�߂�
		else
		{
			player.moveSpeed = PLAYER_SPEED_NORMAL;
		}
	}

	if (stageID == STAGE_ID_ONI)
	{
		//-----����Ĕ���
		//�������~�܂�
		if (GetEvent(player.pos) == EVENT_ID_STOP)
		{
			speedCnt++;
			if (speedCnt < 100)
			{
				player.moveSpeed = PLAYER_SPEED_STOP;
			}
			else if (speedCnt >= 100)
			{
				player.moveSpeed = PLAYER_SPEED_NORMAL;
			}
		}
		//�������x���Ȃ�
		else if (GetEvent(player.pos) == EVENT_ID_SPEEDDOWN)
		{
			player.moveSpeed = PLAYER_SPEED_LOW;
		}
		//��Ұ�ނ��󂯂�
		else if (GetEvent(player.pos) == EVENT_ID_DAMAGE)
		{
			if (lifeCheckCnt == 0)
			{
				player.life -= 5;
				lifeCheckCnt = 100;
			}
		}
		//�ʏ펞�̈ړ��X�s�[�h
		else
		{
			player.moveSpeed = PLAYER_SPEED_NORMAL;
		}

		if (GetEvent(player.pos) != EVENT_ID_STOP)
		{
			speedCnt = 0;
		}
	}
 }