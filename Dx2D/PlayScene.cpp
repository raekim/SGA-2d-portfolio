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

	// �÷��̾� ����
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

	// �÷��̾� Ŀ�� ����
	m_cursor1P = new PlayerCursor;
	m_cursor1P->Init(new Sprite(L"Chicken-Sheet", CHICKEN_SHEET_X/2, CHICKEN_SHEET_Y, (CHICKEN_SHEET_X / 2) * 5 + 5), new Sprite(L"Chicken-Sheet", CHICKEN_SHEET_X / 2, CHICKEN_SHEET_Y, (CHICKEN_SHEET_X / 2) *5 + 6));
	m_cursor1P->SetLeftMoveKey(VK_LEFT);
	m_cursor1P->SetRightMoveKey(VK_RIGHT);
	m_cursor1P->SetUpMoveKey(VK_UP);
	m_cursor1P->SetDownMoveKey(VK_DOWN);
	m_cursor1P->SetSelectKey(VK_RCONTROL);
	m_cursor1P->SetFlipKey(VK_RSHIFT);

	m_cursor2P = new PlayerCursor;
	m_cursor2P->Init(new Sprite(L"Chicken-Sheet-2P", CHICKEN_SHEET_X / 2, CHICKEN_SHEET_Y, (CHICKEN_SHEET_X / 2) * 5 + 5), new Sprite(L"Chicken-Sheet", CHICKEN_SHEET_X / 2, CHICKEN_SHEET_Y, (CHICKEN_SHEET_X / 2) * 5 + 6));
	m_cursor2P->SetLeftMoveKey('F');
	m_cursor2P->SetRightMoveKey('H');
	m_cursor2P->SetUpMoveKey('T');
	m_cursor2P->SetDownMoveKey('G');
	m_cursor2P->SetSelectKey('Z');
	m_cursor2P->SetFlipKey(VK_LSHIFT);

	// �� ó���� ������忡�� ����
	SwitchToMapToolMode();

	m_mapToolModeTransitionDelay = 3.0f;
}

void PlayScene::Update()
{
	// ESC ������ ���α׷� ����
	if (g_pKeyManager->IsOnceKeyDown(VK_ESCAPE))
	{
		PostQuitMessage(0); // WM_QUIT �޽��� �߻�
	}

	// ���� ���(����/�÷���)�� ���� ������Ʈ
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

	g_pCamera->Update();
}

void PlayScene::UpdatePlayMode()
{
	// �÷��̾ ��� ������ �������� ��ȯ
	if (m_player1P->IsGameOver() && m_player2P->IsGameOver())
	{
		if (m_transitionCount >= m_mapToolModeTransitionDelay)
		{
			SwitchToMapToolMode();
			return;
		}
		else
		{
			m_transitionCount += g_pTimeManager->GetDeltaTime();
		}
	}

	// �浹�˻翡 ���� �ݶ��̴��� ����
	// ȭ���� 16x9�� �������� �� ������ ���Ϳ��� �ش� ������ ���ϴ� PlaceableObject���� �����͵��� �ִ�
	vector<vector<PlaceableObject*>> objList(GAMESCREEN_X_RATIO*GAMESCREEN_Y_RATIO);

	// �� ���� ������Ʈ���� ������Ʈ�ϰ� �ݶ��̴� ������ ������ ���Ϳ� �ִ´�
	for (auto obj : m_mapBlocks) obj->Update(objList);
	for (auto obj : m_map->GetPlacedObjects()) obj->Update(objList);
	m_goalFlag->Update(objList);

	// �ݶ��̴� ������ �������� �浹ó��
	m_player1P->Update(objList);
	m_player2P->Update(objList);

	UpdatePlayModeCamera();
}

void PlayScene::UpdatePlayModeCamera()
{
	// 1P�� 2P�� ���¸� �������� ī�޶� ó��
	if (m_player1P->IsDead())
	{
		// 1P�� ���� ��� ī�޶�� 2P�� ���󰣴�
		g_pCamera->SetTarget(m_player2P->GetPosition());
		g_pCamera->SetPositionRange({ 0, GAMESCREEN_X - WINSIZEX }, { 0, GAMESCREEN_Y - WINSIZEY });
		g_pCamera->SetEyeVal(-1.0f);
	}
	else if (m_player2P->IsDead())
	{
		// 2P�� ���� ��� ī�޶�� 1P�� ���󰣴�
		g_pCamera->SetTarget(m_player1P->GetPosition());
		g_pCamera->SetPositionRange({ 0, GAMESCREEN_X - WINSIZEX }, { 0, GAMESCREEN_Y - WINSIZEY });
		g_pCamera->SetEyeVal(-1.0f);
	}
	else
	{
		// 1P, 2P ��ΰ� ����ִ� ��� ī�޶�� ���� �߰� ��ġ�� �����Ѵ�
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
		// �� ����
		m_mapBackground->Render();
		m_mapPaper->Render();
		m_mapForeground->Render();

		for (auto obj : m_placedObjects) obj->RenderPreviewImage();

		// Ŀ�� ����
		m_cursor1P->Render();
		m_cursor2P->Render();
		break;
	case MODE::PLAY_MODE:
		// �� ����
		m_mapBackground->Render();
		m_goalFlag->Render();
		m_mapForeground->Render();

		// ��ֹ� ����
		for (auto obj : m_placedObjects) obj->Render();

		// ĳ���� ����
		m_player1P->Render();
		m_player2P->Render();
		break;
	}
}

PlaceableObject* GetRandomPlaceableObject()
{
	{
		int rnd = rand() % (int)SimplePlatform::Platform_Type::Max;
		return new SimplePlatform(static_cast<SimplePlatform::Platform_Type>(rnd));
	}


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
		return new honeyPlatform;
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
	// ���� ���� �Ѿ��
	m_curMode = MODE::MAPTOOL_MODE;
	m_transitionCount = 0.0f;

	// ī�޶� ���� ����
	g_pCamera->SetTarget(NULL);
	g_pCamera->SetPosition({ 0,0 });
	g_pCamera->SetEyeVal(-1.666f);
	g_pCamera->SetPositionRange({ 0, GAMESCREEN_X - WINSIZEX }, { 0, GAMESCREEN_Y - WINSIZEY });
	g_pCamera->Update();

	// Ŀ�� ����
	m_cursor1P->SetObjectToPlace(GetRandomPlaceableObject());
	m_cursor1P->ResetCursor({ 800,800 });
	m_cursor2P->SetObjectToPlace(GetRandomPlaceableObject());
	m_cursor2P->ResetCursor({ 800,1300 });
}

void PlayScene::SwitchToPlayMode()
{
	// �÷��� ���� �Ѿ��
	m_curMode = MODE::PLAY_MODE;

	// ī�޶� ���� ����
	g_pCamera->SetTarget(NULL);
	g_pCamera->SetEyeVal(-1.0f);
	g_pCamera->SetPosition({ 330.0f, 300.0f });
	g_pCamera->Update();

	// ĳ���� ����
	m_player1P->Revive({ 330.0f, 800.0f });
	m_player2P->Revive({ 370.0f, 800.0f });
}

void PlayScene::Release()
{
	SAFE_DELETE(m_mapBackground);
	SAFE_DELETE(m_mapPaper);
	SAFE_DELETE(m_mapForeground);

	SAFE_DELETE(m_player1P);
	SAFE_DELETE(m_player2P);
	SAFE_DELETE(m_cursor1P);

	m_goalFlag->Release();
}
