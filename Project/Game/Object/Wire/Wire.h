//======================================================
// File Name :Wire.h
// Content	 :���C���[�ɂ���.h
// Author    :Yuki Sato
//======================================================

#pragma once

#include "Game\Common\DeviceResources.h"
#include"Game\Object\Player\Player.h"
#include"Game\Object\Post\Post.h"

class Player;

class Wire
{
public:
	
	//�֐�	:�R���X�g���N�^
	Wire(Player* player);

	//�֐�	:�f�X�g���N�^
	~Wire();

public:
	
	//�֐�	:������
	void Initialize();

	//�֐�	:�X�V
	void Update();

	//�֐�	:�`��
	void Render();

	//�֐�	:�I������
	void Finalize();

	//�֐�	:�x���̍��W���Z�b�g
	void InjectWire(Post* post);

	//�֐�	:���C���[��؂�
	void CutWire();

private:

	//�֐�	:CreateDeviceDependentResources
	void CreateDeviceDependentResources();

private:

	//�x�[�V�b�N�G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

	// �C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;

	//�v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

	//�v���C���[
	Player*    m_player;

	//�x��
	Post*    m_post;

	//�I�_
	DirectX::SimpleMath::Vector3 m_targetPos;

	//���C���[�̎ˏo����
	int count;

	//���C���[�̎ˏo�ő厞��
	int injection;
};

