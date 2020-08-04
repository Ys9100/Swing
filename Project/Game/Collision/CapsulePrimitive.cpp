//======================================================
// File Name :CapsulePrimitive.cpp
// Content	 :カプセルについて
// Author    :Yuki Sato
//======================================================

#include "CapsulePrimitive.h"

//関数	:カプセルプリミティブを作成
//引数	:context,segmentLength,radius
//戻り値:primitive
std::unique_ptr<CapsulePrimitive>  CapsulePrimitive::Create(_In_ ID3D11DeviceContext1* context, float segmentLength, float radius)
{

	std::unique_ptr<CapsulePrimitive> primitive(new CapsulePrimitive(context, segmentLength, radius));

	return primitive;
}

//関数	:コンストラクタ
//引数	:context,segmentLength,diameter
//戻り値:なし
CapsulePrimitive::CapsulePrimitive(ID3D11DeviceContext1* context, float segmentLength, float diameter)
{

	m_pCylinder = DirectX::GeometricPrimitive::CreateCylinder(context, segmentLength, diameter);
	m_pSphere1 = DirectX::GeometricPrimitive::CreateSphere(context, diameter);
	m_pSphere2 = DirectX::GeometricPrimitive::CreateSphere(context, diameter);

	m_segmentLength = segmentLength;
	m_diameter = diameter;
}

//関数	:デストラクタ
//引数	:なし
//戻り値:なし
CapsulePrimitive::~CapsulePrimitive()
{
}

//関数	:カプセルプリミティブを描画
//引数	:world,view,projection,color,texture,wireframe,setCustomState
//戻り値:なし
void CapsulePrimitive::Draw(DirectX::SimpleMath::Matrix world, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection, DirectX::FXMVECTOR color, _In_opt_ ID3D11ShaderResourceView* texture, bool wireframe,
	_In_opt_ std::function<void __cdecl()> setCustomState) const
{
	DirectX::SimpleMath::Matrix localCylinder, localSphere1, localSphere2;

	// 移動
	localSphere1 = DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(0.0f, m_segmentLength * 0.5f, 0.0f));
	localSphere2 = DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(0.0f, -m_segmentLength * 0.5f, 0.0f));

	// 描画
	m_pCylinder->Draw(localCylinder * world, view, projection, color, texture, wireframe, setCustomState);
	m_pSphere1->Draw(localSphere1 * world, view, projection, color, texture, wireframe, setCustomState);
	m_pSphere2->Draw(localSphere2 * world, view, projection, color, texture, wireframe, setCustomState);
}