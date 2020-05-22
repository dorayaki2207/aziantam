#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "effect.h"
#include "enemy.h"
#include "shot.h"
#include "item.h"
#include "stage.h"

//-----•Ï”
//¼°İŠÖ˜A
SCENE SceneID;
SCENE ScenePreID;	//‰ß‹‚Ì¼°İŠi”[—p
int SceneCounter;



//PAUSE
bool paseFlag;
bool iventFlag;

//WinŠÖ”
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	if (!SystemInit())return -1;

	//-----¹Ş°ÑÙ°Ìß
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//key‚Ìî•ñæ“¾
		KeyCheck();
		//¼°İ¶³İÄØ¾¯Ä
		if (SceneID != ScenePreID)
		{
			ScenePreID = SceneID;
			SceneCounter = 0;
		}
		//-----‰æ–Ê•`‰æˆ—
		ClsDrawScreen();	//‰æ–ÊÁ‹
		//¼°İ‘I‘ğ
		switch (SceneID)
		{
		case SCENE_INIT:
			InitScene();
			break;
		//À²ÄÙ¼°İ
		case SCENE_TITLE:
			TitleScene();
			break;
		//¹Ş°Ñ¼°İ
		case SCENE_GAME:
			GameScene();
			break;
		//¹Ş°Ñµ°ÊŞ°¼°İ
		case SCENE_GAMEOVER:
			GameOverScene();
			break;
		default:
			return -1;
			break;
		}
		SceneCounter++;		
		ScreenFlip();		//— ‰æ–Ê‚ğ•\‰æ–Ê‚ÉuŠÔºËß°
	}
	
	DxLib_End();			//DX×²ÌŞ×Ø‚ÌI—¹ˆ—
	return 0;				//‚±‚ÌÌßÛ¸Ş×Ñ‚ÌI—¹

}
//¼½ÃÑ‚Ì‰Šú‰»
bool SystemInit(void)
{
	//--------¼½ÃÑˆ—
	SetWindowText("Œ–é`O‚Â‚Ì_•ó`");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)return false;
	SetDrawScreen(DX_SCREEN_BACK);
	
	//-----keyî•ñ‚Ì‰Šú‰»
	KeyInit();



	
	//-----ŠeÓ¼Ş­°Ù‚Ì‰Šú‰»
	//“Gmob
	EnemySystemInit();
	//±²ÃÑ
	ItemSystmeInit();
	//-----¸Ş×Ì¨¯¸“o˜^


	//-----•Ï”‚Ì‰Šú‰»
	//¼°İŠÖ˜A
	SceneCounter = 0;
	SceneID = SCENE_INIT;
	ScenePreID = SCENE_MAX;
	//PAUSE
	pauseFlag = false;
	//²ÍŞİÄƒŠ
	iventFlag = false;
	
	
	return true;
}
//‰Šú‰»¼°İ
void InitScene(void)
{
	//-----ŠeµÌŞ¼Şª¸Äˆ—
	EnemyGameInit();				//	“G
	ItemGameInit();					//	±²ÃÑ
	

	//-----¼°İ‘JˆÚ
	SceneID = SCENE_TITLE;
}




/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//À²ÄÙ¼°İ
void TitleScene(void)
{
	//-----¼°İ‘JˆÚ
	if (KeyDownTrigger[KEY_ID_SPACE]) SceneID = SCENE_GAME;

	//-----•`‰æ
	TitleDraw();
}
//À²ÄÙ‚Ì•`‰æ
void TitleDraw(void)
{
	//-----•`‰æˆ—

	//-----î•ñˆ—
	DrawFormatString(0, 0, 0xFFFFFF, "Title:%d", SceneCounter);

}



///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//¹Ş°Ñ¼°İ
void GameScene(void)
{
	//¼°İ‘JˆÚ
	if (KeyDownTrigger[KEY_ID_SPACE]) SceneID = SCENE_GAMEOVER;



	//-----²ÍŞİÄØ‹@”\
	//·°ˆ—
	if (KeyDownTrigger[KEY_ID_IVENT]) iventFlag = !iventFlag;
	//Ì×¸Şˆ—
	if (iventFlag)
	{
		SetDrawBright(128, 128, 128);
		pauseFlag = false;
	}

	//-----PAUSE‹@”\
	if (KeyDownTrigger[KEY_ID_PAUSE]) pauseFlag = !pauseFlag;
	if (pauseFlag)
	{
		SetDrawBright(128, 128, 128);
		iventFlag = false;
	}

	//’Êí‘€ì
	if(!iventFlag && !pauseFlag)
	{
		//Šeí‹@”\
		//-----ŠeµÌŞ¼Şª¸Ä‘€ì
		EnemyControl();			//	“G
		ItemControl();			//	±²ÃÑ
	}

	
	//-----•`‰æ
	GameDraw(); 
}


//¹Ş°Ñ‚Ì•`‰æ
void GameDraw(void)
{

	//-----ŠeµÌŞ¼Şª¸Ä•`‰æˆ—
	EnemyGameDraw();			//“G
	ItemGameDraw();				//±²ÃÑ
	//-----²ÍŞİÄØŠÖ˜A
	if (iventFlag)
	{
		SetDrawBright(255, 255, 255);
		DrawBox(100, 100, 700, 600, 0xFFFFFF, true);
		//ŒäD
		ItemI_Draw();

	}
	//----PAUSEŠÖ˜A
	if (pauseFlag)
	{
		SetDrawBright(255, 255, 255);
		DrawBox(100, 100, 700, 600, 0x222222, true);
	}
	
	//-----î•ñˆ—
	DrawFormatString(0, 0, 0xFFFFFF, "Game:%d", SceneCounter);

}





//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//¹Ş°Ñµ°ÊŞ°¼°İ
void GameOverScene(void)
{
	if (KeyDownTrigger[KEY_ID_SPACE]) SceneID = SCENE_INIT;


	GameOverDraw();
}


//¹Ş°Ñµ°ÊŞ°‚Ì•`‰æ
void GameOverDraw(void)
{
	//-----•`‰æˆ—

	//-----î•ñˆ—
	DrawFormatString(0, 0, 0xFFFFFF, "GameOver:%d", SceneCounter);


}
