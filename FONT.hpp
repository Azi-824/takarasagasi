//FONT.hpp

#pragma once

//*********** �w�b�_�[�t�@�C���ǂݍ��� *************
#include "DxLib.h"

//********** �N���X�̒�` ************

class FONT
{
private: 
	char *str[][128];	//�`�悷�镶���������z��
public:
	//�R���X�g���N�^
	FONT(char [][128]);

	//��ʒ����ɕ�����`��
	VOID DrawCenter(char [][128], int, char *, int);

	//�������f�t�H���g�t�H���g�ɐݒ肷��
	VOID SetDefaultFont(BOOL);

	//�f�X�g���N�^
	~FONT();

};
