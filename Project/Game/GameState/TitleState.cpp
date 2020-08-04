//======================================================
// File Name :TitleState.cpp
// Content	 :タイトルーシーンについて
// Author    :Yuki Sato
//======================================================

#include "TitleState.h"

#include <DirectXTK\Mouse.h>
#include <DirectXTK\CommonStates.h>
#include "Game\Font\DebugFont.h"
#include "Game\Common\GameContext.h"
#include "Game\GameState\GameStateManager.h"

//関数	:コンストラクタ
//引数	:なし
//戻り値:なし
TitleState::TitleState()
	: IGameState()
	, m_count(0)
{
}


//関数	:デストラクタ
//引数	:なし
//戻り値:なし
TitleState::~TitleState()
{
}


//関数	:初期化
//引数	:なし
//戻り値:なし
void TitleState::Initialize()
{
	//カウント初期化
	m_count = 0;
}


//関数	:更新
//引数	:なし
//戻り値:なし
void TitleState::Update()
{
	//MouseをGet
	DirectX::Mouse::State mouse = DirectX::Mouse::Get().GetState();

	//クリック時にシーンをプレイシーンへ移行
	if (mouse.leftButton)
	{
		//GameStateManagerをGet
		GameStateManager* gameStateManager = GameContext<GameStateManager>::Get();

		//次のシーンを指定
		gameStateManager->RequestState("Play");
	}
}


//関数	:描画
//引数	:なし
//戻り値:なし
void TitleState::Render()
{
	//デバッグフォント
	DebugFont* debugFont = DebugFont::GetInstance();

	//フォント表示
	debugFont->print(10, 10, L"Swing");

	//フォント表示
	debugFont->print(10, 30, L"Play[MouseLeftButton]");

	//フォント描画開始
	debugFont->draw();
}


//関数	:終了処理
//引数	:なし
//戻り値:なし
void TitleState::Finalize()
{
	
}
