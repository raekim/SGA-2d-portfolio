#include "stdafx.h"
#include "RenderTextureTest.h"


void RenderTextureTest::Init()
{
	m_pBackground = new Sprite(L"Background");
	m_pBackground->SetSize(2, 2);
	m_pBackground->SetLBPosition(0, 0);
	m_pBackground->Update();

	m_pForeground = new Sprite(L"Foreground");
	m_pForeground->SetSize(2, 2);
	m_pForeground->SetLBPosition(0, 0);
	m_pForeground->Update();

	g_pCamera->SetMapSize(m_pForeground->GetWidth(), m_pForeground->GetHeight());

	m_pCircleBrush = new Circle;
	m_pCircleBrush->SetColor(D3DXCOLOR(0, 0, 0, 0));
	m_fBrushRadius = 10.0f;

	g_pTextureManager->AddRenderTargetTexture(L"Map", m_pForeground->GetWidth(), m_pForeground->GetHeight());
	m_pMap = new Sprite(L"Map");
	m_pMap->SetLBPosition(0, 0);
	m_pMap->Update();

	///////////////////////////////////////////////////////

	g_pTextureManager->ClearRenderTargetTexture(L"Map");
	g_pTextureManager->SetRenderTargetToTexture(L"Map");
	g_pCamera->SetRenderScale(m_pForeground->GetWidth(), m_pForeground->GetHeight());
	m_pForeground->Render();
	g_pCamera->SetRenderScale();
	g_pTextureManager->SetRenderTargetToBackBuffer();
}

void RenderTextureTest::Update()
{
	g_pCamera->Update();

	if (g_pKeyManager->IsOnceKeyDown(VK_ESCAPE))
		g_pLoadManager->ChangeScene(SCENE_KIND::Title);

	if (m_pCircleBrush)
	{
		if (g_pKeyManager->IsStayKeyDown(VK_HOME))
			m_fBrushRadius += 1.0f;
		else if (g_pKeyManager->IsStayKeyDown(VK_END))
			m_fBrushRadius -= 1.0f;

		m_pCircleBrush->SetRadius(m_fBrushRadius);
	}

	if (m_pCircleBrush && g_pKeyManager->IsStayKeyDown(VK_LBUTTON))
	{
		g_pTextureManager->SetRenderTargetToTexture(L"Map");
		m_pCircleBrush->SetPosition(g_ptMouse.x + g_pCamera->GetPosition().x * 2.0f, g_ptMouse.y + g_pCamera->GetPosition().y * 2.0f);
		g_pCamera->SetRenderScale(m_pForeground->GetWidth(), m_pForeground->GetHeight());
		m_pCircleBrush->UpdateNRender();
		g_pCamera->SetRenderScale();
		g_pTextureManager->SetRenderTargetToBackBuffer();
	}
}

void RenderTextureTest::Render()
{
	if (m_pBackground)
		m_pBackground->Render();
	
	if (m_pMap)
		m_pMap->Render();

	auto pos = m_pMap->GetPosition();
	auto siz = m_pMap->GetSize();

	m_pMap->SetSize(0.1f, 0.1f);
	m_pMap->SetPosition(WINSIZEX +  g_pCamera->GetPosition().x - m_pMap->GetWidth()*0.5f, WINSIZEY + g_pCamera->GetPosition().y - m_pMap->GetHeight()*0.5f);
	m_pMap->Update();
	m_pMap->Render();

	m_pMap->SetSize(siz);
	m_pMap->SetPosition(pos);
	m_pMap->Update();
}

void RenderTextureTest::Release()
{
	SAFE_DELETE(m_pBackground);
	SAFE_DELETE(m_pForeground);
	SAFE_DELETE(m_pCircleBrush);
}
