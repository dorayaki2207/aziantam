//#pragma once
//-------------------------
// effect.h
// 2019.09.26
// �R�{���R�I
//-------------------------

//-----�萔��`
#define EFFECT_MAX		 20
#define EFFECT_LIFE_MAX  10
#define EFFECT_ANI		  9

//�v���g�^�C�v�錾
//---------------
void EffectSystemInit(void);
void EffectInit(void);					//�G�t�F�N�g�̏�����
bool FadeInScreen(int fadeStep);		//̪��޲݂̏���
bool FadeOutScreen(int fadeStep);		//̪��ޱ�Ă̏���
//��Ұ�޴̪��
void EffectControl(void);
void EffectGameDraw(void);
//void CreateEffect(XY pPpos, DIR pDir, MAGIC_TYPE ptype);
void DeleteEffect(int index);


//extern�錾
//---------------
//��ʐ؂�ւ��G�t�F�N�g
extern int fadeCnt;
extern bool fadeIn;
extern bool fadeOut;
