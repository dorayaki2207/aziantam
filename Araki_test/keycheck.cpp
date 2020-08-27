// keyheck.cpp
// 2019.09.20
// �R�{���R�I

#include "DxLib.h"
#include "keycheck.h"

//�ϐ�
//���������
//���͏��֘A
bool KeyOld[KEY_ID_MAX];			//1�t���[���O�̓��͏��
bool KeyNew[KEY_ID_MAX];			//���݂̓��͏��
bool KeyDownTrigger[KEY_ID_MAX];	//�_�E�����̃g���K�[
bool KeyUpTrigger[KEY_ID_MAX];		//�A�b�v���̃g���K�[


//���͏��̏�����
void KeyInit(void)
{
	for (int k = 0; k < KEY_ID_MAX; k++)
	{
		KeyOld[k] = false;
		KeyNew[k] = false;
		KeyDownTrigger[k] = false;
		KeyUpTrigger[k] = false;
	}
}
//���͏��̊m�F
void KeyCheck(void)
{
	//int mouseButton;					//�}�E�X�̃{�^�����

	//Old�̏���
	for (int KeyID = 0; KeyID < KEY_ID_MAX; KeyID++)
	{
		KeyOld[KeyID] = KeyNew[KeyID];
	}

	//Mouse�̏����擾����
	//GetMousePoint(&mousePos.x, &mousePos.y);
	//mouseButton = GetMouseInput();

	//���݂̏�Ԃ��擾����
	KeyNew[KEY_ID_SPACE] = CheckHitKey(KEY_INPUT_SPACE);
	KeyNew[KEY_ID_PAUSE] = CheckHitKey(KEY_INPUT_P);
	KeyNew[KEY_ID_IVENT] = CheckHitKey(KEY_INPUT_I);
	KeyNew[KEY_ID_SHOT] = CheckHitKey(KEY_INPUT_LCONTROL);
	KeyNew[KEY_ID_SAVE] = CheckHitKey(KEY_INPUT_S);
	KeyNew[KEY_ID_LOAD] = CheckHitKey(KEY_INPUT_L);
	KeyNew[KEY_ID_UP] = CheckHitKey(KEY_INPUT_UP);
	KeyNew[KEY_ID_RIGHT] = CheckHitKey(KEY_INPUT_RIGHT);
	KeyNew[KEY_ID_DOWN] = CheckHitKey(KEY_INPUT_DOWN);
	KeyNew[KEY_ID_LEFT] = CheckHitKey(KEY_INPUT_LEFT); 
	KeyNew[KEY_ID_FIRE] = CheckHitKey(KEY_INPUT_Z);
	KeyNew[KEY_ID_WATER] = CheckHitKey(KEY_INPUT_X);
	KeyNew[KEY_ID_WIND] = CheckHitKey(KEY_INPUT_C);
	KeyNew[KEY_ID_HEAL] = CheckHitKey(KEY_INPUT_V);
	KeyNew[KEY_ID_ENTER] = CheckHitKey(KEY_INPUT_RETURN);


	for (int keyID = 0; keyID < KEY_ID_MAX; keyID++)
	{
		KeyDownTrigger[keyID] = false;
		KeyUpTrigger[keyID] = false;
		//�_�E�����̃g���K�[�̎Z�o
		if (!KeyOld[keyID] && KeyNew[keyID])
		{
			KeyDownTrigger[keyID] = true;
		}
		//�A�b�v���̃g���K�[�̎Z�o
		if (KeyOld[keyID] && !KeyNew[keyID])
		{
			KeyUpTrigger[keyID] = true;
		}
	}


}