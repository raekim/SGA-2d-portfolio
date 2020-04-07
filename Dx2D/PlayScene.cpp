#include "stdafx.h"
#include "PlayScene.h"
#include "SimplePlatform.h"
#include "Player.h"

PlayScene::PlayScene()
{
}


PlayScene::~PlayScene()
{
}

void PlayScene::Init()
{
	// 배경 이미지 불러오기
	m_mapForeground = new Sprite(L"City-Foreground", 1, 1, 0);
	m_mapBackground = new Sprite(L"City-Background", 1, 1, 0);
	m_mapPaper = new Sprite(L"City-Paper", 1, 1, 0);

	m_mapForeground->SetPosition(GAMESCREEN_X*0.5f, GAMESCREEN_Y*0.5f);
	m_mapBackground->SetPosition(GAMESCREEN_X*0.5f, GAMESCREEN_Y*0.5f);
	m_mapPaper->SetPosition(GAMESCREEN_X*0.5f, GAMESCREEN_Y*0.5f);
	m_mapForeground->Update();
	m_mapBackground->Update();
	m_mapPaper->Update();

	m_curMode = MODE::MAPTOOL_MODE;
	g_pCamera->SetEyeVal(-1.666f);

	// 맵 지형 설정
	m_mapBlocks.push_back(new SimplePlatform({ 200.0f, 350.0f }, { 465.0f, 300.0f }));
	m_mapBlocks.push_back(new SimplePlatform({ 447.0f, 380.0f }, { GAMESCREEN_X - 653, 300.0f }));

	g_pCamera->SetMapSize(GAMESCREEN_X, GAMESCREEN_Y);

	// 플레이어 생성
	m_player1P = new Player;
	m_player1P->Init(L"Chicken-Sheet");
	m_player1P->SetJumpKey(VK_RCONTROL);
	m_player1P->SetLeftMoveKey(VK_LEFT);
	m_player1P->SetRightMoveKey(VK_RIGHT);
	m_player2P = new Player;
	m_player2P->Init(L"Chicken-Sheet-2P");
	m_player2P->SetJumpKey('Z');
	m_player2P->SetLeftMoveKey('F');
	m_player2P->SetRightMoveKey('H');
}

void PlayScene::Update()
{
	// ESC 누르면 프로그램 종료
	if (g_pKeyManager->IsOnceKeyDown(VK_ESCAPE))
	{
		PostQuitMessage(0); // WM_QUIT 메시지 발생
	}

	switch (m_curMode)
	{
		case MODE::MAPTOOL_MODE:
			if (g_pKeyManager->IsOnceKeyDown('M'))
			{
				// 플레이 모드로 넘어간다
				m_curMode = MODE::PLAY_MODE;
				g_pCamera->SetEyeVal(-1.0f);
				g_pCamera->SetTarget(m_player1P->GetPosition());
				
				m_player1P->Revive({ 600.0f, 800.0f });
				m_player2P->Revive({ 650.0f, 800.0f });
				break;
			}
			break;
		case MODE::PLAY_MODE:
			if (g_pKeyManager->IsOnceKeyDown('M'))
			{
				// 맵툴 모드로 넘어간다
				m_curMode = MODE::MAPTOOL_MODE;
				g_pCamera->SetEyeVal(-1.666f);
				g_pCamera->SetTarget(NULL);
				g_pCamera->SetPosition({ 0,0 });
				break;
			}

			for (auto obj : m_mapBlocks) obj->Update();
			m_player1P->Update(m_mapBlocks);
			m_player2P->Update(m_mapBlocks);
			break;
	}

	g_pCamera->Update();
}

void PlayScene::Render()
{
	switch (m_curMode)
	{
	case MODE::MAPTOOL_MODE:
		m_mapBackground->Render();
		m_mapPaper->Render();
		m_mapForeground->Render();
		break;
	case MODE::PLAY_MODE:
		m_mapBackground->Render();
		m_mapForeground->Render();

		m_player1P->Render();
		m_player2P->Render();
		break;
	}
}

void PlayScene::Release()
{
	SAFE_DELETE(m_mapBackground);
	SAFE_DELETE(m_mapPaper);
	SAFE_DELETE(m_mapForeground);

	SAFE_DELETE(m_player1P);
}
