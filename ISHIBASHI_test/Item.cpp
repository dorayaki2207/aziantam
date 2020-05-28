///// �{�X��@�����蔻��
/////	key�������ꂽ��@��D�������
/////	�����蔻����H


///// �A���ōU�����ł��Ȃ��悤�ɶ��ĂŊǗ�
/////�@�{�X����̍U���������莟��ύX����\���L��
////	�U�������������Key��������Ȃ�

#include "DxLib.h"
#include "test.h"
#include "KeyCheck.h"
#include "Stage.h"
#include "Item.h"
#include "Battle.h"

//-----�O���ϐ��錾
//���ъ֘A
//��D�i��ۯ��
CHARACTER itemF[ITEM_MAX];					//	��ۯ�߱��ѕϐ��i�[�p
CHARACTER itemFmaster[ITEM_TYPE_F_MAX];
int itemFImage[ITEM_TYPE_F_MAX];			//	��ۯ�߱��їp�摜�iF�F�D�̓�����
//��D�i�������
int itemFIImage[ITEM_TYPE_F_MAX];			//	������ؗp�摜�iF�F�D�̓������CI�F������؂̓�����
//��D�i�޽����
int itemFBImage[ITEM_TYPE_F_MAX];			//	�޽���ٗp�摜�iF�F�D�̓�����,�@B�F���ق̓�����
int lookCnt;
bool itemFBFlag[ITEM_TYPE_F_MAX];			//	�\��,��\���p

//�O��̐_��
CHARACTER itemB[ITEM_TYPE_B_MAX];
int itemBImage[ITEM_TYPE_B_MAX];			//	�_��̉摜�iB�F����̓�����



//-----���я��̏�����
void ItemSystemInit(void)
{
	//-----�ϐ��̏�����
	//��D�i��ۯ�ߗp
	itemFmaster[ITEM_TYPE_HI].charType = ITEM_TYPE_HI;				//	��D�̎��	�F	��
	itemFmaster[ITEM_TYPE_MIZU].charType = ITEM_TYPE_MIZU;			//	��D�̎��	�F	��
	itemFmaster[ITEM_TYPE_KAZE].charType = ITEM_TYPE_KAZE;			//	��D�̎��	�F	��
	itemFmaster[ITEM_TYPE_KAIFUKU].charType = ITEM_TYPE_KAIFUKU;	//	��D�̎��	�F	��
	//��D�܂Ƃ߂ď���
	for (int i = 0; i < ITEM_TYPE_F_MAX; i++)
	{
		itemFmaster[i].pos = { 250,250 };																//�@��D�̒n�}��̍��W
		itemFmaster[i].size = { 20,20 };															//	��D�̉摜����
		itemFmaster[i].offsetSize = { itemFmaster[i].size.x / 2,itemFmaster[i].size.y / 2 };		//�@��D�̵̾��
		itemFmaster[i].point = 0;																	//	��D�̖���
		itemFmaster[i].lifeMax = 20;																//	��D�̗͍̑ő�l�i�\�����ԁj
		itemFmaster[i].life = itemFmaster[i].lifeMax;												//	��D�̗̑�
	}

	//��D�i�޽���ٗp
	for (int type = 0; type < ITEM_TYPE_F_MAX; type++)
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
		itemB[i].offsetSize = { itemB[i].size.x / 2,itemB[i].size.y / 2 };							//�@�O��̐_��̵̾��
		
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
	//��D�i��ۯ�ߗp
	for (int i = 0; i < ITEM_MAX; i++)
	{

		itemF[i] = itemFmaster[GetRand(ITEM_TYPE_F_MAX - 1)];
		itemF[i].pos.x = GetRand(MAP_X * CHIP_SIZE_X - 1);
		itemF[i].pos.y = GetRand(MAP_Y * CHIP_SIZE_Y - 1);
		//	itemF[i].point = 0;																//	��D�̖���
		//	itemF[i].lifeMax = 20;															//	��D�̗͍̑ő�l�i�\�����ԁj
		//	itemF[i].life = itemF[i].lifeMax;												//	��D�̗̑�

	}
	//�O��̐_��
	for (int i = 0; i < ITEM_TYPE_B_MAX; i++)
	{
		itemB[i].pos = { 50,120 };									//�@�O��̐_��̒n�}��̍��W
		itemB[i].lifeMax = 20;										//	�O��̐_��̗͍̑ő�l�i�\�����ԁj
		itemB[i].life = itemB[i].lifeMax;							//	�O��̐_��̗̑�
	}

	

}

