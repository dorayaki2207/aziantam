//#pragma once

//---��`
#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 650
//#define SCREEN_SIZE_X 600
//#define SCREEN_SIZE_Y 800
//#define SCREEN_SIZE_X 700
//#define SCREEN_SIZE_Y 900
//#define SCREEN_SIZE_X 800
//#define SCREEN_SIZE_Y 1000


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

//�G
enum ENEMY	
{
	ENEMY_ONI,		//�S
	ENEMY_TENG,		//�V��
	ENEMY_KAPPA,	//�͓�
	ENEMY_NUE,		//�K
	ENEMY_I_MOB,	//�΋��S��
	ENEMY_Y_MOB,	//�R�{�S��
	ENEMY_A_MOB,	//�r�ؒS��
	ENEMY_MAX
};
//����
enum ITEM
{					//-----�p���Ȃ������f��-----
	ITEM_HI,		//�΂̌�D�F�h���b�v
	ITEM_MIZU,		//���̌�D�F�h���b�v
	ITEM_KAZE,		//���̌�D�F�h���b�v
	ITEM_KAIFUKU,	//�񕜂̌�D�F�h���b�v
					//-----��̫�đf��-----
	ITEM_M_HI,		//�΂̌�D�F�C�x���g��
	ITEM_M_MIZU,	//���̌�D�F�C�x���g��
	ITEM_M_KAZE,	//���̌�D�F�C�x���g��
	ITEM_M_KAIFUKU,	//�񕜂̌�D�F�C�x���g��
					//-----�傫�����ނ̑f��-----
	ITEM_B_HI,		//�΂̌�D�F�{�X��p
	ITEM_B_MIZU,	//���̌�D�F�{�X��p
	ITEM_B_KAZE,	//���̌�D�F�{�X��p
	ITEM_B_KAIFUKU,	//�񕜂̌�D�F�{�X��p
					//-----�K�{���ёf��-----
	ITEM_KEN,		//�O��̐_��F��
	ITEM_KAGAMI,	//�O��̐_��F��
	ITEM_MAGATAMA,	//�O��̐_��F����
	ITEM_MAX
};




//��׸��̎�ފǗ��p
//enum CHARACTER_TYPE
//{
//	CHARACTER_PLAYER,
//	CHARACTER_ENEMY,
//	CHARACTER_SHOT,
//	CHARACTER_MAX,
//};

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
