#include "SceneManager.h"
#include "ControllManager.h"
#include "MapManager.h"
#include "ImageManager.h"


static CMapManager gMapManager;
static CImageManager gImageManager;
static CControllManager gControllManager;

void CSceneManager::Init() {
	ALLEGRO_BITMAP *m_tileImage;
	ALLEGRO_BITMAP *m_pointImage;
	ALLEGRO_BITMAP *m_pacmanImage;
	ALLEGRO_BITMAP *m_ghostImage;
	ALLEGRO_BITMAP *m_speedImage;
	std::cout << "SceneManager initialize" << std::endl;
	try {
		if (al_init_image_addon()) {// 이미지 추가 기능 초기화 
			m_blueprint = gMapManager.LoadLevel("level1.txt"); // 설계도 생성

			m_tileImage = gImageManager.GetImage("tile.png"); // 타일 이미지
			m_pointImage = gImageManager.GetImage("point.png"); // 포인트 이미지

			for (int i = 0; i < kTileY; i++) {
				for (int j = 0; j < kTileX; j++) {
					if (m_blueprint[i][j] == kWall) {
						CObject *tile = new CObject();
						tile->GetTransform()->y = i * al_get_bitmap_height(m_tileImage);
						tile->GetTransform()->x = j * al_get_bitmap_width(m_tileImage);

						tile->AddComponent<CSprite>()->SetSprite(m_tileImage);
						tile->AddComponent<CCollision>();
						m_objects.push_back(tile);
					}
					else if (m_blueprint[i][j] == kPoint) {
						CObject *point = new CObject();
						point->GetTransform()->y = i * al_get_bitmap_height(m_pointImage);
						point->GetTransform()->x = i * al_get_bitmap_width(m_pointImage);

						point->AddComponent<CSprite>()->SetSprite(m_pointImage);
						point->AddComponent<CCollision>();
						m_objects.push_back(point);
					}
				}
			}
			CObject *pacmanManager = new CObject;
			m_pacman = pacmanManager->AddComponent<CPacman>();
			m_pacmanImage = gImageManager.GetImage("deadpac.png");
			m_pacman->SetSprite(m_pacmanImage);
			m_objects.push_back(pacmanManager);

			for (int i = 0; i < kGhostNumber; i++) {
				CObject *ghostManager = new CObject();
				CGhost *ghost = ghostManager->AddComponent<CGhost>();
				ghost->SetVector(&m_objects);
				m_objects.push_back(ghostManager);
				m_ghosts.push_back(ghost);

				m_ghostImage = gImageManager.GetImage("ghost.png");
				ghostManager->AddComponent<CSprite>()->SetSprite(m_ghostImage);

				ghostManager->GetTransform()->x = kDisplayWidth / 2 + i * 50;
				ghostManager->GetTransform()->y = kDisplayHeight / 2;

				gControllManager.RegisterListener(ghost);
			}

			CObject *speedManager = new CObject();
			speedManager->AddComponent<CSpeed>();
			m_speedImage = gImageManager.GetImage("cherry.png");
			speedManager->AddComponent<CSprite>()->SetSprite(m_speedImage);
			speedManager->GetTransform()->x = 16;
			speedManager->GetTransform()->y = 55;
			m_objects.push_back(speedManager);
		}
		else {
			throw kAllegroImageInitError;
		}
	}
	catch(std::string _exception) {
		std::cout << _exception << std::endl;
	}


	/*
	speedManager = new CObject();
	speedManager->AddComponent<CSpeed>();
	speedManager->GetComponent<CSprite>()->SetSprite(speedImage);
	speedManager->GetTransform()->x = kDisplayWidth/2;
	speedManager->GetTransform()->y = 174;
	m_objects.push_back(speedManager);
	*/
	
}

void CSceneManager::Update() {
	for (int i = 0; i < m_objects.size(); i++) {
		m_objects[i]->Update();
	}
}

void CSceneManager::Render() {
	al_clear_to_color(al_map_rgb(0, 0, 0));

	for (int i = 0; i < m_objects.size(); i++) {
		std::cout << "CSceneManager Render()" << std::endl;
		m_objects[i]->Render();
	}

	al_flip_display(); // 화면에 적용
}

int CSceneManager::RemoveObject(CObject *_object) {
	for (int i = 0; m_objects.size(); i++) {
		if (m_objects[i] == _object) {
			m_objects.erase(m_objects.begin() + i);
			return 1;
		}
	}
	delete _object;
	return 0;
}