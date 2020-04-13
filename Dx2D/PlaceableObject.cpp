#include "stdafx.h"
#include "PlaceableObject.h"
#include "Player.h"


PlaceableObject::PlaceableObject()
{
}


PlaceableObject::~PlaceableObject()
{
}

void PlaceableObject::RegisterObjectCollider(Collider* collider, vector<vector<PlaceableObject*>>& objList)
{
	// ��ü ���� ȭ���� ���� ���� �� �ش��ϴ� ���鿡 �� ������Ʈ �����͸� ����
	POINT points[2];
	points[0] = FromPosToGameScreenIndex(collider->GetLeftTopPoint());
	points[1] = FromPosToGameScreenIndex(collider->GetRightBottomPoint());

	int startY = points[0].y, EndY = points[1].y;
	int startX = points[0].x, EndX = points[1].x;

	for (int y = startY; y >= EndY; --y)
	{
		for (int x = startX; x <= EndX; ++x)
		{
			objList[y*GAMESCREEN_X_RATIO + x].push_back(this);
		}
	}
}
