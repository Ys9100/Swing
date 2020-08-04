//======================================================
// File Name :PlayerDroppingState.h
// Content	 :�v���C���[�̗������ɂ���
// Author    :Yuki Sato
//======================================================

#pragma once

#include"Game\Object\Player\PlayerState.h"

class Math;
class Post;

class PlayerDroppingState:public PlayerState
{
public:

	//�֐�	:�R���X�g���N�^
	PlayerDroppingState(Player* player);

	//�֐�	:�f�X�g���N�^
	~PlayerDroppingState();

	//�֐�	:�n���h������
	virtual void HandleInput() override;

	//�֐�	:�X�V
	virtual void Update() override;

	//�֐�	:�}�E�X�ƃJ�v�Z���̓����蔻��
	bool ChangeStateCollider(const DirectX::Mouse::State& mouse);

private:

	//�}�X
	std::unique_ptr<Math> m_math;

	//�|�X�g
	std::unique_ptr<Post> m_post;
};

