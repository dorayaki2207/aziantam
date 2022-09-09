/////	当たり判定作る？


///// 連続で攻撃ができないようにｶｳﾝﾄで管理
/////　ボスからの攻撃等が入り次第変更する可能性有り

//ItemBossControl  同じ処理の為　for文でまわして、　keycheck判定を　type でみるようにする　アイテム拾う処理終了後やってみる


//  テスト用にｱｲﾃﾑをはじめから2枚ずつ所持するようにする

//GetRand 0~3
#include "DxLib.h"
#include "test.h"
#include "KeyCheck.h"
#include "Stage.h"
#include "Item.h"
#include "Battle.h"
#include "Enemy.h"

//-----外部変数宣言
//ｱｲﾃﾑ関連
//御札（ﾄﾞﾛｯﾌﾟ
CHARACTER itemF[ITEM_MAX];					//	ﾄﾞﾛｯﾌﾟｱｲﾃﾑ変数格納用
CHARACTER itemFmaster[MAGIC_TYPE_MAX];
int itemFImage[MAGIC_TYPE_MAX];				//	ﾄﾞﾛｯﾌﾟｱｲﾃﾑ用画像（F：札の頭文字
//御札（ｲﾝﾍﾞﾝﾄﾘ
int itemFIImage[MAGIC_TYPE_MAX];			//	ｲﾝﾍﾞﾝﾄﾘ用画像（F：札の頭文字，I：ｲﾝﾍﾞﾝﾄﾘの頭文字
//御札（ﾎﾞｽﾊﾞﾄﾙ
int itemFBImage[MAGIC_TYPE_MAX];			//	ﾎﾞｽﾊﾞﾄﾙ用画像（F：札の頭文字,　B：ﾊﾞﾄﾙの頭文字
int lookCnt;
bool itemFBFlag[MAGIC_TYPE_MAX];			//	表示,非表示用

//三種の神器
CHARACTER itemB[ITEM_TYPE_B_MAX];
int itemBImage[ITEM_TYPE_B_MAX];			//	神器の画像（B：武器の頭文字



//-----ｱｲﾃﾑ情報の初期化
void ItemSystemInit(void)
{
	//-----変数の初期化
	//御札（ﾄﾞﾛｯﾌﾟ用
	itemFmaster[MAGIC_TYPE_FIRE].charType = MAGIC_TYPE_FIRE;												//	御札の種類	：	火
	itemFmaster[MAGIC_TYPE_WATER].charType = MAGIC_TYPE_WATER;												//	御札の種類	：	水
	itemFmaster[MAGIC_TYPE_WIND].charType = MAGIC_TYPE_WIND;												//	御札の種類	：	風
	itemFmaster[MAGIC_TYPE_HEAL].charType = MAGIC_TYPE_HEAL;												//	御札の種類	：	回復
	//御札まとめて処理
	for (int type = 0; type < MAGIC_TYPE_MAX; type++)
	{
		itemFmaster[type].pos = { 0,0 };																	//	御札の地図上の座標
		itemFmaster[type].size = { 20,20 };																//	御札の画像ｻｲｽﾞ
		itemFmaster[type].offsetSize = { itemFmaster[type].size.x / 2,itemFmaster[type].size.y / 2 };	//	御札のｵﾌｾｯﾄ
		itemFmaster[type].point = 12;																		//	御札の枚数
		itemFmaster[type].lifeMax = 200;																	//	御札の体力最大値（表示時間）
		itemFmaster[type].life = 0;																		//	御札の体力
		itemFmaster[type].hitFlag = false;
	
	}

	//御札（ﾎﾞｽﾊﾞﾄﾙ用
	for (int type = 0; type < MAGIC_TYPE_MAX; type++)
	{
		itemFBFlag[type] = false;									//	true：表示, false：非表示 
	}
	lookCnt = 0;
	//三種の神器
	itemB[ITEM_TYPE_KEN].charType = ITEM_TYPE_KEN;					//	三種の神器　：　剣
	itemB[ITEM_TYPE_KAGAMI].charType = ITEM_TYPE_KAGAMI;			//	三種の神器　：　鏡
	itemB[ITEM_TYPE_MAGATAMA].charType = ITEM_TYPE_MAGATAMA;		//	三種の神器　：　勾玉
	//三種の神器まとめて処理
	for (int i = 0; i < ITEM_TYPE_B_MAX; i++)
	{
		itemB[i].size = { 20,20 };																	//	三種の神器の画像ｻｲｽﾞ
		itemB[i].offsetSize = { itemB[i].size.x / 2,itemB[i].size.y / 2 };						//　三種の神器のｵﾌｾｯﾄ
		
	}




	//-----ｸﾞﾗﾌｨｯｸの登録
	//御札(ﾄﾞﾛｯﾌﾟ用
	LoadDivGraph("aitem/fudaD.png", 4, 4, 1
		, ITEM_M_SIZE, ITEM_M_SIZE, itemFImage);
	//御札（ｲﾝﾍﾞﾝﾄﾘ用
	LoadDivGraph("aitem/fudaI.png", 4, 4, 1
		, ITEM_M_SIZE, ITEM_M_SIZE, itemFIImage);
	//御札（ﾎﾞｽﾊﾞﾄﾙ用
	LoadDivGraph("aitem/fuda_Big.png", 4, 4, 1
		, ITEM_B_SIZE, ITEM_B_SIZE, itemFBImage);
	//三種の神器
	LoadDivGraph("aitem/zingi20.png", 3, 3, 1
		, ITEM_M_SIZE, ITEM_M_SIZE, itemBImage);

}

