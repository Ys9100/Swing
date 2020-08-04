//======================================================
// File Name :CapsulePrimitive.h
// Content	 :�J�v�Z���ɂ���
// Author    :Yuki Sato
//======================================================

#pragma once

#include <DirectXTK\SimpleMath.h>
#include <DirectXTK\GeometricPrimitive.h>

class CapsulePrimitive
{
public:

	//�֐�	:�J�v�Z���v���~�e�B�u���쐬
	static std::unique_ptr<CapsulePrimitive> __cdecl Create(_In_ ID3D11DeviceContext1* context, float segmentLength = 1.0f, float diameter = 1.0f);

	//�֐�	:�f�X�g���N�^
	~CapsulePrimitive();

	//�֐�	:�J�v�Z���v���~�e�B�u��`��
	void Draw(DirectX::SimpleMath::Matrix world, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection, DirectX::FXMVECTOR color = DirectX::Colors::White, _In_opt_ ID3D11ShaderResourceView* texture = nullptr, bool wireframe = false,
		_In_opt_ std::function<void __cdecl()> setCustomState = nullptr) const;

private:

	//�֐�	:�R���X�g���N�^
	CapsulePrimitive(ID3D11DeviceContext1* context, float segmentLength, float diameter) noexcept(false);

private:

	// ���[���h���W
	DirectX::SimpleMath::Matrix						m_worldMtx;

	// ������
	std::unique_ptr<DirectX::GeometricPrimitive>	m_pCylinder;

	// �������P
	std::unique_ptr<DirectX::GeometricPrimitive>	m_pSphere1;	

	// �������Q
	std::unique_ptr<DirectX::GeometricPrimitive>	m_pSphere2;		

	float											m_segmentLength;
	float											m_diameter;
};

