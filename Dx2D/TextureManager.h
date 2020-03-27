#pragma once
#include "SingletonBase.h"

#define g_pTextureManager TextureManager::GetInstance()

struct Texture
{
	D3DX11_IMAGE_INFO			stInfo;
	ID3D11ShaderResourceView*	pSRV;
};

struct RenderTexture : public Texture
{
	ID3D11Texture2D*			pT2D;
	ID3D11RenderTargetView*		pRTV;
};

class TextureManager : public SingletonBase<TextureManager>
{
private:
	map<wstring, Texture*>		m_mapTexture;

public:
	TextureManager();
	~TextureManager();

	void AddTexture(wstring key, wstring file, wstring path = L"../../_Images/");
	const Texture* GetTexture(wstring key);
	void Release(wstring key);

	// 렌더 텍스쳐
	void AddRenderTargetTexture(wstring key, UINT width = WINSIZEX, UINT height = WINSIZEY);			// 기본 빈 텍스쳐 추가
	void SetRenderTargetToTexture(wstring key);		// 렌더 타겟 텍스쳐 설정(기본값 : 백버퍼)
	void ClearRenderTargetTexture(wstring key, D3DXCOLOR c = { 0, 0, 0, 1 }); // 타겟 텍스쳐를 지정 색상으로 초기화
	void SetRenderTargetToBackBuffer();				// 렌더 타겟을 백버퍼로 설정
};

