#include "stdafx.h"
#include "LoadManager.h"


void LoadManager::Init()
{
	g_pTextureManager->AddTexture(L"ProgressBack", L"UIImages/progressBarBack.png");
	g_pTextureManager->AddTexture(L"ProgressFront", L"UIImages/progressBarFront.png");
}

void LoadManager::Update()
{
	if (m_vecResourceList.size() == m_nNumLoaded) // 로딩 완료
	{
		g_pSceneManager->Change(m_eNextScene);
		return;
	}

	switch (m_vecResourceList[m_nNumLoaded]->eType)
	{
		case RESOURCE_TYPE::Image:
		{
			tagTextureInfo* info = (tagTextureInfo*)m_vecResourceList[m_nNumLoaded];
			g_pTextureManager->AddTexture(info->sKey, info->sFile);
		}
		break;
		case RESOURCE_TYPE::Sound:
		{
			tagSoundInfo* info = (tagSoundInfo*)m_vecResourceList[m_nNumLoaded];
			g_pSoundManager->AddSound(info->sKey, info->sFile, info->isBgm, info->isLoop);
		}
		break;
	}

	m_nNumLoaded++;
}

void LoadManager::ReleaseAll()
{
	ReleasePrevResources();
}

void LoadManager::ChangeScene(SCENE_KIND eNext)
{
	g_pSceneManager->Change(SCENE_KIND::Loading);

	m_eNextScene = eNext;
	ReleasePrevResources();
	MakeAResourcesList();
}

void LoadManager::ReleasePrevResources()
{
	for (int i = 0; i < m_vecResourceList.size(); i++)
	{
		switch (m_vecResourceList[i]->eType)
		{
			case RESOURCE_TYPE::Image:
			{
				tagTextureInfo* info = (tagTextureInfo*)m_vecResourceList[i];
				g_pTextureManager->Release(info->sKey);
				SAFE_DELETE(info);
			}
			break;
			case RESOURCE_TYPE::Sound:
			{
				tagSoundInfo* info = (tagSoundInfo*)m_vecResourceList[i];
				g_pSoundManager->ReleaseSound(info->sKey);
				SAFE_DELETE(info);
			}
			break;
		}
	}
	m_vecResourceList.clear();
}

void LoadManager::MakeAResourcesList()
{
	m_nNumLoaded = 0;

	switch (m_eNextScene)
	{
		case SCENE_KIND::Prototype:
			m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Chicken-Sheet", L"kim-rae-hyang-images/chicken-sheet.png"));
			m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Chicken-Sheet-2P", L"kim-rae-hyang-images/chicken-sheet-2P.png"));
			m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"City-background", L"kim-rae-hyang-images/city-background.png"));
			m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Object-Sheet-1", L"kim-rae-hyang-images/objects1-sheet.png"));
			for (int i = 0; i < 6; ++i)
				m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"springBoard-" + to_wstring(i), L"kim-rae-hyang-images/SpringBoard.00" + to_wstring(i) + L".png"));
			break;
		case SCENE_KIND::PlayScene:
			m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Chicken-Sheet", L"kim-rae-hyang-images/chicken-sheet.png"));
			m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Chicken-Sheet-2P", L"kim-rae-hyang-images/chicken-sheet-2P.png"));
			m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"City-Foreground", L"kim-rae-hyang-images/city-background-buildings.png"));
			m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"City-Background", L"kim-rae-hyang-images/city-background-sky.png"));
			m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"City-Paper", L"kim-rae-hyang-images/city-background-paper.png"));
			m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Object-Sheet-1", L"kim-rae-hyang-images/objects1-sheet.png"));
			for (int i = 0; i < 6; ++i)
				m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"springBoard-" + to_wstring(i), L"kim-rae-hyang-images/SpringBoard.00" + to_wstring(i) + L".png"));
			m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Flag-Sheet", L"kim-rae-hyang-images/flag-flutter-sheet.png"));
			m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Flag-Pole", L"kim-rae-hyang-images/Flag-FlagPole.000.png"));
			break;
	//case SCENE_KIND::Title:
	//	m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"TitleBack", L"ChloeBennet.bmp"));
	//	break;
	//case SCENE_KIND::Play:
	//	m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Background", L"BackGround.png"));
	//	m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Black", L"Black1280x720.png"));
	//	break;
	//
	//case SCENE_KIND::RenderTextureTest:
	//	m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Background", L"BackGround00.png"));
	//	m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Foreground", L"BackGround02.png"));
	//	break;
	}
}