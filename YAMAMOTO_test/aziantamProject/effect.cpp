//-------------------------
// effect.cpp
// 2019.09.26
// �R�{���R�I
//-------------------------
#include <DxLib.h>
#include "effect.h"

//�ϐ�
//---------------------
//��ʐ؂�ւ��G�t�F�N�g
int fadeCnt;
bool fadeIn;
bool fadeOut;
//�ꎞ��~�G�t�F�N�g
int pauseFlag;

//�G�t�F�N�g�̏�����
void EffectInit(void)
{
	fadeIn = false;
	fadeOut = false;
	fadeCnt = 0;
	pauseFlag = false;
}
//�t�F�[�h�C������
bool FadeInScreen(int fadeStep)
{
	fadeCnt += fadeStep;
	if (fadeCnt <= 255)
	{
		SetDrawBright(fadeCnt, fadeCnt, fadeCnt);
		return true;
	}
	else
	{
		SetDrawBright(255, 255, 255);
		fadeCnt = 0;
		fadeIn = false;
		return false;
	}
}
//�t�F�[�h�A�E�g����
bool FadeOutScreen(int fadeStep)
{
	fadeCnt += fadeStep;
	if (fadeCnt <= 255)
	{
		SetDrawBright(255 - fadeCnt, 255 - fadeCnt, 255 - fadeCnt);
		return true;
	}
	else
	{
		SetDrawBright(0, 0, 0);
		fadeCnt = 0;
		fadeOut = false;
		return false;
	}
}