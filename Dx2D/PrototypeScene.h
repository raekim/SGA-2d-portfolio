#pragma once
#include "Player.h"
#include "Map.h"

class PrototypeScene : public iGameNode
{
	Map*				m_map;
	Player*				m_player;
	vector<Rect*>		m_vecRect;
public:
	PrototypeScene();
	~PrototypeScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

