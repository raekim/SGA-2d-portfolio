#pragma once
#include "SingletonBase.h"
#include "Shader.h"

#define g_pShaderManager ShaderManager::GetInstance()
class ShaderManager : public SingletonBase<ShaderManager>
{
	map<wstring, Shader*>		m_mapShader;
public:
	ShaderManager();
	~ShaderManager();

	Shader* AddShader(wstring key, D3D11_INPUT_ELEMENT_DESC desc[], UINT count);
	void Release(wstring key);
};

