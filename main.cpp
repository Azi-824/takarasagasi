//********** ヘッダーファイル読み込み *************
#include "DxLib.h"
#include "main.hpp"
#include "FPS.hpp"
#include "KEYDOWN.hpp"


//*********** グローバルオブジェクト ***********
FPS *fps = new FPS(GAME_FPS_SPEED);
KEYDOWN *keydown = new KEYDOWN();


//*********** プログラムで最初に実行される関数 ***************
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(GAME_WINDOW_MODECHANGE);
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);

	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);

	SetMainWindowText(TEXT(GAME_WINDOW_NAME));

	if (DxLib_Init() == -1) { return -1; }

	SetDrawScreen(DX_SCREEN_BACK);

	//背景画像の読み込み
	if (MY_GAZOU_LOAD(&Back[BACKIMAGE_TITLE], 0, 0, TITLE_BACKIMAGE) == FALSE) { MessageBox(NULL, TITLE_BACKIMAGE, "NotFound", MB_OK); return -1; }		//タイトル画面の背景画像を読み込む

	//プレイヤー画像の読み込み
	if (MY_GAZOU_LOAD(&Chara, 0, 0, CHARA_IMAGE) == FALSE) { MessageBox(NULL, CHARA_IMAGE, "NotFound", MB_OK); return -1; }		//プレイヤー画像を読み込む


	while (TRUE)		//無限ループ
	{
		if (ProcessMessage() != 0) { break; }	//メッセージ処理の結果がエラーの時、強制終了

		if (ClearDrawScreen() != 0) { break; }	//画面を消去できなかったとき、強制終了

		fps->Update();		//FPSの処理[更新]

		keydown->KeyDownUpdate();	//キーの状態を取得

		//▼▼▼▼▼▼▼ ゲームのシーンここから ▼▼▼▼▼▼▼▼

		//画面ごとの処理
		switch (GameSceneNow)
		{
		case (int)GAME_SCENE_TITLE:				//タイトル画面の時

			SceneTitle();						//タイトル画面の処理

			break;

		case (int)GAME_SCENE_PLAY:				//プレイ画面の時

			ScenePlay();						//プレイ画面の処理

			break;

		case (int)GAME_SCENE_END:				//エンド画面の処理

			SceneEnd();							//エンド画面の処理

			break;

		default:
			break;

		}

		//▲▲▲▲▲▲▲　ゲームのシーンここまで ▲▲▲▲▲▲▲▲

		fps->Draw(0, 0);				//FPSの処理(描画)

		ScreenFlip();					//モニタのリフレッシュレートの速さで裏画面を再描画

		fps->Wait();					//FPSの処理(待つ)

	}


	delete fps;				//fpsを破棄
	delete keydown;			//keydownを破棄

	DxLib_End();			//DXライブラリ使用の終了処理

	return 0;
}

//************** タイトル画面の処理 ***************
int SceneTitle()
{
	DRAW_BACKIMAGE(&Back[BackImageNow]);	//背景の描画

	DrawString(0, 20, "タイトル画面", GetColor(255, 255, 255));

	//▼▼▼▼▼▼▼▼▼▼ タイトルの描画 ▼▼▼▼▼▼▼▼▼▼
	char StrGameTitle[1][128] = { "宝探し" };
	char StrFontTitle[128] = { "MS ゴシック" };	//大文字半角「MS」、半角「空白」、全角「ゴシック」

	DrawCenter(&StrGameTitle[0], 1, StrFontTitle, 64);		//画面中央に描画
	//▲▲▲▲▲▲▲▲▲▲ タイトルの描画 ▲▲▲▲▲▲▲▲▲▲


	if (keydown->IsKeyDown(KEY_INPUT_RETURN) == TRUE)	//エンターキーが押されていたら
	{
		BackImageNow = (int)BACKIMAGE_PLAY;		//背景画像をプレイ画面に変える
		GameSceneNow = (int)GAME_SCENE_PLAY;	//シーンをプレイ画面に変える
	}

	return 0;
}

//************* プレイ画面の処理 ****************
int ScenePlay()
{

	DrawChara();	//プレイヤーの描画処理

	return 0;
}

//************* エンド画面の処理 ***************
int SceneEnd()
{
	return 0;
}

