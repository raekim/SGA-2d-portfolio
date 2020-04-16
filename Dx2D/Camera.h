#pragma once
#include "SingletonBase.h"

#define g_pCamera Camera::GetInstance()

class Camera : public SingletonBase<Camera>
{
#define MOVESPEED 100//500

private:
	ID3D11Buffer*		m_pViewProjBuffer;	// ��, �������� ��Ʈ���� ����
	ViewProjectionDesc	m_stViewProjMatrix;
	D3D11_VIEWPORT		m_stViewport;		// �� ��Ʈ ����ü

	D3DXVECTOR2*		m_pTarget;

	D3DXVECTOR2			m_vPosition;
	D3DXVECTOR2			m_vFocus;
	D3DXVECTOR2			m_vMapSize;

	D3DXVECTOR3			m_vEye;
	D3DXVECTOR3			m_vLookAt;
	D3DXVECTOR3			m_vUp;

	D3DXVECTOR2			m_positionRangeX;	// ī�޶� x ��ġ �ּ�, �ִ� ����
	D3DXVECTOR2			m_positionRangeY;	// ī�޶� y ��ġ �ּ�, �ִ� ����

	float				m_eyeVal;
public:
	Camera();
	~Camera();

	void Init();
	void Update();

	void SetTarget(D3DXVECTOR2* p) { m_pTarget = p; }
	void SetFocus(D3DXVECTOR2 v) { m_vFocus = v; }
	void SetFocus(float x, float y) { SetFocus(D3DXVECTOR2(x, y)); }
	void SetMapSize(float x, float y) { m_vMapSize.x = x; m_vMapSize.y = y; 
	m_positionRangeX = { 0, m_vMapSize.x - WINSIZEX }; m_positionRangeY = { 0, m_vMapSize.y - WINSIZEY };}

	ID3D11Buffer *const *GetViewProjBuffer() { return &m_pViewProjBuffer; }
	D3DXVECTOR2& GetPosition() { return m_vPosition; }
	D3DXVECTOR2 GetMapSize() { return m_vMapSize; }

	void SetRenderScale(float widht = WINSIZEX, float height = WINSIZEY);
	void SetEyeVal(float val) { m_eyeVal = val; }
	float GetEyeVal() { return m_eyeVal; }
	void SetPosition(D3DXVECTOR2 pos) { m_vPosition = pos; }
	void SetPositionRange(D3DXVECTOR2 xRange, D3DXVECTOR2 yRange) { m_positionRangeX = xRange; m_positionRangeY = yRange;}
};