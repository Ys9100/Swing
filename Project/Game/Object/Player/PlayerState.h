//======================================================
// File Name :PlayerState.h
// Content	 :�v���C���[�̃X�e�[�g���Ǘ�����
// Author    :Yuki Sato
//======================================================


#pragma once

class Player;

class PlayerState
{	
public:

	//�֐�	:�R���X�g���N�^
	//����	:player
	//�߂�l:�Ȃ�
	PlayerState(Player* player)
		: m_player(player)
	{
	}

	//�֐�	:�f�X�g���N�^
	//����	:�Ȃ�
	//�߂�l:�Ȃ�
	virtual ~PlayerState()
	{
		m_player = nullptr;
	}

	//�֐�	:�n���h������
	virtual void HandleInput()=0;

	//�֐�	:�X�V
	virtual void Update()=0;

protected:

	//�v���C���[
	Player* m_player;

};

