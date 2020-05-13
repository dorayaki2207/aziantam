//#pragma once
//-------------------------
// AsoulQuest = main.h
// 2019.09.26
// 山本美由紀
//-------------------------

//定数の定義
//--------------
//画面サイズ
#define SCREEN_SIZE_X 800	//画面ｻｲｽﾞ横
#define SCREEN_SIZE_Y 600	//画面ｻｲｽﾞ縦
#define TITLE_SIZE_X  600	//ﾀｲﾄﾙの横ｻｲｽﾞ
#define TITLE_SIZE_Y  250	//ﾀｲﾄﾙの縦ｻｲｽﾞ
#define GAMEOVER_SIZE_X 457	//ｹﾞｰﾑｵｰﾊﾞｰの横ｻｲｽﾞ
#define GAMEOVER_SIZE_Y 81	//ｹﾞｰﾑｵｰﾊﾞｰの縦ｻｲｽﾞ
#define HITSTARTKEY_SIZE_X 337	//hitstartkeyの横ｻｲｽﾞ
#define HITSTARTKEY_SIZE_Y 53	//hitstartkeyの縦ｻｲｽﾞ

//列挙型の定義
//-----------------
//ｼｰﾝ管理用
enum SCENE_ID
{
	SCENE_ID_INIT,			//初期化
	SCENE_ID_TITLE,			//タイトル
	SCENE_ID_GAME,			//ゲーム
	SCENE_ID_GAMEOVER,		//ゲームオーバー
	SCENE_ID_MAX
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
enum CHARACTER_TYPE
{
	CHARACTER_PLAYER,
	CHARACTER_ENEMY,
	CHARACTER_SHOT,
	CHARACTER_MAX,
};

//構造体
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



//プロトタイプ宣言
//---------------
//ｼｽﾃﾑ
bool SystemInit(void);					//ｼｽﾃﾑの初期化
void InitScene(void);					//初期化ｼｰﾝ
//タイトル
void TitleScene(void);					//ﾀｲﾄﾙｼｰﾝ
void TitleDraw(void);					//ﾀｲﾄﾙｼｰﾝの描画用ｼｰﾝ
//ゲーム
void GameScene(void);					//ｹﾞｰﾑｼｰﾝ
void GameDraw(void);					//ｹﾞｰﾑｼｰﾝの描画用ｼｰﾝ
//ｹﾞｰﾑｵｰﾊﾞｰ
void GameOverScene(void);				//ｹﾞｰﾑｵｰﾊﾞｰ
void GameOverDraw(void);				//ｹﾞｰﾑｵｰﾊﾞｰの描画用ｼｰﾝ
void AddScore(int point);				//得点を追加
bool SaveData(void);					//ﾌｧｲﾙからスコアを保存する
bool LoadData(void);					//ﾌｧｲﾙからスコアを読み込む
void AddCharOrder(CHARACTER_TYPE characterType, int index, int y);		//ｷｬﾗｸﾀ情報をdrawOrderListに追加する