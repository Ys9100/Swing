//======================================================
// File Name :Math.cpp
// Content	 :�v�Z�n��S������
// Author    :Yuki Sato
//======================================================
#include "Math.h"

//�d��
const DirectX::SimpleMath::Vector3 Math::GRAVITY = DirectX::SimpleMath::Vector3(0.0f, -0.01f, 0.0f);

//�֐�	:�_c�Ɛ���ab�̊Ԃ̋����̕�����Ԃ�
//����	:a,b,c
//�߂�l:ac.Dot(ac) - e * e / f
float Math::SqDistPointSegment(DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b, DirectX::SimpleMath::Vector3 c)
{
	DirectX::SimpleMath::Vector3 ab = b - a;
	DirectX::SimpleMath::Vector3 ac = c - a;
	DirectX::SimpleMath::Vector3 bc = c - b;
	float e = ac.Dot(ab);
	if (e <= 0.0f) return ac.Dot(ac);
	float f = ab.Dot(ab);
	if (e >= f) return bc.Dot(bc);
	return ac.Dot(ac) - e * e / f;
}


//�֐�	:�Q�̐����̍ŒZ�����̕�����Ԃ��֐�
//����	:p1,q1,p2,q2,s,t,c1,c2
//�߂�l:(c1 - c2).Dot(c1 - c2)
float Math::ClosestPtSegmentSegment(DirectX::SimpleMath::Vector3 p1, DirectX::SimpleMath::Vector3 q1,
	DirectX::SimpleMath::Vector3 p2, DirectX::SimpleMath::Vector3 q2,
	float &s, float &t, DirectX::SimpleMath::Vector3& c1, DirectX::SimpleMath::Vector3& c2)
{
	DirectX::SimpleMath::Vector3 d1 = q1 - p1;
	DirectX::SimpleMath::Vector3 d2 = q2 - p2;
	DirectX::SimpleMath::Vector3 r = p1 - p2;
	float a = d1.Dot(d1);
	float e = d2.Dot(d2);
	float f = d2.Dot(r);

	if (a <= FLT_EPSILON && e <= FLT_EPSILON) {
		s = t = 0.0f;
		c1 = p1;
		c2 = p2;
		return (c1 - c2).Dot(c1 - c2);
	}
	if (a <= FLT_EPSILON) {
		s = 0.0f;
		t = f / e;
		t = Clamp(t, 0.0f, 1.0f);
	}
	else
	{
		float c = d1.Dot(r);
		if (e <= FLT_EPSILON)
		{
			t = 0.0f; s = Clamp(-c / a, 0.0f, 1.0f);
		}
		else {
			float b = d1.Dot(d2);
			float denom = a * e - b * b;
			if (denom != 0.0f)
			{
				s = Clamp((b * f - c * e) / denom, 0.0f, 1.0f);
			}
			else
			{
				s = 0.0f;
			}
			float tnom = (b * s + f);
			if (tnom < 0.0f)
			{
				t = 0.0f; s = Clamp(-c / a, 0.0f, 1.0f);
			}
			else if (tnom > e)
			{
				t = 1.0f;
				s = Clamp((b - c) / a, 0.0f, 1.0f);
			}
			else
			{
				t = tnom / e;
			}
		}
	}

	c1 = p1 + d1 * s;
	c2 = p2 + d2 * t;
	return (c1 - c2).Dot(c1 - c2);

}


DirectX::SimpleMath::Matrix Math::CreateMatrix_Screen2World(int screen_w, int screen_h, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	// �r���[�|�[�g�X�P�[�����O�s����쐬
	DirectX::SimpleMath::Matrix viewport; viewport._11 = screen_w / 2.0f;
	viewport._22 = -screen_h / 2.0f;
	viewport._41 = screen_w / 2.0f;
	viewport._42 = screen_h / 2.0f;
	// �t�s����쐬 
	DirectX::SimpleMath::Matrix invS = viewport.Invert();
	DirectX::SimpleMath::Matrix invP = projection.Invert();
	DirectX::SimpleMath::Matrix invV = view.Invert();
	// �w�r���[�|�[�g�X�P�[�����O�s��̋t�s��x �~ �w�ˉe�s��̋t�s��x �~ �w�r���[�s��̋t�s��x 
	return invS * invP * invV;
}
