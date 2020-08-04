//======================================================
// File Name :Collision.cpp
// Content	 :当たり判定について
// Author    :Yuki Sato
//======================================================

#include "Collision.h"

#include "Game\Common\Math.h"


//関数	:球とラインの衝突判定関数
//引数	:sphere,line
//戻り値:dist2 <= radius * radius
bool Collision::HitCheck_Sphere2Line(Sphere sphere, Line line)
{
	// 球の中心とラインの開始地点と終了地点の計算
	float dist2 = Math::SqDistPointSegment(line.p, line.p + line.d, sphere.c);
	float radius = sphere.r;
	return dist2 <= radius * radius;
}


//関数	:カプセルとラインの衝突判定関数
//引数	:capsule,line
//戻り値:dist2 <= radius * radius
bool Collision::HitCheck_Capsule2Line(Capsule capsule, Line line)
{
	float s, t;
	DirectX::SimpleMath::Vector3 c1, c2;
	float dist2 = Math::ClosestPtSegmentSegment(capsule.a, capsule.b, line.p, line.d + line.p, s, t, c1, c2);
	float radius = capsule.r;
	return dist2 <= radius * radius;
}