//======================================================
// File Name :PlayerSwingState.h
// Content	 :プレイヤーのスイング時について
// Author    :Yuki Sato
//======================================================

#pragma once

#include"Game\Object\Player\PlayerState.h"



class PlayerSwingState :public PlayerState
{
public:

	//関数	:コンストラクタ
	PlayerSwingState(Player* player);

	//関数	:デストラクタ
	~PlayerSwingState();

	//関数	:支柱の座標を獲得してプレイヤーの座標と支柱の座標の間の速度を求める
	void SetPostPosition(const DirectX::SimpleMath::Vector3& post);

	//関数	:ハンドル入力
	virtual void HandleInput() override;

	//関数	:更新
	virtual void Update() override;

private:

	//支柱の座標
	DirectX::SimpleMath::Vector3 m_postPosition;

	// 重りの角度
	float m_rot;

	// 角速度
	float m_rot_spd;

	//糸の長さ
	float m_length;
};
