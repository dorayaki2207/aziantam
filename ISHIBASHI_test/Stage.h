//#pragma once

//-----�萔��`
#define MAP_X		 	45
#define MAP_Y			45
#define MAP_MOB_X		30
#define MAP_MOB_Y		30
#define MAP_ONI_X		40
#define MAP_ONI_Y		40
#define MAP_ONI2_X		25
#define MAP_ONI2_Y		25

#define MAP_START_Y 40	//�͂��܂�̑�
#define MAP_START_X 40


#define CHIP_SIZE_X		32
#define CHIP_SIZE_Y		32

#define SCROLL_X_MIN 100
#define SCROLL_X_MAX 400
#define SCROLL_Y_MIN 100
#define SCROLL_Y_MAX 400


//-----�񋓌^
//�ð�ޏ��
enum STAGE_ID
{
	STAGE_ID_START,
	STAGE_ID_MOB,				//MOB�G�ð��
	STAGE_ID_ONI,				//�S�ð��
	STAGE_ID_ONI2,				//�S���A
	STAGE_ID_MAX
};
//����ď��
enum EVENT_ID
{
	EVENT_ID_NON,			//����ĂȂ�
	EVENT_ID_KAIDAN,		//�K�i�@
	EVENT_ID_KAIDAN2,		//�K�i�A
	EVENT_ID_DOKUTU,
	EVENT_ID_DAMAGE,		//��Ұ��
	EVENT_ID_STOP,			//�~�܂�
	EVENT_ID_SPEEDDOWN,		//�������x���Ȃ�
	EVENT_ID_MAX
};

enum CHIP_POS
{
	CHIP_POS_KAIDAN,
	CHIP_POS_KAIDAN2,
	CHIP_POS_NON,
	CHIP_POS_MAX
};


//-----�֐��������ߐ錾
void StageSystemInit(void);		//�ð�ޏ��̏�����	
void StageGameInit(void);		//						
void StageGameDraw(void);		//�ð�ޗp�`�揈��
void SetMapData(STAGE_ID stage_ID);
XY PosToIndex(XY pos);	        //�߸�ٍ��W�n����ϯ�ߔz����W�n�ɕϊ�����
bool IsPass(XY pos);			//�w�肵�����W���ʉ߉\����Ԃ� true:�ʉ߂ł���
EVENT_ID GetEvent(XY pos);	    // �w�肵�����W�����ʂɲ���Ă��N���������m�F����@�߂�l�F�����ID
void MapRange();

void GetPos(XY pos);
//-----��۰��ى�
extern XY mapPos;
extern XY mapSize;
