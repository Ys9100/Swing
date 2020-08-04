//======================================================
// File Name :PlayerDroppingState.cpp
// Content	 :�v���C���[�̗������ɂ���
// Author    :Yuki Sato
//======================================================

#include"PlayerDroppingState.h"
#include"Game\Object\Player\Player.h"
#include"Game\Object\Post\Post.h"
#include"Game\Collision\Collision.h"
#include "Game\Common\GameContext.h"
#include"Game\Common\Projection.h"
#include"Game\Common\Math.h"
#include"Game\Game.h"
#include "Game\GameState\PlayState.h"

//�֐�	:�R���X�g���N�^
//����	:player
//�߂�l:�Ȃ�
PlayerDroppingState::PlayerDroppingState(Player* player)
	:PlayerState(player)
{
	//�}�X���l��
	m_math = std::make_unique<Math>();

	//�|�X�g���l��
	m_post = std::make_unique<Post>();
}

//�֐�	:�f�X�g���N�^
//����	:�Ȃ�
//�߂�l:�Ȃ�
PlayerDroppingState::~PlayerDroppingState()
{
}


//�֐�	:�n���h������
//����	:�Ȃ�
//�߂�l:�Ȃ�
void PlayerDroppingState::HandleInput()
{
	//Mouse��Get
	DirectX::Mouse::State mouse = DirectX::Mouse::Get().GetState();

	
		//���N���b�N�������ꂽ��
		if (mouse.leftButton)
		{
			//�}�E�X�ƃ|�X�g���d�Ȃ��Ă��邩
			if (ChangeStateCollider(mouse))
			{
				//�v���C���[�̊֐��Ɉړ�
				m_player->InjectWire(PlayState::s_post);
			}
		}
}

//�֐�	:�X�V
//����	:�Ȃ�
//�߂�l:�Ȃ�
void PlayerDroppingState::Update()
{
	//�������̌v�Z
	//���x=�v���C���[�̌��݂̑��x+�d��
	DirectX::SimpleMath::Vector3 velocity = m_player->GetVelocity() + Math::GRAVITY;

	//�v���C���[�̑��x�Ɍv�Z���velocity����
	m_player->SetVelocity(velocity);
}

//�֐�	:�}�E�X�ƃJ�v�Z���̓����蔻��
//����	:mouse
//�߂�l:true or false
bool PlayerDroppingState::ChangeStateCollider(const DirectX::Mouse::State& mouse)
{
	//Projection��Get
	Projection* projection = GameContext<Projection>::Get();

	//FollowCamera��Get
	FollowCamera* camera = GameContext<FollowCamera>::Get();

	//�}�E�X�̋t�s��
	DirectX::SimpleMath::Matrix Screen = Math::CreateMatrix_Screen2World(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT, camera->getViewMatrix(), projection->GetMatrix());
	DirectX::SimpleMath::Vector3 mouseStart((float)mouse.x, (float)mouse.y, 0);
	DirectX::SimpleMath::Vector3 mouseEnd((float)mouse.x, (float)mouse.y, 1);
	mouseStart = DirectX::SimpleMath::Vector3::Transform(mouseStart, Screen);
	mouseEnd = DirectX::SimpleMath::Vector3::Transform(mouseEnd, Screen);

	//�}�E�X�̓����蔻��̐ݒ�
	Collision::Line line;
	line.p = mouseStart;
	line.d = mouseEnd - mouseStart;

	//�J�v�Z���̓����蔻��̐ݒ�
	Collision::Capsule capsule;
	capsule.r = 0.5f;
	capsule.a = DirectX::SimpleMath::Vector3(0.0f, 0.5f, 0.0f) + m_post->GetPosition();
	capsule.b = DirectX::SimpleMath::Vector3(0.0f, -0.5f, 0.0f) + m_post->GetPosition();

	//�}�E�X�ƃJ�v�Z�����d�Ȃ��Ă�����
	if (Collision::HitCheck_Capsule2Line(capsule, line))
	{
		return true;
	}
	else
	{
		return false;
	}
}
