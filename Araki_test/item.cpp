////	��ۯ�߱��т͓G���|���ꂽ�炻�̏�ɏo��
////	����HP���g���ēG��|���Ĉ�莞�ԓ��Ɏ��Ȃ��Ə�����悤�ɂ��� 
////	�G�̓����蔻��Ɂ@�ς��Ɖ΂̌�D�A�ꔽ�ؖȂ��ƕ��̌�D�A�C�V�傾�Ɛ��̌�D
////	�񕜂̌�D�͑S���̓GMOB����m���ŏo������悤�ɂ���
////	�G���|���ꂽ��@����HP�����炵�Ă���
#include "DxLib.h"
#include "main.h"
#include "item.h"


//-----�O���ϐ��錾
//���ъ֘A
//��D
CHARACTER itemF[ITEM_MAX];					//	��ۯ�߱��ѕϐ��i�[�p
CHARACTER itemFmaster[MAGIC_TYPE_MAX];
int itemFImage[MAGIC_TYPE_MAX];			//	��ۯ�߱��їp�摜�iF�F�D�̓�����
int itemFIImage[MAGIC_TYPE_MAX];			//	������ؗp�摜�iF�F�D�̓������CI�F������؂̓�����
int itemFBImage[MAGIC_TYPE_MAX];			//	�޽���ٗp�摜�iF�F�D�̓�����,�@B�F���ق̓�����
bool itemFBFlag;							//	�\��,��\���p
//�O��̐_��
CHARACTER itemB[ITEM_TYPE_B_MAX];
int itemBImage[ITEM_TYPE_B_MAX];			//	�_��̉摜�iB�F����̓�����




//-----���я��̏�����
void ItemSystmeInit(void)
{
	//-----�ϐ��̏�����
	//��D�i��ۯ�ߗp
	itemFmaster[MAGIC_TYPE_FIRE].charType = MAGIC_TYPE_FIRE;				//	��D�̎��	�F	��
	itemFmaster[MAGIC_TYPE_WATER].charType = MAGIC_TYPE_WATER;			//	��D�̎��	�F	��
	itemFmaster[MAGIC_TYPE_WIND].charType = MAGIC_TYPE_WIND;			//	��D�̎��	�F	��
	itemFmaster[MAGIC_TYPE_HEAL].charType = MAGIC_TYPE_HEAL;	//	��D�̎��	�F	��
	//��D�܂Ƃ߂ď���
	for (int i = 0; i < MAGIC_TYPE_MAX; i++)
	{
		itemFmaster[i].pos = { 0,0 };																//�@��D�̒n�}��̍��W
		itemFmaster[i].size = { 20,20 };															//	��D�̉摜����
		itemFmaster[i].offsetSize = { itemFmaster[i].size.x / 2,itemFmaster[i].size.y / 2 };		//�@��D�̵̾��
		itemFmaster[i].point = 0;																	//	��D�̖���
		itemFmaster[i].lifeMax = 20;																//	��D�̗͍̑ő�l�i�\�����ԁj
		itemFmaster[i].life = itemFmaster[i].lifeMax;												//	��D�̗̑�
	}

	//��D�i�޽���ٗp
	itemFBFlag = false;												//	�����F��\��

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
	LoadDivGraph("item/fudaD.png", 4, 4, 1
		, ITEM_M_SIZE, ITEM_M_SIZE, itemFImage);
	//��D�i�����ؗp
	LoadDivGraph("item/fudaI.png", 4, 4, 1
		, ITEM_M_SIZE, ITEM_M_SIZE, itemFIImage);
	//��D�i�޽���ٗp
	LoadDivGraph("item/fuda_Big.png", 4, 4, 1
		, ITEM_B_SIZE, ITEM_B_SIZE, itemFBImage);
	//�O��̐_��
	LoadDivGraph("item/zingi20.png", 3, 3, 1
		, ITEM_M_SIZE, ITEM_M_SIZE, itemBImage);
	}

