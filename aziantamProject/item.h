//#pragma once



class Item
{
private:
	//-----“› ﬁ∞ïœêî
	int itemImage[ITEM_MAX];
	XY itemPos;
	int itemCount;
	int itemHert;
	bool itemFlag;
	ITEM itemNo;

public:
	Item(ITEM no, int posX, int posY, const char filename[], int max, int MaxX, int MaxY, int sizeX, int sizeY);
	~Item();

	//-----“› ﬁ∞ä÷êî
	void SystemInit(void);
	void GameInit(void);
	void Control(void);
	void GameDraw(ITEM no);

};