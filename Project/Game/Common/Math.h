//======================================================
// File Name :Math.h
// Content	 :�v�Z�n��S������
// Author    :Yuki Sato
//======================================================
#pragma once

#include <DirectXTK\SimpleMath.h>

class Math
{
public:

	//�d��
	static const DirectX::SimpleMath::Vector3 GRAVITY;

public:

	//�֐�	:�N�����v
	//����	:n,min,max
	//�߂�l:,max,min
	static float Clamp(float n, float min, float max)
	{
		if (n < min) return min; if (n > max) return max; return n;
	}

	//�֐�	:�_c�Ɛ���ab�̊Ԃ̋����̕�����Ԃ�
	static float SqDistPointSegment(DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b, DirectX::SimpleMath::Vector3 c);

	//�֐�	:�Q�̐����̍ŒZ�����̕�����Ԃ� 
	static float ClosestPtSegmentSegment(DirectX::SimpleMath::Vector3 p1, DirectX::SimpleMath::Vector3 q1,
		DirectX::SimpleMath::Vector3 p2, DirectX::SimpleMath::Vector3 q2,
		float &s, float &t, DirectX::SimpleMath::Vector3& c1, DirectX::SimpleMath::Vector3& c2);

	static DirectX::SimpleMath::Matrix CreateMatrix_Screen2World(int screen_w, int screen_h, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

};