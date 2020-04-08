#include "stdafx.h"
#include "KeyManager.h"


void KeyManager::Init()
{
	// ��� ������ false�� �ʱ�ȭ
	m_bitKeyUp.reset();
	m_bitKeyDown.reset();
	m_bitKeyToggle.reset();
}

bool KeyManager::IsOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!m_bitKeyDown[key]) // ������ ������ ���� ����
		{
			m_bitKeyDown.set(key, true);
			return true;		// Ű�� ���� �� ���ȴ�.
		}
	}
	else
	{
		m_bitKeyDown.set(key, false);
	}

	return false;
}

bool KeyManager::IsOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		m_bitKeyUp.set(key, true);
	}
	else
	{
		if (m_bitKeyUp[key]) // ������ Ű�� ������ �ִ� ���� ����.
		{
			m_bitKeyUp.set(key, false);
			return true;
		}
	}

	return false;
}

bool KeyManager::IsStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		return true;

	return false;
}

bool KeyManager::IsToggleKey(int key)
{
	//if (GetAsyncKeyState(key) & 0x0001)
	if (IsOnceKeyDown(key))
	{
		m_bitKeyToggle[key].flip();
	}

	return m_bitKeyToggle[key];
}

bool KeyManager::IsAnyKeyDown()
{
	for (int i = 0; i < KEYMAX; i++)
	{
		if (IsStayKeyDown(i))
			return true;
	}

	return false;
}
