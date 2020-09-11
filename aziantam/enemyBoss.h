#pragma once



//-----�񋓌^
//�{�X
enum ENEMY_BOSS
{
	ENEMY_ONI,		//�S
	ENEMY_TENG,		//�V��
	ENEMY_KAPPA,	//�͓�
	ENEMY_B_MAX
};

//-----�֐��������ߐ錾
//��{����
void EnemyBossSystemInit(void);					//��а���̏�����
void EnemyBossGameInit(STAGE_ID stageID);					//	
void EnemyBossControl(XY pPos);					//��а�̑���
void EnemyBossGameDraw(void);					//��а�̕`�揈��

int MoveBossX(CHARACTER* enemy, XY playerPos);
int MoveBossY(CHARACTER* enemy, XY playerPos);
int MoveBossXY(CHARACTER* enemy, XY playerPos);
//�����蔻��
bool EnemyBossHitCheck(XY sPos, int sSize, CHARACTER* shot);		//��а�ƒe�̓����蔻��
bool Player_BHitCheck(XY sPos, int sSize);


//-----extern�錾
extern bool drawFlag[ENEMY_B_MAX];