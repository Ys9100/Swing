//======================================================
// File Name :PlayerSwingState.h
// Content	 :�v���C���[�̃X�C���O���ɂ���
// Author    :Yuki Sato
//======================================================

#pragma once

#include"Game\Object\Player\PlayerState.h"



class PlayerSwingState :public PlayerState
{
public:

	//�֐�	:�R���X�g���N�^
	PlayerSwingState(Player* player);

	//�֐�	:�f�X�g���N�^
	~PlayerSwingState();

	//�֐�	:�x���̍��W���l�����ăv���C���[�̍��W�Ǝx���̍��W�̊Ԃ̑��x�����߂�
	void SetPostPosition(const DirectX::SimpleMath::Vector3& post);

	//�֐�	:�n���h������
	virtual void HandleInput() override;

	//�֐�	:�X�V
	virtual void Update() override;

private:

	//�x���̍��W
	DirectX::SimpleMath::Vector3 m_postPosition;

	// �d��̊p�x
	float m_rot;

	// �p���x
	float m_rot_spd;

	//���̒���
	float m_length;
};
