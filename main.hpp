//main.hpp



#pragma once

//************ �w�b�_�[�t�@�C���ǂݍ��� ***********
#include "DxLib.h"

//************ �}�N����` ***************
#define GAME_WIDTH		800				//��ʂ̏c�̑傫��
#define GAME_HEIGHT		600				//��ʂ̉��̑傫��
#define GAME_COLOR		32				//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_NAME		"GAME TITLE"	//�E�B���h�E�̃^�C�g��
#define GAME_WINDOW_MODECHANGE  TRUE			//TRUE:�E�B���h�E���[�h FALSE:�t���X�N���[��

#define SET_WINDOW_ST_MODE_DEFAULT				0		//�f�t�H���g
#define SET_WINDOW_ST_MODE_TITLE_NONE			1		//�^�C�g���o�[�Ȃ�
#define SET_WINDOW_ST_MODE_TITLE_FLAME_NONE		2		//�^�C�g���o�[�ƃt���[���Ȃ�
#define SET_WINDOW_ST_MODE_FLAME_NONE			3		//�t���[���Ȃ�

#define GAME_FPS_SPEED							60

#define TITLE_BACKIMAGE	"MY_IMG\\BACKIMAGE\\back5.jpg"		//�w�i�摜�̃p�X
#define CHARA_IMAGE		"MY_IMG\\CHARA\\boal.png"			//�v���C���[�摜�̃p�X
#define ITEM_IMAGE		"MY_IMG\\ITEM\\box.png"				//�󔠂̉摜�̃p�X

#define SCENE_KIND	3				//�V�[���̎��

//########## �񋓌^ ##########
enum GAME_SCENE {
	GAME_SCENE_TITLE,	//�^�C�g�����
	GAME_SCENE_PLAY,	//�v���C���
	GAME_SCENE_END		//�G���h���
};

enum BACKIMAGE_SCENE {
	BACKIMAGE_TITLE,	//�^�C�g����ʂ̔w�i
	BACKIMAGE_PLAY,		//�v���C��ʂ̔w�i
	BACKIMAGE_END		//�G���h��ʂ̔w�i
};

enum DIST {
	UP,		//�����
	DOWN,	//������
	LEFT,	//������
	RIGHT	//�E����
};

//########## �\���� ##########
struct STRUCT_GAZOU {
	int Handle;				//�摜�̃n���h��
	char FilePath[128];		//�t�@�C���̃p�X
	int X;					//���̈ʒu
	int Y;					//�c�̈ʒu
	int Width;				//���̃T�C�Y	
	int Height;				//�c�̃T�C�Y
	int C_Width;			//���̒��S�ʒu
	int C_Height;			//�c�̒��S�ʒu
	int Direction;			//�摜�̈ړ�����
	BOOL Num_flg;			//�����p�t���O
	BOOL Positon_flg;		//���W�ݒ芮���p�t���O
	RECT rect;				//�̈�Ǘ��p
};

//****************���O�̍Ē�`********************
typedef STRUCT_GAZOU GAZOU;

//*********** �O���[�o���ϐ� *************
int GameSceneNow;	//���݂̃Q�[���V�[��
int BackImageNow = (int)BACKIMAGE_TITLE;	//���݂̔w�i�摜

int MoveSpead = 5;	//�ړ����x

GAZOU Back[SCENE_KIND];	//�w�i�摜
GAZOU Chara;			//�v���C���[�摜
GAZOU Item;				//�󔠂̉摜

//*********** �v���g�^�C�v�錾 ***************
int SceneTitle();	//�^�C�g����ʂ̏���
int ScenePlay();	//�v���C��ʂ̏���
int SceneEnd();	//�G���h��ʂ̏���

BOOL MY_GAZOU_LOAD(GAZOU *, int, int, const char *);				//�摜��ǂݍ��ފ֐�

VOID DRAW_BACKIMAGE(GAZOU *);		//�w�肵���w�i�摜��`�悷��֐�
VOID DrawChara();					//�v���C���[��`�悷��֐�
VOID DrawItem(GAZOU, int);			//�A�C�e����`�悷��֐�

VOID MoveChara();				//�v���C���[���ړ�������֐�


VOID DrawCenter(char str[][128], int row, char *fontname, int size);	//�����ɕ�����`�悷��֐�
VOID SetDefaultFont(BOOL anti);			//�f�t�H���g�t�H���g�ɐݒ肷��֐�



