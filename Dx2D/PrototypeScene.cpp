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
	m_backgroundImage->SetLBPosition({ 0,0 });
	m_backgroundImage->Update();

	m_player = new Player;

	m_player->Init();

	m_vecObjectList.push_back(new SimplePlatform({ 200.0f, 350.0f}, { 465.0f, 300.0f }));
	m_vecObjectList.push_back(new SimplePlatform({ 447.0f, 380.0f }, { GAMESCREEN_X - 653, 300.0f }));
	m_vecObjectList.push_back(new honeyPlatform({ WINSIZEX*0.5f + 200.0f, WINSIZEY*0.7f + 300 }, true));
	m_vecObjectList.push_back(new honeyPlatform({ WINSIZEX*0.5f + 20.0f, WINSIZEY*0.5f + 200.0f }, false));
	//m_vecObjectList.push_back(new BallShooter({ WINSIZEX*0.5f - 300.0f, WINSIZEY - 700.0f }));

	m_vecObjectList.push_back(new SimplePlatform(SimplePlatform::Platform_Type::SHORT_VERTICAL, { 500.0f, 800.0f }));
	m_vecObjectList.push_back(new SimplePlatform(SimplePlatform::Platform_Type::SHORT_HORIZONTAL, {800.0f, 760.0f }));
	m_vecObjectList.push_back(new SimplePlatform(SimplePlatform::Platform_Type::MID_VERTICAL, {1200.0f, 800.0f }));
	m_vecObjectList.push_back(new SimplePlatform(SimplePlatform::Platform_Type::MID_HORIZONTAL, {1500.0f, 500.0f }));
	m_vecObjectList.push_back(new SimplePlatform(SimplePlatform::Platform_Type::MID_HORIZONTAL, { 1800.0f, 400.0f }));


	for (auto obj : m_vecObjectList) obj->Init();

	g_pCamera->SetMapSize(GAMESCREEN_X, GAMESCREEN_Y);
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
