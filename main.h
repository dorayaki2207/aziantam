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

//---�\����

//---�v���g�^�C�v�錾
bool SystemInit(void);
void InitScene(void);
void TitleScene(void);
void TitleDraw(void);
void GameScene(void);
void GameDraw(void);
void GameOverScene(void);
void GameOverDraw(void);
