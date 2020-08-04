//======================================================
// File Name :Game.h
// Content	 :�Q�[���ɂ���
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

	////�E�B���h�[��
	static LPCWSTR WINDOW_NAME;

	//��ʍ���
	static const int WINDOW_WIDTH;

	//��ʕ�
	static const int WINDOW_HEIGHT;
public:

	//�֐�	:�R���X�g���N�^
	Game() noexcept(false);

	//�֐�	:�f�X�g���N�^
	~Game();

	// Initialization and management
	//�֐�	:������
	void Initialize(HWND window, int width, int height);

	// Basic game loop
	//�֐�	:�u��
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

	//�֐�	:�X�V
	void Update(DX::StepTimer const& timer);

	//�֐�	:�`��	
	void Render();

	//�֐�	:�N���A
	void Clear();

	void CreateDeviceDependentResources();

	void CreateWindowSizeDependentResources();



	//�f�o�C�X���\�[�V�[�Y.
	std::unique_ptr<DX::DeviceResources>    m_deviceResources;

	//�^�C�}�[
	DX::StepTimer                           m_timer;

	// �ˉe�s��
	std::unique_ptr<Projection>             m_projection;

	//�J����
	std::unique_ptr<FollowCamera>			m_camera;

	// �}�E�X
	std::unique_ptr<DirectX::Mouse>			m_mouse;

	//�L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard>      m_keyboard;

	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates>	m_state;

	//�X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch>   m_spriteBatch;

	//�Q�[���}�l�[�W���[
	std::unique_ptr<GameStateManager>       m_gameStateManager;

};
