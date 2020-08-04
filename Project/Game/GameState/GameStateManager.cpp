//======================================================
// File Name :GameStateManager.cpp
// Content	 :シーンを切り替える際に使う
// Author    :Yuki Sato
//======================================================

#include "GameStateManager.h"

#include <cassert>

#include "Game\GameState\GameState.h"
 
//関数	:コンストラクタ
//引数	:なし
//戻り値:なし
GameStateManager::GameStateManager()
	: m_states()
	, m_activeState(nullptr)
	, m_nextState(nullptr)
{
}

//関数	:デストラクタ
//引数	:なし
//戻り値:なし
GameStateManager::~GameStateManager()
{
}

//関数	:ステートの登録
//引数	:stateName,gameState
//戻り値:なし
void GameStateManager::RegisterState(const std::string & stateName, IGameState* gameState)
{
	m_states.insert(std::make_pair(stateName, gameState));
}

//関数	:最初のステートを登録
//引数	:stateName
//戻り値:なし
void GameStateManager::SetStartState(const std::string& stateName)
{
	RequestState(stateName);
}

//関数	:更新
//引数	:なし
//戻り値:なし
void GameStateManager::Update()
{
	//次のシーンか
	if (m_nextState)
	{
		//ステートを変える
		ChangeState();

		//次のステートを破棄する
		m_nextState = nullptr;
	}


	assert(m_activeState && "There is no active state.");

	//アクティブステートの更新
	m_activeState->Update();
}

//関数	:描画
//引数	:なし
//戻り値:なし
void GameStateManager::Render()
{
	assert(m_activeState && "There is no active state.");

	//アクティブステートの描画
	m_activeState->Render();
}

//関数	:ステートを要求する
//引数	:stateName
//戻り値:なし
void GameStateManager::RequestState(const std::string& stateName)
{
	assert(m_states.count(stateName) == 1 && "A GameState with this name is not registered.");

	m_nextState = m_states[stateName].get();
}

//関数	:ステートを変える
//引数	:なし
//戻り値:なし
void GameStateManager::ChangeState()
{
	//アクティブステートか
	if (m_activeState)
	{
		//アクティブステートの終了処理
		m_activeState->Finalize();
	}

	//アクティブステート=次のステート
	m_activeState = m_nextState;

	//アクティブステートの初期化
	m_activeState->Initialize();
}
