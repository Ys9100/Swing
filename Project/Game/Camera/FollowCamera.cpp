//======================================================
// File Name :FollowCamera.cpp
// Content	 :�Ώۂ�Ǐ]����
// Author    :Yuki Sato
//======================================================

#include "FollowCamera.h"

//�֐�	:�R���X�g���N�^
//����	:�Ȃ�
//�߂�l:�Ȃ�
FollowCamera::FollowCamera()
{
	m_eye = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 10.0f);

	m_target = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

	m_up = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);
}

//�֐�	:�f�X�g���N�^
//����	:�Ȃ�
//�߂�l:�Ȃ�
FollowCamera::~FollowCamera()
{

}

//�֐�	:�X�V
//����	:�Ȃ�
//�߂�l:�Ȃ�
void FollowCamera::update()
{
	//�J�����̈ʒu�v�Z
	m_eye += (m_ref_eye_pos - m_eye) * 0.1f;

	//target�̈ʒu�v�Z
	m_target += (m_ref_target_pos - m_target) * 0.1f;
	
	//view�ɑ��
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}