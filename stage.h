
//����
//stage.h
//2020.05.13

//#pragma once

//�萔
#define MAP_X 25				//�}�b�v�`�b�v�摜�̉��T�C�Y
#define MAP_Y 25				//�}�b�v�`�b�v�摜�̏c�T�C�Y
#define MAP_X 25
#define MAP_Y 25
#define MAP_CHIP_X 9
#define MAP_CHIP_Y 9

//�C�x���gID
enum STAGE_ID {
	STAGE_ID_START,
	
	STAGE_ID_MAX
};

//�C�x���g���
enum EVENT_ID {
	EVENT_ID_NON,
	
	EVENT_ID_MAX
};

//extern�錾
//extern int map[MAP_Y][MAP_X];
extern XY mapPos;
extern STAGE_ID stageID;		//�X�e�[�WID

//�v���g�^�C�v�錾
void StageSystemInit(void);			//�X�e�[�W���̏�����
void StageGameInit(void);			//�X�e�[�W���̃Q�[��������
void StageGameDraw(void);			//�Q�[����ʂ̕\������

XY Pos2Index(XY pos);				//�s�N�Z�����W�n����}�b�v�z����W�n�ɕϊ�����B

bool IsPass(XY pos);				//�w�肵�����W���ʉ߉\����Ԃ��@true:�ʉ߂ł���

EVENT_ID GetEvent(XY pos);			//�w�肵�����W�����ʂɃC�x���g���N���������m�F����@�߂�l�F�C�x���gID

void SetMapData(STAGE_ID stageID);	//�X�e�[�W�f�[�^���}�b�v�z��ɃR�s�[����
