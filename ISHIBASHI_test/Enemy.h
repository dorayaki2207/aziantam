

//-----�萔��`
#define ENEMY_MAX 20		//	�G�̐�

//-----�񋓌^
//���u
enum ENEMY_MOB
{
	ENEMY_I_MOB,	//�΋��S��
	ENEMY_Y_MOB,	//�R�{�S��
	ENEMY_A_MOB,	//�r�ؒS��
	ENEMY_M_MAX
};
//�{�X
enum ENEMY_BOSS
{
	ENEMY_ONI,		//�S
	ENEMY_TENG,		//�V��
	ENEMY_KAPPA,	//�͓�
	ENEMY_NUE,		//�K
	ENEMY_B_MAX
};

//-----�֐��������ߐ錾
void EnemySystemInit(void);		//��а���̏�����
void EnemyGameInit(void);		//	
void EnemyControl(XY pPos);		//��а�̑���
void EnemyGameDraw(void);		//��а�̕`�揈��
int MoveEnemyX(CHARACTER* enemy, XY playerPos); //���@��X���W�ɒ��߂���悤�ɓ������@�߂�l�F�ړ�������
int MoveEnemyY(CHARACTER* enemy, XY playerPos); //���@��Y���W�ɒ��߂���悤�ɓ������@�߂�l�F�ړ�������
int MoveEnemyXY(CHARACTER* enemy, XY playerPos); //���@��X��Y�̉����ق�������W�𒲐߂���悤�ɓ������@�߂�l�F�ړ�������


bool EnemyHitCheck(XY sPos, int sSize,int index);