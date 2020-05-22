//#pragma once


//-----列挙型
enum KEY_ID
{
	KEY_ID_SPACE,					//	ｽﾍﾟｰｽｷｰ
	KEY_ID_PAUSE,					//	P
	KEY_ID_IVENT,					//	I
	KEY_ID_UP,						//	↑
	KEY_ID_RIGHT,					//　→
	KEY_ID_DOWN,					//	↓
	KEY_ID_LEFT,					//　←
	KEY_ID_SHOT,					//	左Ctrl
	KEY_ID_FIRE,					//	攻撃：火
	KEY_ID_WATER,					//	攻撃：水
	KEY_ID_WIND,					//　攻撃：風
	KEY_ID_HEAL,					//	回復
	KEY_ID_MAX
};


//-----関数ﾌﾟﾛﾄﾀｲﾌﾟ宣言
void KeyInit(void);										//	入力情報初期化
void KeyCheck(void);									//	入力情報の確認


//-----グローバル化
extern bool keyOld[KEY_ID_MAX];							//	1ﾌﾚｰﾑ前の入力状態
extern bool keyNew[KEY_ID_MAX];							//	現在の入力状態
extern bool keyDownTrigger[KEY_ID_MAX];					//	ﾀﾞｳﾝ時のﾄﾘｶﾞｰ
extern bool keyUpTrigger[KEY_ID_MAX];					//	ｱｯﾌﾟ時のﾄﾘｶﾞｰ


