#include "stdafx.h"
#include "PrototypeScene.h"
#include "SimplePlatform.h"
#include "honeyPlatform.h"
#include "BallShooter.h"

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

	m_player->Init();

	m_vecObjectList.push_back(new SimplePlatform({ WINSIZEY*0.8f, 50.0f}, {WINSIZEX*0.5f, 50.0f}));
	m_vecObjectList.push_back(new SimplePlatform({ 50.0f, 400.0f }, { WINSIZEX*0.5f+300.0f, 700.0f }));
	m_vecObjectList.push_back(new honeyPlatform({ WINSIZEX*0.5f - 300.0f, WINSIZEY - 700.0f }));
	m_vecObjectList.push_back(new BallShooter({ WINSIZEX*0.5f + 400.0f, WINSIZEY*0.5f - 300.0f }));
	//m_vecObjectList.push_back(new honeyPlatform({ WINSIZEX*0.5f + 300.0f, WINSIZEY - 700.0f }));

	for (auto obj : m_vecObjectList) obj->Init();
}

void PrototypeScene::Update()
{
	if (g_pKeyManager->IsOnceKeyDown(VK_ESCAPE))
	{
		PostQuitMessage(0); // WM_QUIT 메시지 발생
	}
	for (auto obj : m_vecObjectList) obj->Update();

	m_player->Update(m_vecObjectList);
}

void PrototypeScene::Render()
{
	for (auto obj : m_vecObjectList) obj->Render();
	m_player->Render();
}

void PrototypeScene::Release()
{
	m_player->Release();
	for (auto obj : m_vecObjectList) obj->Release();
	m_vecObjectList.clear();
}
