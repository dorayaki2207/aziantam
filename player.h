//#pragma once

//列挙型の定義


//クラス化
class Player
{
public:
	const int START_POS_X;		//プレイヤーの初期位置X座標
	const int START_POS_Y;		//プレイヤーの初期位置Y座標
	//メンバ変数
	//--------------------------
	int playerImage;		//ﾌﾟﾚｲﾔの描画
	int playerPosX;			//ﾌﾟﾚｲﾔｰのX座票
	int playerPosY;			//ﾌﾟﾚｲﾔｰのY座標
	int playerSpeed;		//ﾌﾟﾚｲﾔｰの移動量

public:
	//コンストラクタ
	Player();
	//デストラクタ
	~Player();


public:
   //メンバ関数
   //--------------------------
	void PlayerSystemInit(void);				//ﾌﾟﾚｲﾔｰ情報の初期化
	void PlayerGameInit(void);					//プレイヤーの初期化
	void PlayerControl(void);					//プレイヤーの操作
	void PlayerDraw(void);						//プレイヤーの描画
	
};