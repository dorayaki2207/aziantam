////	ﾄﾞﾛｯﾌﾟｱｲﾃﾑは敵が倒されたらその場に出現
////	ｱｲﾃﾑHPを使って敵を倒して一定時間内に取らないと消えるようにする 
////	敵の当たり判定に　狐だと火の御札、一反木綿だと風の御札、海坊主だと水の御札
////	回復の御札は全部の敵MOBから確率で出現するようにする
////	敵が倒されたら　ｱｲﾃﾑHPを減らしていく
#include <DxLib.h>
#include "main.h"
#include "stage.h"
#include "item.h"


//-----外部変数宣言
//ｱｲﾃﾑ関連
//御札
CHARACTER itemF[ITEM_MAX];					//	ﾄﾞﾛｯﾌﾟｱｲﾃﾑ変数格納用
CHARACTER itemFmaster[MAGIC_TYPE_MAX];
int itemFImage[MAGIC_TYPE_MAX];				//	ﾄﾞﾛｯﾌﾟｱｲﾃﾑ用画像（F：札の頭文字
int itemFIImage[MAGIC_TYPE_MAX];			//	ｲﾝﾍﾞﾝﾄﾘ用画像（F：札の頭文字，I：ｲﾝﾍﾞﾝﾄﾘの頭文字
int itemFBImage[MAGIC_TYPE_MAX];			//	ﾎﾞｽﾊﾞﾄﾙ用画像（F：札の頭文字,　B：ﾊﾞﾄﾙの頭文字
bool itemFBFlag;							//	表示,非表示用
//三種の神器
CHARACTER itemB[ITEM_TYPE_B_MAX];
int itemBImage[ITEM_TYPE_B_MAX];			//	神器の画像（B：武器の頭文字



//-----ｱｲﾃﾑ情報の初期化
void ItemSystmeInit(void)
{
	//-----変数の初期化
	//御札（ﾄﾞﾛｯﾌﾟ用
	itemFmaster[MAGIC_TYPE_FIRE].charType = MAGIC_TYPE_FIRE;				//	御札の種類	：	火
	itemFmaster[MAGIC_TYPE_WATER].charType = MAGIC_TYPE_WATER;			//	御札の種類	：	水
	itemFmaster[MAGIC_TYPE_WIND].charType = MAGIC_TYPE_WIND;			//	御札の種類	：	風
	itemFmaster[MAGIC_TYPE_HEAL].charType = MAGIC_TYPE_HEAL;	//	御札の種類	：	回復
	//御札まとめて処理
	for (int i = 0; i < MAGIC_TYPE_MAX; i++)
	{
		itemFmaster[i].pos = { 0,0 };																//　御札の地図上の座標
		itemFmaster[i].size = { 20,20 };															//	御札の画像ｻｲｽﾞ
		itemFmaster[i].offsetSize = { itemFmaster[i].size.x / 2,itemFmaster[i].size.y / 2 };		//　御札のｵﾌｾｯﾄ
		itemFmaster[i].point = 12;																	//	御札の枚数
		itemFmaster[i].lifeMax = 200;																//	御札の体力最大値（表示時間）
		itemFmaster[i].life = itemFmaster[i].lifeMax;												//	御札の体力
		itemFmaster[i].hitFlag = false;
	}

	//御札（ﾎﾞｽﾊﾞﾄﾙ用
	itemFBFlag = false;												//	初期：非表示

	//三種の神器
	itemB[ITEM_TYPE_KEN].charType = ITEM_TYPE_KEN;					//	三種の神器　：　剣
	itemB[ITEM_TYPE_KAGAMI].charType = ITEM_TYPE_KAGAMI;			//	三種の神器　：　鏡
	itemB[ITEM_TYPE_MAGATAMA].charType = ITEM_TYPE_MAGATAMA;		//	三種の神器　：　勾玉
	//三種の神器まとめて処理
	for (int i = 0; i < ITEM_TYPE_B_MAX; i++)
	{
		itemB[i].size = { 20,20 };																	//	三種の神器の画像ｻｲｽﾞ
		itemB[i].offsetSize = { itemB[i].size.x / 2,itemB[i].size.y / 2 };							//　三種の神器のｵﾌｾｯﾄ

	}


	//-----ｸﾞﾗﾌｨｯｸの登録
	//御札(ﾄﾞﾛｯﾌﾟ用
	LoadDivGraph("item/fudaD.png", 4, 4, 1
		, ITEM_M_SIZE, ITEM_M_SIZE, itemFImage);
	//御札（ｲﾍﾞﾝﾄﾘ用
	LoadDivGraph("item/fudaI.png", 4, 4, 1
		, ITEM_M_SIZE, ITEM_M_SIZE, itemFIImage);
	//御札（ﾎﾞｽﾊﾞﾄﾙ用
	LoadDivGraph("item/fuda_Big.png", 4, 4, 1
		, ITEM_B_SIZE, ITEM_B_SIZE, itemFBImage);
	//三種の神器
	LoadDivGraph("item/zingi20.png", 3, 3, 1
		, ITEM_M_SIZE, ITEM_M_SIZE, itemBImage);
	}

