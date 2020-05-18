#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "effect.h"
#include "enemy.h"
#include "shot.h"
#include "item.h"
#include "stage.h"

//•Ï”
SCENE SceneID;
SCENE ScenePreID;	//‰ß‹‚Ì¼°İŠi”[—p
int SceneCounter;

//¸×½‚©‚ç²İ½Àİ½‚ğ¶¬
enemy* enemyI;
enemy* enemyY;
enemy* enemyA;

//WinŠÖ”
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	if (!SystemInit())return -1;

	//-----¹Ş°ÑÙ°Ìß
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
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
	SetWindowText("Œ–é`O‚Â‚Ì_•ó`");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)return false;
	SetDrawScreen(DX_SCREEN_BACK);
	
	//-----²İ½Àİ½‚Ì¶¬
	enemyI = new enemy(ENEMY_I_MOB
		, 100, 100
		, "char/—dŒÏ.png", 16
		,4, 4
		,32, 32
	);
	enemyY = new enemy(ENEMY_Y_MOB
		, 150, 100
		, "char/wind_mob_enemy1.png", 16
		, 4, 4
		, 32, 32
	);
	enemyA = new enemy(ENEMY_A_MOB
		, 200, 100
		, "char/umi0.png", 16
		, 4, 4
		, 32, 32
	);


	//-----ŠeÓ¼Ş­°Ù‚Ì‰Šú‰»
	enemyI->SystemInit();	//Î‹´’S“–MOB
	enemyY->SystemInit();	//R–{’S“–MOB
	enemyA->SystemInit();	//r–Ø’S“–MOB

	//¸Ş×Ì¨¯¸“o˜^

	//•Ï”‚Ì‰Šú‰»
	SceneCounter = 0;
	SceneID = SCENE_INIT;
	ScenePreID = SCENE_MAX;

	return true;
}
//‰Šú‰»¼°İ
void InitScene(void)
{
	//-----ŠeµÌŞ¼Şª¸Äˆ—
	enemyI->GameInit();		//Î‹´’S“–MOB	
	enemyY->GameInit();		//R–{’S“–MOB	
	enemyA->GameInit();		//r–Ø’S“–MOB	

	//-----¼°İ‘JˆÚ
	SceneID = SCENE_TITLE;
}




/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//À²ÄÙ¼°İ
void TitleScene(void)
{
	//-----¼°İ‘JˆÚ
	SceneID = SCENE_GAME;

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
	//-----ŠeµÌŞ¼Şª¸Ä‘€ì
	enemyI->Control();		//Î‹´’S“–MOB
	enemyY->Control();		//R–{’S“–MOB	
	enemyA->Control();		//r–Ø’S“–MOB


	//-----•`‰æ
	GameDraw();
}


//¹Ş°Ñ‚Ì•`‰æ
void GameDraw(void)
{

	//-----•`‰æˆ—
	enemyI->GameDraw();		//Î‹´’S“–MOB
	enemyY->GameDraw();		//R–{’S“–MOB
	enemyA->GameDraw();		//r–Ø’S“–MOB
	//-----î•ñˆ—
	DrawFormatString(0, 0, 0xFFFFFF, "Game:%d", SceneCounter);

}





//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//¹Ş°Ñµ°ÊŞ°¼°İ
void GameOverScene(void)
{
	GameOverDraw();
}


//¹Ş°Ñµ°ÊŞ°‚Ì•`‰æ
void GameOverDraw(void)
{
	//-----•`‰æˆ—

	//-----î•ñˆ—
	DrawFormatString(0, 0, 0xFFFFFF, "GameOver:%d", SceneCounter);


}
