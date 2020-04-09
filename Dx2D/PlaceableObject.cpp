#include "stdafx.h"
#include "PlaceableObject.h"
#include "Player.h"


PlaceableObject::PlaceableObject()
{
}


PlaceableObject::~PlaceableObject()
{
}

//bool PlaceableObject::SimpleRectPlayerCollisionFunc(D3DXVECTOR2 colliderHalfSize, D3DXVECTOR2 colliderCenter, D3DXVECTOR2 pos, Player * player, PlaceableObject::collisionCheckDir dir, bool& colliderEnabled)
//{
//	switch (dir)
//	{
//	case PlaceableObject::collisionCheckDir::BOTTOM:
//		if (player->m_speed.y < 0.0f)
//		{
//			player->m_speed.y = 0.0f;
//			player->SetPositionY(m_AABB->GetAABBTop() + player->GetAABBHalfSize().y);
//		}
//		break;
//	case PlaceableObject::collisionCheckDir::CEILING:
//		if (player->m_speed.y > 0.0f)
//		{
//			player->m_speed.y = 0.0f;
//			player->SetPositionY(m_AABB->GetAABBBottom() - player->GetAABBHalfSize().y);
//		}
//		break;
//	case PlaceableObject::collisionCheckDir::LEFT_WALL:
//		if (player->m_speed.x < 0.0f)
//		{
//			player->m_speed.x = 0.0f;
//			player->SetPositionX(m_AABB->GetAABBRight() + player->GetAABBHalfSize().x);
//		}
//		break;
//	case PlaceableObject::collisionCheckDir::RIGHT_WALL:
//		if (player->m_speed.x > 0.0f)
//		{
//			player->m_speed.x = 0.0f;
//			player->SetPositionX(m_AABB->GetAABBLeft() - player->GetAABBHalfSize().x);
//		}
//		break;
//	}
//	return true;
//}