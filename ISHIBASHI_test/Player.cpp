#include "DxLib.h"
#include "test.h"
#include "KeyCheck.h"
#include "Player.h"

//-----�O���ϐ��錾
//��׸��֘A
CHARACTER player;							//	��ڲ԰�ϐ��i�[�p
int playerImage[DIR_MAX][PLAYER_MAX];		//	��ڲ԰�摜�F�ʏ펞
bool hitFlag;								//	�U�����󂯂����ǂ����@true :�U�����󂯂Ă���


void PlayerSystmeInit(void)
{
	//-----�ϐ��̏�����
	player.moveDir = DIR_DOWN;											//	��׸��̌���
	player.size = { 32,32 };											//	��׸��̉摜����
	player.offsetSize = { player.size.x / 2,player.size.y / 2 };		//�@��׸��̵̾��
	player.moveSpeed = 4;												//	��׸��̈ړ���߰��
	hitFlag = false;

	//-----���̨���̓o�^
	//��׸��֘A
	LoadDivGraph("aitem/�d��.png", DIR_MAX*PLAYER_MAX
		, DIR_MAX, PLAYER_MAX, player.size.x, player.size.y, playerImage[0], true);
}

void PlayerGameInit(void)
{
	player.pos = { SCREEN_SIZE_X / 2,SCREEN_SIZE_Y / 2 };				//�@��׸��̒n�}��̍��W
	player.lifeMax = 150;												//	��׸��̗͍̑ő�l
	player.life = player.lifeMax;										//	��׸��̗̑�
	player.animCnt = 0;													//	��׸��̱�Ұ���

}

XY PlayerControl(void)
{
	bool movedFlag = false;			//�@���삳��Ă��邩���f����
	XY returnValue = player.pos;		// �֐��̖߂�l�i�[�̈�

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
			case DIR_RIGHT:			//	�E
				player.pos.x += player.moveSpeed;
				break;

			case DIR_LEFT:			//	��
				player.pos.x -= player.moveSpeed;
				break;

			case DIR_UP:			//	��
				player.pos.y -= player.moveSpeed;
				break;

			case DIR_DOWN:			//	��
				player.pos.y += player.moveSpeed;
				break;

			default:
				break;
			}

		}
	}
	return returnValue;
}

void PlayerGameDraw(void)
{
	//��ڲ԰�̊e��l��ύX����
	player.animCnt++;
	if (player.life > 0)
	{
		//-----�摜�`��
		//�U�����󂯂Ă��Ȃ����
		if (!hitFlag)
		{
			DrawGraph(player.pos.x - player.offsetSize.x
				, player.pos.y - player.offsetSize.y
				, playerImage[player.moveDir][((player.animCnt / 40) % 4)]
				, true);
		}
	}

}

