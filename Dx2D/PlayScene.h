#pragma once

#include "Player.h"
#include "PlaceableObject.h"
#include "PlayerCursor.h"
#include "GoalFlag.h"

class PlayScene : public iGameNode
{
	enum class MODE
	{
		MAPTOOL_MODE,
		PLAY_MODE
	};
	MODE						m_curMode;
	Player*						m_player1P;
	Player*						m_player2P;
	PlayerCursor*				m_cursor1P;
	PlayerCursor*				m_cursor2P;
	float						m_mapToolModeTransitionDelay;	// 플레이 모드에서 맵툴 모드로 갈 때 걸리는 시간
	float						m_transitionCount;				// 시간 측정용 카운터

	// 맵 관련
	Sprite*						m_mapForeground;				// 맵 포어그라운드 이미지
	Sprite*						m_mapBackground;				// 맵 백그라운드 이미지
	Sprite*						m_mapPaper;						// 맵툴모드에서 쓰이는 격자 종이 이미지
	vector<PlaceableObject*>	m_mapBlocks;					// 맵 지형
	PlaceableObject*			m_vecObjectList[28][32];		// 격자상에 놓인 오브젝트들		[width][height]

	vector<PlaceableObject*>	m_placedObjects;				// 맵 상에 놓여진 오브젝트들
	GoalFlag*					m_goalFlag;						// 골인 지점 깃발

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

