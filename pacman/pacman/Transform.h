#pragma once
#include "allegro5\allegro.h"
#include "allegro5\allegro_image.h"
#include "allegro5\allegro_primitives.h"

#include "Component.h"
#include "Common.h"
#include <iostream>

class CTransform : public CComponent {
public:
	int x;
	int y;
	int width;
	int height;
	
	CTransform(CObject *_object) :CComponent(_object) {
		x = 0;
		y = 0;
		width = kTileWidth;
		height = kTileHeight;
	}

	virtual void Update() {}
	virtual void Render() {
		std::cout << "transform Render()" << std::endl;
 		//al_draw_filled_rectangle(x, y, x + kTileWidth, y + kTileHeight, al_map_rgb(0, 255, 0));
		//al_flip_display();                               
	}
};