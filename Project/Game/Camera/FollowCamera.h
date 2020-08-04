//======================================================
// File Name :FollowCamera.h
// Content	 :�Ώۂ�Ǐ]����
// Author    :Yuki Sato
//======================================================

#pragma once

#include <DirectXTK\SimpleMath.h>

class FollowCamera
{
private:

	// ���_
	DirectX::SimpleMath::Vector3 m_eye;

	// �����_
	DirectX::SimpleMath::Vector3 m_target;

	//��̕���
	DirectX::SimpleMath::Vector3 m_up;

	// �������ꂽ�r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	// �Q�Ǝ��_ 
	DirectX::SimpleMath::Vector3 m_ref_eye_pos;

	// �Q�ƒ����_ 
	DirectX::SimpleMath::Vector3 m_ref_target_pos;

public:

	//�֐�	:�R���X�g���N�^
	FollowCamera();

	//�֐�	;�f�X�g���N�^
	~FollowCamera();

	//�֐�	:�X�V
	void update();


public:

	//�֐�	:m_view���l��
	//����	:�Ȃ�
	//�߂�l:m_view
	DirectX::SimpleMath::Matrix getViewMatrix()
	{
		return m_view;
	}

	//�֐�	:���_�̐ݒ�
	//����	:eye
	//�߂�l:�Ȃ�
	void SetEye(DirectX::SimpleMath::Vector3 eye)
	{
		m_eye = eye;
	}

	//�֐�	:�����_�̐ݒ�
	//����	:target
	//�߂�l:�Ȃ�
	void SetTarget(DirectX::SimpleMath::Vector3 target)
	{
		m_target = target;
	}

	//�֐�	:���_�̍��W
	//����	:ref_eye_pos
	//�߂�l:�Ȃ�
	void SetRefEyePos(DirectX::SimpleMath::Vector3 ref_eye_pos)
	{
		m_ref_eye_pos = ref_eye_pos;
	}

	//�֐�	:���_�̑Ώۂ̍��W
	//����	:ref_target_pos
	//�߂�l:�Ȃ�
	void SetRefTargetPos(DirectX::SimpleMath::Vector3 ref_target_pos)
	{
		m_ref_target_pos = ref_target_pos;
	}
};