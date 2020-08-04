//======================================================
// File Name :Wire.cpp
// Content	 :ワイヤーについて
// Author    :Yuki Sato
//======================================================

#include"Wire.h"

#include "Game\Common\GameContext.h"
#include "Game\Common\Projection.h"

//関数	:コンストラクタ
//引数	:player
//戻り値:なし
Wire::Wire(Player* player)
{
	//playerに代入
	m_player = player;

	//ポストをnullptr
	m_post = nullptr;
}

//関数	:デストラクタ
//引数	:なし
//戻り値:なし
Wire::~Wire()
{
}

//関数	:初期化
//引数	:なし
//戻り値:なし
void Wire::Initialize()
{
	//CreateDeviceDependentResources初期化
	CreateDeviceDependentResources();

	//カウント初期化
	count = 0;

	//ワイヤーの射出最大時間の設定
	injection = 20;
}

//関数	:更新
//引数	:なし
//戻り値:なし
void Wire::Update()
{
	//ポストがnullptrだったら
	if (m_post == nullptr)
	{
		//カウントの方が多い時
		if (count > 0)
		{
			//カウントを減らす
			count--;
		}

		//カウントが0だったら
		if (count == 0)
		{
			//playerのstateを変更
			m_player->ChangeDropping();

			//カウントを0にする
			count = 0;
		}
	}
	else
	{
		//インジェクションの方が多い時
		if (count < injection)
		{
			//カウントを増やす
			count++;

			//カウントとインジェクションの値が同じ時
			if (count == injection)
			{
				//playerのstateを変えて終点の場所をセット
				m_player->ChangeSwing(m_targetPos);
			}
		}
	}
}

//関数	:描画
//引数	:なし
//戻り値:なし
void Wire::Render()
{
	//DeviceResourcesをGet
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();

	//ID3D11DeviceContextをGet
	ID3D11DeviceContext* context = deviceResources->GetD3DDeviceContext();
	
	//ProjectionをGet
	Projection*   projection = GameContext<Projection>::Get();

	//FollowCameraをGet
	FollowCamera* camera     = GameContext<FollowCamera>::Get();

	//basicEffectの設定
	m_basicEffect->SetWorld(DirectX::SimpleMath::Matrix::Identity);
	m_basicEffect->SetView(camera->getViewMatrix());
	m_basicEffect->SetProjection(projection->GetMatrix());
	m_basicEffect->Apply(context);

	//IASetInputLayoutのセット
	context->IASetInputLayout(m_pInputLayout.Get());

	//ワイヤーの始点
	DirectX::SimpleMath::Vector3 startPos = m_player->GetPosition();

	//ワイヤーの終点
	DirectX::SimpleMath::Vector3 v = m_targetPos - startPos;
	float ration = static_cast<float>(count) / injection;
	DirectX::SimpleMath::Vector3 endPos = startPos + v*ration;

	//ワイヤーの始点の座標とカラーセット
	DirectX::VertexPositionColor a(startPos, DirectX::Colors::White);

	//ワイヤーの終点の座標とカラーセット
	DirectX::VertexPositionColor b(endPos, DirectX::Colors::White);

	//ワイヤーの描画開始
	m_primitiveBatch->Begin();

	//ワイヤーの描画
	m_primitiveBatch->DrawLine(a, b);

	//ワイヤーの描画終了
	m_primitiveBatch->End();
}

//関数	:終了処理
//引数	:なし
//戻り値:なし
void Wire::Finalize()
{
	//プリミティブバッチのリセット
	m_primitiveBatch.reset();
}

//関数	:オブジェクトなどを作成
//引数	:なし
//戻り値:なし
void Wire::CreateDeviceDependentResources()
{
	//DeviceResourcesをGet
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();

	//ID3D11DeviceをGet
	ID3D11Device*        device          = deviceResources->GetD3DDevice();

	//ID3D11DeviceContextをGet
	ID3D11DeviceContext* context         = deviceResources->GetD3DDeviceContext();

	// プリミティブオブジェクト生成
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(context);

	// エフェクトの生成
	m_basicEffect = std::make_unique<DirectX::BasicEffect>(device);

	// 頂点カラー(有効)
	m_basicEffect->SetVertexColorEnabled(true);

	// インプットレイアウト生成
	void const* shaderByteCode;

	size_t byteCodeLength;

	m_basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	device->CreateInputLayout(DirectX::VertexPositionColor::InputElements,
		DirectX::VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_pInputLayout.GetAddressOf());
}

//関数	:ポストの座標をセットする
//引数	:post
//戻り値:なし
void Wire::InjectWire(Post* post)
{
	//ポストだったら
	if (post)
	{
		//ポストを代入
		m_post = post;

		//ターゲットをポストの座標にする
		m_targetPos = post->GetPosition();
	}
};

//関数	:ワイヤーを切る
//引数	:なし
//戻り値:なし
void Wire::CutWire()
{
	//ポストの座標を破棄
	m_post = nullptr;

	//ステートをドロッピング
	m_player->ChangeDropping();
}