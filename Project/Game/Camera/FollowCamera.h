//======================================================
// File Name :FollowCamera.h
// Content	 :対象を追従する
// Author    :Yuki Sato
//======================================================

#pragma once

#include <DirectXTK\SimpleMath.h>

class FollowCamera
{
private:

	// 視点
	DirectX::SimpleMath::Vector3 m_eye;

	// 注視点
	DirectX::SimpleMath::Vector3 m_target;

	//上の方向
	DirectX::SimpleMath::Vector3 m_up;

	// 生成されたビュー行列
	DirectX::SimpleMath::Matrix m_view;

	// 参照視点 
	DirectX::SimpleMath::Vector3 m_ref_eye_pos;

	// 参照注視点 
	DirectX::SimpleMath::Vector3 m_ref_target_pos;

public:

	//関数	:コンストラクタ
	FollowCamera();

	//関数	;デストラクタ
	~FollowCamera();

	//関数	:更新
	void update();


public:

	//関数	:m_viewを獲得
	//引数	:なし
	//戻り値:m_view
	DirectX::SimpleMath::Matrix getViewMatrix()
	{
		return m_view;
	}

	//関数	:視点の設定
	//引数	:eye
	//戻り値:なし
	void SetEye(DirectX::SimpleMath::Vector3 eye)
	{
		m_eye = eye;
	}

	//関数	:注視点の設定
	//引数	:target
	//戻り値:なし
	void SetTarget(DirectX::SimpleMath::Vector3 target)
	{
		m_target = target;
	}

	//関数	:視点の座標
	//引数	:ref_eye_pos
	//戻り値:なし
	void SetRefEyePos(DirectX::SimpleMath::Vector3 ref_eye_pos)
	{
		m_ref_eye_pos = ref_eye_pos;
	}

	//関数	:視点の対象の座標
	//引数	:ref_target_pos
	//戻り値:なし
	void SetRefTargetPos(DirectX::SimpleMath::Vector3 ref_target_pos)
	{
		m_ref_target_pos = ref_target_pos;
	}
};