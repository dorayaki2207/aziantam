//#pragma once

//-----�萔��`
#define ITEM_MAX    20
#define ITEM_M_SIZE 20			//	������ؗp��D����(M : ��
#define ITEM_B_SIZE 150			//	���ٗp��D����(B : �ޯ��



//-----�񋓌^
enum ITEM_TYPE_B
{
	ITEM_TYPE_KEN,				//	�O��̐_��E��
	ITEM_TYPE_KAGAMI,			//	�O��̐_��E��
	ITEM_TYPE_MAGATAMA,			//	�O��̐_��E����
	ITEM_TYPE_B_MAX
};


//-----�֐��������ߐ錾
void ItemSystmeInit(void);				//�@���я��̏�����	
void ItemGameInit(void);				//						
void ItemDropControl(void);				//	���т̑���
void ItemGameDraw(void);				//�@���ѕ`�揈��
void ItemI_Draw(void);					//	������ؗp�̱��щ摜�`��
bool ItemMobControl(MAGIC_TYPE type);	//	MOB�G��펞����
bool ItemHitCheck(XY sPos, int sSize);	//	��ۯ�߱��т̓����蔻��
void ItemDrop(XY ePos, MAGIC_TYPE type);//	��ۯ�ߏ���
void DeleteItem();						//	��ۯ�߱��т̍폜
bool GameOverSet();						//	�ްѵ��ް����
//-----��۰��ى�
extern CHARACTER itemF[ITEM_MAX];


