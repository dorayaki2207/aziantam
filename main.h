//#pragma once

//---��`
#define SCREEN_SIZE_X 500
#define SCREEN_SIZE_Y 700
#define SCREEN_SIZE_X 600
#define SCREEN_SIZE_Y 800
#define SCREEN_SIZE_X 700
#define SCREEN_SIZE_Y 900
#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 1000


//�񋓌^�̒�`
enum SCENE				//��݊Ǘ��p
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
//��׸��̎�ފǗ��p
//enum CHARACTER_TYPE
//{
//	CHARACTER_PLAYER,
//	CHARACTER_ENEMY,
//	CHARACTER_SHOT,
//	CHARACTER_MAX,
//};

//---�\����
//----------------
//���_�Ǘ��p
struct FILE_DATA
{
	int Score;				//���ݓ��_
	int hiScore;			//�ō����_
};
//�|�W�V����
struct XY
{
	int x;
	int y;
};
//��׸�
struct CHARACTER
{
	int CharType;	//��׸��̎��
	DIR MoveDir;	//��׸��̌���
	XY Pos;			//��׸��̒n�}��̍��W
	XY Size;		//��׸��摜�̻���
	XY OffsetSize;	//��׸��̵̾��
	int MoveSpeed;	//��׸��̈ړ���߰��
	int LifeMax;	//��׸��̗͍̑ő�l
	int Life;		//��׸��̗̑�
	int AnimCnt;	//��׸��̱�Ұ���

	int point;		//��׸��̓��_
};

//---�v���g�^�C�v�錾
bool SystemInit(void);
void InitScene(void);
void TitleScene(void);
void TitleDraw(void);
void GameScene(void);
void GameDraw(void);
void GameOverScene(void);
void GameOverDraw(void);
