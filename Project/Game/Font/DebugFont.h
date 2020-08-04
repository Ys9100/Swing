//======================================================
// File Name :DebugFont.h
// Content	 :�f�o�b�O�t�H���g������
// Author    :Yuki Sato
//======================================================
#pragma once

#include <DirectXTK\SimpleMath.h>
#include <DirectXTK\SpriteBatch.h>
#include <DirectXTK\SpriteFont.h>

// �V���O���g���̃^�C�v
// 0:���g�̐��|�C���^�ŊǗ��i���F�����I�ȉ�������Ȃ��ƃ��������[�N����j
// 1:���g�̃��j�[�N�|�C���^�ŊǗ��i���F���j�[�N�|�C���^�̗��𐄏��j
// 2:�ÓI�Ȏ��ԂŊǗ��i���F�v���O�����I���̃^�C�~���O�ł�������ł��Ȃ��j

#define DEBUG_FONT_SINGLETON_TYPE 1
class DebugFont
{
public:

	// ������ő吔�T�C�Y
	static const size_t STRING_SIZE_MAX = 256;
private:

	//�֐�	:�R���X�g���N�^
	DebugFont();
public:

	//�֐�	:�f�X�g���N�^
	~DebugFont();
public:

	//�֐�	:�t�H���g�̐���
	void create(ID3D11Device1* device, ID3D11DeviceContext1* context);

	//�֐�	:�t�H���g�̕`��
	void draw();

	//�֐�	:�t�H���g�̃��Z�b�g
	void reset();

	//�֐�	:�\�����o�^
	void print(float posX, float posY, wchar_t const* const format, ...);

	//�֐�	:�\�����o�^�iVector2�Łj
	void print(DirectX::SimpleMath::Vector2 pos, wchar_t const* const format, ...);
#if DEBUG_FONT_SINGLETON_TYPE == 0

#elif DEBUG_FONT_SINGLETON_TYPE == 1
public:
	//�֐�	:�I�u�W�F�N�g�ւ̃|�C���^��Ԃ�
	//����	:�Ȃ�
	//�߂�l:m_pInstance.get()
	static DebugFont* GetInstance()
	{
		if (m_pInstance.get() == nullptr)
		{
			// �I�u�W�F�N�g�𐶐����A�|�C���^��m_pInstance�ϐ��Ɋi�[����
			m_pInstance.reset(new DebugFont());
		}
		// �I�u�W�F�N�g�ւ̃|�C���^��Ԃ�
		return m_pInstance.get();
	}

	//�֐�	:�I�u�W�F�N�g��j������
	//����	:�Ȃ�
	//�߂�l:�Ȃ�
	static void Dispose()
	{
		if (m_pInstance)
			m_pInstance.reset();
	}

private:

	// �I�u�W�F�N�g�ւ̃|�C���^
	static std::unique_ptr<DebugFont> m_pInstance;
#else

#endif
private:

	//�t�H���g
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	//�t�H���g
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;

	//�X�g�����O
	wchar_t* m_string;

	//���W
	DirectX::SimpleMath::Vector2 m_pos;
};
