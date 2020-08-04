//======================================================
// File Name :PlayerDroppingState.h
// Content	 :プレイヤーの落下時について
// Author    :Yuki Sato
//======================================================

#pragma once

#include"Game\Object\Player\PlayerState.h"

class Math;
class Post;

class PlayerDroppingState:public PlayerState
{
public:

	//関数	:コンストラクタ
	PlayerDroppingState(Player* player);

	//関数	:デストラクタ
	~PlayerDroppingState();

	//関数	:ハンドル入力
	virtual void HandleInput() override;

	//関数	:更新
	virtual void Update() override;

	//関数	:マウスとカプセルの当たり判定
	bool ChangeStateCollider(const DirectX::Mouse::State& mouse);

private:

	//マス
	std::unique_ptr<Math> m_math;

	//ポスト
	std::unique_ptr<Post> m_post;
};

