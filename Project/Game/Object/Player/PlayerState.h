//======================================================
// File Name :PlayerState.h
// Content	 :プレイヤーのステートを管理する
// Author    :Yuki Sato
//======================================================


#pragma once

class Player;

class PlayerState
{	
public:

	//関数	:コンストラクタ
	//引数	:player
	//戻り値:なし
	PlayerState(Player* player)
		: m_player(player)
	{
	}

	//関数	:デストラクタ
	//引数	:なし
	//戻り値:なし
	virtual ~PlayerState()
	{
		m_player = nullptr;
	}

	//関数	:ハンドル入力
	virtual void HandleInput()=0;

	//関数	:更新
	virtual void Update()=0;

protected:

	//プレイヤー
	Player* m_player;

};

