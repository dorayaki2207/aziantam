

//-----čč`
#define ENEMY_MAX 2		//	GĚ

#define DAMAGE_NORMAL	2		//ŻŽŤŔŢŇ°źŢĘ
#define DAMAGE_HIGH		3		//LŽŤŔŢŇ°źŢĘ
#define DAMAGE_LOW		1		//sŽŤŔŢŇ°źŢĘ


//-----ń^
//u
enum ENEMY_MOB
{
	ENEMY_I_MOB,	//Î´S
	ENEMY_Y_MOB,	//R{S
	ENEMY_A_MOB,	//rŘS
	ENEMY_M_MAX
};
//{X
enum ENEMY_BOSS
{
	ENEMY_ONI,		//S
	ENEMY_TENG,		//Vç
	ENEMY_KAPPA,	//Íś
	ENEMY_NUE,		//ęK
	ENEMY_B_MAX
};

//-----ÖĚßŰÄŔ˛Ěßéž
void EnemySystemInit(void);					//´ČĐ°îńĚúť
void EnemyGameInit(void);					//	
void EnemyControl(XY pPos);					//´ČĐ°Ěě
void EnemyGameDraw(void);					//´ČĐ°Ě`ć

bool SetEnemyMoment(XY pPos);				//GŞSő|łę˝Ě

bool EnemyHitCheck(XY sPos, int sSize, CHARACTER* shot);		//´ČĐ°ĆeĚ˝čťč
bool PlayerHitCheck(XY sPos, int sSize);

