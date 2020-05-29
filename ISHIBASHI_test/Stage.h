//#pragma once

//-----�萔��`
#define MAP_X			30
#define MAP_Y			30
#define CHIP_SIZE_X		32
#define CHIP_SIZE_Y		32

#define SCROLL_X_MIN 100
#define SCROLL_X_MAX 400
#define SCROLL_Y_MIN 100
#define SCROLL_Y_MAX 550

//�o���\���ǂ���
enum PASS_ID
{
	PASS_OK,				//	�o���\
	PASS_NON
};


//-----�֐��������ߐ錾
void StageSystemInit(void);		//�@�ð�ޏ��̏�����	
void StageGameInit(void);			//						
void StageGameDraw(void);			//�@�ð�ޗp�`�揈��
XY PosToIndex(XY pos);	           //�߸�ٍ��W�n����ϯ�ߔz����W�n�ɕϊ�����
bool IsPass(XY pos);						//�w�肵�����W���ʉ߉\����Ԃ� true:�ʉ߂ł���
//bool IsEnemyPass(XY pos);
PASS_ID Pass(XY pos);
//-----��۰��ى�
extern XY mapPos;
extern PASS_ID passID;