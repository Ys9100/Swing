//======================================================
// File Name :Post.h
// Content	 :�x���ɂ���
// Author    :Yuki Sato
//======================================================

#pragma once

#include <DirectXTK\CommonStates.h>
#include "Game\Common\DeviceResources.h"
#include "Game\\Collision\CapsulePrimitive.h"

class Post
{
public:

	//�֐�	:������
	void Initialize();

	//�֐�	:�X�V
	void Update();

	//�֐�	:�`��
	void Render();

	//�֐�	:�I������
	void Finalize();

public:

	//�֐�	:�x���̍��W�l��
	//����	:�Ȃ�
	//�߂�l:m_position
	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; };

	//�֐�	:���W���Z�b�g
	//����	:position
	//�߂�l:�Ȃ�
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; };

private:

	//�֐�	:�I�u�W�F�N�g�Ȃǂ��쐬
	void CreateDeviceDependentResources();

private:

	//�x���̃I�u�W�F�N�g
	std::unique_ptr<CapsulePrimitive>				m_model;

	//�x���̃}�g���N�X
	DirectX::SimpleMath::Matrix						m_worldMatrix;

	//�x���̍��W
	DirectX::SimpleMath::Vector3					m_position;

	//�x���̃J���[
	DirectX::SimpleMath::Color						m_color;
};