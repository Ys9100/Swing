//======================================================
// File Name :GameContext.h
// Content	 :�Q�[���R���e�L�X�g������
// Author    :Yuki Sato
//======================================================

#pragma once



#include "Game\Common\ServiceLocator.h"

template<typename Context>

class GameContext final
{
private:

	//�R���e�L�X�g
	static Context* s_context;
public:

	//�֐�	:�f�[�^��o�^
	//����	:context
	//�߂�l:�Ȃ�
	static void Register(const std::unique_ptr<Context>& context)
	{
		s_context = context.get();
	}

	//�֐�	:�f�[�^���l��
	//����	:�Ȃ�
	//�߂�l:s_context
	static Context* Get()
	{
		assert(s_context && "The context has not been registered.");
		return s_context;
	}
};

template<typename Context>

//�R���e�L�X�g��nullptr
Context* GameContext<Context>::s_context = nullptr;
