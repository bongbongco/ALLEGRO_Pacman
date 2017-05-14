#pragma once
#include "Component.h"
#include "Object.h"
#include "Transform.h"
#include "allegro5\allegro.h"
#include "allegro5\allegro_image.h"

class CSprite : public CComponent {
public :
	ALLEGRO_BITMAP *m_bitmap;

	CSprite(CObject *_object) : CComponent(_object) {
		m_bitmap = NULL;
	}

	void SetSprite(ALLEGRO_BITMAP *_bitmap);
	ALLEGRO_BITMAP *GetSprite();
	virtual void Update();
	virtual void Render();
};