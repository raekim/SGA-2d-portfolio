#pragma once

#include "Player.h"
#include "PlaceableObject.h"
#include "PlayerCursor.h"
#include "GoalFlag.h"
#include "Map.h"
#include "SimplePlatform.h"
#include "honeyPlatform.h"
#include "BallShooter.h"
#include "SpringPlatform.h"
#include "SpinWheel.h"

class PlayScene : public iGameNode
{
	enum class MODE
	{
		MAPTOOL_MODE,
		PLAY_MODE
	};

	Map*						m_map;
	MODE						m_curMode;
	Player*						m_player1P;
	Player*						m_player2P;
	PlayerCursor*				m_cursor1P;
	PlayerCursor*				m_cursor2P;
	float						m_mapToolModeTransitionDelay;	// 플레이 모드에서 맵툴 모드로 갈 때 걸리는 시간
	float						m_transitionCount;				// 시간 측정용 카운터

	// 카메라 관련
	D3DXVECTOR2					m_camPos;
private:
	void SwitchToMapToolMode();
	void SwitchToPlayMode();

	// 플레이 모드 관련
	void UpdatePlayMode();
	void UpdatePlayModeCamera();
public:
	PlayScene();
	~PlayScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

