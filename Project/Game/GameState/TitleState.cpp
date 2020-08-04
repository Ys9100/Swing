//======================================================
// File Name :TitleState.cpp
// Content	 :�^�C�g���[�V�[���ɂ���
// Author    :Yuki Sato
//======================================================

#include "TitleState.h"

#include <DirectXTK\Mouse.h>
#include <DirectXTK\CommonStates.h>
#include "Game\Font\DebugFont.h"
#include "Game\Common\GameContext.h"
#include "Game\GameState\GameStateManager.h"

//�֐�	:�R���X�g���N�^
//����	:�Ȃ�
//�߂�l:�Ȃ�
TitleState::TitleState()
	: IGameState()
	, m_count(0)
{
}


//�֐�	:�f�X�g���N�^
//����	:�Ȃ�
//�߂�l:�Ȃ�
TitleState::~TitleState()
{
}


//�֐�	:������
//����	:�Ȃ�
//�߂�l:�Ȃ�
void TitleState::Initialize()
{
	//�J�E���g������
	m_count = 0;
}


//�֐�	:�X�V
//����	:�Ȃ�
//�߂�l:�Ȃ�
void TitleState::Update()
{
	//Mouse��Get
	DirectX::Mouse::State mouse = DirectX::Mouse::Get().GetState();

	//�N���b�N���ɃV�[�����v���C�V�[���ֈڍs
	if (mouse.leftButton)
	{
		//GameStateManager��Get
		GameStateManager* gameStateManager = GameContext<GameStateManager>::Get();

		//���̃V�[�����w��
		gameStateManager->RequestState("Play");
	}
}


//�֐�	:�`��
//����	:�Ȃ�
//�߂�l:�Ȃ�
void TitleState::Render()
{
	//�f�o�b�O�t�H���g
	DebugFont* debugFont = DebugFont::GetInstance();

	//�t�H���g�\��
	debugFont->print(10, 10, L"Swing");

	//�t�H���g�\��
	debugFont->print(10, 30, L"Play[MouseLeftButton]");

	//�t�H���g�`��J�n
	debugFont->draw();
}


//�֐�	:�I������
//����	:�Ȃ�
//�߂�l:�Ȃ�
void TitleState::Finalize()
{
	
}
