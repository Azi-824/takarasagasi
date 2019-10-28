//KEYDOW.cpp

//************ �w�b�_�[�t�@�C���̓ǂݍ��� *************
#include "KEYDOWN.hpp"

//*********** �N���X�̒�` *************

char KEYDOWN::AllKeyState[256];

//�R���X�g���N�^
KEYDOWN::KEYDOWN()
{
	return;
}

//�L�[�̓��͏����X�V����
VOID KEYDOWN::KeyDownUpdate()
{
	char TempKey[256];			//�ꎞ�I�ɁA���݂̃L�[�̓��͏�Ԃ��i�[����

	GetHitKeyStateAll(TempKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�

	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)	//������Ă���L�[�̃L�[�R�[�h�������Ă���Ƃ�
		{
			AllKeyState[i]++;	//������Ă���
		}
		else
		{
			AllKeyState[i] = 0;	//������Ă��Ȃ�
		}
	}

	return;
}

//�L�[��������Ă��邩���肷��
BOOL KEYDOWN::IsKeyDown(int keycode)
{
	if (this->AllKeyState[keycode] != 0)
		return TRUE;
	else
		return FALSE;
}

//�f�X�g���N�^
KEYDOWN::~KEYDOWN()
{
	return;
}

//*********** �O���I�u�W�F�N�g *************
extern KEYDOWN *keydown;