//#pragma once

//---定義
#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 650


//-----列挙型の定義
//ｼｰﾝ管理用
enum SCENE				
{
	SCENE_INIT,			//初期化ｼｰﾝ
	SCENE_TITLE,		//ﾀｲﾄﾙｼｰﾝ
	SCENE_GAME,			//ｹﾞｰﾑｼｰﾝ
	SCENE_GAMEOVER,		//ｹﾞｰﾑｵｰﾊﾞｰｼｰﾝ
	SCENE_MAX
};

//向き管理用
enum DIR
{
	DIR_UP,			//上
	DIR_RIGHT,		//右
	DIR_DOWN,		//下
	DIR_LEFT,		//左
	DIR_MAX
};

enum MAGIC_TYPE
{
	MAGIC_TYPE_FIRE,		//属性：火
	MAGIC_TYPE_WATER,		//属性：水
	MAGIC_TYPE_WIND,		//属性：風
	MAGIC_TYPE_HEAL,		//属性：回復
	MAGIC_TYPE_MAX
};




//-----構造体
//----------------
//得点管理用
struct FILE_DATA
{
	int Score;				//現在得点
	int hiScore;			//最高得点
};

//ﾎﾟｼﾞｼﾞｮﾝ
struct XY
{
	int x;
	int y;
};

//ｷｬﾗｸﾀ
struct CHARACTER
{
	int charType;	//ｷｬﾗｸﾀの種類
	DIR moveDir;	//ｷｬﾗｸﾀの向き
	XY pos;			//ｷｬﾗｸﾀの地図上の座標
	XY size;		//ｷｬﾗｸﾀ画像のｻｲｽﾞ
	XY offsetSize;	//ｷｬﾗｸﾀのｵﾌｾｯﾄ
	int moveSpeed;	//ｷｬﾗｸﾀの移動ｽﾋﾟｰﾄﾞ
	int lifeMax;	//ｷｬﾗｸﾀの体力最大値
	int life;		//ｷｬﾗｸﾀの体力
	int animCnt;	//ｷｬﾗｸﾀのｱﾆﾒｰｼｮﾝ
	int point;		//ｷｬﾗｸﾀの得点

};

struct KEY_LIST
{
	int up;
	int right;
	int down;
	int left;
	int shot;
};


//-----ﾌﾟﾛﾄﾀｲﾌﾟ宣言
//初期化
bool SystemInit(void);
void InitScene(void);
//ﾀｲﾄﾙ
void TitleScene(void);
void TitleDraw(void);
//ｹﾞｰﾑ
void GameScene(void);
void GameDraw(void);
//ｹﾞｰﾑｵｰﾊﾞｰ
void GameOverScene(void);
void GameOverDraw(void);
