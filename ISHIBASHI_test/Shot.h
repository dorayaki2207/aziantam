//#pragma once

//-----�萔��`
#define SHOT_ANI		46				//�@�e�̱�Ұ��ݐ�
#define SHOT_LIFE_MAX	46


//-----�񋓌^
enum SHOT_TYPE
{
	SHOT_TYPE_FIRE,				//	�΂̌�D
	SHOT_TYPE_WATER,			//	���̌�D
	SHOT_TYPE_WIND,				//	���̌�D
	SHOT_TYPE_HEAL,				//	�񕜂̌�D
	SHOT_TYPE_MAX
};


//-----�֐��������ߐ錾
void ShotSystemInit(void);				//�@�e���̏�����	
void ShotGameInit(void);
void ShotControl(void);					//	�e�̑���
void ShotGameDraw(void);				//	�e�̕`�揈��
void CreateShot(XY pPos, DIR pDir, SHOT_TYPE ptype/*, ITEM_TYPE_F itype*/);
void DeleteShot(int index);
void ShotAniCnt(SHOT_TYPE type);

//-----��۰��ى�
extern CHARACTER shot[];