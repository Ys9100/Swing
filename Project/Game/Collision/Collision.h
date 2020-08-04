//======================================================
// File Name :Collision.h
// Content	 :�����蔻��ɂ���.h
// Author    :Yuki Sato
//======================================================

#pragma once

class Collision
{
public:

	// �����̍\����
	struct Line
	{
		// �X�^�[�g�ʒu
		DirectX::SimpleMath::Vector3 p;	
		// �����x�N�g��
		DirectX::SimpleMath::Vector3 d;	
	};

	//���̍\����
	struct Sphere
	{
		// ���̒��S 
		DirectX::SimpleMath::Vector3 c; 
		// ���̔��a 
		float r;  
	};

	// �J�v�Z���̍\���� 
	struct Capsule
	{
		// ���ԕ��̐����̊J�n�_ 
		DirectX::SimpleMath::Vector3 a;
		// ���ԕ��̐����̏I���_ 
		DirectX::SimpleMath::Vector3 b; 
		// ���a 
		float r;  
	};

public:

	//�֐�	:���ƃ��C���̏Փ˔���֐��@//�����蔻��̃N���X
	static bool HitCheck_Sphere2Line(Sphere sphere, Line line);

	//�֐�	;�J�v�Z���ƃ��C���̏Փ˔���֐� 
	static bool HitCheck_Capsule2Line(Capsule capsule, Line line);
};