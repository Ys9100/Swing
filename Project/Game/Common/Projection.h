//======================================================
// File Name :Projection.h
// Content	 :プロジェクションを扱う
// Author    :Yuki Sato
//======================================================

#pragma once


#include <DirectXTK\SimpleMath.h>

class Projection final
{
	private:

		//マトリクス
		DirectX::SimpleMath::Matrix m_matrix;


	public:
		//関数	:コンストラクタ
		Projection() = default;

	public:

		//関数	:デストラクタ
		~Projection() = default;


	public:

		//関数	:マトリクスを獲得
		const DirectX::SimpleMath::Matrix& GetMatrix() const;

		//関数	:ビューのパースペクティブフィールドを設定
		void SetPerspectiveFieldOfView(float fov, float aspectRatio, float nearPlane, float farPlane);
};

//関数	:マトリクスを獲得
//引数	:なし
//戻り値:m_matrix;
inline const DirectX::SimpleMath::Matrix& Projection::GetMatrix() const
{
	return m_matrix;
}

//関数	:ビューのパースペクティブフィールドを設定
//引数	;fov,aspectRatio,nearPlane,farPlane
//戻り値:なし
inline void Projection::SetPerspectiveFieldOfView(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	m_matrix = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(fov, aspectRatio, nearPlane, farPlane);
}
