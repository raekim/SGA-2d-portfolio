#include "stdafx.h"
#include "SceneManager.h"
#include "iGameNode.h"


void SceneManager::Init()
{
	m_pCurrScene = NULL;
}

void SceneManager::Update()
{
	if (m_pCurrScene)
		m_pCurrScene->Update();
}

void SceneManager::Render()
{
	if (m_pCurrScene)
		m_pCurrScene->Render();
}

void SceneManager::ReleaseAll()
{
	iSceneList iter = m_mapSceneList.begin();
	for (; iter != m_mapSceneList.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->Release();
			SAFE_DELETE(iter->second);
		}
		iter = m_mapSceneList.erase(iter);
	}
	m_mapSceneList.clear();
}

void SceneManager::AddScene(SCENE_KIND sceneName, iGameNode* scene)
{
	if (scene == NULL) return;

	m_mapSceneList.insert(make_pair(sceneName, scene));
}

void SceneManager::Change(SCENE_KIND sceneName)
{
	iSceneList find = m_mapSceneList.find(sceneName);

	if (find == m_mapSceneList.end())
		assert(false && "찾는 씬이 없음");

	if (find->second == m_pCurrScene)
		assert(false && "찾는 씬이 현재 씬");

	// 현재 씬에서 사용중인 리소스 해제
	if (m_pCurrScene != NULL)
		m_pCurrScene->Release();

	// 씬 변경
	g_pCamera->Init();
	m_pCurrScene = find->second;
	m_pCurrScene->Init();
	g_pCamera->Update();
}
