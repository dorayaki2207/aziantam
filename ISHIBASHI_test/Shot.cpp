#include "DxLib.h"
#include "test.h"
#include "KeyCheck.h"
#include "Item.h"
#include "Player.h"
#include "Shot.h"

#include "Stage.h"

//------�O���ϐ���`
CHARACTER shot[SHOT_TYPE_MAX - 1];
int shotImage[SHOT_TYPE_MAX - 1][SHOT_ANI];
//int shotFlag[SHOT_TYPE_MAX - 1];


void ShotSystemInit(void)
{
	//-----�ϐ��̏�����
	shot[SHOT_TYPE_FIRE].charType = SHOT_TYPE_FIRE;
	shot[SHOT_TYPE_WATER].charType = SHOT_TYPE_WATER;
	shot[SHOT_TYPE_WIND].charType = SHOT_TYPE_WIND;
	for (int sh = 0; sh < SHOT_TYPE_MAX - 1; sh++)
	{
		shot[sh].moveDir = DIR_DOWN;							//	�e�̌���
		shot[sh].size = { 40,40 };								//	�e�̉摜����
		shot[sh].offsetSize = { shot[sh].size.x / 2
			,shot[sh].size.y / 2 };			//�@�e�̵̾��
		shot[sh].moveSpeed = 4;									//	�e�̈ړ���߰��
		shot[sh].pos = { 0,0 };								//�@�e�̒n�}��̍��W

	}

	
	//-----���̨���̓o�^
	//��
	LoadDivGraph("aitem/fire_soft.png", SHOT_ANI, 8, 8
		, shot[SHOT_TYPE_FIRE].size.x
		, shot[SHOT_TYPE_FIRE].size.y
		, shotImage[SHOT_TYPE_FIRE]);
	//��
	LoadDivGraph("aitem/water_soft.png", SHOT_ANI, 8, 8
		, shot[SHOT_TYPE_WATER].size.x
		, shot[SHOT_TYPE_WATER].size.y
		, shotImage[SHOT_TYPE_WATER]);
	//��
	LoadDivGraph("aitem/wind_soft.png", SHOT_ANI, 8, 8
		, shot[SHOT_TYPE_WIND].size.x
		, shot[SHOT_TYPE_WIND].size.y
		, shotImage[SHOT_TYPE_WIND]);

}

void ShotGameInit(void)
{
	

	for (int sh = 0; sh < SHOT_TYPE_MAX - 1; sh++)
	{
		shot[sh].lifeMax = SHOT_LIFE_MAX;						//	�e�̗͍̑ő�l
		shot[sh].life = 0;						//	�e�̗̑�
		shot[sh].animCnt = 0;									//	�e�̱�Ұ���
	}
}

void ShotControl(void)
{
	for (int sh = 0; sh < SHOT_TYPE_MAX - 1; sh++)
	{
		//�����Ă���e��T��
		if (shot[sh].life > 0)
		{
			
			//�e���ړ�������
			if (shot[sh].moveDir == DIR_RIGHT) shot[sh].pos.x += shot[sh].moveSpeed;
			if (shot[sh].moveDir == DIR_LEFT) shot[sh].pos.x -= shot[sh].moveSpeed;
			if (shot[sh].moveDir == DIR_DOWN) shot[sh].pos.y += shot[sh].moveSpeed;
			if (shot[sh].moveDir == DIR_UP) shot[sh].pos.y -= shot[sh].moveSpeed;
			//���������炷�i�˒������j
			shot[sh].life--;

		//			DeleteShot(sh);
		}
	}
}



//-----�e�`�揈��
void ShotGameDraw(void)
{
	//-----�`��
	for (int sh = 0; sh < ITEM_TYPE_F_MAX - 1; sh++)
	{
		if (shot[sh].life > 0)
		{
			shot[sh].animCnt++;

			DrawGraph(shot[sh].pos.x - shot[sh].offsetSize.x + mapPos.x
				, shot[sh].pos.y - shot[sh].offsetSize.y + mapPos.y
				, shotImage[shot[sh].charType][shot[sh].animCnt]
				, true);
		}

		DrawBox(shot[sh].pos.x - shot[sh].offsetSize.x + mapPos.x
			, shot[sh].pos.y - shot[sh].offsetSize.y + mapPos.y
			, shot[sh].pos.x - shot[sh].offsetSize.x + shot[sh].size.x + mapPos.x
			, shot[sh].pos.y - shot[sh].offsetSize.y + shot[sh].size.y + mapPos.y
			, 0xFFFFFF, false);
		//-----��񏈗�
		DrawFormatString(0, 300, 0xFFFFFF, "shotAni:%d", shot[sh].animCnt);

	}


}


//-----�e�𐶐�����
void CreateShot(XY pPos, DIR pDir, SHOT_TYPE ptype/*, ITEM_TYPE_F itype*/)
{

	//�e�̐��������Ă��Ȃ��e���Ȃ������������A
	//�����Ă��Ȃ��e������Έꔭ�e������Ĕ��˂���B
	for (int sh = 0; sh < SHOT_TYPE_MAX - 1; sh++)
	{
			//�����Ă��Ȃ��e��T��
			if (shot[sh].life <= 0)
			{
				//��D�̐���0���ȏ�̏ꍇ�̂ݏ���������
			/*	if (itemF[itype].point > 0)
				{*/
					//�����Ă��Ȃ��e���������̂Ŕ���
					shot[sh].charType = ptype;
					shot[sh].pos.x = pPos.x;				//	�e�̏ꏊ
					shot[sh].pos.y = pPos.y;
					shot[sh].moveDir = pDir;				//	�e�̐i�ނׂ�����
					shot[sh].life = shot[sh].lifeMax;		//	�e�����������Ƃɂ���
					break;
			//	}
		}
	}
}

//-----�e�����ł�����
void DeleteShot(int index)
{
	if (shot[index].life < 0)
	{
		shot[index].life = 0;
	}

}

void ShotAniCnt(SHOT_TYPE type)
{
	if (shot[type].animCnt > SHOT_ANI)
	{
		shot[type].animCnt = 0;
	}
}