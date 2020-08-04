//======================================================
// File Name :FollowCamera.cpp
// Content	 :対象を追従する
// Author    :Yuki Sato
//======================================================

#include "FollowCamera.h"

//関数	:コンストラクタ
//引数	:なし
//戻り値:なし
FollowCamera::FollowCamera()
{
	m_eye = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 10.0f);

	m_target = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

	m_up = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);
}

//関数	:デストラクタ
//引数	:なし
//戻り値:なし
FollowCamera::~FollowCamera()
{

}

//関数	:更新
//引数	:なし
//戻り値:なし
void FollowCamera::update()
{
	//カメラの位置計算
	m_eye += (m_ref_eye_pos - m_eye) * 0.1f;

	//targetの位置計算
	m_target += (m_ref_target_pos - m_target) * 0.1f;
	
	//viewに代入
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}