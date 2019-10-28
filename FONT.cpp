//FONT.cpp

//************ �w�b�_�[�t�@�C���ǂݍ��� ***************
#include "FONT.hpp"
#include "main.hpp"

//************ �N���X�̒�` ****************

//�R���X�g���N�^
FONT::FONT(char setstr[][128])
{
	this->str[0][0] = &setstr[0][0];	//�`�悷�镶�����ݒ�

	return;
}

//��ʒ����ɕ�����`��
//���@���Fchar [][]�F�\�����镶����̐擪�A�h���X
//���@���Fint�@ �@ �F�\������s��
//���@���Fchar *�@ �F�t�H���g�̖��O
//���@���Fint�@ �@ �F�����̑傫��
//�߂�l�F�Ȃ�
VOID FONT::DrawCenter(char str[][128], int row, char *fontname, int size)
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
			GetColor(255, 0, 0), &str[rCnt][0]);			//�f�t�H���g�̃t�H���g�ŕ`��
	}

	SetDefaultFont(TRUE);	//�f�t�H���g�t�H���g�ɐݒ肷��

	return;

}

//�������f�t�H���g�t�H���g�ɐݒ肷��
VOID FONT:: SetDefaultFont(BOOL anti)
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

//�f�X�g���N�^
FONT::~FONT()
{
	return;
}

