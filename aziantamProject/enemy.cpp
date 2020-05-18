#include "DxLib.h"
#include "main.h"
#include "enemy.h"



//-----ºÝ½Ä×¸À
enemy::enemy(ENEMY no, int posX, int posY
	, const char filename[], int max
	, int MaxX, int MaxY, int sizeX, int sizeY): START_POS_X(posX), START_POS_Y(posY)
{
	//-----•Ï”‰Šú‰»
	LoadDivGraph(filename, max, MaxX, MaxY, sizeX, sizeY, enemyImage);

	enemyNo = no;
	enemyPos = { 0,0 };
	enemySpeed = 4;
	enemyFlag = true;
	enemyCount = 0;
	enemyHert = 50;
	
	

}

enemy::~enemy()
{
	DeleteGraph(enemyImage[0], true);
}

void enemy::SystemInit(void)
{
	enemyPos = { START_POS_X,START_POS_Y };
	enemyMov = DIR_DOWN;
}

void enemy::GameInit(void)
{
}

//enemy‘€ì
void enemy::Control(void)
{
}


//•`‰æˆ—
void enemy::GameDraw(void)
{
	if (enemyHert > 0)
	{
		enemyCount++;
		DrawGraph(enemyPos.x, enemyPos.y, enemyImage[enemyMov *4 +((enemyCount / 40) % 4)], true);
	}

}
