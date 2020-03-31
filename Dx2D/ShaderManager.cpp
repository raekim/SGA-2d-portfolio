#include "stdafx.h"
#include "ShaderManager.h"


ShaderManager::ShaderManager()
{
}


ShaderManager::~ShaderManager()
{
	for (auto p : m_mapShader)
		SAFE_DELETE(p.second);
	m_mapShader.clear();
}

Shader * ShaderManager::AddShader(wstring key, D3D11_INPUT_ELEMENT_DESC desc[], UINT count)
{
	if (m_mapShader.find(key) != m_mapShader.end())
	{
		return m_mapShader[key];
	}

	m_mapShader[key] = new Shader(key);
	m_mapShader[key]->CreateinputLayout(desc, count);
	return m_mapShader[key];
}

void ShaderManager::Release(wstring key)
{
	if (m_mapShader.find(key) != m_mapShader.end()) return;

	SAFE_DELETE(m_mapShader[key]);
	m_mapShader.erase(key);
}
