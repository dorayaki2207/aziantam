//#pragma once
// keycheck.h
// 2019.09.19
// �R�{���R�I

//�񋓌^�̒�`
//-----------------
//���ް�ފǗ��p
enum KEY_ID
{
	KEY_ID_SPACE,	//�X�y�[�X�L�[
	KEY_ID_PAUSE,	//P�L�[��pause
	KEY_ID_IVENT,	//I�L�[�Ų�����
	KEY_ID_SHOT,	//�����۰ٷ��Œe����
	KEY_ID_SAVE,	//S���ŕۑ�
	KEY_ID_LOAD,	//L���œǂݍ���
	KEY_ID_UP,		//��L�[
	KEY_ID_RIGHT,	//�E�L�[
	KEY_ID_DOWN,	//���L�[
	KEY_ID_LEFT,	//���L�[
	KEY_ID_FIRE,	//�U���F��
	KEY_ID_WATER,	//�U���F��
	KEY_ID_WIND,	//�U���F��
	KEY_ID_HEAL,	//��
	KEY_ID_ENTER,	//�I��

	KEY_ID_MAX
};

//extern�錾
//---------------
//���͏��֘A
extern bool KeyOld[KEY_ID_MAX];			//1�t���[���O�̓��͏��
extern bool KeyNew[KEY_ID_MAX];			//���݂̓��͏��
extern bool KeyDownTrigger[KEY_ID_MAX];	//�_�E�����̃g���K�[
extern bool KeyUpTrigger[KEY_ID_MAX];	//�A�b�v���̃g���K�[

//�v���g�^�C�v�錾
//---------------
void KeyInit(void);					//���͏��̏�����
void KeyCheck(void);				//���͏��̊m�F