void ItemGameInit(void)
{
	for (int type = 0; type < MAGIC_TYPE_MAX; type++)
	{
		for (int i = 0; i < ITEM_MAX; i++)
		{

			itemF[i] = itemFmaster[type];
			//	itemF[i].pos = { 0,0 };
			//	itemF[i].point = 0;					//	御札の枚数
			//	itemF[i].lifeMax = 0;				//	御札の体力最大値（表示時間）
			itemF[i].life = 0;						//	体力
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



void itemDropControl()
{
	for (int i = 0; i < ITEM_MAX; i++)
	{
		
		//撃っている弾を探す
		if (itemF[i].life >0)
		{

			//寿命を減らす（射程距離）
			itemF[i].life--;
		}
	}
}


//ボス戦処理
void ItemBossControl(CHARACTER* boss)
{
	//攻撃札が表示されていないときのみKey押せる
	if (lookCnt == 0)
	{	
		//火の御札
		if (keyNew[KEY_ID_FIRE])
		{
			//御札が一枚以上ある場合、処理可能
			if (itemF[MAGIC_TYPE_FIRE].point > 0)
			{
				itemF[MAGIC_TYPE_FIRE].point--;
				itemFBFlag[MAGIC_TYPE_FIRE] = true;
				(*boss).life--;
				(*boss).hitFlag = true;
			}
		}
		//水の御札
		if (keyNew[KEY_ID_WATER])
		{
			//御札が一枚以上ある場合、処理可能
			if (itemF[MAGIC_TYPE_WATER].point > 0)
			{
				itemF[MAGIC_TYPE_WATER].point--;
				itemFBFlag[MAGIC_TYPE_WATER] = true;
				(*boss).life--;
				(*boss).hitFlag = true;

			}
		}
		//風の御札
		if (keyNew[KEY_ID_WIND])
		{
			//御札が一枚上ある場合、処理可能
			if (itemF[MAGIC_TYPE_WIND].point > 0)
			{
				itemF[MAGIC_TYPE_WIND].point--;
				itemFBFlag[MAGIC_TYPE_WIND] = true;
				(*boss).life--;
				(*boss).hitFlag = true;

			}
		}
		//回復の御札
		if (keyNew[KEY_ID_HEAL])
		{
			//御札が一枚以上ある場合、処理可能
			if (itemF[MAGIC_TYPE_HEAL].point > 0)
			{
				itemF[MAGIC_TYPE_HEAL].point--;
				itemFBFlag[MAGIC_TYPE_HEAL] = true;
			}
		}
	}
	//攻撃札の表示処理
	for (int type = 0; type < MAGIC_TYPE_MAX; type++)
	{
		if (itemFBFlag[type])
		{
			lookCnt++;
			//ｶｳﾝﾄが50超えると非表示にする
			if (lookCnt > 50)
			{
				itemFBFlag[type] = false;
				lookCnt = 0;
				(*boss).hitFlag = false;
			}
		}
	}

}




//MOB敵交戦時処理
bool ItemMOBControl(MAGIC_TYPE type)
{
	//御札が一枚以上ある場合、処理可能
	if (itemF[type].point > 0)
	{
		itemF[type].point--;
		return true;
	}
	return false;
}



//-----ﾄﾞﾛｯﾌﾟ用
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

			DrawBox(itemF[i].pos.x - itemF[i].offsetSize.x + mapPos.x
				, itemF[i].pos.y - itemF[i].offsetSize.y + mapPos.y
				, itemF[i].pos.x - itemF[i].offsetSize.x + itemF[i].size.x + mapPos.x
				, itemF[i].pos.y - itemF[i].offsetSize.y + itemF[i].size.y + mapPos.y
				, 0xFF00FF, false);
		}
		DrawFormatString(0, 140, 0xFFFFFF, "itemLife : %d", itemF[i].life);
	}

	//三種の神器
	for (int i = 0; i < ITEM_TYPE_B_MAX; i++)
	{
		if (itemB[i].life > 0)
		{
			DrawGraph((itemB[i].pos.x   - itemB[i].offsetSize.x )*i
				, itemB[i].pos.y - itemB[i].offsetSize.y
				, itemBImage[itemB[i].charType]
				, true);

			DrawBox((itemB[i].pos.x - itemB[i].offsetSize.x)*i
				, itemB[i].pos.y - itemB[i].offsetSize.y
				, (itemB[i].pos.x - itemB[i].offsetSize.x) *i+ itemB[i].size.x
				, itemB[i].pos.y - itemB[i].offsetSize.y + itemB[i].size.y
				, 0xFF00FF, false);

		}
	}
}

