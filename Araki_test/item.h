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
void ItemSystmeInit(void);		//�@���я��̏�����	
void ItemGameInit(void);		//						
void ItemControl(void);			//	���т̑���
bool ItemMOBControl(MAGIC_TYPE type);		//	MOB�G�U���p���т̑���
void ItemGameDraw(void);		//�@���ѕ`�揈��
void ItemI_Draw(void);			//	������ؗp�̱��щ摜�`��
bool ItemMobControl(MAGIC_TYPE type);	//	MOB�G��펞����
void ItemDrop(XY ePos, MAGIC_TYPE type);
bool GameOverSet();						//	�ްѵ��ް����
//void ItemB_Draw(void);		//	�޽���ٗp�̱��щ摜�`��
bool ItemHitCheck(XY sPos, int sSize);
void DeleteItem();


//-----��۰��ى�
extern CHARACTER itemF[ITEM_MAX];


