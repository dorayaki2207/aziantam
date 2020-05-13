//#pragma once

//---定義
#define SCREEN_SIZE_X 500
#define SCREEN_SIZE_Y 700
#define SCREEN_SIZE_X 600
#define SCREEN_SIZE_Y 800
#define SCREEN_SIZE_X 700
#define SCREEN_SIZE_Y 900
#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 1000


//列挙型の定義
enum SCENE				//ｼｰﾝ管理用
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
//ｷｬﾗｸﾀの種類管理用
//enum CHARACTER_TYPE
//{
//	CHARACTER_PLAYER,
//	CHARACTER_ENEMY,
//	CHARACTER_SHOT,
//	CHARACTER_MAX,
//};

//---構造体
//----------------
//得点管理用
struct FILE_DATA
{
	int Score;				//現在得点
	int hiScore;			//最高得点
};
//ポジション
struct XY
{
	int x;
	int y;
};
//ｷｬﾗｸﾀ
struct CHARACTER
{
	int CharType;	//ｷｬﾗｸﾀの種類
	DIR MoveDir;	//ｷｬﾗｸﾀの向き
	XY Pos;			//ｷｬﾗｸﾀの地図上の座標
	XY Size;		//ｷｬﾗｸﾀ画像のｻｲｽﾞ
	XY OffsetSize;	//ｷｬﾗｸﾀのｵﾌｾｯﾄ
	int MoveSpeed;	//ｷｬﾗｸﾀの移動ｽﾋﾟｰﾄﾞ
	int LifeMax;	//ｷｬﾗｸﾀの体力最大値
	int Life;		//ｷｬﾗｸﾀの体力
	int AnimCnt;	//ｷｬﾗｸﾀのｱﾆﾒｰｼｮﾝ

	int point;		//ｷｬﾗｸﾀの得点
};

//---プロトタイプ宣言
bool SystemInit(void);
void InitScene(void);
void TitleScene(void);
void TitleDraw(void);
void GameScene(void);
void GameDraw(void);
void GameOverScene(void);
void GameOverDraw(void);
