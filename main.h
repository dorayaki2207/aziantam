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

//---構造体

//---プロトタイプ宣言
bool SystemInit(void);
void InitScene(void);
void TitleScene(void);
void TitleDraw(void);
void GameScene(void);
void GameDraw(void);
void GameOverScene(void);
void GameOverDraw(void);
