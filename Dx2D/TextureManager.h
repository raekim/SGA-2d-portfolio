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

	// ���� �ؽ���
	void AddRenderTargetTexture(wstring key, UINT width = WINSIZEX, UINT height = WINSIZEY);			// �⺻ �� �ؽ��� �߰�
	void SetRenderTargetToTexture(wstring key);		// ���� Ÿ�� �ؽ��� ����(�⺻�� : �����)
	void ClearRenderTargetTexture(wstring key, D3DXCOLOR c = { 0, 0, 0, 1 }); // Ÿ�� �ؽ��ĸ� ���� �������� �ʱ�ȭ
	void SetRenderTargetToBackBuffer();				// ���� Ÿ���� ����۷� ����
};