//-----ｲﾝﾍﾞﾝﾄﾘ用描画
void ItemI_Draw(void)
{
	//火の御札
	DrawGraph(350, 250, itemFIImage[MAGIC_TYPE_FIRE], true);
	DrawFormatString(380, 254, 0xFF22FF, "＠", true);
	DrawFormatString(410, 253, 0xFF22FF, "%d", itemF[MAGIC_TYPE_FIRE].point);
	//水の御札
	DrawGraph(350, 300, itemFIImage[MAGIC_TYPE_WATER], true);
	DrawFormatString(380, 304, 0xFF22FF, "＠", true);
	DrawFormatString(410, 303, 0xFF22FF, "%d", itemF[MAGIC_TYPE_WATER].point);
	//風の御札
	DrawGraph(350, 350, itemFIImage[MAGIC_TYPE_WIND], true);
	DrawFormatString(380, 354, 0xFF22FF, "＠", true);
	DrawFormatString(410, 353, 0xFF22FF, "%d", itemF[MAGIC_TYPE_WIND].point);
	//回復の御札
	DrawGraph(350, 400, itemFIImage[MAGIC_TYPE_HEAL], true);
	DrawFormatString(380, 404, 0xFF22FF, "＠", true);
	DrawFormatString(410, 403, 0xFF22FF, "%d", itemF[MAGIC_TYPE_HEAL].point);

}

