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
	// 전체 게임 화면을 나눈 영역 중 해당하는 곳들에 이 오브젝트 포인터를 저장
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
