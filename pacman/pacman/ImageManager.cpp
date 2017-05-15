#include "ImageManager.h"

ALLEGRO_BITMAP *CImageManager::GetImage(const char *_imageFilePath) {
	if (m_cacheImage[_imageFilePath]) {
		return m_cacheImage[_imageFilePath];
	}
	ALLEGRO_BITMAP *targetBitmap = al_get_target_bitmap(); // ȣ�� �������� Ÿ�� ��Ʈ�� 
	ALLEGRO_BITMAP *originalImage = al_load_bitmap(_imageFilePath); // �̹��� ���� �б�
	ALLEGRO_BITMAP *scaledImage = al_create_bitmap(kTileWidth, kTileHeight); // ���� �����忡 �� ��Ʈ�� ����

	al_set_target_bitmap(scaledImage); // �׸��� �۾��� ������ ��Ʈ�� ����
	al_draw_scaled_bitmap(originalImage, 0, 0, al_get_bitmap_width(originalImage), al_get_bitmap_height(originalImage), 
		0, 0, kTileWidth, kTileHeight, 0); // ��Ʈ�� ���
	al_set_target_bitmap(targetBitmap); // �׸��� �۾� �Ϸ� �� ȣ�� �������� Ÿ�� ��Ʈ�� �ǵ�����

	m_cacheImage[_imageFilePath] = scaledImage;
	return scaledImage;
}