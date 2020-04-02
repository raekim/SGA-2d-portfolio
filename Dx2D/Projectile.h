#pragma once
class AABB;
class Projectile
{
	bool m_isDestroyed;
public:
	Projectile();
	~Projectile();

	void SetDestroyed(bool val) { m_isDestroyed = val; }
	bool IsDestroyed() { return m_isDestroyed; }
	virtual void Destory() PURE;					// 캐릭터 또는 오브젝트와 충돌
	virtual bool Collide(void* other) PURE;			// 다른 오브젝트와의 충돌 감지
};