void ItemB_Draw(void)
{
	//攻撃時表示用
	for (int type = 0; type < MAGIC_TYPE_MAX; type++)
	{
		if (itemFBFlag[type])
		{
			DrawGraph((SCREEN_SIZE_X - ITEM_B_SIZE) / 2, (BOX_Y - ITEM_B_SIZE) / 2, itemFBImage[type], true);
		}
	}

	//所持ｱｲﾃﾑ残量表示用
	//火の御札
	DrawGraph(350, BOX_Y +120, itemFIImage[MAGIC_TYPE_FIRE], true);
	DrawFormatString(352, BOX_Y + 150, 0xFF22FF, "×", true);
	DrawFormatString(380, BOX_Y + 150, 0xFF22FF, "%d", itemF[MAGIC_TYPE_FIRE].point);
	//水の御札
	DrawGraph(450, BOX_Y + 120, itemFIImage[MAGIC_TYPE_WATER], true);
	DrawFormatString(452, BOX_Y + 150, 0xFF22FF, "×", true);
	DrawFormatString(480, BOX_Y + 150, 0xFF22FF, "%d", itemF[MAGIC_TYPE_WATER].point);
	//風の御札
	DrawGraph(550, BOX_Y + 120, itemFIImage[MAGIC_TYPE_WIND], true);
	DrawFormatString(552, BOX_Y + 150, 0xFF22FF, "×", true);
	DrawFormatString(580, BOX_Y + 150, 0xFF22FF, "%d", itemF[MAGIC_TYPE_WIND].point);
	//回復の御札
	DrawGraph(650, BOX_Y + 120, itemFIImage[MAGIC_TYPE_HEAL], true);
	DrawFormatString(652, BOX_Y + 150, 0xFF22FF, "×", true);
	DrawFormatString(680, BOX_Y + 150, 0xFF22FF, "%d", itemF[MAGIC_TYPE_HEAL].point);


	//DrawFormatString(0, 100, 0xFFFFFF, "lookCnt:%d", lookCnt);
}

//-----アイテムとプレイヤーの当たり判定　(true : あたり, false : はずれ)
bool ItemHitCheck(XY sPos, int sSize)
{
	int point = GetRand(5)+1;

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
				//当たった時、ｱｲﾃﾑを消す
				//	itemF[i].life = 0;
				//ﾄﾞﾛｯﾌﾟｱｲﾃﾑを拾った時だけﾎﾟｲﾝﾄ加算
				//御札に触れたら加算
				if (itemF[i].charType == MAGIC_TYPE_FIRE)
				{
					itemF[i].point += point;
					itemF[i].hitFlag = true;
				}
				if (itemF[i].charType == MAGIC_TYPE_WATER)
				{
					itemF[MAGIC_TYPE_WATER].point += point;
					itemF[i].hitFlag = true;
				}
				if (itemF[i].charType == MAGIC_TYPE_WIND)
				{
					itemF[MAGIC_TYPE_WIND].point += point;
					itemF[i].hitFlag = true;
				}
				if (itemF[i].charType == MAGIC_TYPE_HEAL)
				{
					itemF[MAGIC_TYPE_HEAL].point += point;
					itemF[i].hitFlag = true;
				}
				
				return true;
			}
		}
	}
	//弾が外れた時
	return false;
}


//-----ドロップアイテム
void ItemDrop(XY ePos,MAGIC_TYPE type)
{
	//弾の数分撃っていない弾がないかをﾁｪｯｸし、
	//撃っていない弾があれば一発弾を作って発射する。
	for (int item = 0; item < ITEM_MAX; item++)
	{
		//撃っていない弾を探す
		if (itemF[item].life <= 0)
		{
			//撃っていない弾があったので発射
			itemF[item].charType = type;
			itemF[item].pos = { ePos.x,ePos.y };
			itemF[item].life = itemF[item].lifeMax;	
			break;
		}
	
	}
}



//-----ドロップアイテムを消滅させる
void DeleteItem()
{
	for (int item = 0; item< ITEM_MAX; item++)
	{
		if (itemF[item].life > 0 && itemF[item].hitFlag)
		{
			itemF[item].life = 0;
			itemF[item].hitFlag = false;
			break;
		}
	}
}



