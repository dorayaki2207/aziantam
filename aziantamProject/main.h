//#pragma once

//---��`
#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 650


//-----�񋓌^�̒�`
//��݊Ǘ��p
enum SCENE				
{
	SCENE_INIT,			//���������
	SCENE_TITLE,		//���ټ��
	SCENE_GAME,			//�ްѼ��
	SCENE_GAMEOVER,		//�ްѵ��ް���
	SCENE_MAX
};

//�����Ǘ��p
enum DIR
{
	DIR_UP,			//��
	DIR_RIGHT,		//�E
	DIR_DOWN,		//��
	DIR_LEFT,		//��
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
//----------------
//���_�Ǘ��p
struct FILE_DATA
{
	int Score;				//���ݓ��_
	int hiScore;			//�ō����_
};

//�߼޼ޮ�
struct XY
{
	int x;
	int y;
};

//��׸�
struct CHARACTER
{
	int charType;	//��׸��̎��
	DIR moveDir;	//��׸��̌���
	XY pos;			//��׸��̒n�}��̍��W
	XY size;		//��׸��摜�̻���
	XY offsetSize;	//��׸��̵̾��
	int moveSpeed;	//��׸��̈ړ���߰��
	int lifeMax;	//��׸��̗͍̑ő�l
	int life;		//��׸��̗̑�
	int animCnt;	//��׸��̱�Ұ���
	int point;		//��׸��̓��_

};

struct KEY_LIST
{
	int up;
	int right;
	int down;
	int left;
	int shot;
};


//-----�������ߐ錾
//������
bool SystemInit(void);
void InitScene(void);
//����
void TitleScene(void);
void TitleDraw(void);
//�ް�
void GameScene(void);
void GameDraw(void);
//�ްѵ��ް
void GameOverScene(void);
void GameOverDraw(void);
