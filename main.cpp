//********** �w�b�_�[�t�@�C���ǂݍ��� *************
#include "main.hpp"
#include "FPS.hpp"

//*********** �O���[�o���I�u�W�F�N�g ***********
FPS *fps = new FPS(GAME_FPS_SPEED);



//*********** �v���O�����ōŏ��Ɏ��s�����֐� ***************
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(GAME_WINDOW_MODECHANGE);
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);

	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);

	SetMainWindowText(TEXT(GAME_WINDOW_NAME));

	if (DxLib_Init() == -1) { return -1; }

	SetDrawScreen(DX_SCREEN_BACK);



	while (TRUE)		//�������[�v
	{
		if (ProcessMessage() != 0) { break; }	//���b�Z�[�W�����̌��ʂ��G���[�̎��A�����I��

		if (ClearDrawScreen() != 0) { break; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

		fps->Update();		//FPS�̏���[�X�V]

		//�������������� �Q�[���̃V�[���������� ����������������



		//���������������@�Q�[���̃V�[�������܂� ����������������

		fps->Draw(0, 0);				//FPS�̏���(�`��)

		ScreenFlip();					//���j�^�̃��t���b�V�����[�g�̑����ŗ���ʂ��ĕ`��

		fps->Wait();					//FPS�̏���(�҂�)

	}


	delete fps;				//fps��j��

	DxLib_End();			//DX���C�u�����g�p�̏I������

	return 0;
}