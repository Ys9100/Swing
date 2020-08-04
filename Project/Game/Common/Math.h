//======================================================
// File Name :Math.h
// Content	 :ŒvZŒn‚ğ’S“–‚·‚é
// Author    :Yuki Sato
//======================================================
#pragma once

#include <DirectXTK\SimpleMath.h>

class Math
{
public:

	//d—Í
	static const DirectX::SimpleMath::Vector3 GRAVITY;

public:

	//ŠÖ”	:ƒNƒ‰ƒ“ƒv
	//ˆø”	:n,min,max
	//–ß‚è’l:,max,min
	static float Clamp(float n, float min, float max)
	{
		if (n < min) return min; if (n > max) return max; return n;
	}

	//ŠÖ”	:“_c‚Æü•ªab‚ÌŠÔ‚Ì‹——£‚Ì•½•û‚ğ•Ô‚·
	static float SqDistPointSegment(DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b, DirectX::SimpleMath::Vector3 c);

	//ŠÖ”	:‚Q‚Â‚Ìü•ª‚ÌÅ’Z‹——£‚Ì•½•û‚ğ•Ô‚· 
	static float ClosestPtSegmentSegment(DirectX::SimpleMath::Vector3 p1, DirectX::SimpleMath::Vector3 q1,
		DirectX::SimpleMath::Vector3 p2, DirectX::SimpleMath::Vector3 q2,
		float &s, float &t, DirectX::SimpleMath::Vector3& c1, DirectX::SimpleMath::Vector3& c2);

	static DirectX::SimpleMath::Matrix CreateMatrix_Screen2World(int screen_w, int screen_h, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

};