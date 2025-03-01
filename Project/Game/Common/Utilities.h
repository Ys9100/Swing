//======================================================
// File Name :Utilities.h
// Content	 :ユーティリティーを扱う
// Author    :Yuki Sato
//======================================================

#pragma once

#include <algorithm>

template<class T>
inline constexpr const T& Clamp(const T& v, const T& low, const T& high)
{
	return std::min(std::max(v, low), high);
}
