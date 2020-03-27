#pragma once
#include "SingletonBase.h"
#include <bitset>

using namespace std;

/*
bitset : bool Ÿ���� ��� �ִ� �ڷᱸ��

set()			: bit ��� 1�� ����
reset()			: bit ��� 0���� ����
set(i, value)	: i��° ���� value�� ����
[]				: �迭 ������ ���� ����
flip()			: bit �� ��ȯ 0 -> 1, 1 -> 0

all()			: ��� ��Ʈ�� 1�� �� Ʈ�� ��ȯ
none()			: ��� ��Ʈ�� 0�� �� Ʈ�� ��ȯ
any()			: 1���� 1�̸� Ʈ�� ��ȯ
count()			: ���� 1�� ���� �� ��Ʈ�� ���� ��ȯ
*/

#define g_pKeyManager KeyManager::GetInstance()
#define KEYMAX 256

class KeyManager : public SingletonBase<KeyManager>
{
private:
	bitset<KEYMAX>	m_bitKeyUp;
	bitset<KEYMAX>	m_bitKeyDown;
	bitset<KEYMAX>	m_bitKeyToggle;
public:
	void Init();
	bool IsOnceKeyDown(int key);	// Ű�� ������ ��
	bool IsOnceKeyUp(int key);		// Ű���� ���� ��
	bool IsStayKeyDown(int key);	// Ű�� ������ ���� ��
	bool IsToggleKey(int key);		// ���Ű �� ����
	bool IsAnyKeyDown();			// �ƹ�Ű�� ������ ��
};

