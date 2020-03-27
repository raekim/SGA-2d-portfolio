#pragma once
class MainGame
{
private:
	ID3D11BlendState*	m_pNormalBlendState;	// 기본 블렌드 옵션
	ID3D11BlendState*	m_pAlphaBlendState;		// 반투명 블렌드 옵션
	void SetBlendStates();	// 옵션별 블렌드 상태값 생성

public:
	MainGame();
	~MainGame();

	void Update();
	void Render();
};