void ItemGameInit(void)
{
	//御札（ﾄﾞﾛｯﾌﾟ用
	for (int type = 0; type < MAGIC_TYPE_MAX;type++)
	{ 
		for (int i = 0; i < ITEM_MAX; i++)
		{

			itemF[i] = itemFmaster[type];
			itemF[i].life = 0;
		}
	}
	//三種の神器
	for (int i = 0; i < ITEM_TYPE_B_MAX; i++)
	{
		itemB[i].pos = { 50,120 };									//　三種の神器の地図上の座標
		itemB[i].lifeMax = 20;										//	三種の神器の体力最大値（表示時間）
		itemB[i].life = itemB[i].lifeMax;							//	三種の神器の体力
	}



}

void ItemDropControl(void)
{
	for (int i = 0; i < ITEM_MAX; i++)
	{
		//撃ってる弾を探す
		if (itemF[i].life > 0)
		{
			//寿命を減らす(射程距離)
			itemF[i].life--;
		}
	}
}

bool ItemMobControl(MAGIC_TYPE type)
{
	//御札が一枚以上ある場合、処理可能
	if (itemF[type].point > 0)
	{
		itemF[type].point--;
		return true;
	}
	return false;
}


void ItemGameDraw(void)
{
	//-----描画処理
	//御札（ﾄﾞﾛｯﾌﾟ用
	for (int i = 0; i < ITEM_MAX; i++)
	{
		//生きてる御札のみ表示
		if (itemF[i].life > 0)
		{
			//-----画像描画
			DrawGraph(itemF[i].pos.x - itemF[i].offsetSize.x + mapPos.x
				, itemF[i].pos.y - itemF[i].offsetSize.y + mapPos.y
				, itemFImage[itemF[i].charType]
				, true);
		}
	}
	//三種の神器
	//for (int i = 0; i < ITEM_TYPE_B_MAX; i++)
	//{
	//	if (itemB[i].life > 0)
	//	{
	//		DrawGraph((itemB[i].pos.x - itemB[i].offsetSize.x) * i
	//			, itemB[i].pos.y - itemB[i].offsetSize.y
	//			, itemBImage[itemB[i].charType]
	//			, true);

	//		DrawBox((itemB[i].pos.x - itemB[i].offsetSize.x) * i
	//			, itemB[i].pos.y - itemB[i].offsetSize.y
	//			, (itemB[i].pos.x - itemB[i].offsetSize.x) * i + itemB[i].size.x
	//			, itemB[i].pos.y - itemB[i].offsetSize.y + itemB[i].size.y
	//			, 0xFF00FF, false);

	//	}
	//}
}
//-----ｲﾝﾍﾞﾝﾄﾘ用描画
void ItemI_Draw(void)
{
	//火の御札
	DrawGraph(430, 250, itemFIImage[MAGIC_TYPE_FIRE], true);
	DrawFormatString(480, 254, 0xFF22FF, "×", true);
	DrawFormatString(530, 253, 0xFF22FF, "%d", itemF[MAGIC_TYPE_FIRE].point);
	DrawFormatString(560, 254, 0xFF22FF, "枚", true);
	//水の御札
	DrawGraph(430, 300, itemFIImage[MAGIC_TYPE_WATER], true);
	DrawFormatString(480, 304, 0xFF22FF, "×", true);
	DrawFormatString(530, 303, 0xFF22FF, "%d", itemF[MAGIC_TYPE_WATER].point);
	DrawFormatString(560, 304, 0xFF22FF, "枚", true);
	//風の御札
	DrawGraph(430, 350, itemFIImage[MAGIC_TYPE_WIND], true);
	DrawFormatString(480, 354, 0xFF22FF, "×", true);
	DrawFormatString(530, 353, 0xFF22FF, "%d", itemF[MAGIC_TYPE_WIND].point);
	DrawFormatString(560, 354, 0xFF22FF, "枚", true);
	//回復の御札
	DrawGraph(430, 420, itemFIImage[MAGIC_TYPE_HEAL], true);
	DrawFormatString(480, 424, 0xFF22FF, "×", true);
	DrawFormatString(530, 423, 0xFF22FF, "%d", itemF[MAGIC_TYPE_HEAL].point);
	DrawFormatString(560, 424, 0xFF22FF, "枚", true);
}

