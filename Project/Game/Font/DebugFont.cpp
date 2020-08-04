//======================================================
// File Name :DebugFont.cpp
// Content	 :デバッグフォントを扱う
// Author    :Yuki Sato
//======================================================

#include "DebugFont.h"

#if DEBUG_FONT_SINGLETON_TYPE == 0
DebugFont* DebugFont::m_pInstance = nullptr;
#elif DEBUG_FONT_SINGLETON_TYPE == 1
std::unique_ptr<DebugFont> DebugFont::m_pInstance = nullptr;
#else
DebugFont DebugFont::m_instance;
#endif

//関数	:コンストラクタ
//引数	:なし
//戻り値:なし
DebugFont::DebugFont()
	: m_pos(0, 0)
	, m_string(nullptr)
{
	m_string = new wchar_t[STRING_SIZE_MAX];
}

//関数	:デストラクタ
//引数	:なし
//戻り値:なし
DebugFont::~DebugFont()
{
	delete[] m_string;
}

//関数	:フォントの生成
//引数	:device,context
//戻り値:なし
void DebugFont::create(ID3D11Device1* device, ID3D11DeviceContext1* context)
{
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(device, L"Resources\\Fonts\\SegoeUI_18.spritefont");
}

//関数	:フォントの描画
//引数	:なし
//戻り値:なし
void DebugFont::draw()
{
	//描画開始
	m_spriteBatch->Begin();

	//描画
	m_spriteFont->DrawString(m_spriteBatch.get(), m_string, m_pos);

	//描画終了
	m_spriteBatch->End();
}

//関数	:フォントのリセット
//引数	:なし
//戻り値:なし
void DebugFont::reset()
{
	//フォントリセット
	m_spriteBatch.reset();

	//フォントリセット
	m_spriteFont.reset();
}
//関数	:表示情報登録
//引数	:posX,posY,format
//戻り値:なし
void DebugFont::print(float posX, float posY, wchar_t const * const format, ...)
{
	m_pos.x = posX;
	m_pos.y = posY;
	va_list arg_ptr;
	va_start(arg_ptr, format);
	vswprintf(m_string, STRING_SIZE_MAX, format, arg_ptr);
	va_end(arg_ptr);
}

//関数	:表示情報登録（Vector2版）
//引数	:pos,format
//戻り値:なし
void DebugFont::print(DirectX::SimpleMath::Vector2 pos, wchar_t const * const format, ...)
{
	m_pos = pos;
	va_list arg_ptr;
	va_start(arg_ptr, format);
	vswprintf(m_string, STRING_SIZE_MAX, format, arg_ptr);
	va_end(arg_ptr);
}