//======================================================
// File Name :Game.h
// Content	 :ゲームについて
// Author    :Yuki Sato
//======================================================
#pragma once

#include <unordered_map>
#include <DirectXTK\CommonStates.h>
#include <DirectXTK\SpriteBatch.h>
#include <DirectXTK\SimpleMath.h>
#include <DirectXTK\Mouse.h>
#include <DirectXTK\Keyboard.h>
#include <DirectXTK\PrimitiveBatch.h>
#include "Game\Common\DeviceResources.h"
#include "Game\Common\Projection.h"
#include "Game\Common\StepTimer.h"
#include"Game\Camera\FollowCamera.h"

class GameStateManager;


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify
{
public:

	////ウィンドー名
	static LPCWSTR WINDOW_NAME;

	//画面高さ
	static const int WINDOW_WIDTH;

	//画面幅
	static const int WINDOW_HEIGHT;
public:

	//関数	:コンストラクタ
	Game() noexcept(false);

	//関数	:デストラクタ
	~Game();

	// Initialization and management
	//関数	:初期化
	void Initialize(HWND window, int width, int height);

	// Basic game loop
	//関数	:瞬間
	void Tick();

	// IDeviceNotify
	virtual void OnDeviceLost() override;

	virtual void OnDeviceRestored() override;

	// Messages
	void OnActivated();

	void OnDeactivated();

	void OnSuspending();

	void OnResuming();

	void OnWindowMoved();

	void OnWindowSizeChanged(int width, int height);

	// Properties
	void GetDefaultSize(int& width, int& height) const;

private:

	//関数	:更新
	void Update(DX::StepTimer const& timer);

	//関数	:描画	
	void Render();

	//関数	:クリア
	void Clear();

	void CreateDeviceDependentResources();

	void CreateWindowSizeDependentResources();



	//デバイスリソーシーズ.
	std::unique_ptr<DX::DeviceResources>    m_deviceResources;

	//タイマー
	DX::StepTimer                           m_timer;

	// 射影行列
	std::unique_ptr<Projection>             m_projection;

	//カメラ
	std::unique_ptr<FollowCamera>			m_camera;

	// マウス
	std::unique_ptr<DirectX::Mouse>			m_mouse;

	//キーボード
	std::unique_ptr<DirectX::Keyboard>      m_keyboard;

	// コモンステート
	std::unique_ptr<DirectX::CommonStates>	m_state;

	//スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch>   m_spriteBatch;

	//ゲームマネージャー
	std::unique_ptr<GameStateManager>       m_gameStateManager;

};
