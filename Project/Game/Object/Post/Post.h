//======================================================
// File Name :Post.h
// Content	 :支柱について
// Author    :Yuki Sato
//======================================================

#pragma once

#include <DirectXTK\CommonStates.h>
#include "Game\Common\DeviceResources.h"
#include "Game\\Collision\CapsulePrimitive.h"

class Post
{
public:

	//関数	:初期化
	void Initialize();

	//関数	:更新
	void Update();

	//関数	:描画
	void Render();

	//関数	:終了処理
	void Finalize();

public:

	//関数	:支柱の座標獲得
	//引数	:なし
	//戻り値:m_position
	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; };

	//関数	:座標をセット
	//引数	:position
	//戻り値:なし
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; };

private:

	//関数	:オブジェクトなどを作成
	void CreateDeviceDependentResources();

private:

	//支柱のオブジェクト
	std::unique_ptr<CapsulePrimitive>				m_model;

	//支柱のマトリクス
	DirectX::SimpleMath::Matrix						m_worldMatrix;

	//支柱の座標
	DirectX::SimpleMath::Vector3					m_position;

	//支柱のカラー
	DirectX::SimpleMath::Color						m_color;
};