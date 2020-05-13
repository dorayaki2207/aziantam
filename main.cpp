#include "DxLib.h"
#include "main.h"

//•Ï”
SCENE SceneID;
SCENE ScenePreID;	//‰ß‹‚Ì¼°İŠi”[—p
int SceneCounter;

//¸×½‚©‚ç²İ½Àİ½‚ğ¶¬


//WinŠÖ”
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	if (!SystemInit())
	{
		return -1;
	}
	//°°°°°°°¹Ş°ÑÙ°Ìß
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//¼°İ¶³İÄØ¾¯Ä
		if (SceneID != ScenePreID)
		{
			ScenePreID = SceneID;
			SceneCounter = 0;
		}
		//°°°°‰æ–Ê•`‰æˆ—
		ClsDrawScreen();	//‰æ–ÊÁ‹
		//¼°İ‘I‘ğ
		switch (systemScene)
		{
		case SCENE_INIT:
			InitScene();
			break;
		case SCENE_TITLE:
			TitleScene();
			break;
		case SCENE_GAME:
			GameScene();
			break;
		case SCENE_GAMEOVER:
			GameOverScene();
			break;
		default:
			return -1;
			break;
		}
		SceneCounter++;
		ScreenFlip();		//@— ‰æ–Ê‚ğ•\‰æ–Ê‚ÉuŠÔºËß°
	}
	//²İ½Àİ½‚Ì‰ğ•ú


	DxLib_End();			// DX×²ÌŞ×Ø‚ÌI—¹ˆ—
	return 0;				// ‚±‚ÌÌßÛ¸Ş×Ñ‚ÌI—¹

}
//¼½ÃÑ‚Ì‰Šú‰»
bool SystemInit(void)
{
	//--------¼½ÃÑˆ—
	SetWindowText("Œ–é");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)return false;
	SetDrawScreen(DX_SCREEN_BACK);
	
	//²İ½Àİ½‚Ì¶¬

	//¸Ş×Ì¨¯¸“o˜^

	//•Ï”‚Ì‰Šú‰»
	SceneCounter = 0;
	SceneID = SCENE_ID_INIT;
	ScenePreID = SCENE_ID_MAX;

	return true;
}
//‰Šú‰»¼°İ
void InitScene(void)
{
	
}
//À²ÄÙ¼°İ
void TitleScene(void)
{
	TitleDraw();
}
//À²ÄÙ‚Ì•`‰æ
void TitleDraw(void)
{

}

//¹Ş°Ñ¼°İ
void GameScene(void)
{
	GameDraw();
}
//¹Ş°Ñ‚Ì•`‰æ
void GameDraw(void)
{

}
//¹Ş°Ñµ°ÊŞ°¼°İ
void GameOverScene(void)
{
	GameOverDraw();
}
//¹Ş°Ñµ°ÊŞ°‚Ì•`‰æ
void GameOverDraw(void)
{

}
