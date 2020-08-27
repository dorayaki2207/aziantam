//#pragma once
// keycheck.h
// 2019.09.19
// 山本美由紀

//列挙型の定義
//-----------------
//ｷｰﾎﾞｰﾄﾞ管理用
enum KEY_ID
{
	KEY_ID_SPACE,	//スペースキー
	KEY_ID_PAUSE,	//Pキーでpause
	KEY_ID_IVENT,	//Iキーでｲﾍﾞﾝﾄﾘ
	KEY_ID_SHOT,	//左ｺﾝﾄﾛｰﾙｷｰで弾発射
	KEY_ID_SAVE,	//Sｷｰで保存
	KEY_ID_LOAD,	//Lｷｰで読み込み
	KEY_ID_UP,		//上キー
	KEY_ID_RIGHT,	//右キー
	KEY_ID_DOWN,	//下キー
	KEY_ID_LEFT,	//左キー
	KEY_ID_FIRE,	//攻撃：火
	KEY_ID_WATER,	//攻撃：水
	KEY_ID_WIND,	//攻撃：風
	KEY_ID_HEAL,	//回復
	KEY_ID_ENTER,	//選択

	KEY_ID_MAX
};

//extern宣言
//---------------
//入力情報関連
extern bool KeyOld[KEY_ID_MAX];			//1フレーム前の入力情報
extern bool KeyNew[KEY_ID_MAX];			//現在の入力情報
extern bool KeyDownTrigger[KEY_ID_MAX];	//ダウン時のトリガー
extern bool KeyUpTrigger[KEY_ID_MAX];	//アップ時のトリガー

//プロトタイプ宣言
//---------------
void KeyInit(void);					//入力情報の初期化
void KeyCheck(void);				//入力情報の確認

