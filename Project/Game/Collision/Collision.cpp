//======================================================
// File Name :Collision.cpp
// Content	 :�����蔻��ɂ���
// Author    :Yuki Sato
//======================================================

#include "Collision.h"

#include "Game\Common\Math.h"


//�֐�	:���ƃ��C���̏Փ˔���֐�
//����	:sphere,line
//�߂�l:dist2 <= radius * radius
bool Collision::HitCheck_Sphere2Line(Sphere sphere, Line line)
{
	// ���̒��S�ƃ��C���̊J�n�n�_�ƏI���n�_�̌v�Z
	float dist2 = Math::SqDistPointSegment(line.p, line.p + line.d, sphere.c);
	float radius = sphere.r;
	return dist2 <= radius * radius;
}


//�֐�	:�J�v�Z���ƃ��C���̏Փ˔���֐�
//����	:capsule,line
//�߂�l:dist2 <= radius * radius
bool Collision::HitCheck_Capsule2Line(Capsule capsule, Line line)
{
	float s, t;
	DirectX::SimpleMath::Vector3 c1, c2;
	float dist2 = Math::ClosestPtSegmentSegment(capsule.a, capsule.b, line.p, line.d + line.p, s, t, c1, c2);
	float radius = capsule.r;
	return dist2 <= radius * radius;
}