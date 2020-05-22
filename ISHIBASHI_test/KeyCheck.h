//#pragma once


//-----�񋓌^
enum KEY_ID
{
	KEY_ID_SPACE,					//	��߰���
	KEY_ID_PAUSE,					//	P
	KEY_ID_IVENT,					//	I
	KEY_ID_UP,						//	��
	KEY_ID_RIGHT,					//�@��
	KEY_ID_DOWN,					//	��
	KEY_ID_LEFT,					//�@��
	KEY_ID_SHOT,					//	��Ctrl
	KEY_ID_FIRE,					//	�U���F��
	KEY_ID_WATER,					//	�U���F��
	KEY_ID_WIND,					//�@�U���F��
	KEY_ID_HEAL,					//	��
	KEY_ID_MAX
};


//-----�֐��������ߐ錾
void KeyInit(void);										//	���͏�񏉊���
void KeyCheck(void);									//	���͏��̊m�F


//-----�O���[�o����
extern bool keyOld[KEY_ID_MAX];							//	1�ڰёO�̓��͏��
extern bool keyNew[KEY_ID_MAX];							//	���݂̓��͏��
extern bool keyDownTrigger[KEY_ID_MAX];					//	�޳ݎ����ضް
extern bool keyUpTrigger[KEY_ID_MAX];					//	���ߎ����ضް


