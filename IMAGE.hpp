// IMAGE.cpp
//	画像クラス


#pragma once

//********** ヘッダファイル読み込み *************
#include"DxLib.h"
#include<string>

//********** マクロ定義・画像のファイルパスと名前 **********
#define MY_IMG_DIR_BACK_1	R"(.\MY_IMG\BACKIMAGE\)"		//自機の画像ファイルの場所

#define MY_IMG_NAME_BACK_1	R"(back5.jpg)"	//背景画像の名前

//********* マクロ定義・エラーメッセージ ***********
#define IMAGE_ERROR_TITLE	"IMAGE_ERROR"					//エラータイトル
#define IMAGE_ERROR_MSG		"画像が読み込めませんでした"	//エラーメッセージ

//********* クラスの定義 ************

class IMAGE
{
private:
	std::string FilePath;	//パス
	std::string FileName;	//名前

	int Handle;				//ハンドル

	int X;					//X位置
	int Y;					//Y位置
	int Width;				//幅
	int Height;				//高さ

	bool IsLoad;			//読み込めたか？

	bool IsDraw;			//描画してもよい？

public:
	IMAGE(const char*, const char*);		//コンストラクタ
	virtual ~IMAGE();						//デストラクタ

	std::string GetFileName(void);			//名前を取得

	void SetX(int);							//X位置を設定
	void SetY(int);							//Y位置を設定
	int GetX(void);							//X位置を取得
	int GetY(void);							//Y位置を取得
	int GetWidth(void);						//幅を取得
	int GetHeight(void);					//高さを取得

	bool GetIsLoad(void);					//読み込めた？

	void Draw(void);						//画像を描画

};
