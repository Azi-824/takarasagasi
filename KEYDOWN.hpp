//KEYDOWN.hpp

#pragma once

//************* �w�b�_�[�t�@�C���ǂݍ��� *************
#include "DxLib.h"

//************* �N���X�̒�` ***************
class KEYDOWN
{

private:
	static char AllKeyState[256];			//���ׂẴL�[�̏�Ԃ�����

public:

	//�R���X�g���N�^
	KEYDOWN();

	//�L�[�̓��͏����X�V����
	static VOID KeyDownUpdate(void);

	//�L�[��������Ă��邩���肷��
	BOOL IsKeyDown(int);

	//�f�X�g���N�^
	~KEYDOWN();

};
