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
	m_backgroundImage = new Sprite(L"City-background", 1, 1, 0);
	m_backgroundImage->Init();
	m_backgroundImage->SetPosition(GAMESCREEN_X*0.5f, GAMESCREEN_Y*0.5f);
	m_backgroundImage->Update();

	m_player = new Player;

	m_player->Init();

	m_vecObjectList.push_back(new SimplePlatform({ 200.0f, 350.0f}, { 465.0f, 300.0f }));
	m_vecObjectList.push_back(new SimplePlatform({ 447.0f, 380.0f }, { GAMESCREEN_X - 653, 300.0f }));
	m_vecObjectList.push_back(new honeyPlatform({ WINSIZEX*0.5f - 200.0f, WINSIZEY*0.5f }, true));
	m_vecObjectList.push_back(new honeyPlatform({ WINSIZEX*0.5f + 20.0f, WINSIZEY*0.5f + 200.0f }, false));
	//m_vecObjectList.push_back(new BallShooter({ WINSIZEX*0.5f - 300.0f, WINSIZEY - 700.0f }));

	for (auto obj : m_vecObjectList) obj->Init();

	g_pCamera->SetTarget(m_player->GetPosition());
}

void PrototypeScene::Update()
{
	if (g_pKeyManager->IsOnceKeyDown(VK_ESCAPE))
	{
		PostQuitMessage(0); // WM_QUIT 메시지 발생
	}
	for (auto obj : m_vecObjectList) obj->Update();

	m_player->Update(m_vecObjectList);

	g_pCamera->Update();
}

void PrototypeScene::Render()
{
	m_backgroundImage->Render();
	for (auto obj : m_vecObjectList) obj->Render();
	m_player->Render();
}

void PrototypeScene::Release()
{
	m_player->Release();
	for (auto obj : m_vecObjectList) obj->Release();
	m_vecObjectList.clear();
}
