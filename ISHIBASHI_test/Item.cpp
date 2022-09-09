/////	�����蔻����H


///// �A���ōU�����ł��Ȃ��悤�ɶ��ĂŊǗ�
/////�@�{�X����̍U���������莟��ύX����\���L��

//ItemBossControl  ���������ׁ̈@for���ł܂킵�āA�@keycheck������@type �ł݂�悤�ɂ���@�A�C�e���E�������I�������Ă݂�


//  �e�X�g�p�ɱ��т��͂��߂���2������������悤�ɂ���

//GetRand 0~3
#include "DxLib.h"
#include "test.h"
#include "KeyCheck.h"
#include "Stage.h"
#include "Item.h"
#include "Battle.h"
#include "Enemy.h"

//-----�O���ϐ��錾
//���ъ֘A
//��D�i��ۯ��
CHARACTER itemF[ITEM_MAX];					//	��ۯ�߱��ѕϐ��i�[�p
CHARACTER itemFmaster[MAGIC_TYPE_MAX];
int itemFImage[MAGIC_TYPE_MAX];				//	��ۯ�߱��їp�摜�iF�F�D�̓�����
//��D�i�������
int itemFIImage[MAGIC_TYPE_MAX];			//	������ؗp�摜�iF�F�D�̓������CI�F������؂̓�����
//��D�i�޽����
int itemFBImage[MAGIC_TYPE_MAX];			//	�޽���ٗp�摜�iF�F�D�̓�����,�@B�F���ق̓�����
int lookCnt;
bool itemFBFlag[MAGIC_TYPE_MAX];			//	�\��,��\���p

//�O��̐_��
CHARACTER itemB[ITEM_TYPE_B_MAX];
int itemBImage[ITEM_TYPE_B_MAX];			//	�_��̉摜�iB�F����̓�����



//-----���я��̏�����
void ItemSystemInit(void)
{
	//-----�ϐ��̏�����
	//��D�i��ۯ�ߗp
	itemFmaster[MAGIC_TYPE_FIRE].charType = MAGIC_TYPE_FIRE;												//	��D�̎��	�F	��
	itemFmaster[MAGIC_TYPE_WATER].charType = MAGIC_TYPE_WATER;												//	��D�̎��	�F	��
	itemFmaster[MAGIC_TYPE_WIND].charType = MAGIC_TYPE_WIND;												//	��D�̎��	�F	��
	itemFmaster[MAGIC_TYPE_HEAL].charType = MAGIC_TYPE_HEAL;												//	��D�̎��	�F	��
	//��D�܂Ƃ߂ď���
	for (int type = 0; type < MAGIC_TYPE_MAX; type++)
	{
		itemFmaster[type].pos = { 0,0 };																	//	��D�̒n�}��̍��W
		itemFmaster[type].size = { 20,20 };																//	��D�̉摜����
		itemFmaster[type].offsetSize = { itemFmaster[type].size.x / 2,itemFmaster[type].size.y / 2 };	//	��D�̵̾��
		itemFmaster[type].point = 12;																		//	��D�̖���
		itemFmaster[type].lifeMax = 200;																	//	��D�̗͍̑ő�l�i�\�����ԁj
		itemFmaster[type].life = 0;																		//	��D�̗̑�
		itemFmaster[type].hitFlag = false;
	
	}

	//��D�i�޽���ٗp
	for (int type = 0; type < MAGIC_TYPE_MAX; type++)
	{
		itemFBFlag[type] = false;									//	true�F�\��, false�F��\�� 
	}
	lookCnt = 0;
	//�O��̐_��
	itemB[ITEM_TYPE_KEN].charType = ITEM_TYPE_KEN;					//	�O��̐_��@�F�@��
	itemB[ITEM_TYPE_KAGAMI].charType = ITEM_TYPE_KAGAMI;			//	�O��̐_��@�F�@��
	itemB[ITEM_TYPE_MAGATAMA].charType = ITEM_TYPE_MAGATAMA;		//	�O��̐_��@�F�@����
	//�O��̐_��܂Ƃ߂ď���
	for (int i = 0; i < ITEM_TYPE_B_MAX; i++)
	{
		itemB[i].size = { 20,20 };																	//	�O��̐_��̉摜����
		itemB[i].offsetSize = { itemB[i].size.x / 2,itemB[i].size.y / 2 };						//�@�O��̐_��̵̾��
		
	}




	//-----���̨���̓o�^
	//��D(��ۯ�ߗp
	LoadDivGraph("aitem/fudaD.png", 4, 4, 1
		, ITEM_M_SIZE, ITEM_M_SIZE, itemFImage);
	//��D�i������ؗp
	LoadDivGraph("aitem/fudaI.png", 4, 4, 1
		, ITEM_M_SIZE, ITEM_M_SIZE, itemFIImage);
	//��D�i�޽���ٗp
	LoadDivGraph("aitem/fuda_Big.png", 4, 4, 1
		, ITEM_B_SIZE, ITEM_B_SIZE, itemFBImage);
	//�O��̐_��
	LoadDivGraph("aitem/zingi20.png", 3, 3, 1
		, ITEM_M_SIZE, ITEM_M_SIZE, itemBImage);

}

