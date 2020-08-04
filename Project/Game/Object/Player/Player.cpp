//======================================================
// File Name :Player.cpp
// Content	 :プレイヤーについて
// Author    :Yuki Sato
//======================================================

#include"Game\Object\Player\Player.h"

#include <DirectXTK\Mouse.h>
#include "Game\Game.h"
#include "Game\Common\GameContext.h"
#include"Game\Collision\Collision.h"
#include "Game\Camera\FollowCamera.h"
#include"Game\Common\Math.h"

//落下時のプレイヤー
std::unique_ptr<PlayerDroppingState> Player::s_droppingState;

//スイング時のプレイヤー
std::unique_ptr<PlayerSwingState> Player::s_swingState;

//関数	:コンストラクタ
//引数	:なし
//戻り値:なし
Player::Player()
{
	//ワイヤーを獲得
	m_wire = std::make_unique<Wire>(this);
}

//関数	:デストラクタ
//引数	:なし
//戻り値:なし
Player::~Player()
{
}

//関数	:初期化
//引数	:なし
//戻り値:なし
void Player::Initialize()
{

	//落下時のプレイヤー
	s_droppingState = std::make_unique<PlayerDroppingState>(this);

	//スイング時のプレイヤー
	s_swingState = std::make_unique<PlayerSwingState>(this);
	
	//CreateDeviceDependentResourcesの初期化
	CreateDeviceDependentResources();

	m_math = std::make_unique<Math>();
	
	//プレイヤーの初期座標
	m_position = DirectX::SimpleMath::Vector3(-4.0f, 5.0f, 0.0f);

	//プレイヤーの初期速度
	m_velocity = DirectX::SimpleMath::Vector3::Zero;

	//ワイヤーの初期化
	m_wire->Initialize();

	//初期ステート
	ChangeDropping();
	
}

//関数	:更新
//引数	:なし
//戻り値:なし
void Player::Update()
{
	//マウスのステート獲得
	DirectX::Mouse::State mouse = DirectX::Mouse::Get().GetState();

	//プレイヤーのCollision
	Collision::Sphere sphere;
	sphere.c = m_position;
	sphere.r = 0.5f;
	m_color = DirectX::Colors::Red;
	
	//現在のプレイヤーのステート
	m_state->HandleInput();

	//ステートの更新
	m_state->Update();
	
	//プレイヤーの速度更新
	m_position += m_velocity;

	m_wire->Update();
}

//関数	:描画
//引数	:なし
//戻り値:なし
void Player::Render()
{
	//ProjectionをGetする
	Projection* projection = GameContext<Projection>::Get();

	//FollowCameraをGetする
	FollowCamera* camera = GameContext<FollowCamera>::Get();
	
	//プレイヤーの描画
	DirectX::SimpleMath::Matrix matrix = DirectX::SimpleMath::Matrix::Identity;

	//matrix=プレイヤーの座標
	matrix = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	//モデル描画
	m_model->Draw(matrix, camera->getViewMatrix(), projection->GetMatrix(), m_color, nullptr, true);

	m_wire->Render();
}

//関数	:終了処理
//引数	:なし
//戻り値:なし
void Player::Finalize()
{
	//プレイヤーのオブジェクトのリセット
	m_model.reset();
}

//関数	:プレイヤーの状態をスイング状態に切り替える
//引数	:pos
//戻り値:なし
void Player::ChangeSwing(const DirectX::SimpleMath::Vector3 & pos)
{
	//スイングステートを獲得
	PlayerSwingState* swingState = s_swingState.get();

	//支柱の座標をセット
	swingState->SetPostPosition(pos);

	//現在のステートにスイングステートを代入
	m_state = swingState;
}

//関数	:プレイヤーの状態を落下状態に切り替える
//引数	:なし
//戻り値:なし
void Player::ChangeDropping()
{
	//ドロッピングステートを獲得
	PlayerDroppingState* droppingState = s_droppingState.get();

	//現在のステートにドロッピングステートを代入
	m_state = droppingState;
}

//関数	:ポストの座標をセット
//引数	:post
//戻り値:なし
void Player::InjectWire(Post* post)
{
	m_wire->InjectWire(post);
}

//関数	:ワイヤーを切る
//引数	:なし
//戻り値:なし
void Player::CutWire()
{
	m_wire->CutWire();
}

//関数	:オブジェクトなどを作成
//引数	:なし
//戻り値:なし
void Player::CreateDeviceDependentResources()
{
	//DeviceResourcesをGetする
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	
	//ID3D11DeviceをGetする
	ID3D11Device*          device = deviceResources->GetD3DDevice();

	//ID3D11DeviceContext1をGetする
	ID3D11DeviceContext1*   context = deviceResources->GetD3DDeviceContext();

	// TODO: Initialize device dependent objects here (independent of window size).
	device;

	//プレイヤーのオブジェクトの作成
	m_model =DirectX::GeometricPrimitive::CreateSphere(context);
}


