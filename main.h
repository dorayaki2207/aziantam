//#pragma once
//-------------------------
// AsoulQuest = main.h
// 2019.09.26
// �R�{���R�I
//-------------------------

//�萔�̒�`
//--------------
//��ʃT�C�Y
#define SCREEN_SIZE_X 800	//��ʻ��މ�
#define SCREEN_SIZE_Y 600	//��ʻ��ޏc
#define TITLE_SIZE_X  600	//���ق̉�����
#define TITLE_SIZE_Y  250	//���ق̏c����
#define GAMEOVER_SIZE_X 457	//�ްѵ��ް�̉�����
#define GAMEOVER_SIZE_Y 81	//�ްѵ��ް�̏c����
#define HITSTARTKEY_SIZE_X 337	//hitstartkey�̉�����
#define HITSTARTKEY_SIZE_Y 53	//hitstartkey�̏c����

//�񋓌^�̒�`
//-----------------
//��݊Ǘ��p
enum SCENE_ID
{
	SCENE_ID_INIT,			//������
	SCENE_ID_TITLE,			//�^�C�g��
	SCENE_ID_GAME,			//�Q�[��
	SCENE_ID_GAMEOVER,		//�Q�[���I�[�o�[
	SCENE_ID_MAX
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
enum CHARACTER_TYPE
{
	CHARACTER_PLAYER,
	CHARACTER_ENEMY,
	CHARACTER_SHOT,
	CHARACTER_MAX,
};

//�\����
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



//�v���g�^�C�v�錾
//---------------
//����
bool SystemInit(void);					//���т̏�����
void InitScene(void);					//���������
//�^�C�g��
void TitleScene(void);					//���ټ��
void TitleDraw(void);					//���ټ�݂̕`��p���
//�Q�[��
void GameScene(void);					//�ްѼ��
void GameDraw(void);					//�ްѼ�݂̕`��p���
//�ްѵ��ް
void GameOverScene(void);				//�ްѵ��ް
void GameOverDraw(void);				//�ްѵ��ް�̕`��p���
void AddScore(int point);				//���_��ǉ�
bool SaveData(void);					//̧�ق���X�R�A��ۑ�����
bool LoadData(void);					//̧�ق���X�R�A��ǂݍ���
void AddCharOrder(CHARACTER_TYPE characterType, int index, int y);		//��׸�����drawOrderList�ɒǉ�����