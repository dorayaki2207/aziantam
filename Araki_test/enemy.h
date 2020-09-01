

//-----�萔��`
#define ENEMY_MAX 5		//	�G�̐�
#define ENEMY_MAX_B 3		// �{�X�̐�


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
void EnemySystemInit(void);					//��а���̏�����
void EnemyGameInit(void);					//	
void EnemyControl(XY pPos);					//��а�̑���
void EnemyGameDraw(void);					//��а�̕`�揈��

int MoveEnemyX(CHARACTER* enemy, XY playerPos);		//�G��X���W����ɓ�����
int MoveEnemyY(CHARACTER* enemy, XY playerPos);		//�G��Y���W����ɓ�����
int MoveEnemyXY(CHARACTER* enemy, XY playerPos);	//�G��XY���W����ɓ�����

bool EnemyHitCheck(XY sPos, int sSize);		//��а�ƒe�̓����蔻��

bool PlayerHitCheck(XY pPos, int  pSize);