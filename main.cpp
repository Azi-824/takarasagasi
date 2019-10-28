//********** �w�b�_�[�t�@�C���ǂݍ��� *************
#include "DxLib.h"
#include "main.hpp"
#include "FPS.hpp"
#include "KEYDOWN.hpp"


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

	//�w�i�摜�̓ǂݍ���
	if (MY_GAZOU_LOAD(&Back[BACKIMAGE_TITLE], 0, 0, TITLE_BACKIMAGE) == FALSE) { MessageBox(NULL, TITLE_BACKIMAGE, "NotFound", MB_OK); return -1; }		//�^�C�g����ʂ̔w�i�摜��ǂݍ���

	//�v���C���[�摜�̓ǂݍ���
	if (MY_GAZOU_LOAD(&Chara, 0, 0, CHARA_IMAGE) == FALSE) { MessageBox(NULL, CHARA_IMAGE, "NotFound", MB_OK); return -1; }		//�v���C���[�摜��ǂݍ���

	//�A�C�e���摜�̓ǂݍ���
	if (MY_GAZOU_LOAD(&Item, 0, 0, ITEM_IMAGE) == FALSE) { MessageBox(NULL, ITEM_IMAGE, "NotFound", MB_OK); return -1; }		//�A�C�e���摜��ǂݍ���

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

	for (int i = 0; i < SCENE_KIND; i++)
	{
		DeleteGraph(Back[i].Handle);	//�w�i�摜�̃n���h���̍폜
	}
	
	DeleteGraph(Chara.Handle);			//�v���C���[�摜�̃n���h���̍폜
	DeleteGraph(Item.Handle);			//�A�C�e���摜�̃n���h���̍폜

	DxLib_End();			//DX���C�u�����g�p�̏I������

	return 0;
}

//************** �^�C�g����ʂ̏��� ***************
int SceneTitle()
{
	DRAW_BACKIMAGE(&Back[BackImageNow]);	//�w�i�̕`��

	DrawString(0, 20, "�^�C�g�����", GetColor(255, 255, 255));

	//�������������������� �^�C�g���̕`�� ��������������������
	char StrGameTitle[1][128] = { "��T��" };
	char StrFontTitle[128] = { "MS �S�V�b�N" };	//�啶�����p�uMS�v�A���p�u�󔒁v�A�S�p�u�S�V�b�N�v

	DrawCenter(&StrGameTitle[0], 1, StrFontTitle, 64);		//��ʒ����ɕ`��
	//�������������������� �^�C�g���̕`�� ��������������������


	if (keydown->IsKeyDown(KEY_INPUT_RETURN) == TRUE)	//�G���^�[�L�[��������Ă�����
	{
		BackImageNow = (int)BACKIMAGE_PLAY;		//�w�i�摜���v���C��ʂɕς���
		GameSceneNow = (int)GAME_SCENE_PLAY;	//�V�[�����v���C��ʂɕς���
	}

	return 0;
}

//************* �v���C��ʂ̏��� ****************
int ScenePlay()
{
	DrawString(0, 20, "�v���C���", GetColor(255, 255, 255));

	DrawChara();	//�v���C���[�̕`�揈��

	DrawItem(Item, 1);	//�󔠂̕`�揈��

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

//########## �摜��ǂݍ��ސݒ������֐� ##########

//���@���F�摜�\���́@�F�ݒ肷��摜�\���̂̕ϐ�
//���@���Fint�@�F�摜�̉��̈ʒu
//���@���Fint�@�F�摜�̏c�̈ʒu
//���@���Fconst char *�F�ǂݍ��މ摜�̃t�@�C���p�X
//�߂�l�FBOOL�F�G���[���FFALSE
BOOL MY_GAZOU_LOAD(GAZOU *g, int x, int y, const char *path)
{
	wsprintf(g->FilePath, path);					//�t�@�C���p�X���R�s�[
	g->Handle = LoadGraph(g->FilePath);				//�摜���������ɓǂݍ��݁A�n���h�����擾

	if (g->Handle == -1) { return FALSE; }			//�摜�ǂݍ��݃G���[

	GetGraphSize(g->Handle, &g->Width, &g->Height);	//�摜�T�C�Y���擾
	g->X = x;
	g->Y = y;
	g->C_Width = g->Width / 2;						//�摜�̉��T�C�Y�̒��S���擾
	g->C_Height = g->Height / 2;					//�摜�̏c�T�C�Y�̒��S���擾

	//�̈�̐ݒ�
	g->rect.left = x;				//����
	g->rect.top = y;				//����
	g->rect.right = x + g->Width;	//�E��
	g->rect.bottom = y + g->Height;	//�E��

	return TRUE;

}

//########### �w�肵���w�i�摜��`�悷��֐� ###########
VOID DRAW_BACKIMAGE(GAZOU *back)
{
	DrawGraph(back->X, back->Y, back->Handle, FALSE);	//�w�i�̕`��
}

//************ �v���C���[��`�悷��֐� *************
VOID DrawChara()
{
	MoveChara();	//�v���C���[���ړ�������֐�
	DrawGraph(Chara.X, Chara.Y, Chara.Handle, TRUE);	//�v���C���[�̕`��
}

//************ �v���C���[�̈ʒu�𓮂����֐� *************
VOID MoveChara()
{

	if (keydown->IsKeyDown(KEY_INPUT_UP) == TRUE)			//����L�[��������Ă�����
	{
		if (Chara.rect.top > 0)	//��ʓ��Ȃ�
		{
			Chara.Y -= MoveSpead;	//��ֈړ�
			Chara.rect.top -= MoveSpead;	//�̈����ֈړ�
			Chara.rect.bottom -= MoveSpead;	//�̈����ֈړ�
		}
	}	
	else if (keydown->IsKeyDown(KEY_INPUT_DOWN) == TRUE)	//�����L�[��������Ă�����
	{
		if (Chara.rect.bottom < GAME_HEIGHT)	//��ʖ����Ȃ�
		{
			Chara.Y += MoveSpead;	//���ֈړ�
			Chara.rect.top += MoveSpead;	//�̈�����ֈړ�
			Chara.rect.bottom += MoveSpead;	//�̈�����ֈړ�
		}
	}	
	else if (keydown->IsKeyDown(KEY_INPUT_LEFT) == TRUE)	//�����L�[��������Ă�����
	{
		if (Chara.rect.left > 0)	//��ʖ����Ȃ�
		{
			Chara.X -= MoveSpead;	//���ֈړ�
			Chara.rect.left -= MoveSpead;	//�̈�����ֈړ�
			Chara.rect.right -= MoveSpead;	//�̈�����ֈړ�
		}
	}
	else if (keydown->IsKeyDown(KEY_INPUT_RIGHT) == TRUE)	//�E���L�[��������Ă�����
	{
		if (Chara.rect.right < GAME_WIDTH)	//��ʖ����Ȃ�
		{
			Chara.X += MoveSpead;	//�E�ֈړ�
			Chara.rect.left += MoveSpead;	//�̈���E�ֈړ�
			Chara.rect.right += MoveSpead;	//�̈���E�ֈړ�
		}
	}
	return;
}

//************ �A�C�e����`�悷��֐� *************
VOID DrawItem(GAZOU item, int num)
{
	for (int cnt = 0; cnt < num; cnt++)
	{
		DrawGraph(item.X, item.Y, item.Handle, TRUE);	//�A�C�e���̕`��
	}
	

	return;
}