void ItemGameInit(void)
{
	for (int type = 0; type < MAGIC_TYPE_MAX; type++)
	{
		for (int i = 0; i < ITEM_MAX; i++)
		{

			itemF[i] = itemFmaster[type];
			//	itemF[i].pos = { 0,0 };
			//	itemF[i].point = 0;					//	��D�̖���
			//	itemF[i].lifeMax = 0;				//	��D�̗͍̑ő�l�i�\�����ԁj
			itemF[i].life = 0;						//	�̗�
		}
	}
	
	//�O��̐_��
	for (int i = 0; i < ITEM_TYPE_B_MAX; i++)
	{
		itemB[i].pos = { 50,120 };									//�@�O��̐_��̒n�}��̍��W
		itemB[i].lifeMax = 20;										//	�O��̐_��̗͍̑ő�l�i�\�����ԁj
		itemB[i].life = itemB[i].lifeMax;							//	�O��̐_��̗̑�
	}

	

}



void itemDropControl()
{
	for (int i = 0; i < ITEM_MAX; i++)
	{
		
		//�����Ă���e��T��
		if (itemF[i].life >0)
		{

			//���������炷�i�˒������j
			itemF[i].life--;
		}
	}
}


//�{�X�폈��
void ItemBossControl(CHARACTER* boss)
{
	//�U���D���\������Ă��Ȃ��Ƃ��̂�Key������
	if (lookCnt == 0)
	{	
		//�΂̌�D
		if (keyNew[KEY_ID_FIRE])
		{
			//��D���ꖇ�ȏ゠��ꍇ�A�����\
			if (itemF[MAGIC_TYPE_FIRE].point > 0)
			{
				itemF[MAGIC_TYPE_FIRE].point--;
				itemFBFlag[MAGIC_TYPE_FIRE] = true;
				(*boss).life--;
				(*boss).hitFlag = true;
			}
		}
		//���̌�D
		if (keyNew[KEY_ID_WATER])
		{
			//��D���ꖇ�ȏ゠��ꍇ�A�����\
			if (itemF[MAGIC_TYPE_WATER].point > 0)
			{
				itemF[MAGIC_TYPE_WATER].point--;
				itemFBFlag[MAGIC_TYPE_WATER] = true;
				(*boss).life--;
				(*boss).hitFlag = true;

			}
		}
		//���̌�D
		if (keyNew[KEY_ID_WIND])
		{
			//��D���ꖇ�゠��ꍇ�A�����\
			if (itemF[MAGIC_TYPE_WIND].point > 0)
			{
				itemF[MAGIC_TYPE_WIND].point--;
				itemFBFlag[MAGIC_TYPE_WIND] = true;
				(*boss).life--;
				(*boss).hitFlag = true;

			}
		}
		//�񕜂̌�D
		if (keyNew[KEY_ID_HEAL])
		{
			//��D���ꖇ�ȏ゠��ꍇ�A�����\
			if (itemF[MAGIC_TYPE_HEAL].point > 0)
			{
				itemF[MAGIC_TYPE_HEAL].point--;
				itemFBFlag[MAGIC_TYPE_HEAL] = true;
			}
		}
	}
	//�U���D�̕\������
	for (int type = 0; type < MAGIC_TYPE_MAX; type++)
	{
		if (itemFBFlag[type])
		{
			lookCnt++;
			//���Ă�50������Ɣ�\���ɂ���
			if (lookCnt > 50)
			{
				itemFBFlag[type] = false;
				lookCnt = 0;
				(*boss).hitFlag = false;
			}
		}
	}

}




