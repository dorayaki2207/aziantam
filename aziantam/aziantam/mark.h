#pragma once





#define ZINGI_OLD  0
#define ZINGI_NEW  1


//�񋓌^
enum ITEM_TYPE_B
{
	ITEM_TYPE_KEN,				//	�O��̐_��E��
	ITEM_TYPE_KAGAMI,			//	�O��̐_��E��
	ITEM_TYPE_MAGATAMA,			//	�O��̐_��E����
	ITEM_TYPE_B_MAX
};


//�\����
struct MARK
{
	XY pos;
	XY size;
	int aniCnt;
	int flag;
	int type;
};


//�v���g�^�C�v�錾
bool MarkSystemInit(void);
void MarkReGameInit(void);
bool MarkGameInit(void);
void MarkGameDraw(void);

void MarkControl();
bool MarkHitCheck(STAGE_ID Id, XY pPos, XY size);

extern MARK mark[];