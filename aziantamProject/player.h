//#pragma once

//�萔
#define PLAYER_DEF_SPEED  5		//�v���C���[�̏����ړ���
#define PLAYER_MAX_LIFE  100	//�v���C���[�̍ő�̗�


//�v���g�^�C�v�錾
void PlayerSystemInit(void);				//��ڲ԰���̏�����
void PlayerGameInit(void);					//�v���C���[�̏�����
void PlayerControl(void);					//�v���C���[�̑���
void PlayerGameDraw(void);						//�v���C���[�̕`��
