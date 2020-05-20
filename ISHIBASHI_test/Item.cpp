#include "DxLib.h"
#include "test.h"
#include "Item.h"

//-----�O���ϐ��錾
//���ъ֘A
//��D
CHARACTER itemF[ITEM_MAX];					//	��ۯ�߱��ѕϐ��i�[�p
CHARACTER itemFmaster[ITEM_TYPE_F_MAX];
int itemFImage[ITEM_TYPE_F_MAX];					//	��ۯ�߱��щ摜�F�ʏ펞
//�O��̐_��
CHARACTER itemB[ITEM_TYPE_B_MAX];
int itemBImage[ITEM_TYPE_B_MAX];



//-----���я��̏�����
void ItemSystmeInit(void)
{
	//-----�ϐ��̏�����
	//��D
	itemFmaster[ITEM_TYPE_HI].charType = ITEM_TYPE_HI;				//	��D�̎��	�F	��
	itemFmaster[ITEM_TYPE_MIZU].charType = ITEM_TYPE_MIZU;			//	��D�̎��	�F	��
	itemFmaster[ITEM_TYPE_KAZE].charType = ITEM_TYPE_KAZE;			//	��D�̎��	�F	��
	itemFmaster[ITEM_TYPE_KAIFUKU].charType = ITEM_TYPE_KAIFUKU;	//	��D�̎��	�F	��
	//��D�܂Ƃ߂ď���
	for (int i = 0; i < ITEM_TYPE_F_MAX; i++)
	{
		itemFmaster[i].pos = { 50,50 };																//�@��D�̒n�}��̍��W
		itemFmaster[i].size = { 20,20 };															//	��D�̉摜����
		itemFmaster[i].offsetSize = { itemFmaster[i].size.x / 2,itemFmaster[i].size.y / 2 };		//�@��D�̵̾��
		itemFmaster[i].point = 0;																	//	��D�̖���
		itemFmaster[i].lifeMax = 20;																//	��D�̗͍̑ő�l�i�\�����ԁj
		itemFmaster[i].life = itemFmaster[i].lifeMax;												//	��D�̗̑�

	}

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
	//��D
	itemFImage[ITEM_TYPE_HI] = LoadGraph("��D��/R.png");			//	�΂̌�D
	itemFImage[ITEM_TYPE_MIZU] = LoadGraph("��D��/B.png");			//	���̌�D
	itemFImage[ITEM_TYPE_KAZE] = LoadGraph("��D��/G.png");			//	���̌�D
	itemFImage[ITEM_TYPE_KAIFUKU] = LoadGraph("��D��/P.png");		//	�񕜂̌�D
	//�O��̐_��
	itemBImage[ITEM_TYPE_KEN] = LoadGraph("aitem/��20.png");		//	�O��̐_��@�F�@��
	itemBImage[ITEM_TYPE_KAGAMI] = LoadGraph("aitem/��20.png");		//	�O��̐_��@�F�@��
	itemBImage[ITEM_TYPE_MAGATAMA] = LoadGraph("aitem/����20.png");	//	�O��̐_��@�F�@����
}

void ItemGameInit(void)
{
	//��D
	for (int i = 0; i < ITEM_MAX; i++)
	{
		itemF[i] = itemFmaster[GetRand(ITEM_TYPE_F_MAX - 1)];
		itemF[i].pos.x = GetRand(SCREEN_SIZE_X - 1);
		itemF[i].pos.y = GetRand(SCREEN_SIZE_Y - 1);
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

	for (int j = 0; j < SCR_MAX; j++)
	{
		if (totalScrNew > totalScr[j])
		{
			if (j < SCR_MAX - 1)
			{
				for (int f = SCR_MAX - 2; f >= j; f--)
				{
					totalScr[j + 1] = totalScr[j];
				}
			}
			totalScr[j] = totalScrNew;
			break;
		}
	}
	FILE* fp = NULL;
	//	̧���߲���A̧�ٖ��A̧�ٵ���݌`��
	// ̧�ق��J�����Ƃ��̏���
	if (fopen_s(&fp, "scr.dat", "w+") == 0)
	{
		// �z��̐擪��n���A
		fwrite(
			totalScr,
			sizeof(totalScr[0]),
			SCR_MAX,
			fp
		);
		fclose(fp);
	}

}

void ItemControl(void)
{
}

void ItemGameDraw(void)
{
	//-----�`�揈��
	//��D
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