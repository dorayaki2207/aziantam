//#pragma once

//-----�萔��`
#define ITEM_MAX    20
#define ITEM_M_SIZE 20			//	������ؗp��D����(M : ��
#define ITEM_B_SIZE 150			//	���ٗp��D����(B : �ޯ��



//-----�񋓌^
enum ITEM_TYPE_F
{
	ITEM_TYPE_HI,				//	�΂̌�D
	ITEM_TYPE_MIZU,				//	���̌�D
	ITEM_TYPE_KAZE,				//	���̌�D
	ITEM_TYPE_KAIFUKU,			//	�񕜂̌�D
	ITEM_TYPE_F_MAX
};
enum ITEM_TYPE_B
{
	ITEM_TYPE_KEN,				//	�O��̐_��E��
	ITEM_TYPE_KAGAMI,			//	�O��̐_��E��
	ITEM_TYPE_MAGATAMA,			//	�O��̐_��E����
	ITEM_TYPE_B_MAX
};


//-----�֐��������ߐ錾
void ItemSystmeInit(void);		//�@���я��̏�����	
void ItemGameInit(void);		//						
void ItemControl(void);			//	���т̑���
void ItemGameDraw(void);		//�@���ѕ`�揈��
void ItemI_Draw(void);			//	������ؗp�̱��щ摜�`��
//void ItemB_Draw(void);		//	�޽���ٗp�̱��щ摜�`��
//bool ItemHitCheck(XY sPos, int sSize);
//void DeleteItem(int index);

//-----��۰��ى�
extern CHARACTER itemF[];


