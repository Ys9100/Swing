//======================================================
// File Name :PlayerSwingState.cpp
// Content	 :プレイヤーのスイング時について
// Author    :Yuki Sato
//======================================================

#include"PlayerSwingState.h"
#include"Game\Object\Player\Player.h"



//関数	:コンストラクタ
//引数	:player
//戻り値:なし
PlayerSwingState::PlayerSwingState(Player* player)
	:PlayerState(player)
{
	
}

//関数	:デストラクタ
//引数	:なし
//戻り値:なし
PlayerSwingState::~PlayerSwingState()
{
}

//関数	:支柱の座標を獲得してプレイヤーの座標と支柱の座標の間の速度を求める
//引数	:pos
//戻り値:なし
void PlayerSwingState::SetPostPosition(const DirectX::SimpleMath::Vector3 & pos)
{
	//支柱の座標を代入
	m_postPosition = pos;
	
	//プレイヤーの座標と支柱の座標の間の速度=プレイヤーの座標-支柱の座標
	DirectX::SimpleMath::Vector3 v = m_player->GetPosition() - m_postPosition;
	
	//プレイヤーと支柱の位置から初期角度を求める
	m_rot = std::atan2(v.y, v.x) * 180.0f / DirectX::XM_PI;
	
	//プレイヤーと支柱の位置から初期角度を求めた時に自動的に長さが分かる
	m_length = v.Length();
	
	//角速度にプレイヤーの速度を獲得
	m_rot_spd = m_player->GetVelocity().Length();

}

//関数	:ハンドル入力
//引数	:なし
//戻り値:なし
void PlayerSwingState::HandleInput()
{
	//MouseをGet
	DirectX::Mouse::State mouse = DirectX::Mouse::Get().GetState();

	
		//左クリックで切り離す
		if (mouse.rightButton)
		{
			//プレイヤーの関数に移動
			m_player->CutWire();
		};
}

//関数	:更新
//引数	:なし
//戻り値:なし
void PlayerSwingState::Update()
{
	// 現在の重りの位置
	auto rad = m_rot * DirectX::XM_PI / 180;

	//振り子時のプレイヤーの座標
	DirectX::SimpleMath::Vector3 position=DirectX::SimpleMath::Vector3::Zero;
	
	position.x = m_postPosition.x + cos(rad) * m_length;
	position.y = m_postPosition.y + sin(rad) * m_length;
	
	auto vx = position.x - m_postPosition.x;
	auto vy = position.y - m_postPosition.y;
	auto t = (vy * Math::GRAVITY.y) / (vx * vx + vy * vy);
	auto gx = position.x + t * vx;
	auto gy = position.y + Math::GRAVITY.y + t * vy;
	
	// ２つの重りの位置の角度差
	auto r = atan2(gy - m_postPosition.y, gx - m_postPosition.x) * 180 / DirectX::XM_PI;
	
	// 角度差を角速度に加算
	auto sub = r - m_rot;
	sub -= (float)floor(sub / 180.0f) * 180.0f;
	if (sub < -90.0f)	sub += 180.0f;
	if (sub > 90.0f)	sub -= 180.0f;
	m_rot_spd += sub;
	
	// 角度に角速度を加算
	m_rot += m_rot_spd;
	
	// 新しい重りの位置
	rad = m_rot * DirectX::XM_PI / 180;
	position.x = m_postPosition.x + cos(rad) * m_length;
	position.y = m_postPosition.y + sin(rad) * m_length;
	
	//速度=振り子時のプレイヤーの座標-プレイヤーの座標
	DirectX::SimpleMath::Vector3 velocity = position - m_player->GetPosition();
	
	//プレイヤーの速度に計算後のvelocityを代入
	m_player->SetVelocity(velocity);
}