void ItemGameInit(void)
{
	//��D�i��ۯ�ߗp
	for (int i = 0; i < ITEM_MAX; i++)
	{
		itemF[i] = itemFmaster[GetRand(MAGIC_TYPE_MAX - 1)];
		//itemF[i].pos.x = GetRand(SCREEN_SIZE_X - 1);
		//itemF[i].pos.y = GetRand(SCREEN_SIZE_Y - 1);
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

void ItemControl(void)
{
}

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
			DrawGraph(itemF[i].pos.x - itemF[i].offsetSize.x
				, itemF[i].pos.y - itemF[i].offsetSize.y
				, itemFImage[itemF[i].charType]
				, true);

			DrawBox(itemF[i].pos.x - itemF[i].offsetSize.x
				, itemF[i].pos.y - itemF[i].offsetSize.y
				, itemF[i].pos.x - itemF[i].offsetSize.x + itemF[i].size.x
				, itemF[i].pos.y - itemF[i].offsetSize.y + itemF[i].size.y
				, 0xFF00FF, false);
		}
	}
	//�O��̐_��
	for (int i = 0; i < ITEM_TYPE_B_MAX; i++)
	{
		if (itemB[i].life > 0)
		{
			DrawGraph((itemB[i].pos.x - itemB[i].offsetSize.x) * i
				, itemB[i].pos.y - itemB[i].offsetSize.y
				, itemBImage[itemB[i].charType]
				, true);

			DrawBox((itemB[i].pos.x - itemB[i].offsetSize.x) * i
				, itemB[i].pos.y - itemB[i].offsetSize.y
				, (itemB[i].pos.x - itemB[i].offsetSize.x) * i + itemB[i].size.x
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
//
//void ItemB_Draw(void)
//{
//	//�U�����\���p
//	if (!itemFBFlag)
//	{
//		for (int type = 0; type < MAGIC_TYPE_MAX; type++)
//		{
//			DrawGraph((SCREEN_SIZE_X - ITEM_B_SIZE) / 2, (BOX_Y - ITEM_B_SIZE) / 2, itemFBImage[type], true);
//		}
//	}
//	//�������юc�ʕ\���p
//	//�΂̌�D
//	DrawGraph(350, BOX_Y + 120, itemFIImage[MAGIC_TYPE_FIRE], true);
//	DrawFormatString(352, BOX_Y + 150, 0xFF22FF, "�~", true);
//	DrawFormatString(380, BOX_Y + 150, 0xFF22FF, "%d", itemF[MAGIC_TYPE_FIRE].point);
//	//���̌�D
//	DrawGraph(450, BOX_Y + 120, itemFIImage[MAGIC_TYPE_WATER], true);
//	DrawFormatString(452, BOX_Y + 150, 0xFF22FF, "�~", true);
//	DrawFormatString(480, BOX_Y + 150, 0xFF22FF, "%d", itemF[MAGIC_TYPE_WATER].point);
//	//���̌�D
//	DrawGraph(550, BOX_Y + 120, itemFIImage[MAGIC_TYPE_WIND], true);
//	DrawFormatString(552, BOX_Y + 150, 0xFF22FF, "�~", true);
//	DrawFormatString(580, BOX_Y + 150, 0xFF22FF, "%d", itemF[MAGIC_TYPE_WIND].point);
//	//�񕜂̌�D
//	DrawGraph(650, BOX_Y + 120, itemFIImage[MAGIC_TYPE_HEAL], true);
//	DrawFormatString(652, BOX_Y + 150, 0xFF22FF, "�~", true);
//	DrawFormatString(680, BOX_Y + 150, 0xFF22FF, "%d", itemF[MAGIC_TYPE_HEAL].point);
//
//}
//
//

//
////-----�e�ƓG�̓����蔻��@(true : ������, false : �͂���)
//bool ItemHitCheck(XY sPos, int sSize)
//{
//	//�S�Ă̓G�ɓ����蔻������{����
//	for (int i = 0; i < ITEM_MAX; i++)
//	{
//		if (itemF[i].life > 0)
//		{
//			if (((itemF[i].pos.x - itemF[i].size.x / 2) < (sPos.x + sSize / 2))
//				&& ((itemF[i].pos.x + itemF[i].size.x / 2) > (sPos.x - sSize / 2))
//				&& ((itemF[i].pos.y - itemF[i].size.y / 2) < (sPos.y + sSize / 2))
//				&& ((itemF[i].pos.y + itemF[i].size.y / 2) > (sPos.y - sSize / 2)))
//			{
//				//�����������A��а�̗̑͂����炷
//				itemF[i].life = 0;
//				//��а��|�����������߲�ĉ��Z
//				//��D�ɐG�ꂽ����Z
//				if (itemF[i].charType == MAGIC_TYPE_FIRE)
//				{
//					itemF[MAGIC_TYPE_FIRE].point++;
//					//hiCnt++;
//				}
//				if (itemF[i].charType == MAGIC_TYPE_WATER)
//				{
//					itemF[MAGIC_TYPE_WATER].point++;
//					//mizuCnt++;
//				}
//				if (itemF[i].charType == MAGIC_TYPE_WIND)
//				{
//					itemF[MAGIC_TYPE_WIND].point++;
//					//kazeCnt++;
//				}
//				if (itemF[i].charType == MAGIC_TYPE_HEAL)
//				{
//					itemF[MAGIC_TYPE_HEAL].point++;
//					//kaifukuCnt++;
//				}
//				return true;
//			}
//		}
//	}
//	//�e���O�ꂽ��
//	return false;
//}
//
////-----�e�����ł�����
//void DeleteItem(int index)
//{
//	itemF[index].life = 0;
//
//};