//************* 画面中央に文字を描画する関数 *************
VOID DrawCenter(char str[][128], int row, char *fontname, int size)
{
	ChangeFont(fontname, DX_CHARSET_DEFAULT);		//デフォルトのフォントを変更する
	SetFontSize(size);								//デフォルトのフォントサイズを変える
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);	//フォントをきれいにみせる

	int StrHeightSum = 0;
	for (int sum = 0; sum < row; sum++)	//行全体の高さを集計
	{
		StrHeightSum += GetFontSize();	//デフォルトのフォントの高さを取得
	}

	for (int rCnt = 0; rCnt < row; rCnt++)	//フォントを描画
	{
		int StrWidth = GetDrawFormatStringWidth(&str[rCnt][0]);	//デフォルトのフォントの横幅を取得
		int StrHeight = GetFontSize();

		DrawFormatString(
			GAME_WIDTH / 2 - StrWidth / 2,
			GAME_HEIGHT / 2 - StrHeightSum + StrHeight * rCnt,	//画面の中心　-　行全体の文字の高さ　+　１行の高さ
			GetColor(255, 255, 255), &str[rCnt][0]);			//デフォルトのフォントで描画
	}

	SetDefaultFont(TRUE);	//デフォルトフォントに設定する

	return;

}

//***********デフォルトフォントに設定する関数 *************
VOID SetDefaultFont(BOOL anti)
{
	//デフォルトは以下のフォントサイズであると、設定する
	ChangeFont("MS ゴシック", DX_CHARSET_DEFAULT);
	SetFontSize(16);

	if (anti)
	{
		ChangeFontType(DX_FONTTYPE_ANTIALIASING);
	}
	return;

}

//########## 画像を読み込む設定をする関数 ##########

//引　数：画像構造体　：設定する画像構造体の変数
//引　数：int　：画像の横の位置
//引　数：int　：画像の縦の位置
//引　数：const char *：読み込む画像のファイルパス
//戻り値：BOOL：エラー時：FALSE
BOOL MY_GAZOU_LOAD(GAZOU *g, int x, int y, const char *path)
{
	wsprintf(g->FilePath, path);					//ファイルパスをコピー
	g->Handle = LoadGraph(g->FilePath);				//画像をメモリに読み込み、ハンドルを取得

	if (g->Handle == -1) { return FALSE; }			//画像読み込みエラー

	GetGraphSize(g->Handle, &g->Width, &g->Height);	//画像サイズを取得
	g->X = x;
	g->Y = y;
	g->C_Width = g->Width / 2;						//画像の横サイズの中心を取得
	g->C_Height = g->Height / 2;					//画像の縦サイズの中心を取得

	//領域の設定
	g->rect.left = x;				//左上
	g->rect.top = y;				//左上
	g->rect.right = x + g->Width;	//右下
	g->rect.bottom = y + g->Height;	//右下

	return TRUE;

}

//########### 指定した背景画像を描画する関数 ###########
VOID DRAW_BACKIMAGE(GAZOU *back)
{
	DrawGraph(back->X, back->Y, back->Handle, FALSE);	//背景の描画
}

//************ プレイヤーを描画する関数 *************
VOID DrawChara()
{
	MoveChara();	//プレイヤーを移動させる関数
	DrawGraph(Chara.X, Chara.Y, Chara.Handle, FALSE);	//プレイヤーの描画
}

//************ プレイヤーの位置を動かす関数 *************
VOID MoveChara()
{

	if (keydown->IsKeyDown(KEY_INPUT_UP) == TRUE)			//上矢印キーが押されていたら
	{
		if (Chara.rect.top > 0)	//画面内なら
		{
			Chara.Y -= MoveSpead;	//上へ移動
			Chara.rect.top -= MoveSpead;	//領域を上へ移動
			Chara.rect.bottom -= MoveSpead;	//領域を上へ移動
		}
	}	
	else if (keydown->IsKeyDown(KEY_INPUT_DOWN) == TRUE)	//下矢印キーが押されていたら
	{
		if (Chara.rect.bottom < GAME_HEIGHT)	//画面無いなら
		{
			Chara.Y += MoveSpead;	//下へ移動
			Chara.rect.top += MoveSpead;	//領域を下へ移動
			Chara.rect.bottom += MoveSpead;	//領域を下へ移動
		}
	}	
	else if (keydown->IsKeyDown(KEY_INPUT_LEFT) == TRUE)	//左矢印キーが押されていたら
	{
		if (Chara.rect.left > 0)	//画面無いなら
		{
			Chara.X -= MoveSpead;	//左へ移動
			Chara.rect.left -= MoveSpead;	//領域を左へ移動
			Chara.rect.right -= MoveSpead;	//領域を左へ移動
		}
	}
	else if (keydown->IsKeyDown(KEY_INPUT_RIGHT) == TRUE)	//右矢印キーが押されていたら
	{
		if (Chara.rect.right < GAME_WIDTH)	//画面無いなら
		{
			Chara.X += MoveSpead;	//右へ移動
			Chara.rect.left += MoveSpead;	//領域を右へ移動
			Chara.rect.right += MoveSpead;	//領域を右へ移動
		}
	}
	return;
}

