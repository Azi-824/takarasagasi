//SCENE.cpp

//************* ヘッダーファイルの読み込み ************
#include "SCENE.hpp"
#include "KEYDOWN.hpp"


//************* クラスの定義 *****************

//コンストラクタ
SCENE::SCENE()
{
	this->GameSceneNow = (int)GAME_SCENE_TITLE;	//ゲームシーンをタイトル画面に設定

	return;
}

//シーンを設定する
VOID SCENE::SetScene(int next)
{
	this->GameSceneNow = next;		//指定されたシーンに設定する

	return;
}

//タイトル画面の処理
VOID SCENE::SceneTitle(KEYDOWN *keydown)
{

	DrawString(100, 100, "Hello", GetColor(255, 255, 255));


	if (keydown->IsKeyDown(KEY_INPUT_RETURN) == TRUE)	//エンターキーが押されていたら
	{
		this->SetScene(GAME_SCENE_PLAY);	//シーンをプレイ画面に変える
	}

	return;
}

//プレイ画面の処理
VOID SCENE::ScenePlay(KEYDOWN *keycode)
{
	DrawString(300, 100, "Hello", GetColor(255, 255, 255));

	return;
}

//エンド画面の処理
VOID SCENE::SceneEnd(KEYDOWN *keycode)
{

	return;
}

//デストラクタ
SCENE::~SCENE()
{
	return;
}

extern SCENE *GameScene;