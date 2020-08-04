//======================================================
// File Name :DebugFont.h
// Content	 :デバッグフォントを扱う
// Author    :Yuki Sato
//======================================================
#pragma once

#include <DirectXTK\SimpleMath.h>
#include <DirectXTK\SpriteBatch.h>
#include <DirectXTK\SpriteFont.h>

// シングルトンのタイプ
// 0:自身の生ポインタで管理（注：明示的な解放をしないとメモリリークする）
// 1:自身のユニークポインタで管理（注：ユニークポインタの理解推奨）
// 2:静的な実態で管理（注：プログラム終了のタイミングでしか解放できない）

#define DEBUG_FONT_SINGLETON_TYPE 1
class DebugFont
{
public:

	// 文字列最大数サイズ
	static const size_t STRING_SIZE_MAX = 256;
private:

	//関数	:コンストラクタ
	DebugFont();
public:

	//関数	:デストラクタ
	~DebugFont();
public:

	//関数	:フォントの生成
	void create(ID3D11Device1* device, ID3D11DeviceContext1* context);

	//関数	:フォントの描画
	void draw();

	//関数	:フォントのリセット
	void reset();

	//関数	:表示情報登録
	void print(float posX, float posY, wchar_t const* const format, ...);

	//関数	:表示情報登録（Vector2版）
	void print(DirectX::SimpleMath::Vector2 pos, wchar_t const* const format, ...);
#if DEBUG_FONT_SINGLETON_TYPE == 0

#elif DEBUG_FONT_SINGLETON_TYPE == 1
public:
	//関数	:オブジェクトへのポインタを返す
	//引数	:なし
	//戻り値:m_pInstance.get()
	static DebugFont* GetInstance()
	{
		if (m_pInstance.get() == nullptr)
		{
			// オブジェクトを生成し、ポインタをm_pInstance変数に格納する
			m_pInstance.reset(new DebugFont());
		}
		// オブジェクトへのポインタを返す
		return m_pInstance.get();
	}

	//関数	:オブジェクトを破棄する
	//引数	:なし
	//戻り値:なし
	static void Dispose()
	{
		if (m_pInstance)
			m_pInstance.reset();
	}

private:

	// オブジェクトへのポインタ
	static std::unique_ptr<DebugFont> m_pInstance;
#else

#endif
private:

	//フォント
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	//フォント
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;

	//ストリング
	wchar_t* m_string;

	//座標
	DirectX::SimpleMath::Vector2 m_pos;
};
