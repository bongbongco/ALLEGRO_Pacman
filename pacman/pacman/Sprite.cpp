#include "Sprite.h"
#include <iostream>
void CSprite::SetSprite(ALLEGRO_BITMAP *_bitmap) {
	m_bitmap = al_clone_bitmap(_bitmap);
}

ALLEGRO_BITMAP *CSprite::GetSprite() {
	return al_clone_bitmap(m_bitmap);
}

void CSprite::SetLife(int _life) {
	m_life = _life;
}

void CSprite::SetScore(int _score) {
	m_score = _score;
}

void CSprite::SetText(const char *_text) {
	m_text = _text;
}

void CSprite::Update() {
}

void CSprite::Render() {
	CTransform *transform = GetObject()->GetTransform();

	if (m_bitmap) {
		al_draw_bitmap(m_bitmap, transform->x, transform->y, 0);
	}
		
	if (m_text[0] != '0') {
		std::string test = "Score : " + std::to_string(m_score) + " Life : " + std::to_string(m_life);
		const char* tmp = test.c_str();
		al_draw_text(m_font, al_map_rgb(255, 255, 102), transform->x, transform->y - 32, ALLEGRO_ALIGN_LEFT, "Player");
		al_draw_text(m_font, al_map_rgb(255, 000, 000), 1040, 5, ALLEGRO_ALIGN_RIGHT, tmp);
	}
}