#include "Sprite.h"
#include <iostream>
void CSprite::SetSprite(ALLEGRO_BITMAP *_bitmap) {
	m_bitmap = al_clone_bitmap(_bitmap);
}

ALLEGRO_BITMAP *CSprite::GetSprite() {
	return al_clone_bitmap(m_bitmap);
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
		std::string gubun = " : ";
		std::string test = "Player : " + std::to_string(m_score);
		const char* tmp =test.c_str();
		al_draw_text(m_font, al_map_rgb(0, 0, 255), transform->x - 32, transform->y - 32, ALLEGRO_ALIGN_LEFT, tmp);
	}
}