//======================================================
// File Name :CapsulePrimitive.h
// Content	 :カプセルについて
// Author    :Yuki Sato
//======================================================

#pragma once

#include <DirectXTK\SimpleMath.h>
#include <DirectXTK\GeometricPrimitive.h>

class CapsulePrimitive
{
public:

	//関数	:カプセルプリミティブを作成
	static std::unique_ptr<CapsulePrimitive> __cdecl Create(_In_ ID3D11DeviceContext1* context, float segmentLength = 1.0f, float diameter = 1.0f);

	//関数	:デストラクタ
	~CapsulePrimitive();

	//関数	:カプセルプリミティブを描画
	void Draw(DirectX::SimpleMath::Matrix world, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection, DirectX::FXMVECTOR color = DirectX::Colors::White, _In_opt_ ID3D11ShaderResourceView* texture = nullptr, bool wireframe = false,
		_In_opt_ std::function<void __cdecl()> setCustomState = nullptr) const;

private:

	//関数	:コンストラクタ
	CapsulePrimitive(ID3D11DeviceContext1* context, float segmentLength, float diameter) noexcept(false);

private:

	// ワールド座標
	DirectX::SimpleMath::Matrix						m_worldMtx;

	// 筒部分
	std::unique_ptr<DirectX::GeometricPrimitive>	m_pCylinder;

	// 球部分１
	std::unique_ptr<DirectX::GeometricPrimitive>	m_pSphere1;	

	// 球部分２
	std::unique_ptr<DirectX::GeometricPrimitive>	m_pSphere2;		

	float											m_segmentLength;
	float											m_diameter;
};

