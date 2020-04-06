#pragma once
#include "AABB.h"
class Map;
class PlaceableObject;
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

		// ��� ����
		DEATH_SHOCK,
		DEAD,
		Max
	};

	map<ANIM_STATE, D3DXVECTOR2> m_mapAnimOffset;	// �� �ִϸ��̼� Ŭ���� ������

	Animation<ANIM_STATE>*	m_pAnimation;
	ANIM_STATE				m_animState;
	ANIM_STATE				m_prevAnimState;

	D3DXVECTOR2				m_oldPosition;
	
	D3DXVECTOR3				m_rotation;

	D3DXVECTOR2				m_oldSpeed;

	AABB*					m_AABB;
	D3DXVECTOR2				m_AABBOffset;
	D3DXVECTOR2				m_AABBHalfSize;
	wstring					m_sheetKey;				// �ִϸ��̼� ��Ʈ ���ҽ� Ű��

	// ��Ʈ�� ����
	int m_jumpKey, m_leftMoveKey, m_rightMoveKey;

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

private:
	// Init ���� �Լ�
	void InitAnimation();

	// Update ���� �Լ�
	void UpdateWalkSpeed();
	void UpdateJump();
	void UpdateWalk();
	void UpdateStand();
	void UpdatePhysics(vector<PlaceableObject*> objList);
	void UpdateWallSlideAndJump();
	void CheckFourSides(vector<PlaceableObject*> objList);
	void UpdateAnimation();

	// ��,��,��,�� ������Ʈ �浹
	bool HasGround(PlaceableObject* other, D3DXVECTOR2 oldPosition, D3DXVECTOR2 position);
	bool HasCeiling(PlaceableObject* other, D3DXVECTOR2 oldPosition, D3DXVECTOR2 position);
	bool HasLeftWall(PlaceableObject* other, D3DXVECTOR2 oldPosition, D3DXVECTOR2 position);
	bool HasRightWall(PlaceableObject* other, D3DXVECTOR2 oldPosition, D3DXVECTOR2 position);

	bool IsFlipping();			// ���� ������ ���� �ִµ� �������� ������ �ϴ°�? (�Ǵ� �� �ݴ�)
	void GetNextAnimationState();

	bool m_isDead;
public:
		D3DXVECTOR2				m_speed;
		D3DXVECTOR2				m_extSpeed;
		D3DXVECTOR2				m_position;
public:
	Player();
	~Player();

	void Init(wstring sheetKey);
	void Update(vector<PlaceableObject*> obj);
	void Render();
	void Release();

	D3DXVECTOR2 GetAABBHalfSize() { return m_AABB->GetHalfSize(); }
	void SetPosition(D3DXVECTOR2 pos) { m_position = pos; }
	void SetPositionY(float val) { m_position.y = val; }
	void SetPositionX(float val) { m_position.x = val; }
	void Die();
	void Revive();
	D3DXVECTOR2* GetPosition() { return &m_position; }
	void Jump();
	bool IsDead() { return m_isDead; }

	void SetJumpKey(int key) { m_jumpKey = key; }
	void SetLeftMoveKey(int key) { m_leftMoveKey = key; }
	void SetRightMoveKey(int key) { m_rightMoveKey = key; }
};