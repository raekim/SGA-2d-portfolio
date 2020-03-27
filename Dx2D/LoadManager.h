#pragma once
#include "SingletonBase.h"

#define g_pLoadManager LoadManager::GetInstance()

enum class RESOURCE_TYPE
{
	Image,
	Sound,
	End
};

struct tagResourceInfo
{
	RESOURCE_TYPE eType;
};

struct tagTextureInfo : tagResourceInfo
{
	wstring sKey;
	wstring sFile;

	tagTextureInfo(RESOURCE_TYPE type, wstring key, wstring file)
	{
		eType = type;
		sKey = key;
		sFile = file;
	}
};

struct tagSoundInfo : tagResourceInfo
{
	string sKey;
	string sFile;
	bool isBgm;
	bool isLoop;

	tagSoundInfo(RESOURCE_TYPE type, string key, string file, bool bgm, bool loop)
	{
		eType = type;
		sKey = key;
		sFile = file;
		isBgm = bgm;
		isLoop = loop;
	}
};

class LoadManager :	public SingletonBase<LoadManager>
{
private:
	vector<tagResourceInfo*>	m_vecResourceList;	// 사용중인 리소스 목록
	SCENE_KIND					m_eNextScene;		// 현재 씬
	int							m_nNumLoaded;		// 로딩 완료 된 숫자

private:
	void ReleasePrevResources();	// 이전 씬에서 사용 중이던 리소스 해제
	void MakeAResourcesList();		// 다음 씬에서 사용할 리스트 목록 생성

public:
	void Init();						// 로딩씬에서 사용할 리소스 로딩
	void Update();						// 로딩 진행
	void ReleaseAll();					// 리소스 리스트 포인터 해제용
	void ChangeScene(SCENE_KIND eNext);	// 씬 변경 호출 함수

	int GetNumLoaded() { return m_nNumLoaded; }
	int GetNumMax() { return m_vecResourceList.size(); }
};

