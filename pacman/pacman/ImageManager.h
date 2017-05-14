#pragma once
#include "allegro5\allegro.h"
#include "allegro5\allegro_image.h"
#include "Common.h"

class CImageManager {
private:

public:
	ALLEGRO_BITMAP *GetImage(const char *_imageFilePath);

	
};