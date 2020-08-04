//======================================================
// File Name :IGameState.h
// Content	 :ゲームステートを扱う
// Author    :Yuki Sato
//======================================================
#pragma once

#include "Game\Common\StepTimer.h"

class IGameState
{
	public:

		//関数	:コンストラクタ
		IGameState() = default;

	public:

		//関数	:デストラクタ
		virtual ~IGameState() = default;


	public:
		
		//関数	:初期化
		virtual void Initialize() = 0;
		
		//関数	:更新
		virtual void Update() = 0; //steptimer入れる float タイマー入れる
		
	    //関数	:描画
		virtual void Render() = 0;

		//関数	:終了処理
		virtual void Finalize() = 0;
};
