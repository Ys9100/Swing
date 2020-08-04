//======================================================
// File Name :PlayerState.h
// Content	 :�v���C�[�V�[���ɂ���
// Author    :Yuki Sato
//======================================================
#pragma once

#include <memory>


#include <DirectXTK\CommonStates.h>
#include "Game\GameState\GameState.h"
#include "Game\Common\DeviceResources.h"
#include "Game\\Collision\CapsulePrimitive.h"
#include"Game\Object\Player\Player.h"
#include"Game\Object\Post\Post.h"
#include"Game\Object\Wire\Wire.h"




class PlayState : public IGameState
{
public:

	//�x��
	static Post* s_post;

private:
	//�v���C���[
	std::unique_ptr<Player>		m_player;

	//�x��
	std::unique_ptr<Post>		m_post;

public:

	//�J�����̃^�[�Q�b�g
	static const  DirectX::SimpleMath::Vector3 TARGET_TO_EYE_VEC;

public:

	//�֐�	:�R���X�g���N�^
	PlayState();

public:

	//�֐�	:�f�X�g���N�^
	virtual ~PlayState();


public:
	//�֐�	:������
	void Initialize() override;

	//�֐�	:�X�V
	void Update() override;

	//�֐�	:�`��
	void Render() override;

	//�֐�	:�I������
	void Finalize() override;

private:
	//�֐�	:�I�u�W�F�N�g�Ȃǂ��쐬
	void CreateDeviceDependentResources();

	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates>	m_pState;

	//�t�H���g
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;
	
	//m_object1�����݃X�C���O���Ă���object
	DirectX::SimpleMath::Vector3					m_cameraswing;	 

	//�U��q�^�����Ǘ�����flag
	bool m_swingflag;		        
};
