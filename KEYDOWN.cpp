//KEYDOW.cpp

//************ ヘッダーファイルの読み込み *************
#include "KEYDOWN.hpp"

//*********** クラスの定義 *************

char KEYDOWN::AllKeyState[256];

//コンストラクタ
KEYDOWN::KEYDOWN()
{
	return;
}

//キーの入力情報を更新する
VOID KEYDOWN::KeyDownUpdate()
{
	char TempKey[256];			//一時的に、現在のキーの入力状態を格納する

	GetHitKeyStateAll(TempKey); // 全てのキーの入力状態を得る

	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)	//押されているキーのキーコードを押しているとき
		{
			AllKeyState[i]++;	//押されている
		}
		else
		{
			AllKeyState[i] = 0;	//押されていない
		}
	}

	return;
}

//キーが押されているか判定する
BOOL KEYDOWN::IsKeyDown(int keycode)
{
	if (this->AllKeyState[keycode] != 0)
		return TRUE;
	else
		return FALSE;
}

//デストラクタ
KEYDOWN::~KEYDOWN()
{
	return;
}

//*********** 外部オブジェクト *************
extern KEYDOWN *keydown;