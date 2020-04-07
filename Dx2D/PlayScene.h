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

	// �� ����
	Sprite*						m_mapForeground;				// �� ����׶��� �̹���
	Sprite*						m_mapBackground;				// �� ��׶��� �̹���
	Sprite*						m_mapPaper;						// ������忡�� ���̴� ���� ���� �̹���
	vector<SimplePlatform*>		m_mapBlocks;					// �� ����
	PlaceableObject*			m_vecObjectList[28][32];		// ���ڻ� ���� ������Ʈ��

public:
	PlayScene();
	~PlayScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

