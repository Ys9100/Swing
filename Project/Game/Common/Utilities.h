//======================================================
// File Name :Utilities.h
// Content	 :���[�e�B���e�B�[������
// Author    :Yuki Sato
//======================================================

#pragma once

#include <algorithm>

template<class T>
inline constexpr const T& Clamp(const T& v, const T& low, const T& high)
{
	return std::min(std::max(v, low), high);
}
