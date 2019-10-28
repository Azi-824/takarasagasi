//KEYDOWN.hpp

#pragma once

//************* ヘッダーファイル読み込み *************
#include "DxLib.h"

//************* クラスの定義 ***************
class KEYDOWN
{

private:
	static char AllKeyState[256];			//すべてのキーの状態が入る

public:

	//コンストラクタ
	KEYDOWN();

	//キーの入力情報を更新する
	static VOID KeyDownUpdate(void);

	//キーが押されているか判定する
	BOOL IsKeyDown(int);

	//デストラクタ
	~KEYDOWN();

};
