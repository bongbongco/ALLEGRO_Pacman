#pragma once
#include "allegro5\allegro.h"
#include "allegro5\allegro_image.h"
#include "Common.h"
#include <map>

class CImageManager {
private:
	std::map<const char*, ALLEGRO_BITMAP*> m_cacheImage;
public:
	ALLEGRO_BITMAP *GetImage(const char *_imageFilePath);

	
};