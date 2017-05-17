#include "Sprite.h"
#include <iostream>
void CSprite::SetSprite(ALLEGRO_BITMAP *_bitmap) {
	m_bitmap = al_clone_bitmap(_bitmap);
}

ALLEGRO_BITMAP *CSprite::GetSprite() {
	return al_clone_bitmap(m_bitmap);
}

void CSprite::SetText(std::string _text) {
	m_text = _text.c_str();
}

void CSprite::SetText(int _text) {
	std::string tmp = std::to_string(_text);
	m_text = tmp.c_str();
}

void CSprite::Update() {
}

void CSprite::Render() {
	if (m_bitmap) {
		CTransform *transform = GetObject()->GetTransform();
		al_draw_bitmap(m_bitmap, transform->x, transform->y, 0);
	}

	if (m_text[0] != '0') {
		CTransform *transform = GetObject()->GetTransform();
		al_draw_text(m_font, al_map_rgb(0, 0, 255), transform->x, transform->y, ALLEGRO_ALIGN_LEFT, m_text);
	}
}