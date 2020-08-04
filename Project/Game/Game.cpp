//======================================================
// File Name :Game.cpp
// Content	 :ゲームについて
// Author    :Yuki Sato
//======================================================

#include "Game.h"

#include <random>

#include "Game\Font\DebugFont.h"
#include "Game\Common\GameContext.h"
#include "Game\GameState\GameStateManager.h"

#include "Game\GameState\TitleState.h"
#include "Game\GameState\PlayState.h"

extern void ExitGame();

using namespace DirectX;

using Microsoft::WRL::ComPtr;

//ウィンドー名
LPCWSTR Game::WINDOW_NAME = L"Swing";

//画面高さ
const int Game::WINDOW_WIDTH = 800;

//画面幅
const int Game::WINDOW_HEIGHT = 600;


//関数	:コンストラクタ
//引数	:なし
//戻り値:なし
Game::Game() noexcept(false)
{
	//デバイスリソーシーズを獲得
	m_deviceResources = std::make_unique<DX::DeviceResources>();

	m_deviceResources->RegisterDeviceNotify(this);

	//DeviceResourcesをGameContextに登録
	GameContext<DX::DeviceResources>::Register(m_deviceResources);
}

//関数	:デストラクタ
//引数	:なし
//戻り値:なし
Game::~Game()
{
	//デバックフォントを初期化
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->reset();

}

// Initialize the Direct3D resources required to run.
//関数	:初期化
//引数	:window,width,height
//戻り値:なし
void Game::Initialize(HWND window, int width, int height)
{
	// マウスのを獲得
	m_mouse = std::make_unique<Mouse>();

	//Window指定
	m_mouse->SetWindow(window);

	//キーボード獲得
	m_keyboard = std::make_unique<Keyboard>();

	//デバイスリソーシーズに画面情報をセット
	m_deviceResources->SetWindow(window, width, height);

	//デバイスリソーシーズにCreateDeviceResourcesをセット
	m_deviceResources->CreateDeviceResources();

	//CreateDeviceDependentResourcesを初期化
	CreateDeviceDependentResources();

	// コモンステート獲得
	m_state = std::make_unique<CommonStates>(m_deviceResources->GetD3DDevice());

	//CommonStatesをGameContextに登録
	GameContext<DirectX::CommonStates>::Register(m_state);
	
	//カメラを獲得
	m_camera = std::make_unique<FollowCamera>();

	//FollowCameraをGameContextに登録
	GameContext<FollowCamera>::Register(m_camera);

	//デバイスリソーシーズにCreateWindowSizeDependentResourcesをセット
	m_deviceResources->CreateWindowSizeDependentResources();

	//CreateWindowSizeDependentResourcesを初期化
	CreateWindowSizeDependentResources();

	// TODO: Change the timer settings if you want something other than the default variable timestep mode.
	// e.g. for 60 FPS fixed timestep update logic, call:
	/*
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);
	*/

	//フォント初期化
	DebugFont* debugFont = DebugFont::GetInstance();

	//フォントを作成
	debugFont->create(m_deviceResources->GetD3DDevice(), m_deviceResources->GetD3DDeviceContext());

	//ゲームマネージャーを獲得
	m_gameStateManager = std::make_unique<GameStateManager>();

	//タイトルシーンを登録
	m_gameStateManager->RegisterState("Title", new TitleState());

	//プレイシーンを登録
	m_gameStateManager->RegisterState("Play", new PlayState());

	//開始シーンを登録
	m_gameStateManager->SetStartState("Play");

	//GameStateManagerをGameContextに登録
	GameContext<GameStateManager>::Register(m_gameStateManager);
}


#pragma region Frame Update
// Executes the basic game loop.
//関数	:瞬間
//引数	:なし
//戻り値:なし
void Game::Tick()
{
	m_timer.Tick([&]()
	{
		Update(m_timer);
	});

	Render();
}

// Updates the world.
//関数	:更新
//引数	:timer
//戻り値:なし
void Game::Update(DX::StepTimer const& timer)
{
	float elapsedTime = float(timer.GetElapsedSeconds());

	// TODO: Add your game logic here.
	elapsedTime;

	//ゲームマネージャーの更新
	m_gameStateManager->Update();
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
//関数	:描画
//引数	:なし
//戻り値:なし
void Game::Render()
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return;
	}

	//クリア
	Clear();

	m_deviceResources->PIXBeginEvent(L"Render");
	
	//別クラスに持っていく
	auto context = m_deviceResources->GetD3DDeviceContext();

	// TODO: Add your rendering code here.
	context;

	//ゲームマネージャーの描画
	m_gameStateManager->Render();

	m_deviceResources->PIXEndEvent();

	// Show the new frame.
	m_deviceResources->Present();
}

// Helper method to clear the back buffers.
//関数	:クリア
//引数	:なし
//戻り値:なし
void Game::Clear()
{

	m_deviceResources->PIXBeginEvent(L"Clear");

	// Clear the views.
	auto context = m_deviceResources->GetD3DDeviceContext();

	auto renderTarget = m_deviceResources->GetRenderTargetView();

	auto depthStencil = m_deviceResources->GetDepthStencilView();

	context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);

	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	context->OMSetRenderTargets(1, &renderTarget, depthStencil);

	// Set the viewport.
	auto viewport = m_deviceResources->GetScreenViewport();

	context->RSSetViewports(1, &viewport);

	m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
	// TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
	// TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
	// TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
	m_timer.ResetElapsedTime();

	// TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
	auto r = m_deviceResources->GetOutputSize();
	m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
	if (!m_deviceResources->WindowSizeChanged(width, height))
		return;

	CreateWindowSizeDependentResources();

	// TODO: Game window is being resized.
}

// Properties
//関数	:画面サイズ
//引数	:width,height
//戻り値:なし
void Game::GetDefaultSize(int& width, int& height) const
{
	// TODO: Change to desired default window size (note minimum size is 320x200).
	width = WINDOW_WIDTH;

	height = WINDOW_HEIGHT;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
	auto device = m_deviceResources->GetD3DDevice();

	// TODO: Initialize device dependent objects here (independent of window size).
	device;
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
	// TODO: Initialize windows-size dependent objects here.

	// ウインドウサイズからアスペクト比を算出する
	RECT size = m_deviceResources->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	// 画角を設定
	float fovAngleY = XMConvertToRadians(45.0f);

	// 射影行列を作成する
	m_projection = std::make_unique<Projection>();
	m_projection->SetPerspectiveFieldOfView(
		fovAngleY,
		aspectRatio,
		0.01f,
		1000.0f
	);

	//ProjectionをGameContextに登録
	GameContext<Projection>::Register(m_projection);
}

void Game::OnDeviceLost()
{
	// TODO: Add Direct3D resource cleanup here.
}

void Game::OnDeviceRestored()
{
	CreateDeviceDependentResources();

	CreateWindowSizeDependentResources();
}
#pragma endregion
