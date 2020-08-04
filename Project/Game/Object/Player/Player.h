//======================================================
// File Name :Player.h
// Content	 :プレイヤーについて
// Author    :Yuki Sato
//======================================================

#pragma once

#include <DirectXTK\CommonStates.h>
#include "Game\Common\DeviceResources.h"
#include"Game\Common\Math.h"
#include"Game\Camera\FollowCamera.h"
#include"Game\Object\Wire\Wire.h"
#include "Game\Object\Post\Post.h"
#include"Game\Object\Player\PlayerSwingState.h"
#include"Game\Object\Player\PlayerDroppingState.h"


class FollowCamera;
class Wire;
class Math;

class Player
{
public:
	
	//関数	:コンストラクタ
	Player();

	//関数	:デストラクタ
	~Player();

public:

	//関数	:初期化
	void Initialize();

	//関数	:更新
	void Update();

	//関数	:描画
	void Render();

	//関数	:終了処理
	void Finalize();
	
	//関数	:プレイヤーの座標獲得
	//引数	:なし
	//戻り値:m_position
	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; };
	
	//関数	:プレイヤーの速度獲得
	//引数	:なし
	//戻り値:m_velocity
	DirectX::SimpleMath::Vector3 GetVelocity() { return m_velocity; };

	//関数	:プレイヤーの速度をセット
	//引数	:velocity
	//戻り値:なし
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; };

	//関数	:プレイヤーの状態をスイング状態に切り替える
	void ChangeSwing(const DirectX::SimpleMath::Vector3& pos);

	//関数	:プレイヤーの状態を落下状態に切り替える
	void ChangeDropping();

	//関数	:ポストの座標をセット
	void InjectWire(Post* post);

	//関数	:ワイヤーを切る
	void CutWire();

private:

	//関数	:オブジェクトなどを作成
	void CreateDeviceDependentResources();

private:

	//落下時のプレイヤー
	static std::unique_ptr<PlayerDroppingState> s_droppingState;

	//スイング時のプレイヤー
	static std::unique_ptr<PlayerSwingState> s_swingState;

	//プレイヤーのステート
	PlayerState*			m_state;
	
	//マス
	std::unique_ptr<Math>	 m_math;

	//ワイヤー
	std::unique_ptr<Wire>		m_wire;

	//支柱
//	std::unique_ptr<Post>		m_post;
	
	//プレイヤーのオブジェクト
	std::unique_ptr<DirectX::GeometricPrimitive>	m_model;
	
	//プレイヤーの座標
	DirectX::SimpleMath::Vector3					m_position;

	//プレイヤーの速度
	DirectX::SimpleMath::Vector3					m_velocity;
	
	//プレイヤーの色
	DirectX::SimpleMath::Color						m_color;

	//カメラが次に移すobject
	DirectX::SimpleMath::Vector3					m_target_position; 
	
	//m_object1が現在スイングしているobject
	DirectX::SimpleMath::Vector3					m_target_swing;
};

