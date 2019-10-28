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

#define TITLE_BACKIMAGE	"MY_IMG\\BACKIMAGE\\back5.jpg"		//背景画像のパス
#define CHARA_IMAGE		"MY_IMG\\CHARA\\boal.png"			//プレイヤー画像のパス
#define ITEM_IMAGE		"MY_IMG\\ITEM\\box.png"				//宝箱の画像のパス

#define SCENE_KIND	3				//シーンの種類

//########## 列挙型 ##########
enum GAME_SCENE {
	GAME_SCENE_TITLE,	//タイトル画面
	GAME_SCENE_PLAY,	//プレイ画面
	GAME_SCENE_END		//エンド画面
};

enum BACKIMAGE_SCENE {
	BACKIMAGE_TITLE,	//タイトル画面の背景
	BACKIMAGE_PLAY,		//プレイ画面の背景
	BACKIMAGE_END		//エンド画面の背景
};

enum DIST {
	UP,		//上方向
	DOWN,	//下方向
	LEFT,	//左方向
	RIGHT	//右方向
};

//########## 構造体 ##########
struct STRUCT_GAZOU {
	int Handle;				//画像のハンドル
	char FilePath[128];		//ファイルのパス
	int X;					//横の位置
	int Y;					//縦の位置
	int Width;				//横のサイズ	
	int Height;				//縦のサイズ
	int C_Width;			//横の中心位置
	int C_Height;			//縦の中心位置
	int Direction;			//画像の移動向き
	BOOL Num_flg;			//数字用フラグ
	BOOL Positon_flg;		//座標設定完了用フラグ
	RECT rect;				//領域管理用
};

//****************名前の再定義********************
typedef STRUCT_GAZOU GAZOU;

//*********** グローバル変数 *************
int GameSceneNow;	//現在のゲームシーン
int BackImageNow = (int)BACKIMAGE_TITLE;	//現在の背景画像

int MoveSpead = 5;	//移動速度

GAZOU Back[SCENE_KIND];	//背景画像
GAZOU Chara;			//プレイヤー画像
GAZOU Item;				//宝箱の画像

//*********** プロトタイプ宣言 ***************
int SceneTitle();	//タイトル画面の処理
int ScenePlay();	//プレイ画面の処理
int SceneEnd();	//エンド画面の処理

BOOL MY_GAZOU_LOAD(GAZOU *, int, int, const char *);				//画像を読み込む関数

VOID DRAW_BACKIMAGE(GAZOU *);		//指定した背景画像を描画する関数
VOID DrawChara();					//プレイヤーを描画する関数
VOID DrawItem(GAZOU, int);			//アイテムを描画する関数

VOID MoveChara();				//プレイヤーを移動させる関数


VOID DrawCenter(char str[][128], int row, char *fontname, int size);	//中央に文字を描画する関数
VOID SetDefaultFont(BOOL anti);			//デフォルトフォントに設定する関数



