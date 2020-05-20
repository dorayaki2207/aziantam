//#pragma once



#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 650

#define SCR_MAX 3


//-----列挙型
//ｼｰﾝ
enum SCENE_ID
{
	SCENE_ID_INIT,					//	ｼｰﾝ初期化
	SCENE_ID_TITLE,					//	ﾀｲﾄﾙ
	SCENE_ID_GAME,					//	ｹﾞｰﾑ
	SCENE_ID_MAX
};
//向き
enum DIR
{
	DIR_UP,							//	↑
	DIR_RIGHT,						//	→
	DIR_DOWN,						//	↓
	DIR_LEFT,						// ←
	DIR_MAX
};

//-----構造体
//座標
struct XY
{
	int x;							//	X座標
	int y;							//	Y座標
};
//ｷｬﾗｸﾀ用
struct CHARACTER
{
	int charType;					//	ｷｬﾗｸﾀの種類
	DIR moveDir;					//	ｷｬﾗｸﾀの向き
	XY pos;							//　ｷｬﾗｸﾀの地図上の座標
	XY size;						//	ｷｬﾗｸﾀの画像ｻｲｽﾞ
	XY offsetSize;					//　ｷｬﾗｸﾀのｵﾌｾｯﾄ
	int moveSpeed;					//	ｷｬﾗｸﾀの移動ｽﾋﾟｰﾄﾞ
	int lifeMax;					//	ｷｬﾗｸﾀの体力最大値
	int life;						//	ｷｬﾗｸﾀの体力
	int animCnt;					//	ｷｬﾗｸﾀのｱﾆﾒｰｼｮﾝ
	int point;						//	ｷｬﾗｸﾀのｽｺｱ
};



//-----ﾌﾟﾛﾄﾀｲﾌﾟ宣言
bool SystemInit(void);
void InitScene(void);
void GameScene(void);
void GameDraw(void);

void TitleScene(void);


extern int totalScrNew;
extern int totalScr[SCR_MAX];
extern int hiCnt;
extern int mizuCnt;
extern int kazeCnt;
extern int kaifukuCnt;