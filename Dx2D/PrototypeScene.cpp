#include "stdafx.h"
#include "PrototypeScene.h"
#include "SimplePlatform.h"
#include "honeyPlatform.h"
#include "BallShooter.h"
#include "SpringPlatform.h"
#include "SpinWheel.h"

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
	m_player2P = new Player;

	m_player->Init(L"Chicken-Sheet");
	m_player->SetJumpKey(VK_RCONTROL);
	m_player->SetLeftMoveKey(VK_LEFT);
	m_player->SetRightMoveKey(VK_RIGHT);

	m_player2P->Init(L"Chicken-Sheet-2P");
	m_player2P->SetJumpKey('Z');
	m_player2P->SetLeftMoveKey('F');
	m_player2P->SetRightMoveKey('H');

	m_vecObjectList.push_back(new SimplePlatform({ 200.0f, 350.0f}, { 465.0f, 300.0f }));
	m_vecObjectList.push_back(new SimplePlatform({ 447.0f, 380.0f }, { GAMESCREEN_X - 653, 300.0f }));
	m_vecObjectList.push_back(new honeyPlatform({ WINSIZEX*0.5f + 300.0f, WINSIZEY*0.5f - 200}, true));
	m_vecObjectList.push_back(new honeyPlatform({ WINSIZEX*0.5f + 800.0f, WINSIZEY*0.5f + 200.0f }, false));
	
	m_vecObjectList.push_back(new SimplePlatform(SimplePlatform::Platform_Type::SHORT_VERTICAL, { 500.0f, 800.0f }));
	m_vecObjectList.push_back(new SimplePlatform(SimplePlatform::Platform_Type::SHORT_HORIZONTAL, {800.0f, 760.0f }));
	m_vecObjectList.push_back(new SimplePlatform(SimplePlatform::Platform_Type::MID_VERTICAL, {1200.0f, 800.0f }));
	m_vecObjectList.push_back(new SimplePlatform(SimplePlatform::Platform_Type::MID_HORIZONTAL, {1500.0f, 500.0f }));
	m_vecObjectList.push_back(new SimplePlatform(SimplePlatform::Platform_Type::MID_HORIZONTAL, { 1800.0f, 400.0f }));

	//m_vecObjectList.push_back(new BallShooter({ WINSIZEX*0.5f, WINSIZEY - 200.0f }, false));
	//m_vecObjectList.push_back(new BallShooter({ WINSIZEX*0.5f + 400, WINSIZEY - 300.0f }, true));

	m_vecObjectList.push_back(new SpringPlatform({ 1700, 200 }));
	m_vecObjectList.push_back(new SpringPlatform({ 1100, 200 }));
	m_vecObjectList.push_back(new SpringPlatform({ 800, 300 }));

	m_vecObjectList.push_back(new SpinWheel({ 1800, 600 }));
	m_vecObjectList.push_back(new SpinWheel({ 2000, 900 }));


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
	m_player2P->Update(m_vecObjectList);

	g_pCamera->Update();
}

void PrototypeScene::Render()
{
	m_backgroundImage->Render();
	for (auto obj : m_vecObjectList) obj->Render();
	m_player->Render();
	m_player2P->Render();
}

void PrototypeScene::Release()
{
	SAFE_DELETE(m_player);
	SAFE_DELETE(m_player2P);
	for (auto obj : m_vecObjectList) obj->Release();
	m_vecObjectList.clear();
}
