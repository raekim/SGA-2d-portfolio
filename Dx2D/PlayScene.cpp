#include "stdafx.h"
#include "PlayScene.h"


PlayScene::PlayScene()
{

}


PlayScene::~PlayScene()
{
}

void PlayScene::Init()
{
	m_curMode = MODE::MAPTOOL_MODE;
}

void PlayScene::Update()
{
	switch (m_curMode)
	{
		case MODE::MAPTOOL_MODE:
			break;
		case MODE::PLAY_MODE:
			break;
	}
}

void PlayScene::Render()
{
	switch (m_curMode)
	{
	case MODE::MAPTOOL_MODE:
		break;
	case MODE::PLAY_MODE:
		break;
	}
}

void PlayScene::Release()
{
}
