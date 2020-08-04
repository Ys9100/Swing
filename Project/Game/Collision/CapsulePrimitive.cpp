//======================================================
// File Name :CapsulePrimitive.cpp
// Content	 :�J�v�Z���ɂ���
// Author    :Yuki Sato
//======================================================

#include "CapsulePrimitive.h"

//�֐�	:�J�v�Z���v���~�e�B�u���쐬
//����	:context,segmentLength,radius
//�߂�l:primitive
std::unique_ptr<CapsulePrimitive>  CapsulePrimitive::Create(_In_ ID3D11DeviceContext1* context, float segmentLength, float radius)
{

	std::unique_ptr<CapsulePrimitive> primitive(new CapsulePrimitive(context, segmentLength, radius));

	return primitive;
}

//�֐�	:�R���X�g���N�^
//����	:context,segmentLength,diameter
//�߂�l:�Ȃ�
CapsulePrimitive::CapsulePrimitive(ID3D11DeviceContext1* context, float segmentLength, float diameter)
{

	m_pCylinder = DirectX::GeometricPrimitive::CreateCylinder(context, segmentLength, diameter);
	m_pSphere1 = DirectX::GeometricPrimitive::CreateSphere(context, diameter);
	m_pSphere2 = DirectX::GeometricPrimitive::CreateSphere(context, diameter);

	m_segmentLength = segmentLength;
	m_diameter = diameter;
}

//�֐�	:�f�X�g���N�^
//����	:�Ȃ�
//�߂�l:�Ȃ�
CapsulePrimitive::~CapsulePrimitive()
{
}

//�֐�	:�J�v�Z���v���~�e�B�u��`��
//����	:world,view,projection,color,texture,wireframe,setCustomState
//�߂�l:�Ȃ�
void CapsulePrimitive::Draw(DirectX::SimpleMath::Matrix world, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection, DirectX::FXMVECTOR color, _In_opt_ ID3D11ShaderResourceView* texture, bool wireframe,
	_In_opt_ std::function<void __cdecl()> setCustomState) const
{
	DirectX::SimpleMath::Matrix localCylinder, localSphere1, localSphere2;

	// �ړ�
	localSphere1 = DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(0.0f, m_segmentLength * 0.5f, 0.0f));
	localSphere2 = DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(0.0f, -m_segmentLength * 0.5f, 0.0f));

	// �`��
	m_pCylinder->Draw(localCylinder * world, view, projection, color, texture, wireframe, setCustomState);
	m_pSphere1->Draw(localSphere1 * world, view, projection, color, texture, wireframe, setCustomState);
	m_pSphere2->Draw(localSphere2 * world, view, projection, color, texture, wireframe, setCustomState);
}