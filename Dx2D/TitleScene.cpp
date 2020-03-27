#include "stdafx.h"
#include "TitleScene.h"


void TitleScene::Init()
{
	m_pBackground = new Sprite(L"TitleBack");

	m_strTitle = "Any Key To Continue";
	m_fElapsedTime = 0.0f;
	m_isRender = true;
}

void TitleScene::Update()
{
	if (g_pKeyManager->IsOnceKeyDown(VK_ESCAPE))
		PostQuitMessage(0);
	else if (g_pKeyManager->IsOnceKeyDown('1'))
		g_pLoadManager->ChangeScene(SCENE_KIND::Play);
	else if (g_pKeyManager->IsOnceKeyDown('2'))
		g_pLoadManager->ChangeScene(SCENE_KIND::MapTool);
	else if (g_pKeyManager->IsOnceKeyDown('3'))
		g_pLoadManager->ChangeScene(SCENE_KIND::SortTest);
	else if (g_pKeyManager->IsOnceKeyDown('4'))
		g_pLoadManager->ChangeScene(SCENE_KIND::RenderTextureTest);

	m_fElapsedTime += g_pTimeManager->GetDeltaTime();

	if (m_fElapsedTime >= 0.5f)
	{
		m_fElapsedTime = 0.0f;
		m_isRender = !m_isRender;
	}
}

void TitleScene::Render()
{
	if (m_pBackground)
		m_pBackground->Render();

	if (m_isRender)
		g_pTextManager->AlphabetRender(m_strTitle.c_str(), HALFSIZEX - 280, HALFSIZEY, 50);
}

void TitleScene::Release()
{
	g_pTextureManager->Release(L"TitleBack");
}
