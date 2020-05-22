#include "DxLib.h"
#include "KeyCheck.h"


//���֘A
bool keyOld[KEY_ID_MAX];										//	1�ڰёO�̓��͏��
bool keyNew[KEY_ID_MAX];										//	���݂̓��͏��
bool keyDownTrigger[KEY_ID_MAX];								//	�޳ݎ����ضް
bool keyUpTrigger[KEY_ID_MAX];									//	���ߎ����ضް



//-----���֘A
//���͏��̏�����
void KeyInit(void)
{
	for (int keyID = 0; keyID < KEY_ID_MAX; keyID++)
	{
		keyOld[keyID] = false;
		keyNew[keyID] = false;
		keyDownTrigger[keyID] = false;
		keyUpTrigger[keyID] = false;
	}
}

//���͏��̊m�F
void KeyCheck(void)
{
	//Old�̏���
	for (int key = 0; key < KEY_ID_MAX; key++)
	{
		keyOld[key] = keyNew[key];
	}
	
	//���݂̏�Ԃ��擾����
	keyNew[KEY_ID_SPACE] = CheckHitKey(KEY_INPUT_SPACE);
	keyNew[KEY_ID_PAUSE] = CheckHitKey(KEY_INPUT_P);
	keyNew[KEY_ID_IVENT] = CheckHitKey(KEY_INPUT_I);
	keyNew[KEY_ID_UP] = CheckHitKey(KEY_INPUT_UP);
	keyNew[KEY_ID_RIGHT] = CheckHitKey(KEY_INPUT_RIGHT);
	keyNew[KEY_ID_DOWN] = CheckHitKey(KEY_INPUT_DOWN);
	keyNew[KEY_ID_LEFT] = CheckHitKey(KEY_INPUT_LEFT);
	keyNew[KEY_ID_SHOT] = CheckHitKey(KEY_INPUT_LCONTROL);
	keyNew[KEY_ID_FIRE] = CheckHitKey(KEY_INPUT_Z);
	keyNew[KEY_ID_WATER] = CheckHitKey(KEY_INPUT_X);
	keyNew[KEY_ID_WIND] = CheckHitKey(KEY_INPUT_C);
	keyNew[KEY_ID_HEAL] = CheckHitKey(KEY_INPUT_V);

	//�g���K�[�̎Z�o
	for (int keyID = 0; keyID < KEY_ID_MAX; keyID++)
	{
		keyDownTrigger[keyID] = false;
		keyUpTrigger[keyID] = false;

		// �_�E���g���K�[
		if (!keyOld[keyID] && keyNew[keyID])
		{
			keyDownTrigger[keyID] = true;
		}
		// �A�b�v�g���K�[
		if (keyOld[keyID] && !keyNew[keyID])
		{
			keyUpTrigger[keyID] = true;
		}

	}
}