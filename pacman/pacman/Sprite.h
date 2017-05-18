#pragma once
#include "Component.h"
#include "Object.h"
#include "Transform.h"
#include "allegro5\allegro.h"
#include "allegro5\allegro_image.h"
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_ttf.h"


class CSprite : public CComponent {
private:
	int m_score;
public :
	const char *m_text;
	ALLEGRO_FONT *m_font = al_load_ttf_font("font.ttf", 24, ALLEGRO_TTF_NO_KERNING);
	ALLEGRO_BITMAP *m_bitmap;

	CSprite(CObject *_object) : CComponent(_object) {
		m_bitmap = NULL;
		m_text = "0";
		m_score = 0;
	}

	void SetSprite(ALLEGRO_BITMAP *_bitmap);
	ALLEGRO_BITMAP *GetSprite();
	
	void SetScore(int _score);
	void SetText(const char *_text);

	virtual void Update();
	virtual void Render();
};