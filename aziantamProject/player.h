//#pragma once

//�萔
#define PLAYER_DEF_SPEED  4		//��ڲ԰�̏����ړ���
#define PLAYER_MAX_LIFE  250	//��ڲ԰�̍ő�̗�

#define SCROLL_X_MIN	200		//��۰ى\�����WX
#define SCROLL_X_MAX	500		//��۰ى\�����WY
#define SCROLL_Y_MIN	200		//��۰ى\��K���WX
#define SCROLL_Y_MAX	500		//��۰ى\��K���WY

enum PLAYER_SPEED
{
	PLAYER_SPEED_LOW = 1,		//�x��
	PLAYER_SPEED_L = 2,
	PLAYER_SPEED_NORMAL = 3,	//�ʏ�
	PLAYER_SPEED_HIGH = 7,		//����
	PLAYER_SPEED_STOP = 0,		//�~�܂�
	PLAYER_SPEED_MAX
};


//�v���g�^�C�v�錾
void PlayerSystemInit(void);	//��ڲ԰���̏�����
void PlayerGameInit(void);		//��ڲ԰�̏�����
XY PlayerControl(void);			//��ڲ԰�̑���
void PlayerGameDraw(void);		//��ڲ԰�̕`��
void PlayerTextDraw();
void PlayerEvent(void);			//����ď���
void MapChange(void);			//ϯ�߈ړ�
bool PlayerDid(void);			//���S�m�F

void SetInitMoment(STAGE_ID stageID);//�X�e�[�W�ړ�����p�̏������֐�
bool PlayerPosInit(void);		//player�̍��W��p�̏������֐