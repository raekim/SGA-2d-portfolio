#include "stdafx.h"
#include "PlayScene.h"

PlayScene::PlayScene()
{
}


PlayScene::~PlayScene()
{
}

void PlayScene::Init()
{
	g_pCamera->SetMapSize(GAMESCREEN_X, GAMESCREEN_Y);
	g_pCamera->SetTarget(NULL);

	// 플레이어 생성
	m_player1P = new Player;
	m_player1P->Init(L"Chicken-Sheet");
	m_player1P->SetJumpKey(VK_RCONTROL);
	m_player1P->SetLeftMoveKey(VK_LEFT);
	m_player1P->SetRightMoveKey(VK_RIGHT);

	m_player2P = new Player;
	m_player2P->Init(L"Chicken-Sheet-2P");
	m_player2P->SetJumpKey('Z');
	m_player2P->SetLeftMoveKey('F');
	m_player2P->SetRightMoveKey('H');

	// 맵 생성
	m_map = new Map;
	m_map->Init();

	// 플레이어 커서 생성
	m_cursor1P = new PlayerCursor;
	m_cursor1P->Init(new Sprite(L"Chicken-Sheet", CHICKEN_SHEET_X/2, CHICKEN_SHEET_Y, (CHICKEN_SHEET_X / 2) * 5 + 5), new Sprite(L"Chicken-Sheet", CHICKEN_SHEET_X / 2, CHICKEN_SHEET_Y, (CHICKEN_SHEET_X / 2) *5 + 6));
	m_cursor1P->SetLeftMoveKey(VK_LEFT);
	m_cursor1P->SetRightMoveKey(VK_RIGHT);
	m_cursor1P->SetUpMoveKey(VK_UP);
	m_cursor1P->SetDownMoveKey(VK_DOWN);
	m_cursor1P->SetSelectKey(VK_RCONTROL);
	m_cursor1P->SetFlipKey(VK_RSHIFT);
	m_cursor1P->SetMap(m_map);

	m_cursor2P = new PlayerCursor;
	m_cursor2P->Init(new Sprite(L"Chicken-Sheet-2P", CHICKEN_SHEET_X / 2, CHICKEN_SHEET_Y, (CHICKEN_SHEET_X / 2) * 5 + 5), new Sprite(L"Chicken-Sheet-2P", CHICKEN_SHEET_X / 2, CHICKEN_SHEET_Y, (CHICKEN_SHEET_X / 2) * 5 + 6));
	m_cursor2P->SetLeftMoveKey('F');
	m_cursor2P->SetRightMoveKey('H');
	m_cursor2P->SetUpMoveKey('T');
	m_cursor2P->SetDownMoveKey('G');
	m_cursor2P->SetSelectKey('Z');
	m_cursor2P->SetFlipKey(VK_LSHIFT);
	m_cursor2P->SetMap(m_map);

	// 맨 처음은 맵툴모드에서 시작
	SwitchToMapToolMode();

	m_mapToolModeTransitionDelay = 3.0f;

	m_UI = new PlaySceneUI;
}

void PlayScene::Update()
{
	// ESC 누르면 프로그램 종료
	if (g_pKeyManager->IsOnceKeyDown(VK_ESCAPE))
	{
		PostQuitMessage(0); // WM_QUIT 메시지 발생
	}

	// 현재 모드(맵툴/플레이)에 따라 업데이트
	switch (m_curMode)
	{
		case MODE::MAPTOOL_MODE:
			if (m_cursor1P->HasPlacedObject() && m_cursor2P->HasPlacedObject())
			{
				SwitchToPlayMode();
				break;
			}
			else
			{
				m_cursor1P->Update(m_map->GetPlacedObjects());
				m_cursor2P->Update(m_map->GetPlacedObjects());
			}
			break;
		case MODE::PLAY_MODE:
			UpdatePlayMode();
	}

	m_UI->Update();
	g_pCamera->Update();
}

