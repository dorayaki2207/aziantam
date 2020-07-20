//#pragma once


//-----�萔��`
#define ITEM_MAX    20
#define ITEM_M_SIZE 20					//	������ؗp��D����
#define ITEM_B_SIZE 150				//	���ٗp��D����


//-----�񋓌^
enum ITEM_TYPE_B
{
	ITEM_TYPE_KEN,							//	�O��̐_��E��
	ITEM_TYPE_KAGAMI,					//	�O��̐_��E��
	ITEM_TYPE_MAGATAMA,			//	�O��̐_��E����
	ITEM_TYPE_B_MAX
};


//-----�֐��������ߐ錾
void ItemSystemInit(void);					//�@���я��̏�����	
void ItemGameInit(void);					//	
void itemDropControl();
void ItemBossControl(CHARACTER* boss);		//	�޽�U���p���т̑���
bool ItemMOBControl(MAGIC_TYPE type);		//	MOB�G�U���p���т̑���
void ItemGameDraw(void);					//�@���ѕ`�揈��
void ItemGameDraw(int index);
void ItemI_Draw(void);						//	������ؗp�̱��щ摜�`��
void ItemB_Draw(void);						//	�޽���ٗp�̱��щ摜�`��
bool ItemHitCheck(XY sPos, int sSize);		//	��ۯ�߱��т̓����蔻��
void ItemDrop(XY ePos, MAGIC_TYPE type);
void DeleteItem();					//	��ۯ�߱��т̍폜


//-----��۰��ى�
extern CHARACTER itemF[];
