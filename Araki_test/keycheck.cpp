// keyheck.cpp
// 2019.09.20
// 山本美由紀

#include "DxLib.h"
#include "keycheck.h"

//変数
//ｰｰｰｰｰｰｰｰｰ
//入力情報関連
bool KeyOld[KEY_ID_MAX];			//1フレーム前の入力情報
bool KeyNew[KEY_ID_MAX];			//現在の入力情報
bool KeyDownTrigger[KEY_ID_MAX];	//ダウン時のトリガー
bool KeyUpTrigger[KEY_ID_MAX];		//アップ時のトリガー


//入力情報の初期化
void KeyInit(void)
{
	for (int k = 0; k < KEY_ID_MAX; k++)
	{
		KeyOld[k] = false;
		KeyNew[k] = false;
		KeyDownTrigger[k] = false;
		KeyUpTrigger[k] = false;
	}
}
//入力情報の確認
void KeyCheck(void)
{
	//int mouseButton;					//マウスのボタン状態

	//Oldの準備
	for (int KeyID = 0; KeyID < KEY_ID_MAX; KeyID++)
	{
		KeyOld[KeyID] = KeyNew[KeyID];
	}

	//Mouseの情報を取得する
	//GetMousePoint(&mousePos.x, &mousePos.y);
	//mouseButton = GetMouseInput();

	//現在の状態を取得する
	KeyNew[KEY_ID_SPACE] = CheckHitKey(KEY_INPUT_SPACE);
	KeyNew[KEY_ID_PAUSE] = CheckHitKey(KEY_INPUT_P);
	KeyNew[KEY_ID_IVENT] = CheckHitKey(KEY_INPUT_I);
	KeyNew[KEY_ID_SHOT] = CheckHitKey(KEY_INPUT_LCONTROL);
	KeyNew[KEY_ID_SAVE] = CheckHitKey(KEY_INPUT_S);
	KeyNew[KEY_ID_LOAD] = CheckHitKey(KEY_INPUT_L);
	KeyNew[KEY_ID_UP] = CheckHitKey(KEY_INPUT_UP);
	KeyNew[KEY_ID_RIGHT] = CheckHitKey(KEY_INPUT_RIGHT);
	KeyNew[KEY_ID_DOWN] = CheckHitKey(KEY_INPUT_DOWN);
	KeyNew[KEY_ID_LEFT] = CheckHitKey(KEY_INPUT_LEFT); 
	KeyNew[KEY_ID_FIRE] = CheckHitKey(KEY_INPUT_Z);
	KeyNew[KEY_ID_WATER] = CheckHitKey(KEY_INPUT_X);
	KeyNew[KEY_ID_WIND] = CheckHitKey(KEY_INPUT_C);
	KeyNew[KEY_ID_HEAL] = CheckHitKey(KEY_INPUT_V);
	KeyNew[KEY_ID_ENTER] = CheckHitKey(KEY_INPUT_RETURN);


	for (int keyID = 0; keyID < KEY_ID_MAX; keyID++)
	{
		KeyDownTrigger[keyID] = false;
		KeyUpTrigger[keyID] = false;
		//ダウン時のトリガーの算出
		if (!KeyOld[keyID] && KeyNew[keyID])
		{
			KeyDownTrigger[keyID] = true;
		}
		//アップ時のトリガーの算出
		if (KeyOld[keyID] && !KeyNew[keyID])
		{
			KeyUpTrigger[keyID] = true;
		}
	}


}