void ItemControl(CHARACTER boss)
{
	//�U���D���\������Ă��Ȃ��Ƃ��̂�Key������
	if (lookCnt == 0)
	{	
		//�΂̌�D
		if (keyDownTrigger[KEY_ID_FIRE])
		{
			//��D���ꖇ�ȏ゠��ꍇ�A�����\
			if (itemF[ITEM_TYPE_HI].point > 0)
			{
				itemF[ITEM_TYPE_HI].point--;
				itemFBFlag[ITEM_TYPE_HI] = true;
				boss.life--;
				boss.hitFlag = true;
			}
		}
		//���̌�D
		if (keyDownTrigger[KEY_ID_WATER])
		{
			//��D���ꖇ�ȏ゠��ꍇ�A�����\
			if (itemF[ITEM_TYPE_MIZU].point > 0)
			{
				itemF[ITEM_TYPE_MIZU].point--;
				itemFBFlag[ITEM_TYPE_MIZU] = true;
				boss.life--;
				boss.hitFlag = true;

			}
		}
		//���̌�D
		if (keyDownTrigger[KEY_ID_WIND])
		{
			//��D���ꖇ�゠��ꍇ�A�����\
			if (itemF[ITEM_TYPE_KAZE].point > 0)
			{
				itemF[ITEM_TYPE_KAZE].point--;
				itemFBFlag[ITEM_TYPE_KAZE] = true;
				boss.life--;
				boss.hitFlag = true;

			}
		}
		//�񕜂̌�D
		if (keyDownTrigger[KEY_ID_HEAL])
		{
			//��D���ꖇ�ȏ゠��ꍇ�A�����\
			if (itemF[ITEM_TYPE_KAIFUKU].point > 0)
			{
				itemF[ITEM_TYPE_KAIFUKU].point--;
				itemFBFlag[ITEM_TYPE_KAIFUKU] = true;
			}
		}
	}
	//�U���D�̕\������
	for (int type = 0; type < ITEM_TYPE_F_MAX; type++)
	{
		if (itemFBFlag[type])
		{
			lookCnt++;
			//���Ă�50������Ɣ�\���ɂ���
			if (lookCnt > 50)
			{
				itemFBFlag[type] = false;
				lookCnt = 0;
				boss.hitFlag = false;
			}
		}
	}

}
//-----��ۯ�ߗp
void ItemGameDraw(void)
{
	//-----�`�揈��
	//��D�i��ۯ�ߗp
	for (int i = 0; i < ITEM_MAX; i++)
	{
	//	if (Pass(itemF[i].pos) == PASS_OK)
	//	{
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
	//	}
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
	DrawGraph(350, 250, itemFIImage[ITEM_TYPE_HI], true);
	DrawFormatString(380, 254, 0xFF22FF, "��", true);
	DrawFormatString(410, 253, 0xFF22FF, "%d", itemF[ITEM_TYPE_HI].point);
	//���̌�D
	DrawGraph(350, 300, itemFIImage[ITEM_TYPE_MIZU], true);
	DrawFormatString(380, 304, 0xFF22FF, "��", true);
	DrawFormatString(410, 303, 0xFF22FF, "%d", itemF[ITEM_TYPE_MIZU].point);
	//���̌�D
	DrawGraph(350, 350, itemFIImage[ITEM_TYPE_KAZE], true);
	DrawFormatString(380, 354, 0xFF22FF, "��", true);
	DrawFormatString(410, 353, 0xFF22FF, "%d", itemF[ITEM_TYPE_KAZE].point);
	//�񕜂̌�D
	DrawGraph(350, 400, itemFIImage[ITEM_TYPE_KAIFUKU], true);
	DrawFormatString(380, 404, 0xFF22FF, "��", true);
	DrawFormatString(410, 403, 0xFF22FF, "%d", itemF[ITEM_TYPE_KAIFUKU].point);

}

void ItemB_Draw(void)
{
	//�U�����\���p
	for (int type = 0; type < ITEM_TYPE_F_MAX; type++)
	{
		if (itemFBFlag[type])
		{
			DrawGraph((SCREEN_SIZE_X - ITEM_B_SIZE) / 2, (BOX_Y - ITEM_B_SIZE) / 2, itemFBImage[type], true);
		}
	}
	//�������юc�ʕ\���p
	//�΂̌�D
	DrawGraph(350, BOX_Y +120, itemFIImage[ITEM_TYPE_HI], true);
	DrawFormatString(352, BOX_Y + 150, 0xFF22FF, "�~", true);
	DrawFormatString(380, BOX_Y + 150, 0xFF22FF, "%d", itemF[ITEM_TYPE_HI].point);
	//���̌�D
	DrawGraph(450, BOX_Y + 120, itemFIImage[ITEM_TYPE_MIZU], true);
	DrawFormatString(452, BOX_Y + 150, 0xFF22FF, "�~", true);
	DrawFormatString(480, BOX_Y + 150, 0xFF22FF, "%d", itemF[ITEM_TYPE_MIZU].point);
	//���̌�D
	DrawGraph(550, BOX_Y + 120, itemFIImage[ITEM_TYPE_KAZE], true);
	DrawFormatString(552, BOX_Y + 150, 0xFF22FF, "�~", true);
	DrawFormatString(580, BOX_Y + 150, 0xFF22FF, "%d", itemF[ITEM_TYPE_KAZE].point);
	//�񕜂̌�D
	DrawGraph(650, BOX_Y + 120, itemFIImage[ITEM_TYPE_KAIFUKU], true);
	DrawFormatString(652, BOX_Y + 150, 0xFF22FF, "�~", true);
	DrawFormatString(680, BOX_Y + 150, 0xFF22FF, "%d", itemF[ITEM_TYPE_KAIFUKU].point);


	DrawFormatString(0, 100, 0xFFFFFF, "lookCnt:%d", lookCnt);
}

//-----�e�ƓG�̓����蔻��@(true : ������, false : �͂���)
bool ItemHitCheck(XY sPos, int sSize)
{
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
				//�����������A��а�̗̑͂����炷
				itemF[i].life = 0;
				//��а��|�����������߲�ĉ��Z
				//��D�ɐG�ꂽ����Z
				if (itemF[i].charType == ITEM_TYPE_HI)
				{
					itemF[ITEM_TYPE_HI].point++;
					//hiCnt++;
				}
				if (itemF[i].charType == ITEM_TYPE_MIZU)
				{
					itemF[ITEM_TYPE_MIZU].point++;
					//mizuCnt++;
				}
				if (itemF[i].charType == ITEM_TYPE_KAZE)
				{
					itemF[ITEM_TYPE_KAZE].point++;
					//kazeCnt++;
				}
				if (itemF[i].charType == ITEM_TYPE_KAIFUKU)
				{
					itemF[ITEM_TYPE_KAIFUKU].point++;
					//kaifukuCnt++;
				}
				return true;
			}
		}
	}
	//�e���O�ꂽ��
	return false;
}

//-----�e�����ł�����
void DeleteItem(int index)
{
	itemF[index].life = 0;
	
};