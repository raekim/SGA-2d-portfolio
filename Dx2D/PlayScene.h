#pragma once

#include "Player.h"
#include "PlaceableObject.h"
#include "PlayerCursor.h"


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

	// �� ����
	Sprite*						m_mapForeground;				// �� ����׶��� �̹���
	Sprite*						m_mapBackground;				// �� ��׶��� �̹���
	Sprite*						m_mapPaper;						// ������忡�� ���̴� ���� ���� �̹���
	vector<PlaceableObject*>	m_mapBlocks;					// �� ����
	PlaceableObject*			m_vecObjectList[28][32];		// ���ڻ� ���� ������Ʈ��


	vector<PlaceableObject*>	m_placedObjects;				// �� ����

private:
	void SwitchToMapToolMode();
	void SwitchToPlayMode();

public:
	PlayScene();
	~PlayScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

