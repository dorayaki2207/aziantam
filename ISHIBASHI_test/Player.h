//#pragma once


//-----�萔��`
#define PLAYER_MAX	4

//-----�񋓌^
enum PLAYER_SPEED
{
	PLAYER_SPEED_LOW = 2,		//	�x��
	PLAYER_SPEED_NOMAL = 4,		//	�ʏ�
	PLATER_SPEED_HIGH = 6,		//	����
	PLATER_SPEED_MAX
};

//-----�֐��������ߐ錾
void PlayerSystemInit(void);		//�@��ڲ԰���̏�����	
void PlayerGameInit(void);			//						
XY PlayerControl(void);			//	��ڲ԰�̑���(�߂�l�F��ڲ԰�̍��W)
void PlayerGameDraw(void);			//�@��ڲ԰�`�揈��

