#include "stdafx.h"
#include "LoadingScene.h"


void LoadingScene::Init()
{
	m_pProgressBar = new ProgressBar(L"ProgressBack", L"ProgressFront");

	float sizeX = WINSIZEX - 100;

	m_pProgressBar->SetSize(sizeX, 50);
	m_pProgressBar->SetPos(HALFSIZEX - sizeX * 0.5f, HALFSIZEY - 25);
}

void LoadingScene::Update()
{
	g_pLoadManager->Update();
}

void LoadingScene::Render()
{
	if (m_pProgressBar)
	{
		m_pProgressBar->SetProgress(g_pLoadManager->GetNumMax(), g_pLoadManager->GetNumLoaded(), true);
		m_pProgressBar->Update();
		m_pProgressBar->Render();
	}
}

void LoadingScene::Release()
{
	SAFE_DELETE(m_pProgressBar);
}
