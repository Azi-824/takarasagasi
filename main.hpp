//main.hpp



#pragma once

//************ ヘッダーファイル読み込み ***********
#include "DxLib.h"

//************ マクロ定義 ***************
#define GAME_WIDTH		800				//画面の縦の大きさ
#define GAME_HEIGHT		600				//画面の横の大きさ
#define GAME_COLOR		32				//画面のカラービット

#define GAME_WINDOW_NAME		"GAME TITLE"	//ウィンドウのタイトル
#define GAME_WINDOW_MODECHANGE  TRUE			//TRUE:ウィンドウモード FALSE:フルスクリーン

#define SET_WINDOW_ST_MODE_DEFAULT				0		//デフォルト
#define SET_WINDOW_ST_MODE_TITLE_NONE			1		//タイトルバーなし
#define SET_WINDOW_ST_MODE_TITLE_FLAME_NONE		2		//タイトルバーとフレームなし
#define SET_WINDOW_ST_MODE_FLAME_NONE			3		//フレームなし

#define GAME_FPS_SPEED							60

//########## 列挙型 ##########
enum GAME_SCENE {
	GAME_SCENE_TITLE,	//タイトル画面
	GAME_SCENE_PLAY,	//プレイ画面
	GAME_SCENE_END		//エンド画面
};

//*********** グローバル変数 *************
int GameSceneNow;	//現在のゲームシーン

//*********** プロトタイプ宣言 ***************
int SceneTitle();	//タイトル画面の処理
int ScenePlay();	//プレイ画面の処理
int SceneEnd();	//エンド画面の処理

VOID DrawCenter(char str[][128], int row, char *fontname, int size);	//中央に文字を描画する関数
VOID SetDefaultFont(BOOL anti);			//デフォルトフォントに設定する関数