//MOB�G��펞����
bool ItemMOBControl(MAGIC_TYPE type)
{
	//��D���ꖇ�ȏ゠��ꍇ�A�����\
	if (itemF[type].point > 0)
	{
		itemF[type].point--;
		return true;
	}
	return false;
}



//-----��ۯ�ߗp
void ItemGameDraw(void)
{
	//-----�`�揈��
	//��D�i��ۯ�ߗp
	for (int i = 0; i < ITEM_MAX; i++)
	{
		//�����Ă��D�̂ݕ\��
		if (itemF[i].life > 0)
		{
			//-----�摜�`��
			DrawGraph(itemF[i].pos.x - itemF[i].offsetSize.x + mapPos.x
				, itemF[i].pos.y - itemF[i].offsetSize.y + mapPos.y
				, itemFImage[itemF[i].charType]
				, true);

			DrawBox(itemF[i].pos.x - itemF[i].offsetSize.x + mapPos.x
				, itemF[i].pos.y - itemF[i].offsetSize.y + mapPos.y
				, itemF[i].pos.x - itemF[i].offsetSize.x + itemF[i].size.x + mapPos.x
				, itemF[i].pos.y - itemF[i].offsetSize.y + itemF[i].size.y + mapPos.y
				, 0xFF00FF, false);
		}
		DrawFormatString(0, 140, 0xFFFFFF, "itemLife : %d", itemF[i].life);
	}

	//�O��̐_��
	for (int i = 0; i < ITEM_TYPE_B_MAX; i++)
	{
		if (itemB[i].life > 0)
		{
			DrawGraph((itemB[i].pos.x   - itemB[i].offsetSize.x )*i
				, itemB[i].pos.y - itemB[i].offsetSize.y
				, itemBImage[itemB[i].charType]
				, true);

			DrawBox((itemB[i].pos.x - itemB[i].offsetSize.x)*i
				, itemB[i].pos.y - itemB[i].offsetSize.y
				, (itemB[i].pos.x - itemB[i].offsetSize.x) *i+ itemB[i].size.x
				, itemB[i].pos.y - itemB[i].offsetSize.y + itemB[i].size.y
				, 0xFF00FF, false);

		}
	}
}

//-----������ؗp�`��
void ItemI_Draw(void)
{
	//�΂̌�D
	DrawGraph(350, 250, itemFIImage[MAGIC_TYPE_FIRE], true);
	DrawFormatString(380, 254, 0xFF22FF, "��", true);
	DrawFormatString(410, 253, 0xFF22FF, "%d", itemF[MAGIC_TYPE_FIRE].point);
	//���̌�D
	DrawGraph(350, 300, itemFIImage[MAGIC_TYPE_WATER], true);
	DrawFormatString(380, 304, 0xFF22FF, "��", true);
	DrawFormatString(410, 303, 0xFF22FF, "%d", itemF[MAGIC_TYPE_WATER].point);
	//���̌�D
	DrawGraph(350, 350, itemFIImage[MAGIC_TYPE_WIND], true);
	DrawFormatString(380, 354, 0xFF22FF, "��", true);
	DrawFormatString(410, 353, 0xFF22FF, "%d", itemF[MAGIC_TYPE_WIND].point);
	//�񕜂̌�D
	DrawGraph(350, 400, itemFIImage[MAGIC_TYPE_HEAL], true);
	DrawFormatString(380, 404, 0xFF22FF, "��", true);
	DrawFormatString(410, 403, 0xFF22FF, "%d", itemF[MAGIC_TYPE_HEAL].point);

}

