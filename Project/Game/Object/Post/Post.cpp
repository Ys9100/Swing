//======================================================
// File Name :Post.cpp
// Content	 :�x���ɂ���
// Author    :Yuki Sato
//======================================================

#include "Post.h"

#include "Game\Common\GameContext.h"
#include"Game\Collision\Collision.h"
#include "Game\Camera\FollowCamera.h"
#include "Game\Game.h"

using namespace DirectX;

using Microsoft::WRL::ComPtr;


//�֐�	:������
//����	:�Ȃ�
//�߂�l:�Ȃ�
void Post::Initialize()
{
	//CreateDeviceDependentResources�̏�����
	CreateDeviceDependentResources();

	//�������W
	m_position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

	//�����J���[
	m_color = DirectX::Colors::White;
}

//�֐�	:�X�V
//����	:�Ȃ�
//�߂�l:�Ȃ�
void Post::Update()
{
	
}

//�֐�	:�`��
//����	:�Ȃ�
//�߂�l:�Ȃ�
void Post::Render()
{
	//Projection��Get
	Projection* projection = GameContext<Projection>::Get();

	//FollowCamera��Get
	FollowCamera* camera = GameContext<FollowCamera>::Get();

	//�}�g���N�X�̎w��
	DirectX::SimpleMath::Matrix matrix = DirectX::SimpleMath::Matrix::Identity;

	//matrix=�x���̍��W
	matrix = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	//�x���̕`��
	m_model->Draw(matrix, camera->getViewMatrix(), projection->GetMatrix(), m_color);
}

//�֐�	:�I������
//����	:�Ȃ�
//�߂�l:�Ȃ�
void Post::Finalize()
{
	//�x���̃I�u�W�F�N�g�̃��Z�b�g
	m_model.reset();
}

//�֐�	:�I�u�W�F�N�g�Ȃǂ��쐬
//����	:�Ȃ�
//�߂�l:�Ȃ�
void Post::CreateDeviceDependentResources()
{
	//DeviceResources��Get����
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();

	//ID3D11Device��Get����
	ID3D11Device*          device = deviceResources->GetD3DDevice();

	//ID3D11DeviceContext1��Get����
	ID3D11DeviceContext1*   context = deviceResources->GetD3DDeviceContext();

	// TODO: Initialize device dependent objects here (independent of window size).
	device;

	//�x���̃I�u�W�F�N�g�̍쐬
	m_model = CapsulePrimitive::Create(context);
}
