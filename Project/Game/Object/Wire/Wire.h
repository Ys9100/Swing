//======================================================
// File Name :Wire.h
// Content	 :ワイヤーについて.h
// Author    :Yuki Sato
//======================================================

#pragma once

#include "Game\Common\DeviceResources.h"
#include"Game\Object\Player\Player.h"
#include"Game\Object\Post\Post.h"

class Player;

class Wire
{
public:
	
	//関数	:コンストラクタ
	Wire(Player* player);

	//関数	:デストラクタ
	~Wire();

public:
	
	//関数	:初期化
	void Initialize();

	//関数	:更新
	void Update();

	//関数	:描画
	void Render();

	//関数	:終了処理
	void Finalize();

	//関数	:支柱の座標をセット
	void InjectWire(Post* post);

	//関数	:ワイヤーを切る
	void CutWire();

private:

	//関数	:CreateDeviceDependentResources
	void CreateDeviceDependentResources();

private:

	//ベーシックエフェクト
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

	// インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;

	//プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

	//プレイヤー
	Player*    m_player;

	//支柱
	Post*    m_post;

	//終点
	DirectX::SimpleMath::Vector3 m_targetPos;

	//ワイヤーの射出時間
	int count;

	//ワイヤーの射出最大時間
	int injection;
};

