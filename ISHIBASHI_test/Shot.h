//#pragma once

//-----�萔��`
#define SHOT_ANI		46				//�@�e�̱�Ұ��ݐ�
#define SHOT_LIFE_MAX	46
#define SHOT_MAX		20




//-----�֐��������ߐ錾
void ShotSystemInit(void);					//�@�e���̏�����	
void ShotGameInit(void);
void ShotControl(XY pPos);					//	�e�̑���
void ShotGameDraw(void);				//	�e�̕`�揈��
void CreateShot(XY pPos, DIR pDir, MAGIC_TYPE ptype);
void DeleteShot(int index);

//-----��۰��ى�
extern CHARACTER shot[];