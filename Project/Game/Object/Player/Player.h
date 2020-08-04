//======================================================
// File Name :Player.h
// Content	 :�v���C���[�ɂ���
// Author    :Yuki Sato
//======================================================

#pragma once

#include <DirectXTK\CommonStates.h>
#include "Game\Common\DeviceResources.h"
#include"Game\Common\Math.h"
#include"Game\Camera\FollowCamera.h"
#include"Game\Object\Wire\Wire.h"
#include "Game\Object\Post\Post.h"
#include"Game\Object\Player\PlayerSwingState.h"
#include"Game\Object\Player\PlayerDroppingState.h"


class FollowCamera;
class Wire;
class Math;

class Player
{
public:
	
	//�֐�	:�R���X�g���N�^
	Player();

	//�֐�	:�f�X�g���N�^
	~Player();

public:

	//�֐�	:������
	void Initialize();

	//�֐�	:�X�V
	void Update();

	//�֐�	:�`��
	void Render();

	//�֐�	:�I������
	void Finalize();
	
	//�֐�	:�v���C���[�̍��W�l��
	//����	:�Ȃ�
	//�߂�l:m_position
	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; };
	
	//�֐�	:�v���C���[�̑��x�l��
	//����	:�Ȃ�
	//�߂�l:m_velocity
	DirectX::SimpleMath::Vector3 GetVelocity() { return m_velocity; };

	//�֐�	:�v���C���[�̑��x���Z�b�g
	//����	:velocity
	//�߂�l:�Ȃ�
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; };

	//�֐�	:�v���C���[�̏�Ԃ��X�C���O��Ԃɐ؂�ւ���
	void ChangeSwing(const DirectX::SimpleMath::Vector3& pos);

	//�֐�	:�v���C���[�̏�Ԃ𗎉���Ԃɐ؂�ւ���
	void ChangeDropping();

	//�֐�	:�|�X�g�̍��W���Z�b�g
	void InjectWire(Post* post);

	//�֐�	:���C���[��؂�
	void CutWire();

private:

	//�֐�	:�I�u�W�F�N�g�Ȃǂ��쐬
	void CreateDeviceDependentResources();

private:

	//�������̃v���C���[
	static std::unique_ptr<PlayerDroppingState> s_droppingState;

	//�X�C���O���̃v���C���[
	static std::unique_ptr<PlayerSwingState> s_swingState;

	//�v���C���[�̃X�e�[�g
	PlayerState*			m_state;
	
	//�}�X
	std::unique_ptr<Math>	 m_math;

	//���C���[
	std::unique_ptr<Wire>		m_wire;

	//�x��
//	std::unique_ptr<Post>		m_post;
	
	//�v���C���[�̃I�u�W�F�N�g
	std::unique_ptr<DirectX::GeometricPrimitive>	m_model;
	
	//�v���C���[�̍��W
	DirectX::SimpleMath::Vector3					m_position;

	//�v���C���[�̑��x
	DirectX::SimpleMath::Vector3					m_velocity;
	
	//�v���C���[�̐F
	DirectX::SimpleMath::Color						m_color;

	//�J���������Ɉڂ�object
	DirectX::SimpleMath::Vector3					m_target_position; 
	
	//m_object1�����݃X�C���O���Ă���object
	DirectX::SimpleMath::Vector3					m_target_swing;
};

