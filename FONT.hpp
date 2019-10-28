//FONT.hpp

#pragma once

//*********** ヘッダーファイル読み込み *************
#include "DxLib.h"

//********** クラスの定義 ************

class FONT
{
private: 
	char *str[][128];	//描画する文字列を入れる配列
public:
	//コンストラクタ
	FONT(char [][128]);

	//画面中央に文字を描画
	VOID DrawCenter(char [][128], int, char *, int);

	//文字をデフォルトフォントに設定する
	VOID SetDefaultFont(BOOL);

	//デストラクタ
	~FONT();

};
