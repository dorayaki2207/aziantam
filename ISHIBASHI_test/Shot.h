//#pragma once

//-----’è”’è‹`
#define SHOT_ANI		46				//@’e‚Ì±ÆÒ°¼®Ý”
#define SHOT_LIFE_MAX	46


//-----—ñ‹“Œ^
enum SHOT_TYPE
{
	SHOT_TYPE_FIRE,				//	‰Î‚ÌŒäŽD
	SHOT_TYPE_WATER,			//	…‚ÌŒäŽD
	SHOT_TYPE_WIND,				//	•—‚ÌŒäŽD
	SHOT_TYPE_HEAL,				//	‰ñ•œ‚ÌŒäŽD
	SHOT_TYPE_MAX
};


//-----ŠÖ”ÌßÛÄÀ²ÌßéŒ¾
void ShotSystemInit(void);				//@’eî•ñ‚Ì‰Šú‰»	
void ShotGameInit(void);
void ShotControl(void);					//	’e‚Ì‘€ì
void ShotGameDraw(void);				//	’e‚Ì•`‰æˆ—
void CreateShot(XY pPos, DIR pDir, SHOT_TYPE ptype/*, ITEM_TYPE_F itype*/);
void DeleteShot(int index);
void ShotAniCnt(SHOT_TYPE type);

//-----¸ÞÛ°ÊÞÙ‰»
extern CHARACTER shot[];