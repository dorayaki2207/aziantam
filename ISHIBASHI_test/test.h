//#pragma once



#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 650


//-----�񋓌^
//���
enum SCENE_ID
{
	SCENE_ID_INIT,					//	��ݏ�����
	SCENE_ID_TITLE,					//	����
	SCENE_ID_GAME,					//	�ް�
	SCENE_ID_BATTLE,				//	�޽���
	SCENE_ID_MAX
};
//����
enum DIR
{
	DIR_UP,							//	��
	DIR_RIGHT,						//	��
	DIR_DOWN,						//	��
	DIR_LEFT,						// ��
	DIR_MAX
};

enum MAGIC_TYPE
{
	MAGIC_TYPE_FIRE,		//�����F��
	MAGIC_TYPE_WATER,		//�����F��
	MAGIC_TYPE_WIND,		//�����F��
	MAGIC_TYPE_HEAL,		//�����F��
	MAGIC_TYPE_MAX
};

//-----�\����
//���W
struct XY
{
	int x;							//	X���W
	int y;							//	Y���W
};
//��׸��p
struct CHARACTER
{
	int charType;					//	��׸��̎��
	DIR moveDir;					//	��׸��̌���
	XY pos;							//�@��׸��̒n�}��̍��W
	XY size;						//	��׸��̉摜����
	XY offsetSize;					//�@��׸��̵̾��
	int moveSpeed;					//	��׸��̈ړ���߰��
	int lifeMax;					//	��׸��̗͍̑ő�l
	int life;						//	��׸��̗̑�
	int animCnt;					//	��׸��̱�Ұ���
	int point;						//	��׸��̽��
	bool hitFlag;					//	��׸����U�����󂯂����ǂ���
};



//-----�������ߐ錾
bool SystemInit(void);
void InitScene(void);
void GameScene(void);
void GameDraw(void);

void TitleScene(void);

//-----��۰��ى�


extern SCENE_ID sceneID;
//ýėp
extern int SceneCounter;