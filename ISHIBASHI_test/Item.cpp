///// ボス戦　当たり判定
/////	keyを押されたら　御札が現れる
/////	当たり判定作る？


///// 連続で攻撃ができないようにｶｳﾝﾄで管理
/////　ボスからの攻撃等が入り次第変更する可能性有り
////	攻撃をくらったらKeyが押せるなど

#include "DxLib.h"
#include "test.h"
#include "KeyCheck.h"
#include "Stage.h"
#include "Item.h"
#include "Battle.h"

//-----外部変数宣言
//ｱｲﾃﾑ関連
//御札（ﾄﾞﾛｯﾌﾟ
CHARACTER itemF[ITEM_MAX];					//	ﾄﾞﾛｯﾌﾟｱｲﾃﾑ変数格納用
CHARACTER itemFmaster[ITEM_TYPE_F_MAX];
int itemFImage[ITEM_TYPE_F_MAX];			//	ﾄﾞﾛｯﾌﾟｱｲﾃﾑ用画像（F：札の頭文字
//御札（ｲﾝﾍﾞﾝﾄﾘ
int itemFIImage[ITEM_TYPE_F_MAX];			//	ｲﾝﾍﾞﾝﾄﾘ用画像（F：札の頭文字，I：ｲﾝﾍﾞﾝﾄﾘの頭文字
//御札（ﾎﾞｽﾊﾞﾄﾙ
int itemFBImage[ITEM_TYPE_F_MAX];			//	ﾎﾞｽﾊﾞﾄﾙ用画像（F：札の頭文字,　B：ﾊﾞﾄﾙの頭文字
int lookCnt;
bool itemFBFlag[ITEM_TYPE_F_MAX];			//	表示,非表示用

//三種の神器
CHARACTER itemB[ITEM_TYPE_B_MAX];
int itemBImage[ITEM_TYPE_B_MAX];			//	神器の画像（B：武器の頭文字



//-----ｱｲﾃﾑ情報の初期化
void ItemSystemInit(void)
{
	//-----変数の初期化
	//御札（ﾄﾞﾛｯﾌﾟ用
	itemFmaster[ITEM_TYPE_HI].charType = ITEM_TYPE_HI;				//	御札の種類	：	火
	itemFmaster[ITEM_TYPE_MIZU].charType = ITEM_TYPE_MIZU;			//	御札の種類	：	水
	itemFmaster[ITEM_TYPE_KAZE].charType = ITEM_TYPE_KAZE;			//	御札の種類	：	風
	itemFmaster[ITEM_TYPE_KAIFUKU].charType = ITEM_TYPE_KAIFUKU;	//	御札の種類	：	回復
	//御札まとめて処理
	for (int i = 0; i < ITEM_TYPE_F_MAX; i++)
	{
		itemFmaster[i].pos = { 250,250 };																//　御札の地図上の座標
		itemFmaster[i].size = { 20,20 };															//	御札の画像ｻｲｽﾞ
		itemFmaster[i].offsetSize = { itemFmaster[i].size.x / 2,itemFmaster[i].size.y / 2 };		//　御札のｵﾌｾｯﾄ
		itemFmaster[i].point = 0;																	//	御札の枚数
		itemFmaster[i].lifeMax = 20;																//	御札の体力最大値（表示時間）
		itemFmaster[i].life = itemFmaster[i].lifeMax;												//	御札の体力
	}

	//御札（ﾎﾞｽﾊﾞﾄﾙ用
	for (int type = 0; type < ITEM_TYPE_F_MAX; type++)
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
		itemB[i].offsetSize = { itemB[i].size.x / 2,itemB[i].size.y / 2 };							//　三種の神器のｵﾌｾｯﾄ
		
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
	//御札（ﾄﾞﾛｯﾌﾟ用
	for (int i = 0; i < ITEM_MAX; i++)
	{

		itemF[i] = itemFmaster[GetRand(ITEM_TYPE_F_MAX - 1)];
		itemF[i].pos.x = GetRand(MAP_X * CHIP_SIZE_X - 1);
		itemF[i].pos.y = GetRand(MAP_Y * CHIP_SIZE_Y - 1);
		//	itemF[i].point = 0;																//	御札の枚数
		//	itemF[i].lifeMax = 20;															//	御札の体力最大値（表示時間）
		//	itemF[i].life = itemF[i].lifeMax;												//	御札の体力

	}
	//三種の神器
	for (int i = 0; i < ITEM_TYPE_B_MAX; i++)
	{
		itemB[i].pos = { 50,120 };									//　三種の神器の地図上の座標
		itemB[i].lifeMax = 20;										//	三種の神器の体力最大値（表示時間）
		itemB[i].life = itemB[i].lifeMax;							//	三種の神器の体力
	}

	

}

