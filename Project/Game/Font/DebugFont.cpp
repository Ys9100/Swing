//======================================================
// File Name :DebugFont.cpp
// Content	 :�f�o�b�O�t�H���g������
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

//�֐�	:�R���X�g���N�^
//����	:�Ȃ�
//�߂�l:�Ȃ�
DebugFont::DebugFont()
	: m_pos(0, 0)
	, m_string(nullptr)
{
	m_string = new wchar_t[STRING_SIZE_MAX];
}

//�֐�	:�f�X�g���N�^
//����	:�Ȃ�
//�߂�l:�Ȃ�
DebugFont::~DebugFont()
{
	delete[] m_string;
}

//�֐�	:�t�H���g�̐���
//����	:device,context
//�߂�l:�Ȃ�
void DebugFont::create(ID3D11Device1* device, ID3D11DeviceContext1* context)
{
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(device, L"Resources\\Fonts\\SegoeUI_18.spritefont");
}

//�֐�	:�t�H���g�̕`��
//����	:�Ȃ�
//�߂�l:�Ȃ�
void DebugFont::draw()
{
	//�`��J�n
	m_spriteBatch->Begin();

	//�`��
	m_spriteFont->DrawString(m_spriteBatch.get(), m_string, m_pos);

	//�`��I��
	m_spriteBatch->End();
}

//�֐�	:�t�H���g�̃��Z�b�g
//����	:�Ȃ�
//�߂�l:�Ȃ�
void DebugFont::reset()
{
	//�t�H���g���Z�b�g
	m_spriteBatch.reset();

	//�t�H���g���Z�b�g
	m_spriteFont.reset();
}
//�֐�	:�\�����o�^
//����	:posX,posY,format
//�߂�l:�Ȃ�
void DebugFont::print(float posX, float posY, wchar_t const * const format, ...)
{
	m_pos.x = posX;
	m_pos.y = posY;
	va_list arg_ptr;
	va_start(arg_ptr, format);
	vswprintf(m_string, STRING_SIZE_MAX, format, arg_ptr);
	va_end(arg_ptr);
}

//�֐�	:�\�����o�^�iVector2�Łj
//����	:pos,format
//�߂�l:�Ȃ�
void DebugFont::print(DirectX::SimpleMath::Vector2 pos, wchar_t const * const format, ...)
{
	m_pos = pos;
	va_list arg_ptr;
	va_start(arg_ptr, format);
	vswprintf(m_string, STRING_SIZE_MAX, format, arg_ptr);
	va_end(arg_ptr);
}