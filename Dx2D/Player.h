#pragma once
#include "AABB.h"
#include "MovingObject.h"
class Map;
class Player : public MovingObject
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

		// ���� ����
		JUMP_GOING_UP,
		UP_TO_TOP,
		JUMP_TOP,
		TOP_TO_DOWN,
		JUMP_GOING_DOWN,
		LANDING_SOFT,
		JUMP_TOP_FLIP,

		// �� �����̵�, ������ ����
		TOP_TO_WALLSLIDE,
		TO_WALLSLIDE_OPPOSITE_START,
		WALLSLIDE,
		WALLSLIDE_TO_JUMP_UP,
		Max
	};

	map<ANIM_STATE, D3DXVECTOR2> m_mapAnimOffset;	// �� �ִϸ��̼� Ŭ���� ������

	Animation<ANIM_STATE>*	m_pAnimation;
	ANIM_STATE				m_animState;
	ANIM_STATE				m_prevAnimState;

	D3DXVECTOR2				m_oldPosition;
	D3DXVECTOR2				m_position;
	D3DXVECTOR3				m_rotation;
	D3DXVECTOR2				m_movingPlatformOffset;	// �����̴� �÷����� Ÿ�� �ִ� ��� ĳ���Ϳ� �����ؾ� �� offset

	D3DXVECTOR2				m_oldSpeed;
	D3DXVECTOR2				m_speed;

	AABB*					m_AABB;
	D3DXVECTOR2				m_AABBOffset;

	// Position States
	bool m_pushedRightWall;
	bool m_pushesRightWall;
	bool m_slidRightWall;
	bool m_slidesRightWall;

	bool m_pushedLeftWall;
	bool m_pushesLeftWall;
	bool m_slidLeftWall;
	bool m_slidesLeftWall;

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

	STATE m_curState;
	float m_jumpSpeed;
	float m_walkSpeed;
	float m_maxWalkSpeed;
	float m_fallingSpeedBound;				// ĳ���Ͱ� �ʹ� �ް��ϰ� �߶����� �ʵ��� �� �ִ� �߶� �ӵ� ����

	bool m_pressingJumpingButton;			// ���� ���� ��ư�� ������ �ִ°�? (�� ����, ª�� ������ ���)
	bool m_isWallJumpingTowardLeft;			// �������� ƨ�ܳ����� ������ ��
	bool m_isWallJumpingTowardRight;		// ���������� ƨ�ܳ����� ������ ��
	bool m_isRidingMovingPlatform;

private:
	// Init ���� �Լ�
	void InitAnimation();

	// Update ���� �Լ�
	void UpdateWalkSpeed();
	void UpdateJump();
	void UpdateWalk();
	void UpdateStand();
	void UpdatePhysics(AABB* obj);
	void UpdateAnimation();

	// ��,��,��,�� Ÿ�ϸ� ���� �浹
	bool HasGround(D3DXVECTOR2 oldPosition, D3DXVECTOR2 position, D3DXVECTOR2 speed, float& groundY);
	bool HasCeiling(D3DXVECTOR2 oldPosition, D3DXVECTOR2 position, float& ceilingY);
	bool HasLeftWall(D3DXVECTOR2 oldPosition, D3DXVECTOR2 position, float& WallX);
	bool HasRightWall(D3DXVECTOR2 oldPosition, D3DXVECTOR2 position, float& WallX);

	// ��,��,��,�� AABB �浹
	bool HasGround(AABB* other, D3DXVECTOR2 oldPosition, D3DXVECTOR2 position, float& groundY);
	bool HasCeiling(AABB* other, D3DXVECTOR2 oldPosition, D3DXVECTOR2 position, float& ceilingY);
	bool HasLeftWall(AABB* other, D3DXVECTOR2 oldPosition, D3DXVECTOR2 position, float& WallX);
	bool HasRightWall(AABB* other, D3DXVECTOR2 oldPosition, D3DXVECTOR2 position, float& WallX);

	bool IsFlipping();		// ���� ������ ���� �ִµ� �������� ������ �ϴ°�? (�Ǵ� �� �ݴ�)
	void GetNextAnimationState();
public:
	Player();
	~Player();

	void Init(Map* map);
	void Update(AABB* obj);
	void Render();
	void Release();
};

