#include "DxLib.h"
#include "test.h"
#include "KeyCheck.h"
#include "Item.h"
#include "Player.h"
#include "Shot.h"
#include "Stage.h"

//------�O���ϐ���`
CHARACTER shotMaster[MAGIC_TYPE_MAX];
CHARACTER shot[SHOT_MAX];
int shotImage[MAGIC_TYPE_MAX][SHOT_ANI];



void ShotSystemInit(void)
{
	//-----�ϐ��̏�����
	shotMaster[MAGIC_TYPE_FIRE].charType = MAGIC_TYPE_FIRE;
	shotMaster[MAGIC_TYPE_WATER].charType = MAGIC_TYPE_WATER;
	shotMaster[MAGIC_TYPE_WIND].charType = MAGIC_TYPE_WIND;
	shotMaster[MAGIC_TYPE_HEAL].charType = MAGIC_TYPE_HEAL;
	for (int type = 0; type < MAGIC_TYPE_MAX; type++)
	{
		shotMaster[type].moveDir = DIR_DOWN;						//	�e�̌���
		shotMaster[type].size = { 40,40 };							//	�e�̉摜����
		shotMaster[type].offsetSize = { shotMaster[type].size.x / 2
			,shotMaster[type].size.y / 2 };							//�@�e�̵̾��
		shotMaster[type].moveSpeed = 4;								//	�e�̈ړ���߰��
		shotMaster[type].pos = { 0,0 };								//�@�e�̒n�}��̍��W
		shotMaster[type].lifeMax = SHOT_LIFE_MAX;						//	�e�̗͍̑ő�l
		shotMaster[type].life = 0;									//	�e�̗̑�
		shotMaster[type].animCnt = 0;								//	�e�̱�Ұ���


		for (int sh = 0; sh < SHOT_MAX; sh++)
		{
			shot[sh] = shotMaster[type];
			shot[sh].pos = {0,0};
			shot[sh].lifeMax = SHOT_LIFE_MAX;						//	�e�̗͍̑ő�l
			shot[sh].life = 0;									//	�e�̗̑�
			shot[sh].animCnt = 0;								//	�e�̱�Ұ���

		}
	}
	//-----���̨���̓o�^
	//��
	LoadDivGraph("aitem/fire_soft.png", SHOT_ANI, 8, 8
		, shot[MAGIC_TYPE_FIRE].size.x
		, shot[MAGIC_TYPE_FIRE].size.y
		, shotImage[MAGIC_TYPE_FIRE]);
	//��
	LoadDivGraph("aitem/water_soft.png", SHOT_ANI, 8, 8
		, shot[MAGIC_TYPE_WATER].size.x
		, shot[MAGIC_TYPE_WATER].size.y
		, shotImage[MAGIC_TYPE_WATER]);
	//��
	LoadDivGraph("aitem/wind_soft.png", SHOT_ANI, 8, 8
		, shot[MAGIC_TYPE_WIND].size.x
		, shot[MAGIC_TYPE_WIND].size.y
		, shotImage[MAGIC_TYPE_WIND]);
	//��
	LoadDivGraph("aitem/life.png", SHOT_ANI, 8, 8
		, shot[MAGIC_TYPE_HEAL].size.x
		, shot[MAGIC_TYPE_HEAL].size.y
		, shotImage[MAGIC_TYPE_HEAL]);

}

void ShotGameInit(void)
{
	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		shot[sh].pos = { 0,0 };
		shot[sh].life = 0;									//	�e�̗̑�
		
	}
}

void ShotControl(XY pPos)
{
	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		shot[sh].animCnt++;
		//�����Ă���e��T��
		if (shot[sh].life > 0)
		{

			//�e���ړ�������
			if (shot[sh].moveDir == DIR_RIGHT) shot[sh].pos.x += shot[sh].moveSpeed;
			if (shot[sh].moveDir == DIR_LEFT) shot[sh].pos.x -= shot[sh].moveSpeed;
			if (shot[sh].moveDir == DIR_DOWN) shot[sh].pos.y += shot[sh].moveSpeed;
			if (shot[sh].moveDir == DIR_UP) shot[sh].pos.y -= shot[sh].moveSpeed;
			
			if (shot[sh].charType == MAGIC_TYPE_HEAL)
			{
				if (shot[sh].moveDir == DIR_RIGHT) shot[sh].pos.x = pPos.x;
				if (shot[sh].moveDir == DIR_LEFT) shot[sh].pos.x = pPos.x;
				if (shot[sh].moveDir == DIR_DOWN) shot[sh].pos.y = pPos.y;
				if (shot[sh].moveDir == DIR_UP) shot[sh].pos.y = pPos.y;
			}

			//���������炷�i�˒������j
			shot[sh].life--;
			if (shot[sh].animCnt > SHOT_ANI)
			{
				shot[sh].animCnt = 0;
			}

		}
	}
}



//-----�e�`�揈��
void ShotGameDraw(void)
{
	//-----�`��
	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		if (shot[sh].life > 0)
		{
			shot[sh].animCnt++;

			DrawGraph(shot[sh].pos.x - shot[sh].offsetSize.x + mapPos.x
				, shot[sh].pos.y - shot[sh].offsetSize.y + mapPos.y
				, shotImage[shot[sh].charType][shot[sh].animCnt]
				, true);


			DrawBox(shot[sh].pos.x - shot[sh].offsetSize.x + mapPos.x
				, shot[sh].pos.y - shot[sh].offsetSize.y + mapPos.y
				, shot[sh].pos.x - shot[sh].offsetSize.x + shot[sh].size.x + mapPos.x
				, shot[sh].pos.y - shot[sh].offsetSize.y + shot[sh].size.y + mapPos.y
				, 0xFFFFFF, false);
		}
		//-----��񏈗�
		DrawFormatString(0, 100, 0xFFFFFF, "shotPos : %d,%d", shot[sh].pos.x, shot[sh].pos.y);
		DrawFormatString(0, 120, 0xFFFFFF, "shotAni : %d", shot[sh].animCnt);
		DrawFormatString(0, 160, 0xFFFFFF, "shotLife : %d", shot[sh].life);

	}


}



//-----�e�𐶐�����
void CreateShot(XY pPos, DIR pDir, MAGIC_TYPE ptype/*, ITEM_TYPE_F itype*/)
{

	//�e�̐��������Ă��Ȃ��e���Ȃ������������A
	//�����Ă��Ȃ��e������Έꔭ�e������Ĕ��˂���B
	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		//�����Ă��Ȃ��e��T��
		if (shot[sh].life <= 0)
		{
			//��D�̐���0���ȏ�̏ꍇ�̂ݏ���������
			if (ItemMOBControl(ptype))
			{
				//�����Ă��Ȃ��e���������̂Ŕ���
				shot[sh].charType = ptype;
				shot[sh].pos = { pPos.x,pPos.y };		//	�e�̏ꏊ
				shot[sh].moveDir = pDir;				//	�e�̐i�ނׂ�����
				shot[sh].life = shot[sh].lifeMax;		//	�e�����������Ƃɂ���
			}
		}
		break;
	}
}

//-----�e�����ł�����
void DeleteShot(int index)
{
	shot[index].life = 0;
}