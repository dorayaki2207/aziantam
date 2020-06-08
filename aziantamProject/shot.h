//#pragma once

//-----�萔��`
#define SHOT_ANI		46		//�e�̱�Ұ��ݐ�
#define SHOT_LIFE_MAX	46		//�e�̗̑�
#define SHOT_MAX		20		//�e�̑���

#define DAMAGE_NORMAL	2		//��������Ұ�ޗ�
#define DAMAGE_HIGH		3		//�L��������Ұ�ޗ�
#define DAMAGE_LOW		1		//�s��������Ұ�ޗ�

//-----�֐��������ߐ錾
void ShotSystemInit(void);									//�e���̏�����
void ShotGameInit(void);
void ShotControl(XY pPos);									//�e�̑���
void ShotGameDraw(void);										//�e�̕`�揈��
void CreateShot(XY pPos, DIR pDir, MAGIC_TYPE ptype);		//�e�𐶐�����
void DeleteShot(int index);									//�e�����ł�����

//-----��۰��ى�
extern CHARACTER shot[SHOT_MAX];