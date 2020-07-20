//#pragma once

//-----’è”’è‹`
#define SHOT_ANI		46				//@’e‚Ì±ÆÒ°¼®İ”
#define SHOT_LIFE_MAX	46
#define SHOT_MAX		20




//-----ŠÖ”ÌßÛÄÀ²ÌßéŒ¾
void ShotSystemInit(void);					//@’eî•ñ‚Ì‰Šú‰»	
void ShotGameInit(void);
void ShotControl(XY pPos);					//	’e‚Ì‘€ì
void ShotGameDraw(void);				//	’e‚Ì•`‰æˆ—
void CreateShot(XY pPos, DIR pDir, MAGIC_TYPE ptype);
void DeleteShot(int index);

//-----¸ŞÛ°ÊŞÙ‰»
extern CHARACTER shot[];