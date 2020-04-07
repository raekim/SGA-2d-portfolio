#pragma once

class Player;
class PlaceableObject;
class SimplePlatform;
class PlayScene : public iGameNode
{
	enum class MODE
	{
		MAPTOOL_MODE,
		PLAY_MODE
	};
	MODE						m_curMode;
	Player*						m_player;
	Player*						m_player2P;

	// 맵 관련
	Sprite*						m_mapForeground;				// 맵 포어그라운드 이미지
	Sprite*						m_mapBackground;				// 맵 백그라운드 이미지
	Sprite*						m_mapPaper;						// 맵툴모드에서 쓰이는 격자 종이 이미지
	vector<SimplePlatform*>		m_mapBlocks;					// 맵 지형
	PlaceableObject*			m_vecObjectList[28][32];		// 격자상에 놓인 오브젝트들

public:
	PlayScene();
	~PlayScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

