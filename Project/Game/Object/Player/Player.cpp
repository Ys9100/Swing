//======================================================
// File Name :Player.cpp
// Content	 :�v���C���[�ɂ���
// Author    :Yuki Sato
//======================================================

#include"Game\Object\Player\Player.h"

#include <DirectXTK\Mouse.h>
#include "Game\Game.h"
#include "Game\Common\GameContext.h"
#include"Game\Collision\Collision.h"
#include "Game\Camera\FollowCamera.h"
#include"Game\Common\Math.h"

//�������̃v���C���[
std::unique_ptr<PlayerDroppingState> Player::s_droppingState;

//�X�C���O���̃v���C���[
std::unique_ptr<PlayerSwingState> Player::s_swingState;

//�֐�	:�R���X�g���N�^
//����	:�Ȃ�
//�߂�l:�Ȃ�
Player::Player()
{
	//���C���[���l��
	m_wire = std::make_unique<Wire>(this);
}

//�֐�	:�f�X�g���N�^
//����	:�Ȃ�
//�߂�l:�Ȃ�
Player::~Player()
{
}

//�֐�	:������
//����	:�Ȃ�
//�߂�l:�Ȃ�
void Player::Initialize()
{

	//�������̃v���C���[
	s_droppingState = std::make_unique<PlayerDroppingState>(this);

	//�X�C���O���̃v���C���[
	s_swingState = std::make_unique<PlayerSwingState>(this);
	
	//CreateDeviceDependentResources�̏�����
	CreateDeviceDependentResources();

	m_math = std::make_unique<Math>();
	
	//�v���C���[�̏������W
	m_position = DirectX::SimpleMath::Vector3(-4.0f, 5.0f, 0.0f);

	//�v���C���[�̏������x
	m_velocity = DirectX::SimpleMath::Vector3::Zero;

	//���C���[�̏�����
	m_wire->Initialize();

	//�����X�e�[�g
	ChangeDropping();
	
}

//�֐�	:�X�V
//����	:�Ȃ�
//�߂�l:�Ȃ�
void Player::Update()
{
	//�}�E�X�̃X�e�[�g�l��
	DirectX::Mouse::State mouse = DirectX::Mouse::Get().GetState();

	//�v���C���[��Collision
	Collision::Sphere sphere;
	sphere.c = m_position;
	sphere.r = 0.5f;
	m_color = DirectX::Colors::Red;
	
	//���݂̃v���C���[�̃X�e�[�g
	m_state->HandleInput();

	//�X�e�[�g�̍X�V
	m_state->Update();
	
	//�v���C���[�̑��x�X�V
	m_position += m_velocity;

	m_wire->Update();
}

//�֐�	:�`��
//����	:�Ȃ�
//�߂�l:�Ȃ�
void Player::Render()
{
	//Projection��Get����
	Projection* projection = GameContext<Projection>::Get();

	//FollowCamera��Get����
	FollowCamera* camera = GameContext<FollowCamera>::Get();
	
	//�v���C���[�̕`��
	DirectX::SimpleMath::Matrix matrix = DirectX::SimpleMath::Matrix::Identity;

	//matrix=�v���C���[�̍��W
	matrix = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	//���f���`��
	m_model->Draw(matrix, camera->getViewMatrix(), projection->GetMatrix(), m_color, nullptr, true);

	m_wire->Render();
}

//�֐�	:�I������
//����	:�Ȃ�
//�߂�l:�Ȃ�
void Player::Finalize()
{
	//�v���C���[�̃I�u�W�F�N�g�̃��Z�b�g
	m_model.reset();
}

//�֐�	:�v���C���[�̏�Ԃ��X�C���O��Ԃɐ؂�ւ���
//����	:pos
//�߂�l:�Ȃ�
void Player::ChangeSwing(const DirectX::SimpleMath::Vector3 & pos)
{
	//�X�C���O�X�e�[�g���l��
	PlayerSwingState* swingState = s_swingState.get();

	//�x���̍��W���Z�b�g
	swingState->SetPostPosition(pos);

	//���݂̃X�e�[�g�ɃX�C���O�X�e�[�g����
	m_state = swingState;
}

//�֐�	:�v���C���[�̏�Ԃ𗎉���Ԃɐ؂�ւ���
//����	:�Ȃ�
//�߂�l:�Ȃ�
void Player::ChangeDropping()
{
	//�h���b�s���O�X�e�[�g���l��
	PlayerDroppingState* droppingState = s_droppingState.get();

	//���݂̃X�e�[�g�Ƀh���b�s���O�X�e�[�g����
	m_state = droppingState;
}

//�֐�	:�|�X�g�̍��W���Z�b�g
//����	:post
//�߂�l:�Ȃ�
void Player::InjectWire(Post* post)
{
	m_wire->InjectWire(post);
}

//�֐�	:���C���[��؂�
//����	:�Ȃ�
//�߂�l:�Ȃ�
void Player::CutWire()
{
	m_wire->CutWire();
}

//�֐�	:�I�u�W�F�N�g�Ȃǂ��쐬
//����	:�Ȃ�
//�߂�l:�Ȃ�
void Player::CreateDeviceDependentResources()
{
	//DeviceResources��Get����
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	
	//ID3D11Device��Get����
	ID3D11Device*          device = deviceResources->GetD3DDevice();

	//ID3D11DeviceContext1��Get����
	ID3D11DeviceContext1*   context = deviceResources->GetD3DDeviceContext();

	// TODO: Initialize device dependent objects here (independent of window size).
	device;

	//�v���C���[�̃I�u�W�F�N�g�̍쐬
	m_model =DirectX::GeometricPrimitive::CreateSphere(context);
}