//-----弾と敵の当たり判定　(true : あたり, false : はずれ)
bool ItemHitCheck(XY sPos, int sSize)
{
	int point = GetRand(2) + 1;
	//全ての敵に当たり判定を実施する
	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (itemF[i].life > 0)
		{
			if (((itemF[i].pos.x - itemF[i].size.x / 2) < (sPos.x + sSize / 2))
				&& ((itemF[i].pos.x + itemF[i].size.x / 2) > (sPos.x - sSize / 2))
				&& ((itemF[i].pos.y - itemF[i].size.y / 2) < (sPos.y + sSize / 2))
				&& ((itemF[i].pos.y + itemF[i].size.y / 2) > (sPos.y - sSize / 2)))
			{
				//ｱｲﾃﾑを拾った時だけﾎﾟｲﾝﾄ加算
				//御札に触れたら加算
				if (itemF[i].charType == MAGIC_TYPE_FIRE)
				{
					itemF[i].point += point;
					itemF[i].hitFlag = true;
				}
				if (itemF[i].charType == MAGIC_TYPE_WATER)
				{
					itemF[i].point += point;
					itemF[i].hitFlag = true;
				}
				if (itemF[i].charType == MAGIC_TYPE_WIND)
				{
					itemF[i].point += point;
					itemF[i].hitFlag = true;
				}
				if (itemF[i].charType == MAGIC_TYPE_HEAL)
				{
					itemF[i].point += point;
					itemF[i].hitFlag = true;
				}
				return true;
			}
		}
	}
	//弾が外れた時
	return false;
}


//-----ドロップアイテム生成
void ItemDrop(XY ePos, MAGIC_TYPE type)
{
	//ドロップしていないものがないかチェック
	//していないものがあれは生成する
	for (int item = 0; item < ITEM_MAX; item++)
	{
		//ドロップしていないものを探す
		if (itemF[item].life <= 0)
		{
			//アイテムを落とす
			itemF[item].charType = type;
			itemF[item].pos = { ePos.x,ePos.y };
			itemF[item].life = itemF[item].lifeMax;
			break;
		}
	}
}


//-----ドロップアイテム消滅
void DeleteItem()
{
	for (int item = 0; item < ITEM_MAX; item++)
	{
		if (itemF[item].life > 0 && itemF[item].hitFlag)
		{
			itemF[item].life = 0;
			itemF[item].hitFlag = false;
			break;
		}
	}
}
bool GameOverSet()
{
	if ((itemF[MAGIC_TYPE_FIRE].point == 0) 
		&& (itemF[MAGIC_TYPE_WATER].point == 0) 
		&& (itemF[MAGIC_TYPE_WIND].point == 0))
	{
		return true;
	}
	return false;
}
