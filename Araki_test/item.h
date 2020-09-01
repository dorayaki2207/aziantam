//#pragma once

//-----定数定義
#define ITEM_MAX    20
#define ITEM_M_SIZE 20			//	ｲﾝﾍﾞﾝﾄﾘ用御札ｻｲｽﾞ(M : ﾐﾆ
#define ITEM_B_SIZE 150			//	ﾊﾞﾄﾙ用御札ｻｲｽﾞ(B : ﾋﾞｯｸﾞ



//-----列挙型
enum ITEM_TYPE_B
{
	ITEM_TYPE_KEN,				//	三種の神器・剣
	ITEM_TYPE_KAGAMI,			//	三種の神器・鏡
	ITEM_TYPE_MAGATAMA,			//	三種の神器・勾玉
	ITEM_TYPE_B_MAX
};


//-----関数ﾌﾟﾛﾄﾀｲﾌﾟ宣言
void ItemSystmeInit(void);		//　ｱｲﾃﾑ情報の初期化	
void ItemGameInit(void);		//						
void ItemControl(void);			//	ｱｲﾃﾑの操作
bool ItemMOBControl(MAGIC_TYPE type);		//	MOB敵攻撃用ｱｲﾃﾑの操作
void ItemGameDraw(void);		//　ｱｲﾃﾑ描画処理
void ItemI_Draw(void);			//	ｲﾝﾍﾞﾝﾄﾘ用のｱｲﾃﾑ画像描画
bool ItemMobControl(MAGIC_TYPE type);	//	MOB敵交戦時処理
void ItemDrop(XY ePos, MAGIC_TYPE type);
bool GameOverSet();						//	ｹﾞｰﾑｵｰﾊﾞｰ条件
//void ItemB_Draw(void);		//	ﾎﾞｽﾊﾞﾄﾙ用のｱｲﾃﾑ画像描画
bool ItemHitCheck(XY sPos, int sSize);
void DeleteItem();


//-----ｸﾞﾛｰﾊﾞﾙ化
extern CHARACTER itemF[ITEM_MAX];


