#include "stdafx.h"
#include "PlaceableObject.h"


PlaceableObject::PlaceableObject()
{
}


PlaceableObject::~PlaceableObject()
{
}

void PlaceableObject::RenderPreviewImage()
{
	m_previewImg->SetPosition(m_position); 
	float rotate = (m_flipped) ? D3DX_PI : 0;
	m_previewImg->SetRotation({ 0,rotate,0 });
	m_previewImg->Update();  
	m_previewImg->Render();
}
