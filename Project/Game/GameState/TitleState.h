//======================================================
// File Name :TitleState.h
// Content	 :タイトルーシーンについて
// Author    :Yuki Sato
//======================================================

#pragma once


#include "Game\Common\StepTimer.h"
#include "Game\GameState\GameState.h"


class TitleState : public IGameState
{
private:

	//カウント
	int m_count;
public:

	//関数	:コンストラクタ
	TitleState();

public:

	//関数	:デストラクタ
	virtual ~TitleState();


public:
	//関数	:初期化
	void Initialize() override;

	//関数	:更新
	void Update() override;

	//関数	:描画
	void Render() override;

	//関数	:終了処理
	void Finalize() override;
};
