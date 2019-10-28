//FONT.cpp

//************ ヘッダーファイル読み込み ***************
#include "FONT.hpp"
#include "main.hpp"

//************ クラスの定義 ****************

//コンストラクタ
FONT::FONT(char setstr[][128])
{
	this->str[0][0] = &setstr[0][0];	//描画する文字列を設定

	return;
}

//画面中央に文字を描画
//引　数：char [][]：表示する文字列の先頭アドレス
//引　数：int　 　 ：表示する行数
//引　数：char *　 ：フォントの名前
//引　数：int　 　 ：文字の大きさ
//戻り値：なし
VOID FONT::DrawCenter(char str[][128], int row, char *fontname, int size)
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
			GetColor(255, 0, 0), &str[rCnt][0]);			//デフォルトのフォントで描画
	}

	SetDefaultFont(TRUE);	//デフォルトフォントに設定する

	return;

}

//文字をデフォルトフォントに設定する
VOID FONT:: SetDefaultFont(BOOL anti)
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

//デストラクタ
FONT::~FONT()
{
	return;
}

