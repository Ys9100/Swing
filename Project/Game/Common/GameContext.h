//======================================================
// File Name :GameContext.h
// Content	 :ゲームコンテキストを扱う
// Author    :Yuki Sato
//======================================================

#pragma once



#include "Game\Common\ServiceLocator.h"

template<typename Context>

class GameContext final
{
private:

	//コンテキスト
	static Context* s_context;
public:

	//関数	:データを登録
	//引数	:context
	//戻り値:なし
	static void Register(const std::unique_ptr<Context>& context)
	{
		s_context = context.get();
	}

	//関数	:データを獲得
	//引数	:なし
	//戻り値:s_context
	static Context* Get()
	{
		assert(s_context && "The context has not been registered.");
		return s_context;
	}
};

template<typename Context>

//コンテキストをnullptr
Context* GameContext<Context>::s_context = nullptr;
