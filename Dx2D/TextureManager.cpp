#include "stdafx.h"
#include "TextureManager.h"


TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
	for (auto p : m_mapTexture)
		SAFE_RELEASE(p.second->pSRV);
	m_mapTexture.clear();
}

void TextureManager::AddTexture(wstring key, wstring file, wstring path)
{
	if (m_mapTexture.find(key) != m_mapTexture.end()) return;

	wstring fullPath = path + file;

	Texture* texture = new Texture;

	// 파일 정보 읽기 (사이즈 값 사용)
	{
		HRESULT hr;

		D3DX11GetImageInfoFromFile(fullPath.c_str(), NULL, &texture->stInfo, &hr);
		assert(SUCCEEDED(hr) && "파일을 읽어 올 수 없습니다.");
	}

	// 이미지 로드
	{
		HRESULT hr;

		D3DX11CreateShaderResourceViewFromFile(Device, fullPath.c_str(), NULL, NULL, &texture->pSRV, &hr);
		assert(SUCCEEDED(hr) && "파일을 읽어 올 수 없습니다.");
	}

	m_mapTexture[key] = texture;
}

const Texture* TextureManager::GetTexture(wstring key)
{
	if (m_mapTexture.find(key) == m_mapTexture.end()) return NULL;

	return m_mapTexture[key];
}

void TextureManager::Release(wstring key)
{
	map<wstring, Texture*>::iterator iter;
	iter = m_mapTexture.find(key);

	if (iter == m_mapTexture.end()) return;

	SAFE_RELEASE(iter->second->pSRV);	// 이미지 할당 해제
	m_mapTexture.erase(iter);
}

void TextureManager::AddRenderTargetTexture(wstring key, UINT width, UINT height)
{
	if (m_mapTexture.find(key) != m_mapTexture.end()) return;

	RenderTexture* stRTexture = new RenderTexture;

	HRESULT hr;

	// 렌더 타겟 텍스쳐  생성
	D3D11_TEXTURE2D_DESC stT2DDesc;
	stT2DDesc.Width = width;
	stT2DDesc.Height = height;
	stT2DDesc.MipLevels = 1;
	stT2DDesc.ArraySize = 1;
	stT2DDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	stT2DDesc.SampleDesc.Count = 1;
	stT2DDesc.SampleDesc.Quality = 0;
	stT2DDesc.Usage = D3D11_USAGE_DEFAULT;
	stT2DDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	stT2DDesc.CPUAccessFlags = 0;
	stT2DDesc.MiscFlags = 0;

	hr = Device->CreateTexture2D(&stT2DDesc, NULL, &stRTexture->pT2D);
	assert(SUCCEEDED(hr));

	// 렌더 타겟 뷰 생성
	D3D11_RENDER_TARGET_VIEW_DESC stRTVDesc;
	stRTVDesc.Format = stT2DDesc.Format;
	stRTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	stRTVDesc.Texture2D.MipSlice = 0;

	hr = Device->CreateRenderTargetView(stRTexture->pT2D, &stRTVDesc, &stRTexture->pRTV);
	assert(SUCCEEDED(hr));

	// 셰이더 리소스 뷰 생성
	D3D11_SHADER_RESOURCE_VIEW_DESC stSRVDesc;
	stSRVDesc.Format = stT2DDesc.Format;
	stSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	stSRVDesc.Texture2D.MostDetailedMip = 0;
	stSRVDesc.Texture2D.MipLevels = 1;

	hr = Device->CreateShaderResourceView(stRTexture->pT2D, &stSRVDesc, &stRTexture->pSRV);
	assert(SUCCEEDED(hr));

	stRTexture->stInfo.Width = width;
	stRTexture->stInfo.Height = height;

	m_mapTexture.insert(make_pair(key, stRTexture));
}

void TextureManager::SetRenderTargetToTexture(wstring key)
{
	if (m_mapTexture.find(key) == m_mapTexture.end()) return;

	RenderTexture* pRT = (RenderTexture*)m_mapTexture[key];
	DeviceContext->OMSetRenderTargets(1, &pRT->pRTV, NULL);
}

void TextureManager::ClearRenderTargetTexture(wstring key, D3DXCOLOR c)
{
	if (m_mapTexture.find(key) == m_mapTexture.end()) return;

	RenderTexture* pRT = (RenderTexture*)m_mapTexture[key];
	DeviceContext->ClearRenderTargetView(pRT->pRTV, c);
}

void TextureManager::SetRenderTargetToBackBuffer()
{
	DeviceContext->OMSetRenderTargets(1, &RTV, NULL);
}
