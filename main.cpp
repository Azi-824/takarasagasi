//********** ヘッダーファイル読み込み *************
#include "DxLib.h"
#include "main.hpp"
#include "FPS.hpp"
#include "KEYDOWN.hpp"
#include "IMAGE.hpp"


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
	IMAGE *back = new IMAGE(MY_IMG_DIR_BACK_1, MY_IMG_NAME_BACK_1);
	if (back->GetIsLoad() == FALSE) { return -1; };	//画像読み込みチェック
	back->Draw();

	DrawString(0, 20, "タイトル画面", GetColor(255, 255, 255));

	//▼▼▼▼▼▼▼▼▼▼ タイトルの描画 ▼▼▼▼▼▼▼▼▼▼
	char StrGameTitle[1][128] = { "宝探し" };
	char StrFontTitle[128] = { "MS ゴシック" };	//大文字半角「MS」、半角「空白」、全角「ゴシック」

	DrawCenter(&StrGameTitle[0], 1, StrFontTitle, 64);		//画面中央に描画
	//▲▲▲▲▲▲▲▲▲▲ タイトルの描画 ▲▲▲▲▲▲▲▲▲▲


	if (keydown->IsKeyDown(KEY_INPUT_RETURN) == TRUE)	//エンターキーが押されていたら
	{
		GameSceneNow = (int)GAME_SCENE_PLAY;	//シーンをプレイ画面に変える
	}

	return 0;
}

//************* プレイ画面の処理 ****************
int ScenePlay()
{
	DrawString(300, 100, "Hello", GetColor(255, 255, 255));

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