//======================================================
// File Name :TitleState.h
// Content	 :�^�C�g���[�V�[���ɂ���
// Author    :Yuki Sato
//======================================================

#pragma once


#include "Game\Common\StepTimer.h"
#include "Game\GameState\GameState.h"


class TitleState : public IGameState
{
private:

	//�J�E���g
	int m_count;
public:

	//�֐�	:�R���X�g���N�^
	TitleState();

public:

	//�֐�	:�f�X�g���N�^
	virtual ~TitleState();


public:
	//�֐�	:������
	void Initialize() override;

	//�֐�	:�X�V
	void Update() override;

	//�֐�	:�`��
	void Render() override;

	//�֐�	:�I������
	void Finalize() override;
};
