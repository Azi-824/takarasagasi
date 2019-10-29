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
	if (MY_GAZOU_LOAD(&Back[BACKIMAGE_END], 0, 0, END_BACKIMAGE) == FALSE) { MessageBox(NULL, END_BACKIMAGE, "NotFound", MB_OK); return -1; }		//�^�C�g����ʂ̔w�i�摜��ǂݍ���


	//�v���C���[�摜�̓ǂݍ���
	if (MY_GAZOU_LOAD(&Chara, 0, 0, CHARA_IMAGE) == FALSE) { MessageBox(NULL, CHARA_IMAGE, "NotFound", MB_OK); return -1; }		//�v���C���[�摜��ǂݍ���

	//�A�C�e���摜�̓ǂݍ���
	for (int i = 0; i < ITEM_KAZU; i++)
	{
		if (MY_GAZOU_LOAD(&Item[i], 0, 0, ITEM_IMAGE) == FALSE) { MessageBox(NULL, ITEM_IMAGE, "NotFound", MB_OK); return -1; }		//�A�C�e���摜��ǂݍ���
	}

	while (TRUE)		//�������[�v
	{
		if (ProcessMessage() != 0) { break; }	//���b�Z�[�W�����̌��ʂ��G���[�̎��A�����I��

		if (ClearDrawScreen() != 0) { break; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

		fps->Update();		//FPS�̏���[�X�V]

		keydown->KeyDownUpdate();	//�L�[�̏�Ԃ��擾

		if (GameEndflg == true)	//�Q�[���I���t���O�������Ă�����
			break;	//�Q�[���I��

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
		DeleteGraph(Back[i].Handle);			//�w�i�摜�̃n���h���̍폜
	}
	
	DeleteGraph(Chara.Handle);					//�v���C���[�摜�̃n���h���̍폜
	for (int i = 0; i < ITEM_KAZU; i++)
	{
		DeleteGraph(Item[i].Handle);			//�A�C�e���摜�̃n���h���̍폜
	}

	DxLib_End();			//DX���C�u�����g�p�̏I������

	return 0;
}

//************** �^�C�g����ʂ̏��� ***************
int SceneTitle()
{

	Init();		//�������֐�

	DRAW_BACKIMAGE(&Back[BackImageNow]);	//�w�i�̕`��

	DrawString(0, 20, "�^�C�g�����", GetColor(255, 255, 255));
	DrawString(0, 40, "�X�y�[�X�L�[�������Ă�������", GetColor(255, 255, 255));


	//�������������������� �^�C�g���̕`�� ��������������������
	char StrGameTitle[1][128] = { "��T��" };
	char StrFontTitle[128] = { "MS �S�V�b�N" };	//�啶�����p�uMS�v�A���p�u�󔒁v�A�S�p�u�S�V�b�N�v

	DrawCenter(&StrGameTitle[0], 1, StrFontTitle, 64);		//��ʒ����ɕ`��
	//�������������������� �^�C�g���̕`�� ��������������������


	if (keydown->IsKeyDown(KEY_INPUT_SPACE) == TRUE)	//�X�y�[�X�L�[��������Ă�����
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
	DrawFormatString(0, 40, GetColor(255, 255, 255), "������:%d/%d", GetNum, ITEM_KAZU);	//���݂̔�������`��

	DrawChara();	//�v���C���[�̕`�揈��

	DrawItem(ITEM_KAZU);	//�󔠂̕`�揈��

	CheckTakara();			//�󔠂Ɠ����������m�F

	if (GetNum == ITEM_KAZU)	//�S�Ă̕󔠂𔭌�������
	{
		BackImageNow = (int)BACKIMAGE_END;		//�w�i�摜���G���h��ʂɕς���
		GameSceneNow = (int)GAME_SCENE_END;		//�V�[�����G���h��ʂɕς���

	}

	return 0;
}

