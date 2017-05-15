#include "ImageManager.h"

ALLEGRO_BITMAP *CImageManager::GetImage(const char *_imageFilePath) {
	if (m_cacheImage[_imageFilePath]) {
		return m_cacheImage[_imageFilePath];
	}
	ALLEGRO_BITMAP *targetBitmap = al_get_target_bitmap(); // 호출 스레드의 타겟 비트맵 
	ALLEGRO_BITMAP *originalImage = al_load_bitmap(_imageFilePath); // 이미지 파일 읽기
	ALLEGRO_BITMAP *scaledImage = al_create_bitmap(kTileWidth, kTileHeight); // 현재 스레드에 새 비트맵 구성

	al_set_target_bitmap(scaledImage); // 그리기 작업을 수행할 비트맵 선택
	al_draw_scaled_bitmap(originalImage, 0, 0, al_get_bitmap_width(originalImage), al_get_bitmap_height(originalImage), 
		0, 0, kTileWidth, kTileHeight, 0); // 비트맵 축소
	al_set_target_bitmap(targetBitmap); // 그리기 작업 완료 후 호출 스레드의 타겟 비트맵 되돌리기

	m_cacheImage[_imageFilePath] = scaledImage;
	return scaledImage;
}