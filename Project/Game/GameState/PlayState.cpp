//======================================================
// File Name :PlayerState.cpp
// Content	 :プレイーシーンについて
// Author    :Yuki Sato
//======================================================

#include "PlayState.h"

#include <DirectXTK\Mouse.h>
#include<DirectXTK\Keyboard.h>
#include "Game\Game.h"
#include "Game\Common\GameContext.h"
#include "Game\GameState\GameStateManager.h"
#include "Game\Camera\FollowCamera.h"
#include"Game\Collision\Collision.h"


//カメラのターゲット
const DirectX::SimpleMath::Vector3 PlayState::TARGET_TO_EYE_VEC(0.0f, 0.0f, 20.0f);

using namespace DirectX;

using Microsoft::WRL::ComPtr;

//s_postをnullptrにする
Post* PlayState::s_post = nullptr;

//関数	:コンストラクタ
//引数	:なし
//戻り値:なし
PlayState::PlayState()
	: IGameState()
{
	
}


//関数	:デストラクタ
//引数	:なし
//戻り値:なし
PlayState::~PlayState()
{

}


//関数	:初期化
//引数	:なし
//戻り値:なし
void PlayState::Initialize()
{
	//プレイヤーを獲得
	m_player = std::make_unique<Player>();
	
	//プレイヤーの初期化
	m_player->Initialize();

	//支柱を獲得
	m_post = std::make_unique<Post>();

	//支柱の初期化
	m_post->Initialize();

	//支柱を獲得
	s_post = m_post.get();
	
	//CreateDeviceDependentResources初期化
	CreateDeviceDependentResources();
	
	m_cameraswing = DirectX::SimpleMath::Vector3(0.0f,0.0f, 20.0f);
}


//関数	:更新
//引数	:なし
//戻り値:なし
void PlayState::Update()
{
	//FollowCameraをGet
	FollowCamera* m_camera = GameContext<FollowCamera>::Get();
	
	//KeyboardをGet
	DirectX::Keyboard::State keyboard = DirectX::Keyboard::Get().GetState();

	//プレイヤーの更新
	m_player->Update();

	//支柱の更新
	m_post->Update();

	//カメラのZ軸を-1.0f動かす
	if (keyboard.W)
	{
		m_cameraswing.z -= 1.0f;
	}

	//カメラのZ軸を+1.0f動かす
	if (keyboard.S)
	{
		m_cameraswing.z += 1.0f;
	}

	if (keyboard.Q)
	{
		//GameStateManagerをGet
		GameStateManager* gameStateManager = GameContext<GameStateManager>::Get();

		//次のシーンを指定
		gameStateManager->RequestState("Play");
	}
	//カメラのセット
	m_camera->SetRefEyePos(m_cameraswing);

	//カメラの更新
	m_camera->update();
}


//関数	:描画
//引数	:なし
//戻り値:なし
void PlayState::Render()
{
	//プレイヤーの描画
	m_player->Render();

	//支柱の描画
	m_post->Render();

	//フォントの描画開始
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_pState->NonPremultiplied());
	
	//フォントの描画
	m_spriteFont->DrawString(m_spriteBatch.get(), "PlayState", SimpleMath::Vector2(0, 0), Colors::White);

	//フォントの描画終了
	m_spriteBatch->End();
}


//関数	:終了処理
//引数	:なし
//戻り値:なし
void PlayState::Finalize()
{
	//プレイヤーの終了
	m_player->Finalize();

	//支柱の終了
	m_post->Finalize();

	//コモンステートの終了
	m_pState.reset();
	
	//フォントの終了
	m_spriteBatch.reset();

	//フォントの終了
	m_spriteFont.reset();
}

#pragma endregion


#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.

//関数	:オブジェクトなどを作成
//引数	:なし
//戻り値:なし
void PlayState::CreateDeviceDependentResources()
{
	//DeviceResourcesをGet
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();

	//ID3D11DeviceをGet
	ID3D11Device*          device = deviceResources->GetD3DDevice();

	//ID3D11DeviceContext1をGet
	ID3D11DeviceContext1*   context = deviceResources->GetD3DDeviceContext();
	
	// TODO: Initialize device dependent objects here (independent of window size).
	device;

	//コモンステート
	m_pState = std::make_unique<CommonStates>(device);

	//フォント
	m_spriteBatch = std::make_unique<SpriteBatch>(context);

	//フォントの指定
	m_spriteFont = std::make_unique<SpriteFont>(device, L"Resources\\Fonts\\SegoeUI_18.spritefont");
}

