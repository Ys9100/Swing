//======================================================
// File Name :PlayerState.cpp
// Content	 :�v���C�[�V�[���ɂ���
// Author    :Yuki Sato
//======================================================

#include "PlayState.h"

#include <DirectXTK\Mouse.h>
#include<DirectXTK\Keyboard.h>
#include "Game\Game.h"
#include "Game\Common\GameContext.h"
#include "Game\GameState\GameStateManager.h"
#include "Game\Camera\FollowCamera.h"
#include"Game\Collision\Collision.h"


//�J�����̃^�[�Q�b�g
const DirectX::SimpleMath::Vector3 PlayState::TARGET_TO_EYE_VEC(0.0f, 0.0f, 20.0f);

using namespace DirectX;

using Microsoft::WRL::ComPtr;

//s_post��nullptr�ɂ���
Post* PlayState::s_post = nullptr;

//�֐�	:�R���X�g���N�^
//����	:�Ȃ�
//�߂�l:�Ȃ�
PlayState::PlayState()
	: IGameState()
{
	
}


//�֐�	:�f�X�g���N�^
//����	:�Ȃ�
//�߂�l:�Ȃ�
PlayState::~PlayState()
{

}


//�֐�	:������
//����	:�Ȃ�
//�߂�l:�Ȃ�
void PlayState::Initialize()
{
	//�v���C���[���l��
	m_player = std::make_unique<Player>();
	
	//�v���C���[�̏�����
	m_player->Initialize();

	//�x�����l��
	m_post = std::make_unique<Post>();

	//�x���̏�����
	m_post->Initialize();

	//�x�����l��
	s_post = m_post.get();
	
	//CreateDeviceDependentResources������
	CreateDeviceDependentResources();
	
	m_cameraswing = DirectX::SimpleMath::Vector3(0.0f,0.0f, 20.0f);
}


//�֐�	:�X�V
//����	:�Ȃ�
//�߂�l:�Ȃ�
void PlayState::Update()
{
	//FollowCamera��Get
	FollowCamera* m_camera = GameContext<FollowCamera>::Get();
	
	//Keyboard��Get
	DirectX::Keyboard::State keyboard = DirectX::Keyboard::Get().GetState();

	//�v���C���[�̍X�V
	m_player->Update();

	//�x���̍X�V
	m_post->Update();

	//�J������Z����-1.0f������
	if (keyboard.W)
	{
		m_cameraswing.z -= 1.0f;
	}

	//�J������Z����+1.0f������
	if (keyboard.S)
	{
		m_cameraswing.z += 1.0f;
	}

	if (keyboard.Q)
	{
		//GameStateManager��Get
		GameStateManager* gameStateManager = GameContext<GameStateManager>::Get();

		//���̃V�[�����w��
		gameStateManager->RequestState("Play");
	}
	//�J�����̃Z�b�g
	m_camera->SetRefEyePos(m_cameraswing);

	//�J�����̍X�V
	m_camera->update();
}


//�֐�	:�`��
//����	:�Ȃ�
//�߂�l:�Ȃ�
void PlayState::Render()
{
	//�v���C���[�̕`��
	m_player->Render();

	//�x���̕`��
	m_post->Render();

	//�t�H���g�̕`��J�n
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_pState->NonPremultiplied());
	
	//�t�H���g�̕`��
	m_spriteFont->DrawString(m_spriteBatch.get(), "PlayState", SimpleMath::Vector2(0, 0), Colors::White);

	//�t�H���g�̕`��I��
	m_spriteBatch->End();
}


//�֐�	:�I������
//����	:�Ȃ�
//�߂�l:�Ȃ�
void PlayState::Finalize()
{
	//�v���C���[�̏I��
	m_player->Finalize();

	//�x���̏I��
	m_post->Finalize();

	//�R�����X�e�[�g�̏I��
	m_pState.reset();
	
	//�t�H���g�̏I��
	m_spriteBatch.reset();

	//�t�H���g�̏I��
	m_spriteFont.reset();
}

#pragma endregion


#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.

//�֐�	:�I�u�W�F�N�g�Ȃǂ��쐬
//����	:�Ȃ�
//�߂�l:�Ȃ�
void PlayState::CreateDeviceDependentResources()
{
	//DeviceResources��Get
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();

	//ID3D11Device��Get
	ID3D11Device*          device = deviceResources->GetD3DDevice();

	//ID3D11DeviceContext1��Get
	ID3D11DeviceContext1*   context = deviceResources->GetD3DDeviceContext();
	
	// TODO: Initialize device dependent objects here (independent of window size).
	device;

	//�R�����X�e�[�g
	m_pState = std::make_unique<CommonStates>(device);

	//�t�H���g
	m_spriteBatch = std::make_unique<SpriteBatch>(context);

	//�t�H���g�̎w��
	m_spriteFont = std::make_unique<SpriteFont>(device, L"Resources\\Fonts\\SegoeUI_18.spritefont");
}

