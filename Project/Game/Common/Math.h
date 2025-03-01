//======================================================
// File Name :Math.h
// Content	 :計算系を担当する
// Author    :Yuki Sato
//======================================================
#pragma once

#include <DirectXTK\SimpleMath.h>

class Math
{
public:

	//重力
	static const DirectX::SimpleMath::Vector3 GRAVITY;

public:

	//関数	:クランプ
	//引数	:n,min,max
	//戻り値:,max,min
	static float Clamp(float n, float min, float max)
	{
		if (n < min) return min; if (n > max) return max; return n;
	}

	//関数	:点cと線分abの間の距離の平方を返す
	static float SqDistPointSegment(DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b, DirectX::SimpleMath::Vector3 c);

	//関数	:２つの線分の最短距離の平方を返す 
	static float ClosestPtSegmentSegment(DirectX::SimpleMath::Vector3 p1, DirectX::SimpleMath::Vector3 q1,
		DirectX::SimpleMath::Vector3 p2, DirectX::SimpleMath::Vector3 q2,
		float &s, float &t, DirectX::SimpleMath::Vector3& c1, DirectX::SimpleMath::Vector3& c2);

	static DirectX::SimpleMath::Matrix CreateMatrix_Screen2World(int screen_w, int screen_h, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

};