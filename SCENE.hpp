//SCENE.hpp

#pragma once

//********** ヘッダーファイル読み込み *************
#include "DxLib.h"
#include "KEYDOWN.hpp"

//########## 列挙型 ##########
enum GAME_SCENE {
	GAME_SCENE_TITLE,	//タイトル画面
	GAME_SCENE_PLAY,	//プレイ画面
	GAME_SCENE_END		//エンド画面
};

//********** クラスの定義 *****************
class SCENE
{
private:
	

public:

	int GameSceneNow;	//現在のゲームシーン

	//コンストラクタ
	SCENE();

	//シーンを設定する
	VOID SetScene(int);

	//タイトル画面の処理
	VOID SceneTitle(KEYDOWN *);

	//プレイ画面の処理
	VOID ScenePlay(KEYDOWN *);

	//エンド画面の処理
	VOID SceneEnd(KEYDOWN *);

	//デストラクタ
	~SCENE();
};
