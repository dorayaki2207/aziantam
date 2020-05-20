//月夜
//stage.cpp
//2020.05.20

#include "DxLib.h"
#include "main.h"
#include "stage.h"
#include "player.h"
#include "enemy.h"

//変数
int chipImage[81];
int stageOffset;

//ﾏｯﾌﾟの配列

//ﾀﾞﾝｼﾞｮﾝ
//村のﾏｯﾌﾟ
int stage[MAP_Y][MAP_X] = {
{58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58},
{58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58},
{6,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,8},
{6,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,8},
{6,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,8},

{6,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,8},
{15,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,17},
{15,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,17},
{15,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,17},
{15,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,17},

{15,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,17},
{15,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,17},
{15,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,17},
{15,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,17},
{24,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,26},

{24,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,26},
{24,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,26},
{24,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,26},
{24,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,26},
{24,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,58, 58,58,58,58,26},
};

//紅鬼のﾏｯﾌﾟ
int stageI[MAPI_Y][MAPI_X] = {

}

//天狗のﾏｯﾌﾟ
int stageY[MAPY_Y][MAPY_X] = {

}

//河童のﾏｯﾌﾟ
int stageA[MAPA_Y][MAPA_X] = {

}

XY mapPos;					//ﾏｯﾌﾟのｵﾌｾｯﾄ
STAGE_ID stageID;			//ｽﾃｰｼﾞID
XY mapSize;					//ﾏｯﾌﾟのｻｲｽﾞ

//ｽﾃｰｼﾞ情報の初期化
void StageSystemInit(void)
{
	//グラフィックの登録
	//ﾏｯﾌﾟﾁｯﾌﾟの画像を読み込む
	LoadDivGraph("char/map.char"
		, 81, 9, 9
		, CHIP_SIZE_X, CHIP_SIZE_Y
		, chipImage);

	mapPos.x = 0;
	mapPos.y = 0;

	stageOffset = 0;

	//ﾏｯﾌﾟ作成ﾃﾞｰﾀ
	stageID = STAGE_ID_START;
	SetMapData(STAGE_ID_START);
}

//ｽﾃｰｼﾞ情報のｹﾞｰﾑ初期化
void StageGameInit(void)
{
	mapPos.x = 0;
	mapPos.y = 0;

	stageOffset = 0;

	//ﾏｯﾌﾟ作成ﾃﾞｰﾀ
	stageID = STAGE_ID_START;
	SetMapData(STAGE_ID_START);
}

//ﾋﾟｸｾﾙ座標系ｶﾗﾏｯﾌﾟ配列座標系ﾆ変換する
XY Pos2Index(XY pos)
{
	XY tmp;

	tmp.x = pos.x / CHIP_SIZE_X;		//posのx座標を変換;
	tmp.y = pos.y / CHIP_SIZE_Y;		//posのy座標を変換;

	//変換した値を返す
	return tmp;
}

//指定した座標が通過可能かを返す true:通過可能
bool IsPass(XY pos)
{
	XY indexPos = Pos2Index(pos);

	switch (map[indexPos.y][indexPos.x])
	{

		//ﾓﾘ
	case 6:
	case 7:
	case 8:
	case 15:
	case 16:
	case 17:
	case 24:
	case 25:
	case 26:
		//ｲｴ
	case 60:
	case 61:
	case 69:
	case 70:
		//ｻｲﾀﾞﾝ
	case 62:
	case 71:
		//ﾔｼﾞﾙｼ
	case 68:
	case 77:
		//ｸｻ
	case 75:
		//ｲﾜ
	case 76:
		//ｼﾞﾝｼﾞｬ
	case 78:
	case 79:
	case 80:

	case 66:
	case 67:

		return false;
		break;

	default:
		break;.
	}
	return true;
}

//指定した座標が特別にｲﾍﾞﾝﾄｦ起こすかを確認する 戻り値:ｲﾍﾞﾝﾄID
EVENT_ID GetEvent(XY pos)
{
	XY indexPos;

	indexPos = Pos2Index(pos);
	switch (map[indexPos.y][indexPos.x])
	{
		//火
	case 27:
	case 28:
	case 29:
	case 36:
	case 37:
	case 38:
	case 45:
	case 46:
	case 47:
		//ｲﾍﾞﾝﾄの発生場所
		return EVENT_ID_HONO;
		break;

		//水
	case 30:
	case 31:
	case 32:
	case 39:
	case 40:
	case 41:
	case 48:
	case 49:
	case 50:
		//ｲﾍﾞﾝﾄの発生場所
		return EVENT_ID_MIZU;
		break;
	default:
		break;
	}
	//ｲﾍﾞﾝﾄなし
	return EVENT_ID_NON;
}

//ｽﾃｰｼﾞﾃﾞｰﾀﾞをﾏｯﾌﾟ配列にｺﾋﾟｰする
void SetMapData(STAGE_ID stage_ID)
{
	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			map[y][x] = 0;
		}
	}

	if (stage_ID == STAGE_ID_START)
	{
		mapSize.x = MAP_X;
		mapSize.y = MAP_Y;

		for (int y = 0; y < mapSize.y; y++)
		{
			for (int x = 0; x < mapSize.x; x++)
			{
				map[y][x] = stage[y][x];
			}
		}
	}
	else if (stage_ID == STAGE_ID_MAX)//ｽﾃｰｼﾞID追加//
	{
		mapSize.x = MAP2_X;
		mapSize.y = MAP2_Y;

		for (int y = 0; y < mapSize.y; y++)
		{
			for (int x = 0; x < mapSize.x; x++)
			{
				map[y][x] = stageI[y][x];
			}
		}
	}
}

//ｹﾞｰﾑ画面の表示処理
void StageGameDraw(void)
{
	for (int y = 0; t < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			DrawGraph(x*CHIP_SIZE_X + -mapPos.x
				, y*CHIP_SIZE_Y + -mapPos.y
				, chipImage[map[y][x]], true);
		}
	}
}