void ItemControl(CHARACTER boss)
{
	//攻撃札が表示されていないときのみKey押せる
	if (lookCnt == 0)
	{	
		//火の御札
		if (keyDownTrigger[KEY_ID_FIRE])
		{
			//御札が一枚以上ある場合、処理可能
			if (itemF[ITEM_TYPE_HI].point > 0)
			{
				itemF[ITEM_TYPE_HI].point--;
				itemFBFlag[ITEM_TYPE_HI] = true;
				boss.life--;
				boss.hitFlag = true;
			}
		}
		//水の御札
		if (keyDownTrigger[KEY_ID_WATER])
		{
			//御札が一枚以上ある場合、処理可能
			if (itemF[ITEM_TYPE_MIZU].point > 0)
			{
				itemF[ITEM_TYPE_MIZU].point--;
				itemFBFlag[ITEM_TYPE_MIZU] = true;
				boss.life--;
				boss.hitFlag = true;

			}
		}
		//風の御札
		if (keyDownTrigger[KEY_ID_WIND])
		{
			//御札が一枚上ある場合、処理可能
			if (itemF[ITEM_TYPE_KAZE].point > 0)
			{
				itemF[ITEM_TYPE_KAZE].point--;
				itemFBFlag[ITEM_TYPE_KAZE] = true;
				boss.life--;
				boss.hitFlag = true;

			}
		}
		//回復の御札
		if (keyDownTrigger[KEY_ID_HEAL])
		{
			//御札が一枚以上ある場合、処理可能
			if (itemF[ITEM_TYPE_KAIFUKU].point > 0)
			{
				itemF[ITEM_TYPE_KAIFUKU].point--;
				itemFBFlag[ITEM_TYPE_KAIFUKU] = true;
			}
		}
	}
	//攻撃札の表示処理
	for (int type = 0; type < ITEM_TYPE_F_MAX; type++)
	{
		if (itemFBFlag[type])
		{
			lookCnt++;
			//ｶｳﾝﾄが50超えると非表示にする
			if (lookCnt > 50)
			{
				itemFBFlag[type] = false;
				lookCnt = 0;
				boss.hitFlag = false;
			}
		}
	}

}
//-----ﾄﾞﾛｯﾌﾟ用
void ItemGameDraw(void)
{
	//-----描画処理
	//御札（ﾄﾞﾛｯﾌﾟ用
	for (int i = 0; i < ITEM_MAX; i++)
	{
	//	if (Pass(itemF[i].pos) == PASS_OK)
	//	{
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
	//	}
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
	DrawGraph(350, 250, itemFIImage[ITEM_TYPE_HI], true);
	DrawFormatString(380, 254, 0xFF22FF, "＠", true);
	DrawFormatString(410, 253, 0xFF22FF, "%d", itemF[ITEM_TYPE_HI].point);
	//水の御札
	DrawGraph(350, 300, itemFIImage[ITEM_TYPE_MIZU], true);
	DrawFormatString(380, 304, 0xFF22FF, "＠", true);
	DrawFormatString(410, 303, 0xFF22FF, "%d", itemF[ITEM_TYPE_MIZU].point);
	//風の御札
	DrawGraph(350, 350, itemFIImage[ITEM_TYPE_KAZE], true);
	DrawFormatString(380, 354, 0xFF22FF, "＠", true);
	DrawFormatString(410, 353, 0xFF22FF, "%d", itemF[ITEM_TYPE_KAZE].point);
	//回復の御札
	DrawGraph(350, 400, itemFIImage[ITEM_TYPE_KAIFUKU], true);
	DrawFormatString(380, 404, 0xFF22FF, "＠", true);
	DrawFormatString(410, 403, 0xFF22FF, "%d", itemF[ITEM_TYPE_KAIFUKU].point);

}

void ItemB_Draw(void)
{
	//攻撃時表示用
	for (int type = 0; type < ITEM_TYPE_F_MAX; type++)
	{
		if (itemFBFlag[type])
		{
			DrawGraph((SCREEN_SIZE_X - ITEM_B_SIZE) / 2, (BOX_Y - ITEM_B_SIZE) / 2, itemFBImage[type], true);
		}
	}
	//所持ｱｲﾃﾑ残量表示用
	//火の御札
	DrawGraph(350, BOX_Y +120, itemFIImage[ITEM_TYPE_HI], true);
	DrawFormatString(352, BOX_Y + 150, 0xFF22FF, "×", true);
	DrawFormatString(380, BOX_Y + 150, 0xFF22FF, "%d", itemF[ITEM_TYPE_HI].point);
	//水の御札
	DrawGraph(450, BOX_Y + 120, itemFIImage[ITEM_TYPE_MIZU], true);
	DrawFormatString(452, BOX_Y + 150, 0xFF22FF, "×", true);
	DrawFormatString(480, BOX_Y + 150, 0xFF22FF, "%d", itemF[ITEM_TYPE_MIZU].point);
	//風の御札
	DrawGraph(550, BOX_Y + 120, itemFIImage[ITEM_TYPE_KAZE], true);
	DrawFormatString(552, BOX_Y + 150, 0xFF22FF, "×", true);
	DrawFormatString(580, BOX_Y + 150, 0xFF22FF, "%d", itemF[ITEM_TYPE_KAZE].point);
	//回復の御札
	DrawGraph(650, BOX_Y + 120, itemFIImage[ITEM_TYPE_KAIFUKU], true);
	DrawFormatString(652, BOX_Y + 150, 0xFF22FF, "×", true);
	DrawFormatString(680, BOX_Y + 150, 0xFF22FF, "%d", itemF[ITEM_TYPE_KAIFUKU].point);


	DrawFormatString(0, 100, 0xFFFFFF, "lookCnt:%d", lookCnt);
}

//-----弾と敵の当たり判定　(true : あたり, false : はずれ)
bool ItemHitCheck(XY sPos, int sSize)
{
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
				//当たった時、ｴﾈﾐｰの体力を減らす
				itemF[i].life = 0;
				//ｴﾈﾐｰを倒した時だけﾎﾟｲﾝﾄ加算
				//御札に触れたら加算
				if (itemF[i].charType == ITEM_TYPE_HI)
				{
					itemF[ITEM_TYPE_HI].point++;
					//hiCnt++;
				}
				if (itemF[i].charType == ITEM_TYPE_MIZU)
				{
					itemF[ITEM_TYPE_MIZU].point++;
					//mizuCnt++;
				}
				if (itemF[i].charType == ITEM_TYPE_KAZE)
				{
					itemF[ITEM_TYPE_KAZE].point++;
					//kazeCnt++;
				}
				if (itemF[i].charType == ITEM_TYPE_KAIFUKU)
				{
					itemF[ITEM_TYPE_KAIFUKU].point++;
					//kaifukuCnt++;
				}
				return true;
			}
		}
	}
	//弾が外れた時
	return false;
}

//-----弾を消滅させる
void DeleteItem(int index)
{
	itemF[index].life = 0;
	
};