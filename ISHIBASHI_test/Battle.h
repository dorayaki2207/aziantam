//#pragma once

//-----�萔��`
#define BOX_X		15
#define BOX_Y		SCREEN_SIZE_Y - 220
#define BOX_END_X	SCREEN_SIZE_X - 15
#define BOX_END_Y	SCREEN_SIZE_Y - 5


//-----�֐��������ߐ錾
void BattleSystmeInit(void);		//�@�޽����̏�����	
void BattleGameInit(void);			//						
void BattleControl(void);			//	�޽��̑���
void BattleScene(void);				//	�޽��̼��
void BattleGameDraw(void);			//�@�޽��̕`�揈��

