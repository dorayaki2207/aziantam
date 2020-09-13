#include <DxLib.h>
#include "main.h"
#include "title.h"
#include "keycheck.h"


//ﾀｲﾄﾙｼｰﾝ関連
int titleMsgImage;
int rogoImage;
int bgImage;
//int msgImage[MSG_MAX];
//bool msgCheck[MSG_MAX];
//bool msgFlag;
//int msgCnt;
int titleCounter;

//int msgID;
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

void TitleSystemInit()
{

	//-----ｸﾞﾗﾌｨｯｸ登録
	titleMsgImage = LoadGraph("item/title.png");
	rogoImage = LoadGraph("item/rogo_.png");
	bgImage = LoadGraph("item/bg.png");
//	LoadDivGraph(("item/msg.png"), MSG_MAX, 1, MSG_MAX, 400, 100, msgImage);

	//-----初期化処理

	//msgFlag = false;
	//for (int i = 0; i < MSG_MAX; i++)
	//{
	//	msgCheck[i] = false;
	//}
	//msgCnt = 0;
	titleCounter = 0;
	//msgID = 0;
}

//ﾀｲﾄﾙｼｰﾝ
void TitleScene(void)
{
	titleCounter++;

	//-----ｼｰﾝ遷移
	if (KeyDownTrigger[KEY_ID_SPACE])
	{
		SceneID = SCENE_GAME;
	}
	//if (msgType == MSG_START)
	//{
	//	//はじめからする、選択でｹﾞｰﾑｼｰﾝへ
	//	if (KeyDownTrigger[KEY_ID_SPACE])
	//	{
	//		SceneID = SCENE_GAME;
	//	}
	//}
	//else if (msgType == MSG_LOAD)
	//{
	//	//つづきからする、一時的にﾒｯｾｰｼﾞ描画
	//	if (KeyDownTrigger[KEY_ID_SPACE]) msgFlag = true;
	//	if ((msgCnt > 250) || KeyDownTrigger[KEY_ID_ENTER])
	//	{
	//		msgCnt = 0;
	//		msgFlag = false;
	//	}
	//}



	//-----ﾀｲﾄﾙ操作
	TitleControl();


	//-----描画
	TitleDraw();
}




//ﾀｲﾄﾙ操作
void TitleControl()
{
	////ｾﾚｸﾄ
	//for (int i = 0; i < MSG_MAX; i++)
	//{
	//	if (!msgCheck[i])
	//	{
	//		switch (msgType)
	//		{
	//		case MSG_START:
	//			msgCheck[MSG_START] = true;
	//			msgCheck[MSG_LOAD] = false;
	//			break;
	//		case MSG_LOAD:
	//			msgCheck[MSG_LOAD] = true;
	//			msgCheck[MSG_START] = false;
	//			break;
	//		case MSG_MAX:
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//}

	//	if (KeyDownTrigger[KEY_ID_UP])
	//	{
	//		msgID--;
	//		if (msgID < 0) msgID = MSG_MAX - 1;
	//		//	msgType = MSG_START;
	//	}
	//	
	//	if (KeyDownTrigger[KEY_ID_DOWN])
	//	{	
	//		msgID++;
	//		if (msgID > MSG_MAX -1) msgID = 0;
	//	}

	//	if (msgID == 0)
	//	{
	//		msgType = MSG_START;
	//	}
	//	else if (msgID == 1)
	//	{
	//		msgType = MSG_LOAD;
	//	}
	//
}


//ﾀｲﾄﾙの描画
void TitleDraw(void)
{
	//-----描画処理
	DrawGraph(0, 0, bgImage, true);								//背景
	DrawGraph((SCREEN_SIZE_X - 400) / 2, 10, rogoImage, true);	//ﾛｺﾞ
//	DrawGraph((SCREEN_SIZE_X - 600) / 2, 450, titleMsgImage, true);

	if ((titleCounter / 30) % 2 == 0)
	{
		DrawGraph((SCREEN_SIZE_X - 600) / 2, 450, titleMsgImage, true);
	}


	//for (int i = 0; i < MSG_MAX; i++)							//ﾒｯｾｰｼﾞ
	//{
		//選択時
	//	if (msgCheck[i])
	//	{
	//		if (msgType == MSG_START)
	//		{
	//			if ((titleCounter / 30) % 2 == 0)
	//			{
	//				DrawGraph((SCREEN_SIZE_X - 400) / 2, 400, msgImage[MSG_START], true);
	//			}
	//			
	//		}
	//		else if (msgType == MSG_LOAD)
	//		{
	//			if ((titleCounter / 30) % 2 == 0)
	//			{
	//				DrawGraph((SCREEN_SIZE_X - 400) / 2, 500, msgImage[MSG_LOAD], true);

	//			}
	//		}
	//	}
	//	//未選択時
	//	else
	//	{
	//		DrawGraph((SCREEN_SIZE_X - 400) / 2, 400 + 100 * i, msgImage[i], true);
	//	}
	//}

	////つづきからする、を選択した時のﾒｯｾｰｼﾞ
	//if (msgFlag)
	//{
	//	msgCnt++;
	//	DrawBox(250, 200, 550, 450, 0xFFFFFF, true);
	//	SetFontSize(16);
	//	DrawString(295, 240,
	//		"　　 　　※※※\nセーブデータが存在しません\n\n　　＜はじめかする＞\n\n  を選び始めてください",
	//		0x000000);
	//	SetFontSize(12);
	//	DrawString(255, 410, "※この画面はENTER KEY\n　又は、時間経過で閉じます", 0x000000);
	//}

	//-----情報処理
//	DrawFormatString(0, 0, 0xFFFFFF, "Title:%d", titleCounter);

}

