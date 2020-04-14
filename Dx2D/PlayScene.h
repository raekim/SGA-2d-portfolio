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
	float						m_mapToolModeTransitionDelay;	// �÷��� ��忡�� ���� ���� �� �� �ɸ��� �ð�
	float						m_transitionCount;				// �ð� ������ ī����

	// ī�޶� ����
	D3DXVECTOR2					m_camPos;
private:
	void SwitchToMapToolMode();
	void SwitchToPlayMode();

	// �÷��� ��� ����
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

