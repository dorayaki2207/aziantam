//#pragma once

//�萔
#define PLAYER_DEF_SPEED  4		//��ڲ԰�̏����ړ���
#define PLAYER_MAX_LIFE  100	//��ڲ԰�̍ő�̗�

#define SCROLL_X_MIN	100		//��۰ى\�����WX
#define SCROLL_X_MAX	700		//��۰ى\�����WY
#define SCROLL_Y_MIN	100		//��۰ى\��K���WX
#define SCROLL_Y_MAX	500		//��۰ى\��K���WY


//�v���g�^�C�v�錾
void PlayerSystemInit(void);	//��ڲ԰���̏�����
void PlayerGameInit(void);		//��ڲ԰�̏�����
XY PlayerControl(void);			//��ڲ԰�̑���
void PlayerGameDraw(void);		//��ڲ԰�̕`��
