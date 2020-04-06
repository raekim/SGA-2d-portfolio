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

	// 애니메이션 state
	enum class ANIM_STATE
	{
		READY = -1,
		IDLE,
		FLIP_STAND,
		WALK,

		// 점프 관련
		JUMP_GOING_UP,
		UP_TO_TOP,
		JUMP_TOP,
		TOP_TO_DOWN,
		JUMP_GOING_DOWN,
		LANDING_SOFT,
		JUMP_TOP_FLIP,

		// 벽 슬라이딩, 벽점프 관련
		TOP_TO_WALLSLIDE,
		TO_WALLSLIDE_OPPOSITE_START,
		WALLSLIDE,
		WALLSLIDE_TO_JUMP_UP,

		// 사망 관련
		DEATH_SHOCK,
		DEAD,
		Max
	};

	map<ANIM_STATE, D3DXVECTOR2> m_mapAnimOffset;	// 각 애니메이션 클립의 오프셋

	Animation<ANIM_STATE>*	m_pAnimation;
	ANIM_STATE				m_animState;
	ANIM_STATE				m_prevAnimState;

	D3DXVECTOR2				m_oldPosition;
	
	D3DXVECTOR3				m_rotation;

	D3DXVECTOR2				m_oldSpeed;

	AABB*					m_AABB;
	D3DXVECTOR2				m_AABBOffset;
	D3DXVECTOR2				m_AABBHalfSize;
	wstring					m_sheetKey;				// 애니메이션 시트 리소스 키값

	// 컨트롤 정보
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

	bool m_hasNoWalls;						// 캐릭터의 4방향 어디에도 벽이 없는 상태
	bool m_facingRight;

	STATE m_curState;
	float m_jumpSpeed;
	float m_walkSpeed;
	float m_maxWalkSpeed;
	float m_fallingSpeedBound;				// 캐릭터가 너무 급격하게 추락하지 않도록 해 주는 추락 속도 상한

	bool m_pressingJumpingButton;			// 현재 점프 버튼을 누르고 있는가? (긴 점프, 짧은 점프에 사용)
	bool m_isWallJumpingTowardLeft;			// 왼쪽으로 튕겨나가는 벽점프 중
	bool m_isWallJumpingTowardRight;		// 오른쪽으로 튕겨나가는 벽점프 중

private:
	// Init 관련 함수
	void InitAnimation();

	// Update 관련 함수
	void UpdateWalkSpeed();
	void UpdateJump();
	void UpdateWalk();
	void UpdateStand();
	void UpdatePhysics(vector<PlaceableObject*> objList);
	void UpdateWallSlideAndJump();
	void CheckFourSides(vector<PlaceableObject*> objList);
	void UpdateAnimation();

	// 상,하,좌,우 오브젝트 충돌
	bool HasGround(PlaceableObject* other, D3DXVECTOR2 oldPosition, D3DXVECTOR2 position);
	bool HasCeiling(PlaceableObject* other, D3DXVECTOR2 oldPosition, D3DXVECTOR2 position);
	bool HasLeftWall(PlaceableObject* other, D3DXVECTOR2 oldPosition, D3DXVECTOR2 position);
	bool HasRightWall(PlaceableObject* other, D3DXVECTOR2 oldPosition, D3DXVECTOR2 position);

	bool IsFlipping();			// 현재 왼쪽을 보고 있는데 오른쪽을 보려고 하는가? (또는 그 반대)
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