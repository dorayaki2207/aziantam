#include "DxLib.h"
#include "main.h"

//�ϐ�
SCENE SceneID;
SCENE ScenePreID;	//�ߋ��̼�݊i�[�p
int SceneCounter;

//�׽����ݽ�ݽ�𐶐�


//Win�֐�
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	if (!SystemInit())
	{
		return -1;
	}
	//��������ް�ٰ��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//��ݶ���ؾ��
		if (SceneID != ScenePreID)
		{
			ScenePreID = SceneID;
			SceneCounter = 0;
		}
		//������ʕ`�揈��
		ClsDrawScreen();	//��ʏ���
		//��ݑI��
		switch (systemScene)
		{
		case SCENE_INIT:
			InitScene();
			break;
		case SCENE_TITLE:
			TitleScene();
			break;
		case SCENE_GAME:
			GameScene();
			break;
		case SCENE_GAMEOVER:
			GameOverScene();
			break;
		default:
			return -1;
			break;
		}
		SceneCounter++;
		ScreenFlip();		//�@����ʂ�\��ʂɏu�Ժ�߰
	}
	//�ݽ�ݽ�̉��


	DxLib_End();			// DXײ���؂̏I������
	return 0;				// ������۸��т̏I��

}
//���т̏�����
bool SystemInit(void)
{
	//--------���я���
	SetWindowText("����");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)return false;
	SetDrawScreen(DX_SCREEN_BACK);
	
	//�ݽ�ݽ�̐���

	//���̨���o�^

	//�ϐ��̏�����
	SceneCounter = 0;
	SceneID = SCENE_ID_INIT;
	ScenePreID = SCENE_ID_MAX;

	return true;
}
//���������
void InitScene(void)
{
	
}
//���ټ��
void TitleScene(void)
{
	TitleDraw();
}
//���ق̕`��
void TitleDraw(void)
{

}

//�ްѼ��
void GameScene(void)
{
	GameDraw();
}
//�ްт̕`��
void GameDraw(void)
{

}
//�ްѵ��ް���
void GameOverScene(void)
{
	GameOverDraw();
}
//�ްѵ��ް�̕`��
void GameOverDraw(void)
{

}
