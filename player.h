//#pragma once

//�񋓌^�̒�`


//�N���X��
class Player
{
public:
	const int START_POS_X;		//�v���C���[�̏����ʒuX���W
	const int START_POS_Y;		//�v���C���[�̏����ʒuY���W
	//�����o�ϐ�
	//--------------------------
	int playerImage;		//��ڲԂ̕`��
	int playerPosX;			//��ڲ԰��X���[
	int playerPosY;			//��ڲ԰��Y���W
	int playerSpeed;		//��ڲ԰�̈ړ���

public:
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();


public:
   //�����o�֐�
   //--------------------------
	void PlayerSystemInit(void);				//��ڲ԰���̏�����
	void PlayerGameInit(void);					//�v���C���[�̏�����
	void PlayerControl(void);					//�v���C���[�̑���
	void PlayerDraw(void);						//�v���C���[�̕`��
	
};