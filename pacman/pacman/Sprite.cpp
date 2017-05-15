#include "Sprite.h"
#include <iostream>
void CSprite::SetSprite(ALLEGRO_BITMAP *_bitmap) {
	m_bitmap = al_clone_bitmap(_bitmap);
}

ALLEGRO_BITMAP *CSprite::GetSprite() {
	return al_clone_bitmap(m_bitmap);
}

void CSprite::Update() {
}

void CSprite::Render() {
	if (m_bitmap) {
		std::cout << "Sprite Render();" << std::endl;
		CTransform *transform = this->GetObject()->GetTransform();
		al_draw_bitmap(m_bitmap, transform->x, transform->y, 0);
		al_flip_display();
	}
}