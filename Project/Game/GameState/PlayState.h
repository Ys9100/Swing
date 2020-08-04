//======================================================
// File Name :PlayerState.h
// Content	 :プレイーシーンについて
// Author    :Yuki Sato
//======================================================
#pragma once

#include <memory>


#include <DirectXTK\CommonStates.h>
#include "Game\GameState\GameState.h"
#include "Game\Common\DeviceResources.h"
#include "Game\\Collision\CapsulePrimitive.h"
#include"Game\Object\Player\Player.h"
#include"Game\Object\Post\Post.h"
#include"Game\Object\Wire\Wire.h"




class PlayState : public IGameState
{
public:

	//支柱
	static Post* s_post;

private:
	//プレイヤー
	std::unique_ptr<Player>		m_player;

	//支柱
	std::unique_ptr<Post>		m_post;

public:

	//カメラのターゲット
	static const  DirectX::SimpleMath::Vector3 TARGET_TO_EYE_VEC;

public:

	//関数	:コンストラクタ
	PlayState();

public:

	//関数	:デストラクタ
	virtual ~PlayState();


public:
	//関数	:初期化
	void Initialize() override;

	//関数	:更新
	void Update() override;

	//関数	:描画
	void Render() override;

	//関数	:終了処理
	void Finalize() override;

private:
	//関数	:オブジェクトなどを作成
	void CreateDeviceDependentResources();

	// コモンステート
	std::unique_ptr<DirectX::CommonStates>	m_pState;

	//フォント
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;
	
	//m_object1が現在スイングしているobject
	DirectX::SimpleMath::Vector3					m_cameraswing;	 

	//振り子運動を管理するflag
	bool m_swingflag;		        
};
