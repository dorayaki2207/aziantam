
//月夜
//stage.h
//2020.05.13

//#pragma once

//定数
#define MAP_X 25				//マップチップ画像の横サイズ
#define MAP_Y 25				//マップチップ画像の縦サイズ
#define MAP_X 25
#define MAP_Y 25
#define MAP_CHIP_X 9
#define MAP_CHIP_Y 9

//イベントID
enum STAGE_ID {
	STAGE_ID_START,
	
	STAGE_ID_MAX
};

//イベント情報
enum EVENT_ID {
	EVENT_ID_NON,
	
	EVENT_ID_MAX
};

//extern宣言
//extern int map[MAP_Y][MAP_X];
extern XY mapPos;
extern STAGE_ID stageID;		//ステージID

//プロトタイプ宣言
void StageSystemInit(void);			//ステージ情報の初期化
void StageGameInit(void);			//ステージ情報のゲーム初期化
void StageGameDraw(void);			//ゲーム画面の表示処理

XY Pos2Index(XY pos);				//ピクセル座標系からマップ配列座標系に変換する。

bool IsPass(XY pos);				//指定した座標が通過可能かを返す　true:通過できる

EVENT_ID GetEvent(XY pos);			//指定した座標が特別にイベントを起こすかを確認する　戻り値：イベントID

void SetMapData(STAGE_ID stageID);	//ステージデータをマップ配列にコピーする
