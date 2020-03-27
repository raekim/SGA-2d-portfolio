#pragma once
#include "Unit.h"

class Player;

enum class ENEMY_STATE
{
	READY = -1,
	Flying,
	MAX
};

class Enemy : public Unit<ENEMY_STATE>
{
private:
	Player*		m_pPlayer;

public:
	Enemy();
	~Enemy();

	void Init() override;
	void Update() override;
	void Render() override;

	void SetPlayer(Player* p) { m_pPlayer = p; }
};