void PlayScene::UpdatePlayMode()
{
	// 플레이어가 모두 게임오버
	if (m_player1P->IsGameOver() && m_player2P->IsGameOver())
	{
		// 카메라 줌아웃 시킨다
		g_pCamera->SetTarget(NULL);
		g_pCamera->SetPositionRange({ 0, GAMESCREEN_X - WINSIZEX }, { 0, GAMESCREEN_Y - WINSIZEY });
		// 점수판을 보여준다
		m_UI->ShowScoreBoard();
		if (ZoomOutCamera())
		{
			// 카메라 줌아웃이 끝났다
			if (m_transitionCount >= m_mapToolModeTransitionDelay)
			{
				// 맵툴모드로 전환한다
				SwitchToMapToolMode();
				return;
			}
			else
			{
				m_transitionCount += g_pTimeManager->GetDeltaTime();
			}
		}
	}

	// 충돌검사에 쓰일 콜라이더들 정보
	// 화면을 16x9로 분할했을 때 각각의 벡터에는 해당 영역에 속하는 PlaceableObject들의 포인터들이 있다
	vector<vector<PlaceableObject*>> objList(GAMESCREEN_X_RATIO*GAMESCREEN_Y_RATIO);

	// 맵 상의 오브젝트들을 업데이트하고 콜라이더 정보를 정해진 벡터에 넣는다
	m_map->Update(objList);

	// 콜라이더 정보를 바탕으로 충돌처리
	m_player1P->Update(objList);
	m_player2P->Update(objList);

	UpdatePlayModeCamera();
}

bool PlayScene::ZoomOutCamera()
{
	auto eye = g_pCamera->GetEyeVal();

	if (fabs(g_pCamera->GetPosition().x) <= 0.01f && fabs(g_pCamera->GetPosition().y) <= 0.01f &&
		fabs(g_pCamera->GetEyeVal() - (-1.666f)) <= 0.01f)
	{
		return true;
	}

	// 카메라 줌을 최대한 당긴다
	float moveSpeed = 3.0f;
	float zoomOutSpeed = 2.0f;
	g_pCamera->SetPosition(g_pCamera->GetPosition() + 
		(D3DXVECTOR2(0, 0) - g_pCamera->GetPosition())*g_pTimeManager->GetDeltaTime()*moveSpeed);

	g_pCamera->SetEyeVal(g_pCamera->GetEyeVal() +
		(-1.666f - g_pCamera->GetEyeVal())*g_pTimeManager->GetDeltaTime()*zoomOutSpeed);

	
	g_pCamera->Update();

	return false;
}

void PlayScene::UpdatePlayModeCamera()
{
	// 1P, 2P 둘 다 게임오버(죽거나 골인하거나) 인 경우 ZoomOutCamera에서 처리
	if (m_player1P->IsGameOver() && m_player2P->IsGameOver())
	{
		return;
	}

	// 1P와 2P의 상태를 바탕으로 카메라 처리
	if (m_player1P->IsDead())
	{
		// 1P가 죽은 경우 카메라는 2P를 따라간다
		g_pCamera->SetTarget(m_player2P->GetPosition());
		g_pCamera->SetPositionRange({ 0, GAMESCREEN_X - WINSIZEX }, { 0, GAMESCREEN_Y - WINSIZEY });
		g_pCamera->SetEyeVal(-1.0f);
	}
	else if (m_player2P->IsDead())
	{
		// 2P가 죽은 경우 카메라는 1P를 따라간다
		g_pCamera->SetTarget(m_player1P->GetPosition());
		g_pCamera->SetPositionRange({ 0, GAMESCREEN_X - WINSIZEX }, { 0, GAMESCREEN_Y - WINSIZEY });
		g_pCamera->SetEyeVal(-1.0f);
	}
	else
	{
		// 1P, 2P 모두가 살아있는 경우 카메라는 둘의 중간 위치로 설정한다
		m_camPos.x = fabs(m_player1P->GetPosition()->x + m_player2P->GetPosition()->x) / 2;
		m_camPos.y = fabs(m_player1P->GetPosition()->y + m_player2P->GetPosition()->y) / 2;
		g_pCamera->SetTarget(&m_camPos);

		float eyeVal;
		D3DXVECTOR2 distVec = *(m_player1P->GetPosition()) - *(m_player2P->GetPosition());
		float dist = D3DXVec2Length(&distVec);
		dist = min(dist, GAMESCREEN_X);
		eyeVal = LinearInterpolation(-0.9f, -1.666f, dist / GAMESCREEN_X);
		g_pCamera->SetPositionRange(
			D3DXVECTOR2(0, (FLOAT)LinearInterpolation(GAMESCREEN_X - WINSIZEX, 0, (eyeVal + 1) / -0.666f)),
			D3DXVECTOR2(0, (FLOAT)LinearInterpolation(GAMESCREEN_Y - WINSIZEY, 0, (eyeVal + 1) / -0.666f))
		);
		g_pCamera->SetEyeVal(eyeVal);
	}
}

