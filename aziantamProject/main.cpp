#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "effect.h"
#include "enemy.h"
#include "shot.h"
#include "item.h"
#include "stage.h"

//変数
SCENE SceneID;
SCENE ScenePreID;	//過去のｼｰﾝ格納用
int SceneCounter;

//ｸﾗｽからｲﾝｽﾀﾝｽを生成
//敵
Enemy* enemyI;		//石橋担当MOB
Enemy* enemyY;		//山本担当MOB
Enemy* enemyA;		//荒木担当MOB
//ｱｲﾃﾑ
Item* item_m_hi;			//火の御札：ﾃﾞﾌｫﾙﾄ
Item* zingi_ken20;			//三種の神器：剣(ｻｲｽﾞ20)

//Win関数
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	if (!SystemInit())return -1;

	//-----ｹﾞｰﾑﾙｰﾌﾟ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//ｼｰﾝｶｳﾝﾄﾘｾｯﾄ
		if (SceneID != ScenePreID)
		{
			ScenePreID = SceneID;
			SceneCounter = 0;
		}
		//-----画面描画処理
		ClsDrawScreen();	//画面消去
		//ｼｰﾝ選択
		switch (SceneID)
		{
		case SCENE_INIT:
			InitScene();
			break;
		//ﾀｲﾄﾙｼｰﾝ
		case SCENE_TITLE:
			TitleScene();
			break;
		//ｹﾞｰﾑｼｰﾝ
		case SCENE_GAME:
			GameScene();
			break;
		//ｹﾞｰﾑｵｰﾊﾞｰｼｰﾝ
		case SCENE_GAMEOVER:
			GameOverScene();
			break;
		default:
			return -1;
			break;
		}
		SceneCounter++;		
		ScreenFlip();		//裏画面を表画面に瞬間ｺﾋﾟｰ
	}
	//-----ｲﾝｽﾀﾝｽの解放
	//敵
	delete enemyI;			//石橋担当MOB
	delete enemyY;			//山本担当MOB
	delete enemyA;			//荒木担当MOB
	//ｱｲﾃﾑ
	delete item_m_hi;		//火の御札：ﾃﾞﾌｫﾙﾄ
	delete zingi_ken20;		//三種の神器：剣（ｻｲｽﾞ20）	

	DxLib_End();			//DXﾗｲﾌﾞﾗﾘの終了処理
	return 0;				//このﾌﾟﾛｸﾞﾗﾑの終了

}
//ｼｽﾃﾑの初期化
bool SystemInit(void)
{
	//--------ｼｽﾃﾑ処理
	SetWindowText("月夜～三つの神宝～");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)return false;
	SetDrawScreen(DX_SCREEN_BACK);
	
	//-----ｲﾝｽﾀﾝｽの生成
	//敵
	enemyI = new Enemy(ENEMY_I_MOB			//石橋担当MOB
		, 100, 100
		, "char/妖狐.png", 16
		,4, 4
		,32, 32
	);										
	enemyY = new Enemy(ENEMY_Y_MOB			//山本担当MOB
		, 150, 100
		, "char/wind_mob_enemy1.png", 16
		, 4, 4
		, 32, 32
	);
	enemyA = new Enemy(ENEMY_A_MOB			//荒木担当MOB
		, 200, 100
		, "char/umi0.png", 16
		, 4, 4
		, 32, 32
	);
	//ｱｲﾃﾑ
	item_m_hi = new Item(ITEM_M_HI, 150, 150	//火の御札：ﾃﾞﾌｫﾙﾄ
		, "item/fuda.png", 8, 4, 2, 20, 20);
	zingi_ken20 = new Item(ITEM_KEN, 150, 200	//三種の神器：剣（ｻｲｽﾞ20）
		, "item/zingi20.png", 3, 3, 1, 20, 20);


	//-----各ﾓｼﾞｭｰﾙの初期化
	//敵
	enemyI->SystemInit();	//石橋担当MOB
	enemyY->SystemInit();	//山本担当MOB
	enemyA->SystemInit();	//荒木担当MOB
	//ｱｲﾃﾑ
	item_m_hi->SystemInit();		//火の御札：ﾃﾞﾌｫﾙﾄ
	zingi_ken20->SystemInit();		//三種の神器：剣（ｻｲｽﾞ20）

	//-----ｸﾞﾗﾌｨｯｸ登録


	//-----変数の初期化
	SceneCounter = 0;
	SceneID = SCENE_INIT;
	ScenePreID = SCENE_MAX;

	return true;
}
//初期化ｼｰﾝ
void InitScene(void)
{
	//-----各ｵﾌﾞｼﾞｪｸﾄ処理
	//敵
	enemyI->GameInit();		//石橋担当MOB	
	enemyY->GameInit();		//山本担当MOB	
	enemyA->GameInit();		//荒木担当MOB	
	//ｱｲﾃﾑ
	item_m_hi->GameInit();			//火の御札：ﾃﾞﾌｫﾙﾄ
	zingi_ken20->GameInit();		//三種の神器：剣（ｻｲｽﾞ20）

	//-----ｼｰﾝ遷移
	SceneID = SCENE_TITLE;
}




/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//ﾀｲﾄﾙｼｰﾝ
void TitleScene(void)
{
	//-----ｼｰﾝ遷移
	SceneID = SCENE_GAME;

	//-----描画
	TitleDraw();
}
//ﾀｲﾄﾙの描画
void TitleDraw(void)
{
	//-----描画処理

	//-----情報処理
	DrawFormatString(0, 0, 0xFFFFFF, "Title:%d", SceneCounter);

}



///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//ｹﾞｰﾑｼｰﾝ
void GameScene(void)
{
	//-----各ｵﾌﾞｼﾞｪｸﾄ操作
	//敵
	enemyI->Control();		//石橋担当MOB
	enemyY->Control();		//山本担当MOB	
	enemyA->Control();		//荒木担当MOB
	//ｱｲﾃﾑ
	item_m_hi->Control();		//火の御札：ﾃﾞﾌｫﾙﾄ
	zingi_ken20->Control();		//三種の神器：剣（ｻｲｽﾞ20）

	//-----描画
	GameDraw(); 
}


//ｹﾞｰﾑの描画
void GameDraw(void)
{

	//-----描画処理
	//敵
	enemyI->GameDraw();		//石橋担当MOB
	enemyY->GameDraw();		//山本担当MOB
	enemyA->GameDraw();		//荒木担当MOB
	//ｱｲﾃﾑ
	item_m_hi->GameDraw(ITEM_M_HI);		//火の御札：ﾃﾞﾌｫﾙﾄ
	zingi_ken20->GameDraw(ITEM_KEN);	//三種の神器：剣（ｻｲｽﾞ20）

	//-----情報処理
	DrawFormatString(0, 0, 0xFFFFFF, "Game:%d", SceneCounter);

}





//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//ｹﾞｰﾑｵｰﾊﾞｰｼｰﾝ
void GameOverScene(void)
{
	GameOverDraw();
}


//ｹﾞｰﾑｵｰﾊﾞｰの描画
void GameOverDraw(void)
{
	//-----描画処理

	//-----情報処理
	DrawFormatString(0, 0, 0xFFFFFF, "GameOver:%d", SceneCounter);


}
