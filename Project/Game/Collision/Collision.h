//======================================================
// File Name :Collision.h
// Content	 :当たり判定について.h
// Author    :Yuki Sato
//======================================================

#pragma once

class Collision
{
public:

	// 直線の構造体
	struct Line
	{
		// スタート位置
		DirectX::SimpleMath::Vector3 p;	
		// 方向ベクトル
		DirectX::SimpleMath::Vector3 d;	
	};

	//球の構造体
	struct Sphere
	{
		// 球の中心 
		DirectX::SimpleMath::Vector3 c; 
		// 球の半径 
		float r;  
	};

	// カプセルの構造体 
	struct Capsule
	{
		// 中間部の線分の開始点 
		DirectX::SimpleMath::Vector3 a;
		// 中間部の線分の終了点 
		DirectX::SimpleMath::Vector3 b; 
		// 半径 
		float r;  
	};

public:

	//関数	:球とラインの衝突判定関数　//当たり判定のクラス
	static bool HitCheck_Sphere2Line(Sphere sphere, Line line);

	//関数	;カプセルとラインの衝突判定関数 
	static bool HitCheck_Capsule2Line(Capsule capsule, Line line);
};