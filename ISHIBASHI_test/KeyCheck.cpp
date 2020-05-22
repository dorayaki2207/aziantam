#include "DxLib.h"
#include "KeyCheck.h"


//ｷｰ関連
bool keyOld[KEY_ID_MAX];										//	1ﾌﾚｰﾑ前の入力状態
bool keyNew[KEY_ID_MAX];										//	現在の入力状態
bool keyDownTrigger[KEY_ID_MAX];								//	ﾀﾞｳﾝ時のﾄﾘｶﾞｰ
bool keyUpTrigger[KEY_ID_MAX];									//	ｱｯﾌﾟ時のﾄﾘｶﾞｰ



//-----ｷｰ関連
//入力情報の初期化
void KeyInit(void)
{
	for (int keyID = 0; keyID < KEY_ID_MAX; keyID++)
	{
		keyOld[keyID] = false;
		keyNew[keyID] = false;
		keyDownTrigger[keyID] = false;
		keyUpTrigger[keyID] = false;
	}
}

//入力情報の確認
void KeyCheck(void)
{
	//Oldの準備
	for (int key = 0; key < KEY_ID_MAX; key++)
	{
		keyOld[key] = keyNew[key];
	}
	
	//現在の状態を取得する
	keyNew[KEY_ID_SPACE] = CheckHitKey(KEY_INPUT_SPACE);
	keyNew[KEY_ID_PAUSE] = CheckHitKey(KEY_INPUT_P);
	keyNew[KEY_ID_IVENT] = CheckHitKey(KEY_INPUT_I);
	keyNew[KEY_ID_UP] = CheckHitKey(KEY_INPUT_UP);
	keyNew[KEY_ID_RIGHT] = CheckHitKey(KEY_INPUT_RIGHT);
	keyNew[KEY_ID_DOWN] = CheckHitKey(KEY_INPUT_DOWN);
	keyNew[KEY_ID_LEFT] = CheckHitKey(KEY_INPUT_LEFT);
	keyNew[KEY_ID_SHOT] = CheckHitKey(KEY_INPUT_LCONTROL);
	keyNew[KEY_ID_FIRE] = CheckHitKey(KEY_INPUT_Z);
	keyNew[KEY_ID_WATER] = CheckHitKey(KEY_INPUT_X);
	keyNew[KEY_ID_WIND] = CheckHitKey(KEY_INPUT_C);
	keyNew[KEY_ID_HEAL] = CheckHitKey(KEY_INPUT_V);

	//トリガーの算出
	for (int keyID = 0; keyID < KEY_ID_MAX; keyID++)
	{
		keyDownTrigger[keyID] = false;
		keyUpTrigger[keyID] = false;

		// ダウントリガー
		if (!keyOld[keyID] && keyNew[keyID])
		{
			keyDownTrigger[keyID] = true;
		}
		// アップトリガー
		if (keyOld[keyID] && !keyNew[keyID])
		{
			keyUpTrigger[keyID] = true;
		}

	}
}