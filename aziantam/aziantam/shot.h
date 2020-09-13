//#pragma once

//-----’è”’è‹`
#define SHOT_ANI		46		//’e‚Ì±ÆÒ°¼®İ”
#define SHOT_LIFE_MAX	46		//’e‚Ì‘Ì—Í
#define SHOT_MAX		20		//’e‚Ì‘”


//-----ŠÖ”ÌßÛÄÀ²ÌßéŒ¾
void ShotSystemInit(void);									//’eî•ñ‚Ì‰Šú‰»
void ShotGameInit(void);
void ShotControl(XY pPos);									//’e‚Ì‘€ì
void ShotGameDraw(void);										//’e‚Ì•`‰æˆ—
void CreateShot(XY pPos, DIR pDir, MAGIC_TYPE ptype);		//’e‚ğ¶¬‚·‚é
void DeleteShot(int index);									//’e‚ğÁ–Å‚³‚¹‚é

//-----¸ŞÛ°ÊŞÙ‰»
extern CHARACTER shot[SHOT_MAX];