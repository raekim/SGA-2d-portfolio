#pragma once
#include "Player.h"
#include "Map.h"
#include "PlaceableObject.h"

class PrototypeScene : public iGameNode
{
	Map*						m_map;
	Player*						m_player;
	vector<Rect*>				m_vecRect;

	Sprite*						m_backgroundImage;

	vector<PlaceableObject*>	m_vecObjectList;
public:
	PrototypeScene();
	~PrototypeScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

