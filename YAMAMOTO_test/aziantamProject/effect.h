//#pragma once
//-------------------------
// effect.h
// 2019.09.26
// �R�{���R�I
//-------------------------

//extern�錾
//---------------
//��ʐ؂�ւ��G�t�F�N�g
extern int fadeCnt;
extern bool fadeIn;
extern bool fadeOut;
//�ꎞ��~�G�t�F�N�g
extern int pauseFlag;

//�v���g�^�C�v�錾
//---------------
void EffectInit(void);					//�G�t�F�N�g�̏�����
bool FadeInScreen(int fadeStep);		//̪��޲݂̏���
bool FadeOutScreen(int fadeStep);		//̪��ޱ�Ă̏���