//======================================================
// File Name :Wire.cpp
// Content	 :���C���[�ɂ���
// Author    :Yuki Sato
//======================================================

#include"Wire.h"

#include "Game\Common\GameContext.h"
#include "Game\Common\Projection.h"

//�֐�	:�R���X�g���N�^
//����	:player
//�߂�l:�Ȃ�
Wire::Wire(Player* player)
{
	//player�ɑ��
	m_player = player;

	//�|�X�g��nullptr
	m_post = nullptr;
}

//�֐�	:�f�X�g���N�^
//����	:�Ȃ�
//�߂�l:�Ȃ�
Wire::~Wire()
{
}

//�֐�	:������
//����	:�Ȃ�
//�߂�l:�Ȃ�
void Wire::Initialize()
{
	//CreateDeviceDependentResources������
	CreateDeviceDependentResources();

	//�J�E���g������
	count = 0;

	//���C���[�̎ˏo�ő厞�Ԃ̐ݒ�
	injection = 20;
}

//�֐�	:�X�V
//����	:�Ȃ�
//�߂�l:�Ȃ�
void Wire::Update()
{
	//�|�X�g��nullptr��������
	if (m_post == nullptr)
	{
		//�J�E���g�̕���������
		if (count > 0)
		{
			//�J�E���g�����炷
			count--;
		}

		//�J�E���g��0��������
		if (count == 0)
		{
			//player��state��ύX
			m_player->ChangeDropping();

			//�J�E���g��0�ɂ���
			count = 0;
		}
	}
	else
	{
		//�C���W�F�N�V�����̕���������
		if (count < injection)
		{
			//�J�E���g�𑝂₷
			count++;

			//�J�E���g�ƃC���W�F�N�V�����̒l��������
			if (count == injection)
			{
				//player��state��ς��ďI�_�̏ꏊ���Z�b�g
				m_player->ChangeSwing(m_targetPos);
			}
		}
	}
}

//�֐�	:�`��
//����	:�Ȃ�
//�߂�l:�Ȃ�
void Wire::Render()
{
	//DeviceResources��Get
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();

	//ID3D11DeviceContext��Get
	ID3D11DeviceContext* context = deviceResources->GetD3DDeviceContext();
	
	//Projection��Get
	Projection*   projection = GameContext<Projection>::Get();

	//FollowCamera��Get
	FollowCamera* camera     = GameContext<FollowCamera>::Get();

	//basicEffect�̐ݒ�
	m_basicEffect->SetWorld(DirectX::SimpleMath::Matrix::Identity);
	m_basicEffect->SetView(camera->getViewMatrix());
	m_basicEffect->SetProjection(projection->GetMatrix());
	m_basicEffect->Apply(context);

	//IASetInputLayout�̃Z�b�g
	context->IASetInputLayout(m_pInputLayout.Get());

	//���C���[�̎n�_
	DirectX::SimpleMath::Vector3 startPos = m_player->GetPosition();

	//���C���[�̏I�_
	DirectX::SimpleMath::Vector3 v = m_targetPos - startPos;
	float ration = static_cast<float>(count) / injection;
	DirectX::SimpleMath::Vector3 endPos = startPos + v*ration;

	//���C���[�̎n�_�̍��W�ƃJ���[�Z�b�g
	DirectX::VertexPositionColor a(startPos, DirectX::Colors::White);

	//���C���[�̏I�_�̍��W�ƃJ���[�Z�b�g
	DirectX::VertexPositionColor b(endPos, DirectX::Colors::White);

	//���C���[�̕`��J�n
	m_primitiveBatch->Begin();

	//���C���[�̕`��
	m_primitiveBatch->DrawLine(a, b);

	//���C���[�̕`��I��
	m_primitiveBatch->End();
}

//�֐�	:�I������
//����	:�Ȃ�
//�߂�l:�Ȃ�
void Wire::Finalize()
{
	//�v���~�e�B�u�o�b�`�̃��Z�b�g
	m_primitiveBatch.reset();
}

//�֐�	:�I�u�W�F�N�g�Ȃǂ��쐬
//����	:�Ȃ�
//�߂�l:�Ȃ�
void Wire::CreateDeviceDependentResources()
{
	//DeviceResources��Get
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();

	//ID3D11Device��Get
	ID3D11Device*        device          = deviceResources->GetD3DDevice();

	//ID3D11DeviceContext��Get
	ID3D11DeviceContext* context         = deviceResources->GetD3DDeviceContext();

	// �v���~�e�B�u�I�u�W�F�N�g����
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(context);

	// �G�t�F�N�g�̐���
	m_basicEffect = std::make_unique<DirectX::BasicEffect>(device);

	// ���_�J���[(�L��)
	m_basicEffect->SetVertexColorEnabled(true);

	// �C���v�b�g���C�A�E�g����
	void const* shaderByteCode;

	size_t byteCodeLength;

	m_basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	device->CreateInputLayout(DirectX::VertexPositionColor::InputElements,
		DirectX::VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_pInputLayout.GetAddressOf());
}

//�֐�	:�|�X�g�̍��W���Z�b�g����
//����	:post
//�߂�l:�Ȃ�
void Wire::InjectWire(Post* post)
{
	//�|�X�g��������
	if (post)
	{
		//�|�X�g����
		m_post = post;

		//�^�[�Q�b�g���|�X�g�̍��W�ɂ���
		m_targetPos = post->GetPosition();
	}
};

//�֐�	:���C���[��؂�
//����	:�Ȃ�
//�߂�l:�Ȃ�
void Wire::CutWire()
{
	//�|�X�g�̍��W��j��
	m_post = nullptr;

	//�X�e�[�g���h���b�s���O
	m_player->ChangeDropping();
}