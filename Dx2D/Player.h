#pragma once
#include "AABB.h"
class Map;
class Player
{
	Map*		m_map;
	enum class STATE
	{
		Stand,
		Walk,
		Jump,
		Max
	};

	// �ִϸ��̼� state
	enum class ANIM_STATE
	{
		READY = -1,
		IDLE,
		FLIP_STAND,
		WALK,
		Max
	};

	map<ANIM_STATE, D3DXVECTOR2> m_mapAnimOffset;	// �� �ִϸ��̼� Ŭ���� ������

	Animation<ANIM_STATE>*	m_pAnimation;
	ANIM_STATE				m_flipAnimState;
	ANIM_STATE				m_animState;

	D3DXVECTOR2				m_oldPosition;
	D3DXVECTOR2				m_position;
	D3DXVECTOR3				m_rotation;

	D3DXVECTOR2				m_oldSpeed;
	D3DXVECTOR2				m_speed;

	D3DXVECTOR2				m_scale;

	AABB*					m_AABB;
	D3DXVECTOR2				m_AABBOffset;

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

	bool m_hasNoWalls;						// ĳ������ 4���� ��𿡵� ���� ���� ����
	bool m_facingRight;
	bool m_isFlipping;

	STATE m_curState;
	float m_jumpSpeed;
	float m_walkSpeed;
	float m_maxWalkSpeed;
	float m_fallingSpeedBound;				// ĳ���Ͱ� �ʹ� �ް��ϰ� �߶����� �ʵ��� �� �ִ� �߶� �ӵ� ����

	bool m_pressingJumpingButton;			// ���� ���� ��ư�� ������ �ִ°�? (�� ����, ª�� ������ ���)
	bool m_isWallJumpingTowardLeft;			// �������� ƨ�ܳ����� ������ ��
	bool m_isWallJumpingTowardRight;		// ���������� ƨ�ܳ����� ������ ��

private:
	// Update ���� �Լ�
	void UpdateWalkSpeed();
	void UpdateJump();
	void UpdateWalk();
	void UpdateStand();
	void UpdatePhysics();
	void UpdateAnimation();
	void UpdateAnimationFlip();				// ĳ���� �ִϸ��̼� ��/�찡 �ڹٲ� �� flip �ִϸ��̼��� ������ ���

	// ��,��,��,�� Ÿ�ϸ� ���� �浹
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

