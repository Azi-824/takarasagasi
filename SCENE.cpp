//SCENE.cpp

//************* �w�b�_�[�t�@�C���̓ǂݍ��� ************
#include "SCENE.hpp"
#include "KEYDOWN.hpp"


//************* �N���X�̒�` *****************

//�R���X�g���N�^
SCENE::SCENE()
{
	this->GameSceneNow = (int)GAME_SCENE_TITLE;	//�Q�[���V�[�����^�C�g����ʂɐݒ�

	return;
}

//�V�[����ݒ肷��
VOID SCENE::SetScene(int next)
{
	this->GameSceneNow = next;		//�w�肳�ꂽ�V�[���ɐݒ肷��

	return;
}

//�^�C�g����ʂ̏���
VOID SCENE::SceneTitle(KEYDOWN *keydown)
{

	DrawString(100, 100, "Hello", GetColor(255, 255, 255));


	if (keydown->IsKeyDown(KEY_INPUT_RETURN) == TRUE)	//�G���^�[�L�[��������Ă�����
	{
		this->SetScene(GAME_SCENE_PLAY);	//�V�[�����v���C��ʂɕς���
	}

	return;
}

//�v���C��ʂ̏���
VOID SCENE::ScenePlay(KEYDOWN *keycode)
{
	DrawString(300, 100, "Hello", GetColor(255, 255, 255));

	return;
}

//�G���h��ʂ̏���
VOID SCENE::SceneEnd(KEYDOWN *keycode)
{

	return;
}

//�f�X�g���N�^
SCENE::~SCENE()
{
	return;
}

extern SCENE *GameScene;