//#pragma once

//-----�萔��`
#define MAP_X			45
#define MAP_Y			45
#define MAP_MOB_X		30
#define MAP_MOB_Y		30
#define MAP_ONI_X		40
#define MAP_ONI_Y		40

#define MAP_TEST_X		30
#define MAP_TEST_Y		30


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
	STAGE_ID_MOB,				//MOB�G�ð��
	STAGE_ID_ONI,				//�S�ð��
	STAGE_ID_TEST,
	STAGE_ID_TEST2,
	STAGE_ID_MAX
};

//�o���\���ǂ���
enum PASS_ID
{
	PASS_OK,					//�o���\
	PASS_NON
};


//-----�֐��������ߐ錾
void StageSystemInit(void);		//�ð�ޏ��̏�����	
void StageGameInit(void);		//						
void StageGameDraw(void);		//�ð�ޗp�`�揈��
void SetMapData(STAGE_ID stage_ID);
XY PosToIndex(XY pos);	        //�߸�ٍ��W�n����ϯ�ߔz����W�n�ɕϊ�����
bool IsPass(XY pos);			//�w�肵�����W���ʉ߉\����Ԃ� true:�ʉ߂ł���
//bool IsEnemyPass(XY pos);
PASS_ID Pass(XY pos);
void MapRange();
//-----��۰��ى�
extern XY mapPos;
extern XY mapSize;
extern PASS_ID passID;