//************* �G���h��ʂ̏��� ***************
int SceneEnd()
{

	DRAW_BACKIMAGE(&Back[BackImageNow]);	//�w�i�̕`��

	DrawString(0, 20, "�G���h���", GetColor(255, 255, 255));
	DrawString(0, 40, "�G���^�[�L�[:�������", GetColor(255, 255, 255));
	DrawString(0, 60, "�o�b�N�X�y�[�X�L�[:�Q�[���I��", GetColor(255, 255, 255));

	//�������������������� �G���h�`�� ��������������������
	char StrGameTitle[1][128] = { "GAME CLEAR!" };
	char StrFontTitle[128] = { "MS �S�V�b�N" };	//�啶�����p�uMS�v�A���p�u�󔒁v�A�S�p�u�S�V�b�N�v

	DrawCenter(&StrGameTitle[0], 1, StrFontTitle, 64);		//��ʒ����ɕ`��
	//�������������������� �G���h�`�� ��������������������


	if (keydown->IsKeyDown(KEY_INPUT_RETURN) == TRUE)	//�G���^�[�L�[��������Ă�����
	{
		BackImageNow = (int)BACKIMAGE_TITLE;		//�w�i�摜���^�C�g����ʂɕς���
		GameSceneNow = (int)GAME_SCENE_TITLE;		//�V�[�����^�C�g����ʂɕς���
	}
	else if (keydown->IsKeyDown(KEY_INPUT_BACK) == TRUE)	//�o�b�N�X�y�[�X�L�[��������Ă�����
	{
		GameEndflg = true;	//�Q�[���I���t���O�𗧂Ă�
	}


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

	g->Positon_flg = FALSE;	//���W���ݒ�

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
VOID DrawItem(int num)
{
	if (Item[ITEM_KAZU - 1].Positon_flg == FALSE)	//�Ō�̕󔠂̍��W�ݒ肪�I����ĂȂ���΁A
	{
		SetItemPos();	//���W�ݒ�
	}

	//�������������������������� �`�揈�� ��������������������������������
	for (int cnt = 0; cnt < num; cnt++)
	{
		if (Item[cnt].IsDraw == TRUE)	//�`�悵�Ă悯���
		{
			DrawGraph(Item[cnt].X, Item[cnt].Y, Item[cnt].Handle, TRUE);	//�A�C�e���̕`��
		}

		DrawBox(Item[cnt].rect.left,
			Item[cnt].rect.top,
			Item[cnt].rect.right,
			Item[cnt].rect.bottom,
			GetColor(255, 255, 255), FALSE);//�󔠂̗̈��`��
	}
	//�������������������������� �`�揈�� ��������������������������������

	return;
}

//************** �A�C�e���̕`��ʒu��ݒ肷��֐� **************
VOID SetItemPos()
{
	int num = 0;	//����������

	for (int cnt = 0; cnt < ITEM_KAZU; cnt++)	//�󔠂̐���
	{
		num = GetRand(GAME_WIDTH);		//�󔠂�`�悷��X���W����ʓ��̒l�Ő���

		if (num>0&&(num + Item[cnt].Width)<GAME_WIDTH)		//��ʓ��Ȃ�A
		{
			Item[cnt].X = num;		//�󔠂�x���W�ɑ��
		}
		else
		{
			cnt--;
			continue;
		}

		num = GetRand(GAME_HEIGHT);		//�󔠂�`�悷��Y���W����ʓ��̒l�Ő���

		if (num > 0 && (num + Item[cnt].Height) < GAME_HEIGHT)		//��ʓ��Ȃ�A
		{
			Item[cnt].Y = num;		//�󔠂�x���W�ɑ��
		}
		else
		{
			cnt--;
			continue;
		}

		RectSet(&Item[cnt]);			//�̈�̍Đݒ�
		Item[cnt].Positon_flg = TRUE;	//���W�ݒ芮��

		//�������������������� ���̗̈悪����Ă��邩���� ��������������������
		for (int cnt_r = 0; cnt_r < cnt; cnt_r++)
		{
			if (MY_CHECK_RECT_ATARI(Item[cnt].rect, Item[cnt_r].rect) == TRUE)		//�̈悪����Ă�����
			{
				cnt--;											//cnt�̒l���}�C�i�X���āA���W��ݒ肵�Ȃ���
				Item[cnt + cnt_r].Positon_flg = FALSE;		//���W�ݒ�̃t���O��FALSE�ɂ���
				break;
			}
		}
		//���������������������� ���̗̈悪����Ă��邩���� ������������������������

		if (Item[cnt].Positon_flg == TRUE)	//���W�ݒ芮�����Ă�����A
			Item[cnt].IsDraw = FALSE;	//�`�悵�Ȃ�

	}

	

	return;
}

//########## �̈�̓����蔻�������֐� ##########
BOOL MY_CHECK_RECT_ATARI(RECT a, RECT b)
{
	if (a.left<b.right&&
		a.top<b.bottom&&
		a.right>b.left&&
		a.bottom>b.top)
	{
		return TRUE;	//�������Ă���
	}

	return FALSE;		//�������ĂȂ�

}

//********** �̈�̐ݒ������֐� ************
VOID RectSet(GAZOU *item)
{
	item->rect.left = item->X;
	item->rect.top = item->Y;
	item->rect.right = item->X + item->Width;
	item->rect.bottom = item->Y + item->Height;

}

//********* �󔠂Ɠ����������m�F����֐� **********:
VOID CheckTakara()
{
	for (int i = 0; i < ITEM_KAZU; i++)
	{
		if (MY_CHECK_RECT_ATARI(Item[i].rect, Chara.rect) == TRUE) //�v���C���[���󔠂ɓ���������A
		{
			if (Item[i].IsDraw == FALSE)	//��������������A
			{
				Item[i].IsDraw = TRUE;	//�󔠂�`�悷��
				GetNum++;	//�������󔠂̐������Z����
			}
		}
	}
	return;
}

//******** �������֐� ************
VOID Init()
{

	SetPlayer();		//�v���C���[�̐ݒ�

	BackImageNow = (int)BACKIMAGE_TITLE;		//�w�i�摜���^�C�g����ʂɕς���
	GameSceneNow = (int)GAME_SCENE_TITLE;		//�V�[�����^�C�g����ʂɕς���

	GetNum = 0;	//������������

	for (int i = 0; i < ITEM_KAZU; i++)
	{
		Item[i].Positon_flg = false;	//���W�ݒ菉����
	}

}

//********* �v���C���[�̐ݒ������֐� ***********
VOID SetPlayer()
{
	//�ʒu��^�񒆂ɐݒ�
	Chara.X = (GAME_WIDTH / 2) - (Chara.Width / 2);		//X���W�ݒ�
	Chara.Y = (GAME_HEIGHT / 2) - (Chara.Height / 2);	//Y���W�ݒ�

	RectSet(&Chara);	//�̈�ݒ�

}

