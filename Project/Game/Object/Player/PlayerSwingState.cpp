//======================================================
// File Name :PlayerSwingState.cpp
// Content	 :�v���C���[�̃X�C���O���ɂ���
// Author    :Yuki Sato
//======================================================

#include"PlayerSwingState.h"
#include"Game\Object\Player\Player.h"



//�֐�	:�R���X�g���N�^
//����	:player
//�߂�l:�Ȃ�
PlayerSwingState::PlayerSwingState(Player* player)
	:PlayerState(player)
{
	
}

//�֐�	:�f�X�g���N�^
//����	:�Ȃ�
//�߂�l:�Ȃ�
PlayerSwingState::~PlayerSwingState()
{
}

//�֐�	:�x���̍��W���l�����ăv���C���[�̍��W�Ǝx���̍��W�̊Ԃ̑��x�����߂�
//����	:pos
//�߂�l:�Ȃ�
void PlayerSwingState::SetPostPosition(const DirectX::SimpleMath::Vector3 & pos)
{
	//�x���̍��W����
	m_postPosition = pos;
	
	//�v���C���[�̍��W�Ǝx���̍��W�̊Ԃ̑��x=�v���C���[�̍��W-�x���̍��W
	DirectX::SimpleMath::Vector3 v = m_player->GetPosition() - m_postPosition;
	
	//�v���C���[�Ǝx���̈ʒu���珉���p�x�����߂�
	m_rot = std::atan2(v.y, v.x) * 180.0f / DirectX::XM_PI;
	
	//�v���C���[�Ǝx���̈ʒu���珉���p�x�����߂����Ɏ����I�ɒ�����������
	m_length = v.Length();
	
	//�p���x�Ƀv���C���[�̑��x���l��
	m_rot_spd = m_player->GetVelocity().Length();

}

//�֐�	:�n���h������
//����	:�Ȃ�
//�߂�l:�Ȃ�
void PlayerSwingState::HandleInput()
{
	//Mouse��Get
	DirectX::Mouse::State mouse = DirectX::Mouse::Get().GetState();

	
		//���N���b�N�Ő؂藣��
		if (mouse.rightButton)
		{
			//�v���C���[�̊֐��Ɉړ�
			m_player->CutWire();
		};
}

//�֐�	:�X�V
//����	:�Ȃ�
//�߂�l:�Ȃ�
void PlayerSwingState::Update()
{
	// ���݂̏d��̈ʒu
	auto rad = m_rot * DirectX::XM_PI / 180;

	//�U��q���̃v���C���[�̍��W
	DirectX::SimpleMath::Vector3 position=DirectX::SimpleMath::Vector3::Zero;
	
	position.x = m_postPosition.x + cos(rad) * m_length;
	position.y = m_postPosition.y + sin(rad) * m_length;
	
	auto vx = position.x - m_postPosition.x;
	auto vy = position.y - m_postPosition.y;
	auto t = (vy * Math::GRAVITY.y) / (vx * vx + vy * vy);
	auto gx = position.x + t * vx;
	auto gy = position.y + Math::GRAVITY.y + t * vy;
	
	// �Q�̏d��̈ʒu�̊p�x��
	auto r = atan2(gy - m_postPosition.y, gx - m_postPosition.x) * 180 / DirectX::XM_PI;
	
	// �p�x�����p���x�ɉ��Z
	auto sub = r - m_rot;
	sub -= (float)floor(sub / 180.0f) * 180.0f;
	if (sub < -90.0f)	sub += 180.0f;
	if (sub > 90.0f)	sub -= 180.0f;
	m_rot_spd += sub;
	
	// �p�x�Ɋp���x�����Z
	m_rot += m_rot_spd;
	
	// �V�����d��̈ʒu
	rad = m_rot * DirectX::XM_PI / 180;
	position.x = m_postPosition.x + cos(rad) * m_length;
	position.y = m_postPosition.y + sin(rad) * m_length;
	
	//���x=�U��q���̃v���C���[�̍��W-�v���C���[�̍��W
	DirectX::SimpleMath::Vector3 velocity = position - m_player->GetPosition();
	
	//�v���C���[�̑��x�Ɍv�Z���velocity����
	m_player->SetVelocity(velocity);
}