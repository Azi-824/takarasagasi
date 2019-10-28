//SCENE.hpp

#pragma once

//********** �w�b�_�[�t�@�C���ǂݍ��� *************
#include "DxLib.h"
#include "KEYDOWN.hpp"

//########## �񋓌^ ##########
enum GAME_SCENE {
	GAME_SCENE_TITLE,	//�^�C�g�����
	GAME_SCENE_PLAY,	//�v���C���
	GAME_SCENE_END		//�G���h���
};

//********** �N���X�̒�` *****************
class SCENE
{
private:
	

public:

	int GameSceneNow;	//���݂̃Q�[���V�[��

	//�R���X�g���N�^
	SCENE();

	//�V�[����ݒ肷��
	VOID SetScene(int);

	//�^�C�g����ʂ̏���
	VOID SceneTitle(KEYDOWN *);

	//�v���C��ʂ̏���
	VOID ScenePlay(KEYDOWN *);

	//�G���h��ʂ̏���
	VOID SceneEnd(KEYDOWN *);

	//�f�X�g���N�^
	~SCENE();
};
