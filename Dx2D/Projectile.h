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
	virtual void Destory() PURE;					// ĳ���� �Ǵ� ������Ʈ�� �浹
	virtual bool Collide(void* other) PURE;			// �ٸ� ������Ʈ���� �浹 ����
};

