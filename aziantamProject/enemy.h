
class Enemy
{
public:
	//-----���ް�ϐ�

private:
	const int START_POS_X;
	const int START_POS_Y;

	int enemyImage[16];
	XY  enemyPos;
	int enemySpeed;
	DIR enemyMov;
	int enemyCount;
	int enemyHert;
	bool enemyFlag;
	ENEMY enemyNo;
//	KEY_LIST keyID;

public:
	Enemy(ENEMY no, int posX, int posY, const char filename[],int max, int MaxX,int MaxY,int sizeX, int sizeY);
	~Enemy();

	//-----���ފ֐�
	void SystemInit(void);
	void GameInit(void);
	void Control(void);
	void GameDraw(void);


};
//#pragma once




