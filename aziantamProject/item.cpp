#include "DxLib.h"
#include "main.h"
#include "item.h"



//-----ºÝ½Ä×¸À
Item::Item(ITEM no, int posX, int posY, const char filename[],int max, int MaxX, int MaxY, int sizeX, int sizeY)
{
	//-----•Ï”‰Šú‰»
	LoadDivGraph(filename, max, MaxX, MaxY, sizeX, sizeY, itemImage);

	itemNo = no;
	itemPos = { 0,0 };
	itemFlag = true;
	itemCount = 0;
	itemHert = 10;

}


//-----
Item::~Item()
{
	DeleteGraph(itemImage[0], true);
}

//-----‰Šú‰»
void Item::SystemInit(void)
{
	itemPos = { 20,20 };

}


//-----ƒQ[ƒ€“à‰Šú‰»
void Item::GameInit(void)
{

}

//-----‘€ìˆ—
void Item::Control(void)
{
}

//-----•`‰æˆ—
void Item::GameDraw(ITEM no)
{
	if (itemHert > 0)
	{
		DrawGraph(itemPos.x, itemPos.y, itemImage[no], true);
	}

}
