

//-----定数定義
#define ENEMY_MAX 5		//	敵の数
#define ENEMY_MAX_B 3		// ボスの数


//-----列挙型
//モブ
enum ENEMY_MOB
{
	ENEMY_I_MOB,	//石橋担当
	ENEMY_Y_MOB,	//山本担当
	ENEMY_A_MOB,	//荒木担当
	ENEMY_M_MAX
};
//ボス
enum ENEMY_BOSS
{
	ENEMY_ONI,		//鬼
	ENEMY_TENG,		//天狗
	ENEMY_KAPPA,	//河童
	ENEMY_NUE,		//鵺
	ENEMY_B_MAX
};

//-----関数ﾌﾟﾛﾄﾀｲﾌﾟ宣言
void EnemySystemInit(void);					//ｴﾈﾐｰ情報の初期化
void EnemyGameInit(void);					//	
void EnemyControl(XY pPos);					//ｴﾈﾐｰの操作
void EnemyGameDraw(void);					//ｴﾈﾐｰの描画処理

int MoveEnemyX(CHARACTER* enemy, XY playerPos);		//敵をX座標を基準に動かす
int MoveEnemyY(CHARACTER* enemy, XY playerPos);		//敵をY座標を基準に動かす
int MoveEnemyXY(CHARACTER* enemy, XY playerPos);	//敵をXY座標を基準に動かす

bool EnemyHitCheck(XY sPos, int sSize);		//ｴﾈﾐｰと弾の当たり判定

bool PlayerHitCheck(XY pPos, int  pSize);