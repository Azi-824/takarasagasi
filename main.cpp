//********** ヘッダーファイル読み込み *************
#include "main.hpp"
#include "FPS.hpp"

//*********** グローバルオブジェクト ***********
FPS *fps = new FPS(GAME_FPS_SPEED);



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

		//▼▼▼▼▼▼▼ ゲームのシーンここから ▼▼▼▼▼▼▼▼



		//▲▲▲▲▲▲▲　ゲームのシーンここまで ▲▲▲▲▲▲▲▲

		fps->Draw(0, 0);				//FPSの処理(描画)

		ScreenFlip();					//モニタのリフレッシュレートの速さで裏画面を再描画

		fps->Wait();					//FPSの処理(待つ)

	}


	delete fps;				//fpsを破棄

	DxLib_End();			//DXライブラリ使用の終了処理

	return 0;
}