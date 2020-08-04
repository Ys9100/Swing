//======================================================
// File Name :GameStateManager.h
// Content	 :シーンを切り替える際に使う
// Author    :Yuki Sato
//======================================================
#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Game\Common\StepTimer.h"


class IGameState;


class GameStateManager final
{
	private:

		using GameStatePtr  = std::unique_ptr<IGameState>;

		using GameStateList = std::unordered_map<std::string, GameStatePtr>;

	private:

		//ステート
		GameStateList m_states;

		//アクティブステート
		IGameState*    m_activeState;

		//次のステート
		IGameState*    m_nextState;


	public:

		//関数	:コンストラクタ
		GameStateManager();


	public:

		//関数	:デストラクタ
		~GameStateManager();


	public:

		//関数	:ステートの登録
		void RegisterState(const std::string& stateName, IGameState* gameState);

		//関数	:最初のステートを登録
		void SetStartState(const std::string& stateName);

		//関数	:更新
		void Update();

		//関数	:描画
		void Render();

		//関数	:ステートを要求する
		void RequestState(const std::string& stateName);


	private:

		//関数	:ステートを変える
		void ChangeState();
};
