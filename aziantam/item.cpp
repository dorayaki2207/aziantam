////	��ۯ�߱��т͓G���|���ꂽ�炻�̏�ɏo��
////	����HP���g���ēG��|���Ĉ�莞�ԓ��Ɏ��Ȃ��Ə�����悤�ɂ��� 
////	�G�̓����蔻��Ɂ@�ς��Ɖ΂̌�D�A�ꔽ�ؖȂ��ƕ��̌�D�A�C�V�傾�Ɛ��̌�D
////	�񕜂̌�D�͑S���̓GMOB����m���ŏo������悤�ɂ���
////	�G���|���ꂽ��@����HP�����炵�Ă���
#include <DxLib.h>
#include "main.h"
#include "stage.h"
#include "item.h"


//-----�O���ϐ��錾
//���ъ֘A
//��D
CHARACTER itemF[ITEM_MAX];					//	��ۯ�߱��ѕϐ��i�[�p
CHARACTER itemFmaster[MAGIC_TYPE_MAX];
int itemFImage[MAGIC_TYPE_MAX];				//	��ۯ�߱��їp�摜�iF�F�D�̓�����
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
		itemFmaster[i].point = 12;																	//	��D�̖���
		itemFmaster[i].lifeMax = 200;																//	��D�̗͍̑ő�l�i�\�����ԁj
		itemFmaster[i].life = itemFmaster[i].lifeMax;												//	��D�̗̑�
		itemFmaster[i].hitFlag = false;
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
	for (int type = 0; type < MAGIC_TYPE_MAX;type++)
	{ 
		for (int i = 0; i < ITEM_MAX; i++)
		{

			itemF[i] = itemFmaster[type];
			itemF[i].life = 0;
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

void ItemDropControl(void)
{
	for (int i = 0; i < ITEM_MAX; i++)
	{
		//�����Ă�e��T��
		if (itemF[i].life > 0)
		{
			//���������炷(�˒�����)
			itemF[i].life--;
		}
	}
}

bool ItemMobControl(MAGIC_TYPE type)
{
	//��D���ꖇ�ȏ゠��ꍇ�A�����\
	if (itemF[type].point > 0)
	{
		itemF[type].point--;
		return true;
	}
	return false;
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
			DrawGraph(itemF[i].pos.x - itemF[i].offsetSize.x + mapPos.x
				, itemF[i].pos.y - itemF[i].offsetSize.y + mapPos.y
				, itemFImage[itemF[i].charType]
				, true);
		}
	}
	//�O��̐_��
	//for (int i = 0; i < ITEM_TYPE_B_MAX; i++)
	//{
	//	if (itemB[i].life > 0)
	//	{
	//		DrawGraph((itemB[i].pos.x - itemB[i].offsetSize.x) * i
	//			, itemB[i].pos.y - itemB[i].offsetSize.y
	//			, itemBImage[itemB[i].charType]
	//			, true);

	//		DrawBox((itemB[i].pos.x - itemB[i].offsetSize.x) * i
	//			, itemB[i].pos.y - itemB[i].offsetSize.y
	//			, (itemB[i].pos.x - itemB[i].offsetSize.x) * i + itemB[i].size.x
	//			, itemB[i].pos.y - itemB[i].offsetSize.y + itemB[i].size.y
	//			, 0xFF00FF, false);

	//	}
	//}
}
//-----������ؗp�`��
void ItemI_Draw(void)
{
	//�΂̌�D
	DrawGraph(430, 250, itemFIImage[MAGIC_TYPE_FIRE], true);
	DrawFormatString(480, 254, 0xFF22FF, "�~", true);
	DrawFormatString(530, 253, 0xFF22FF, "%d", itemF[MAGIC_TYPE_FIRE].point);
	DrawFormatString(560, 254, 0xFF22FF, "��", true);
	//���̌�D
	DrawGraph(430, 300, itemFIImage[MAGIC_TYPE_WATER], true);
	DrawFormatString(480, 304, 0xFF22FF, "�~", true);
	DrawFormatString(530, 303, 0xFF22FF, "%d", itemF[MAGIC_TYPE_WATER].point);
	DrawFormatString(560, 304, 0xFF22FF, "��", true);
	//���̌�D
	DrawGraph(430, 350, itemFIImage[MAGIC_TYPE_WIND], true);
	DrawFormatString(480, 354, 0xFF22FF, "�~", true);
	DrawFormatString(530, 353, 0xFF22FF, "%d", itemF[MAGIC_TYPE_WIND].point);
	DrawFormatString(560, 354, 0xFF22FF, "��", true);
	//�񕜂̌�D
	DrawGraph(430, 420, itemFIImage[MAGIC_TYPE_HEAL], true);
	DrawFormatString(480, 424, 0xFF22FF, "�~", true);
	DrawFormatString(530, 423, 0xFF22FF, "%d", itemF[MAGIC_TYPE_HEAL].point);
	DrawFormatString(560, 424, 0xFF22FF, "��", true);
}

//-----�e�ƓG�̓����蔻��@(true : ������, false : �͂���)
bool ItemHitCheck(XY sPos, int sSize)
{
	int point = GetRand(2) + 1;
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
				//���т��E�����������߲�ĉ��Z
				//��D�ɐG�ꂽ����Z
				if (itemF[i].charType == MAGIC_TYPE_FIRE)
				{
					itemF[i].point += point;
					itemF[i].hitFlag = true;
				}
				if (itemF[i].charType == MAGIC_TYPE_WATER)
				{
					itemF[i].point += point;
					itemF[i].hitFlag = true;
				}
				if (itemF[i].charType == MAGIC_TYPE_WIND)
				{
					itemF[i].point += point;
					itemF[i].hitFlag = true;
				}
				if (itemF[i].charType == MAGIC_TYPE_HEAL)
				{
					itemF[i].point += point;
					itemF[i].hitFlag = true;
				}
				return true;
			}
		}
	}
	//�e���O�ꂽ��
	return false;
}


//-----�h���b�v�A�C�e������
void ItemDrop(XY ePos, MAGIC_TYPE type)
{
	//�h���b�v���Ă��Ȃ����̂��Ȃ����`�F�b�N
	//���Ă��Ȃ����̂�����͐�������
	for (int item = 0; item < ITEM_MAX; item++)
	{
		//�h���b�v���Ă��Ȃ����̂�T��
		if (itemF[item].life <= 0)
		{
			//�A�C�e���𗎂Ƃ�
			itemF[item].charType = type;
			itemF[item].pos = { ePos.x,ePos.y };
			itemF[item].life = itemF[item].lifeMax;
			break;
		}
	}
}


//-----�h���b�v�A�C�e������
void DeleteItem()
{
	for (int item = 0; item < ITEM_MAX; item++)
	{
		if (itemF[item].life > 0 && itemF[item].hitFlag)
		{
			itemF[item].life = 0;
			itemF[item].hitFlag = false;
			break;
		}
	}
}
bool GameOverSet()
{
	if ((itemF[MAGIC_TYPE_FIRE].point == 0) 
		&& (itemF[MAGIC_TYPE_WATER].point == 0) 
		&& (itemF[MAGIC_TYPE_WIND].point == 0))
	{
		return true;
	}
	return false;
}
