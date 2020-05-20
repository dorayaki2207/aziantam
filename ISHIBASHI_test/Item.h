//#pragma once


//-----�萔��`
#define ITEM_MAX 50

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
bool ItemHitCheck(XY sPos, int sSize);
void DeleteItem(int index);

//-----��۰��ى�
extern CHARACTER itemF[];
