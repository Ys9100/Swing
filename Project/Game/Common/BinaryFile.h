//======================================================
// File Name :BinaryFile.h
// Content	 :バイナリファイルを扱う
// Author    :Yuki Sato
//======================================================

/// <summary>
/// バイナリファイルを扱うクラス
/// </summary>

#pragma once


#include <memory>


class BinaryFile
{
public:

	//ファイル名を指定してロード
	static BinaryFile LoadFile(const wchar_t* fileName);

	//コンストラクタ
	BinaryFile();

	//ムーブコンストラクタ
	BinaryFile(BinaryFile&& in);

	//関数	:データを獲得
	//引数	:なし
	//戻り値:m_Data.get()
	char* GetData() { return m_Data.get(); }

	//関数	:サイズを獲得
	//引数	:なし
	//戻り値:m_Size
	unsigned int GetSize() { return m_Size; }

protected:

	// データ
	std::unique_ptr<char[]> m_Data;
	// サイズ
	unsigned int m_Size;
};
