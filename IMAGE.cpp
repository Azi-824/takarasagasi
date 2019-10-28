// IMAGE.cpp


//********** ヘッダーファイルの読み込み ************
#include"IMAGE.hpp"

//********** クラスの定義 *************

//コンストラクタ
//引数: const char* :画像のディレクトリ
//引数: const char* :画像の名前
IMAGE::IMAGE(const char *dir, const char *name)
{
	//メンバ変数を初期化
	this->FilePath = "";	//パス
	this->FileName = "";	//名前

	this->Handle = -1;		//ハンドル

	this->X = 0;			//X位置
	this->Y = 0;			//Y位置
	this->Width = 0;		//幅
	this->Height = 0;		//高さ

	this->IsLoad = false;	//読み込めたか？

	this->IsDraw = false;	//描画してはいけない

	//画像を読み込み
	std::string LoadfilePath;	//画像のファイルパスを作成
	LoadfilePath += dir;
	LoadfilePath += name;

	this->Handle = LoadGraph(LoadfilePath.c_str());	//画像を読み込み

	if (this->Handle == -1)	//画像が読み込めなかったとき
	{
		std::string ErrorMsg(IMAGE_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');					//改行
		ErrorMsg += LoadfilePath;				//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char *を返す
			TEXT(IMAGE_ERROR_TITLE),
			MB_OK);

		return;
	}

	this->FilePath = LoadfilePath;		//画像のパスを設定
	this->FileName = name;				//画像の名前を設定

	GetGraphSize(
		this->Handle,		//このハンドルの画像の大きさを取得
		&this->Width,		//Widthのアドレスを渡す
		&this->Height		//Heightのアドレスを渡す
	);

	this->IsLoad = true;	//読み込めた

	this->IsDraw = true;	//描画してよい

	return;
}

//デストラクタ
IMAGE::~IMAGE()
{
	DeleteGraph(this->Handle);		//読み込んだ画像を削除
	return;
}

//ファイルの名前を取得
std::string IMAGE::GetFileName(void)
{
	return this->FileName;
}

//X位置を設定
void IMAGE::SetX(int numX)
{
	this->X = numX;	return;
}

//Y位置を設定
void IMAGE::SetY(int numY)
{
	this->Y = numY;	return;
}

//X位置を取得
int IMAGE::GetX(void)
{
	return this->X;
}

//Y位置を取得
int IMAGE::GetY(void)
{
	return this->Y;
}

//幅を取得
int IMAGE::GetWidth(void)
{
	return this->Width;
}

//高さを取得
int IMAGE::GetHeight(void)
{
	return this->Height;
}

//読み込めた？
bool IMAGE::GetIsLoad(void)
{
	return this->IsLoad;
}

//画像を描画
void IMAGE::Draw(void)
{
	if (this->IsDraw == true)	//描画してよいなら
	{
		DrawGraph(this->X, this->Y, this->Handle, TRUE);
	}
	return;
}