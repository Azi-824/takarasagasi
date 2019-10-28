//********** �w�b�_�[�t�@�C���ǂݍ��� *************
#include "DxLib.h"
#include "main.hpp"
#include "FPS.hpp"
#include "KEYDOWN.hpp"
#include "IMAGE.hpp"


//*********** �O���[�o���I�u�W�F�N�g ***********
FPS *fps = new FPS(GAME_FPS_SPEED);
KEYDOWN *keydown = new KEYDOWN();


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

		keydown->KeyDownUpdate();	//�L�[�̏�Ԃ��擾

		//�������������� �Q�[���̃V�[���������� ����������������

		//��ʂ��Ƃ̏���
		switch (GameSceneNow)
		{
		case (int)GAME_SCENE_TITLE:				//�^�C�g����ʂ̎�

			SceneTitle();						//�^�C�g����ʂ̏���

			break;

		case (int)GAME_SCENE_PLAY:				//�v���C��ʂ̎�

			ScenePlay();						//�v���C��ʂ̏���

			break;

		case (int)GAME_SCENE_END:				//�G���h��ʂ̏���

			SceneEnd();							//�G���h��ʂ̏���

			break;

		default:
			break;

		}

		//���������������@�Q�[���̃V�[�������܂� ����������������

		fps->Draw(0, 0);				//FPS�̏���(�`��)

		ScreenFlip();					//���j�^�̃��t���b�V�����[�g�̑����ŗ���ʂ��ĕ`��

		fps->Wait();					//FPS�̏���(�҂�)

	}


	delete fps;				//fps��j��
	delete keydown;			//keydown��j��

	DxLib_End();			//DX���C�u�����g�p�̏I������

	return 0;
}

//************** �^�C�g����ʂ̏��� ***************
int SceneTitle()
{
	IMAGE *back = new IMAGE(MY_IMG_DIR_BACK_1, MY_IMG_NAME_BACK_1);
	if (back->GetIsLoad() == FALSE) { return -1; };	//�摜�ǂݍ��݃`�F�b�N
	back->Draw();

	DrawString(0, 20, "�^�C�g�����", GetColor(255, 255, 255));

	//�������������������� �^�C�g���̕`�� ��������������������
	char StrGameTitle[1][128] = { "��T��" };
	char StrFontTitle[128] = { "MS �S�V�b�N" };	//�啶�����p�uMS�v�A���p�u�󔒁v�A�S�p�u�S�V�b�N�v

	DrawCenter(&StrGameTitle[0], 1, StrFontTitle, 64);		//��ʒ����ɕ`��
	//�������������������� �^�C�g���̕`�� ��������������������


	if (keydown->IsKeyDown(KEY_INPUT_RETURN) == TRUE)	//�G���^�[�L�[��������Ă�����
	{
		GameSceneNow = (int)GAME_SCENE_PLAY;	//�V�[�����v���C��ʂɕς���
	}

	return 0;
}

//************* �v���C��ʂ̏��� ****************
int ScenePlay()
{
	DrawString(300, 100, "Hello", GetColor(255, 255, 255));

	return 0;
}

//************* �G���h��ʂ̏��� ***************
int SceneEnd()
{
	return 0;
}

//************* ��ʒ����ɕ�����`�悷��֐� *************
VOID DrawCenter(char str[][128], int row, char *fontname, int size)
{
	ChangeFont(fontname, DX_CHARSET_DEFAULT);		//�f�t�H���g�̃t�H���g��ύX����
	SetFontSize(size);								//�f�t�H���g�̃t�H���g�T�C�Y��ς���
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);	//�t�H���g�����ꂢ�ɂ݂���

	int StrHeightSum = 0;
	for (int sum = 0; sum < row; sum++)	//�s�S�̂̍������W�v
	{
		StrHeightSum += GetFontSize();	//�f�t�H���g�̃t�H���g�̍������擾
	}

	for (int rCnt = 0; rCnt < row; rCnt++)	//�t�H���g��`��
	{
		int StrWidth = GetDrawFormatStringWidth(&str[rCnt][0]);	//�f�t�H���g�̃t�H���g�̉������擾
		int StrHeight = GetFontSize();

		DrawFormatString(
			GAME_WIDTH / 2 - StrWidth / 2,
			GAME_HEIGHT / 2 - StrHeightSum + StrHeight * rCnt,	//��ʂ̒��S�@-�@�s�S�̂̕����̍����@+�@�P�s�̍���
			GetColor(255, 255, 255), &str[rCnt][0]);			//�f�t�H���g�̃t�H���g�ŕ`��
	}

	SetDefaultFont(TRUE);	//�f�t�H���g�t�H���g�ɐݒ肷��

	return;

}

//***********�f�t�H���g�t�H���g�ɐݒ肷��֐� *************
VOID SetDefaultFont(BOOL anti)
{
	//�f�t�H���g�͈ȉ��̃t�H���g�T�C�Y�ł���ƁA�ݒ肷��
	ChangeFont("MS �S�V�b�N", DX_CHARSET_DEFAULT);
	SetFontSize(16);

	if (anti)
	{
		ChangeFontType(DX_FONTTYPE_ANTIALIASING);
	}
	return;

}