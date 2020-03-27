#pragma once
#include "AABB.h"
class Map;
class Player
{
	Map*		m_map;
	enum class STATE
	{
		Ready = 1,
		Stand,
		Walk,
		Jump,
		GrabLedge,
		Max
	};

	D3DXVECTOR2 m_oldPosition;
	D3DXVECTOR2 m_position;

	D3DXVECTOR2 m_oldSpeed;
	D3DXVECTOR2 m_speed;

	D3DXVECTOR2 m_scale;

	AABB* m_AABB;
	D3DXVECTOR2 m_AABBOffset;

	// Position States
	bool m_pushedRightWall;
	bool m_pushesRightWall;

	bool m_pushedLeftWall;
	bool m_pushesLeftWall;

	bool m_wasOnGround;
	bool m_onGround;

	bool m_wasAtCeiling;
	bool m_atCeiling;

	bool m_wasWallSliding;
	bool m_isWallSliding;

	bool m_isWalkingLeft;
	bool m_isWalkingRight;

	bool m_hasNoWalls;						// 캐릭터의 4방향 어디에도 벽이 없는 상태

	STATE m_curState;
	float m_jumpSpeed;
	float m_walkSpeed;
	float m_maxWalkSpeed;
	float m_fallingSpeedBound;				// 캐릭터가 너무 급격하게 추락하지 않도록 해 주는 추락 속도 상한

	bool m_pressingJumpingButton;			// 현재 점프 버튼을 누르고 있는가? (긴 점프, 짧은 점프에 사용)
	bool m_isWallJumpingTowardLeft;			// 왼쪽으로 튕겨나가는 벽점프 중
	bool m_isWallJumpingTowardRight;		// 오른쪽으로 튕겨나가는 벽점프 중

private:
	void UpdatePhysics();
	// 상,하,좌,우 타일맵 벽과 충돌
	bool HasGround(D3DXVECTOR2 oldPosition, D3DXVECTOR2 position, D3DXVECTOR2 speed, float& groundY);
	bool HasCeiling(D3DXVECTOR2 oldPosition, D3DXVECTOR2 position, float& ceilingY);
	bool HasLeftWall(D3DXVECTOR2 oldPosition, D3DXVECTOR2 position, float& WallX);
	bool HasRightWall(D3DXVECTOR2 oldPosition, D3DXVECTOR2 position, float& WallX);
public:
	Player();
	~Player();

	void Init(Map* map);
	void Update();
	void Render();
	void Release();
};

