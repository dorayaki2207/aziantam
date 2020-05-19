#include "DxLib.h"
#include "main.h"
#include "item.h"



//-----�ݽ�׸�
Item::Item(ITEM no, int posX, int posY, const char filename[],int max, int MaxX, int MaxY, int sizeX, int sizeY)
{
	//-----�ϐ�������
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

//-----������
void Item::SystemInit(void)
{
	itemPos = { 20,20 };

}


//-----�Q�[����������
void Item::GameInit(void)
{

}

//-----���쏈��
void Item::Control(void)
{
}

//-----�`�揈��
void Item::GameDraw(ITEM no)
{
	if (itemHert > 0)
	{
		DrawGraph(itemPos.x, itemPos.y, itemImage[no], true);
	}

}
