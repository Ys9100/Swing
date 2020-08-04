//======================================================
// File Name :Post.cpp
// Content	 :支柱について
// Author    :Yuki Sato
//======================================================

#include "Post.h"

#include "Game\Common\GameContext.h"
#include"Game\Collision\Collision.h"
#include "Game\Camera\FollowCamera.h"
#include "Game\Game.h"

using namespace DirectX;

using Microsoft::WRL::ComPtr;


//関数	:初期化
//引数	:なし
//戻り値:なし
void Post::Initialize()
{
	//CreateDeviceDependentResourcesの初期化
	CreateDeviceDependentResources();

	//初期座標
	m_position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

	//初期カラー
	m_color = DirectX::Colors::White;
}

//関数	:更新
//引数	:なし
//戻り値:なし
void Post::Update()
{
	
}

//関数	:描画
//引数	:なし
//戻り値:なし
void Post::Render()
{
	//ProjectionをGet
	Projection* projection = GameContext<Projection>::Get();

	//FollowCameraをGet
	FollowCamera* camera = GameContext<FollowCamera>::Get();

	//マトリクスの指定
	DirectX::SimpleMath::Matrix matrix = DirectX::SimpleMath::Matrix::Identity;

	//matrix=支柱の座標
	matrix = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	//支柱の描画
	m_model->Draw(matrix, camera->getViewMatrix(), projection->GetMatrix(), m_color);
}

//関数	:終了処理
//引数	:なし
//戻り値:なし
void Post::Finalize()
{
	//支柱のオブジェクトのリセット
	m_model.reset();
}

//関数	:オブジェクトなどを作成
//引数	:なし
//戻り値:なし
void Post::CreateDeviceDependentResources()
{
	//DeviceResourcesをGetする
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();

	//ID3D11DeviceをGetする
	ID3D11Device*          device = deviceResources->GetD3DDevice();

	//ID3D11DeviceContext1をGetする
	ID3D11DeviceContext1*   context = deviceResources->GetD3DDeviceContext();

	// TODO: Initialize device dependent objects here (independent of window size).
	device;

	//支柱のオブジェクトの作成
	m_model = CapsulePrimitive::Create(context);
}
