#include "stdafx.h"
#include "PrototypeScene.h"


PrototypeScene::PrototypeScene()
{
}


PrototypeScene::~PrototypeScene()
{
}

void PrototypeScene::Init()
{
	m_map = new Map;
	m_map->Init();

	m_player = new Player;
	m_player->Init(m_map);

	m_honeyPlatform.Init();
}

void PrototypeScene::Update()
{
	if (g_pKeyManager->IsOnceKeyDown(VK_ESCAPE))
	{
		PostQuitMessage(0); // WM_QUIT �޽��� �߻�
	}
	m_honeyPlatform.Update();
	m_player->Update(m_honeyPlatform.GetAABB());
}

void PrototypeScene::Render()
{
	m_map->Render();
	m_honeyPlatform.Render();
	m_player->Render();
}

void PrototypeScene::Release()
{
	m_player->Release();
	m_map->Release();
}