void ItemB_Draw(void)
{
	//�U�����\���p
	for (int type = 0; type < MAGIC_TYPE_MAX; type++)
	{
		if (itemFBFlag[type])
		{
			DrawGraph((SCREEN_SIZE_X - ITEM_B_SIZE) / 2, (BOX_Y - ITEM_B_SIZE) / 2, itemFBImage[type], true);
		}
	}

	//�������юc�ʕ\���p
	//�΂̌�D
	DrawGraph(350, BOX_Y +120, itemFIImage[MAGIC_TYPE_FIRE], true);
	DrawFormatString(352, BOX_Y + 150, 0xFF22FF, "�~", true);
	DrawFormatString(380, BOX_Y + 150, 0xFF22FF, "%d", itemF[MAGIC_TYPE_FIRE].point);
	//���̌�D
	DrawGraph(450, BOX_Y + 120, itemFIImage[MAGIC_TYPE_WATER], true);
	DrawFormatString(452, BOX_Y + 150, 0xFF22FF, "�~", true);
	DrawFormatString(480, BOX_Y + 150, 0xFF22FF, "%d", itemF[MAGIC_TYPE_WATER].point);
	//���̌�D
	DrawGraph(550, BOX_Y + 120, itemFIImage[MAGIC_TYPE_WIND], true);
	DrawFormatString(552, BOX_Y + 150, 0xFF22FF, "�~", true);
	DrawFormatString(580, BOX_Y + 150, 0xFF22FF, "%d", itemF[MAGIC_TYPE_WIND].point);
	//�񕜂̌�D
	DrawGraph(650, BOX_Y + 120, itemFIImage[MAGIC_TYPE_HEAL], true);
	DrawFormatString(652, BOX_Y + 150, 0xFF22FF, "�~", true);
	DrawFormatString(680, BOX_Y + 150, 0xFF22FF, "%d", itemF[MAGIC_TYPE_HEAL].point);


	//DrawFormatString(0, 100, 0xFFFFFF, "lookCnt:%d", lookCnt);
}

//-----�A�C�e���ƃv���C���[�̓����蔻��@(true : ������, false : �͂���)
bool ItemHitCheck(XY sPos, int sSize)
{
	int point = GetRand(5)+1;

	//�S�Ă̓G�ɓ����蔻������{����
	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (itemF[i].life > 0)
		{
			if (((itemF[i].pos.x - itemF[i].size.x / 2) < (sPos.x + sSize / 2))
				&& ((itemF[i].pos.x + itemF[i].size.x / 2) > (sPos.x - sSize / 2))
				&& ((itemF[i].pos.y - itemF[i].size.y / 2) < (sPos.y + sSize / 2))

				&& ((itemF[i].pos.y + itemF[i].size.y / 2) > (sPos.y - sSize / 2)))
			{
				//�����������A���т�����
				//	itemF[i].life = 0;
				//��ۯ�߱��т��E�����������߲�ĉ��Z
				//��D�ɐG�ꂽ����Z
				if (itemF[i].charType == MAGIC_TYPE_FIRE)
				{
					itemF[i].point += point;
					itemF[i].hitFlag = true;
				}
				if (itemF[i].charType == MAGIC_TYPE_WATER)
				{
					itemF[MAGIC_TYPE_WATER].point += point;
					itemF[i].hitFlag = true;
				}
				if (itemF[i].charType == MAGIC_TYPE_WIND)
				{
					itemF[MAGIC_TYPE_WIND].point += point;
					itemF[i].hitFlag = true;
				}
				if (itemF[i].charType == MAGIC_TYPE_HEAL)
				{
					itemF[MAGIC_TYPE_HEAL].point += point;
					itemF[i].hitFlag = true;
				}
				
				return true;
			}
		}
	}
	//�e���O�ꂽ��
	return false;
}


//-----�h���b�v�A�C�e��
void ItemDrop(XY ePos,MAGIC_TYPE type)
{
	//�e�̐��������Ă��Ȃ��e���Ȃ������������A
	//�����Ă��Ȃ��e������Έꔭ�e������Ĕ��˂���B
	for (int item = 0; item < ITEM_MAX; item++)
	{
		//�����Ă��Ȃ��e��T��
		if (itemF[item].life <= 0)
		{
			//�����Ă��Ȃ��e���������̂Ŕ���
			itemF[item].charType = type;
			itemF[item].pos = { ePos.x,ePos.y };
			itemF[item].life = itemF[item].lifeMax;	
			break;
		}
	
	}
}



//-----�h���b�v�A�C�e�������ł�����
void DeleteItem()
{
	for (int item = 0; item< ITEM_MAX; item++)
	{
		if (itemF[item].life > 0 && itemF[item].hitFlag)
		{
			itemF[item].life = 0;
			itemF[item].hitFlag = false;
			break;
		}
	}
}



