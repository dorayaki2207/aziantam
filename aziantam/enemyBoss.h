#pragma once



//-----列挙型
//ボス
enum ENEMY_BOSS
{
	ENEMY_ONI,		//鬼
	ENEMY_TENG,		//天狗
	ENEMY_KAPPA,	//河童
	ENEMY_B_MAX
};

//-----関数ﾌﾟﾛﾄﾀｲﾌﾟ宣言
//基本処理
void EnemyBossSystemInit(void);					//ｴﾈﾐｰ情報の初期化
void EnemyBossGameInit(STAGE_ID stageID);					//	
void EnemyBossControl(XY pPos);					//ｴﾈﾐｰの操作
void EnemyBossGameDraw(void);					//ｴﾈﾐｰの描画処理

int MoveBossX(CHARACTER* enemy, XY playerPos);
int MoveBossY(CHARACTER* enemy, XY playerPos);
int MoveBossXY(CHARACTER* enemy, XY playerPos);
//当たり判定
bool EnemyBossHitCheck(XY sPos, int sSize, CHARACTER* shot);		//ｴﾈﾐｰと弾の当たり判定
bool Player_BHitCheck(XY sPos, int sSize);


//-----extern宣言
extern bool drawFlag[ENEMY_B_MAX];