void PlayScene::Render()
{
	switch (m_curMode)
	{
	case MODE::MAPTOOL_MODE:
		// 맵툴모드 맵 렌더
		m_map->RenderMapToolMode();

		// 커서 렌더
		m_cursor1P->Render();
		m_cursor2P->Render();
		break;
	case MODE::PLAY_MODE:
		// 플레이 모드 맵 렌더
		m_map->RenderPlayMode();

		// 캐릭터 렌더
		m_player1P->Render();
		m_player2P->Render();
		break;
	}
	m_UI->Render();
}

PlaceableObject* GetRandomPlaceableObject()
{
	return new BallShooter;
	int rnd = rand() % 6;
	
	switch (rnd)
	{
	case 0:
	case 1:
	{
		int rnd = rand() % (int)SimplePlatform::Platform_Type::Max;
		return new SimplePlatform(static_cast<SimplePlatform::Platform_Type>(rnd));
	}
	case 2:
		return new honeyPlatform; // applied cannot-place
	case 3:
		return new SpinWheel;
	case 4:
		return new SpringPlatform;
	case 5:
		return new BallShooter;
	}
}

void PlayScene::SwitchToMapToolMode()
{
	// 맵툴 모드로 넘어간다
	m_curMode = MODE::MAPTOOL_MODE;
	m_transitionCount = 0.0f;

	// 카메라 시점 설정
	g_pCamera->SetTarget(NULL);
	g_pCamera->SetPosition({ 0,0 });
	g_pCamera->SetEyeVal(-1.666f);
	g_pCamera->SetPositionRange({ 0, GAMESCREEN_X - WINSIZEX }, { 0, GAMESCREEN_Y - WINSIZEY });
	g_pCamera->Update();

	// 커서 설정
	m_cursor1P->SetObjectToPlace(GetRandomPlaceableObject());
	m_cursor1P->ResetCursor({ 800,800 });
	m_cursor2P->SetObjectToPlace(GetRandomPlaceableObject());
	m_cursor2P->ResetCursor({ 800,1300 });
}

void PlayScene::SwitchToPlayMode()
{
	// 플레이 모드로 넘어간다
	m_curMode = MODE::PLAY_MODE;

	// 카메라 시점 설정
	g_pCamera->SetTarget(NULL);
	g_pCamera->SetEyeVal(-1.0f);
	g_pCamera->SetPosition({ 330.0f, 300.0f });
	g_pCamera->Update();

	// 캐릭터 설정
	m_player1P->Revive({ 330.0f, 800.0f });
	m_player2P->Revive({ 370.0f, 800.0f });
}

void PlayScene::Release()
{
	SAFE_DELETE(m_player1P);
	SAFE_DELETE(m_player2P);
	SAFE_DELETE(m_cursor1P);
}
