//#pragma once

//---定義
#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 650
//#define SCREEN_SIZE_X 600
//#define SCREEN_SIZE_Y 800
//#define SCREEN_SIZE_X 700
//#define SCREEN_SIZE_Y 900
//#define SCREEN_SIZE_X 800
//#define SCREEN_SIZE_Y 1000


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

//敵
enum ENEMY	
{
	ENEMY_ONI,		//鬼
	ENEMY_TENG,		//天狗
	ENEMY_KAPPA,	//河童
	ENEMY_NUE,		//鵺
	ENEMY_I_MOB,	//石橋担当
	ENEMY_Y_MOB,	//山本担当
	ENEMY_A_MOB,	//荒木担当
	ENEMY_MAX
};
//ｱｲﾃﾑ
enum ITEM
{					//-----角が曲がった素材-----
	ITEM_HI,		//火の御札：ドロップ
	ITEM_MIZU,		//水の御札：ドロップ
	ITEM_KAZE,		//風の御札：ドロップ
	ITEM_KAIFUKU,	//回復の御札：ドロップ
					//-----ﾃﾞﾌｫﾙﾄ素材-----
	ITEM_M_HI,		//火の御札：イベントリ
	ITEM_M_MIZU,	//水の御札：イベントリ
	ITEM_M_KAZE,	//風の御札：イベントリ
	ITEM_M_KAIFUKU,	//回復の御札：イベントリ
					//-----大きいｻｲｽﾞの素材-----
	ITEM_B_HI,		//火の御札：ボス戦用
	ITEM_B_MIZU,	//水の御札：ボス戦用
	ITEM_B_KAZE,	//風の御札：ボス戦用
	ITEM_B_KAIFUKU,	//回復の御札：ボス戦用
					//-----必須ｱｲﾃﾑ素材-----
	ITEM_KEN,		//三種の神器：剣
	ITEM_KAGAMI,	//三種の神器：鏡
	ITEM_MAGATAMA,	//三種の神器：勾玉
	ITEM_MAX
};




//ｷｬﾗｸﾀの種類管理用
//enum CHARACTER_TYPE
//{
//	CHARACTER_PLAYER,
//	CHARACTER_ENEMY,
//	CHARACTER_SHOT,
//	CHARACTER_MAX,
//};

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
