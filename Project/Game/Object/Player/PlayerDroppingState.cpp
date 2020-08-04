//======================================================
// File Name :PlayerDroppingState.cpp
// Content	 :プレイヤーの落下時について
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

//関数	:コンストラクタ
//引数	:player
//戻り値:なし
PlayerDroppingState::PlayerDroppingState(Player* player)
	:PlayerState(player)
{
	//マスを獲得
	m_math = std::make_unique<Math>();

	//ポストを獲得
	m_post = std::make_unique<Post>();
}

//関数	:デストラクタ
//引数	:なし
//戻り値:なし
PlayerDroppingState::~PlayerDroppingState()
{
}


//関数	:ハンドル入力
//引数	:なし
//戻り値:なし
void PlayerDroppingState::HandleInput()
{
	//MouseをGet
	DirectX::Mouse::State mouse = DirectX::Mouse::Get().GetState();

	
		//左クリックが押された時
		if (mouse.leftButton)
		{
			//マウスとポストが重なっているか
			if (ChangeStateCollider(mouse))
			{
				//プレイヤーの関数に移動
				m_player->InjectWire(PlayState::s_post);
			}
		}
}

//関数	:更新
//引数	:なし
//戻り値:なし
void PlayerDroppingState::Update()
{
	//落下時の計算
	//速度=プレイヤーの現在の速度+重力
	DirectX::SimpleMath::Vector3 velocity = m_player->GetVelocity() + Math::GRAVITY;

	//プレイヤーの速度に計算後のvelocityを代入
	m_player->SetVelocity(velocity);
}

//関数	:マウスとカプセルの当たり判定
//引数	:mouse
//戻り値:true or false
bool PlayerDroppingState::ChangeStateCollider(const DirectX::Mouse::State& mouse)
{
	//ProjectionをGet
	Projection* projection = GameContext<Projection>::Get();

	//FollowCameraをGet
	FollowCamera* camera = GameContext<FollowCamera>::Get();

	//マウスの逆行列
	DirectX::SimpleMath::Matrix Screen = Math::CreateMatrix_Screen2World(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT, camera->getViewMatrix(), projection->GetMatrix());
	DirectX::SimpleMath::Vector3 mouseStart((float)mouse.x, (float)mouse.y, 0);
	DirectX::SimpleMath::Vector3 mouseEnd((float)mouse.x, (float)mouse.y, 1);
	mouseStart = DirectX::SimpleMath::Vector3::Transform(mouseStart, Screen);
	mouseEnd = DirectX::SimpleMath::Vector3::Transform(mouseEnd, Screen);

	//マウスの当たり判定の設定
	Collision::Line line;
	line.p = mouseStart;
	line.d = mouseEnd - mouseStart;

	//カプセルの当たり判定の設定
	Collision::Capsule capsule;
	capsule.r = 0.5f;
	capsule.a = DirectX::SimpleMath::Vector3(0.0f, 0.5f, 0.0f) + m_post->GetPosition();
	capsule.b = DirectX::SimpleMath::Vector3(0.0f, -0.5f, 0.0f) + m_post->GetPosition();

	//マウスとカプセルが重なっていたら
	if (Collision::HitCheck_Capsule2Line(capsule, line))
	{
		return true;
	}
	else
	{
		return false;
	}
}
