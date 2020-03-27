#pragma once
#include "SingletonBase.h"

#define g_pSceneManager SceneManager::GetInstance()

class iGameNode;

enum class SCENE_KIND
{
	Loading,
	Title,
	Play,
	MapTool,
	SortTest,
	RenderTextureTest,
	Prototype,
	End
};

class SceneManager : public SingletonBase<SceneManager>
{
private:
	typedef map<SCENE_KIND, iGameNode*>				mSceneList;
	typedef map<SCENE_KIND, iGameNode*>::iterator	iSceneList;

private:
	mSceneList	m_mapSceneList;
	iGameNode*	m_pCurrScene;

public:
	void Init();
	void Update();
	void Render();
	void ReleaseAll();

	void AddScene(SCENE_KIND sceneName, iGameNode* scene); // ¾À Ãß°¡
	void Change(SCENE_KIND sceneName);	// ÇöÀç ¾À º¯°æ
};

