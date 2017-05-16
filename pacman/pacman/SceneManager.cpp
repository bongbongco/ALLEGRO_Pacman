#include "SceneManager.h"
#include "ControllManager.h"
#include "MapManager.h"
#include "ImageManager.h"


static CMapManager gMapManager;


void CSceneManager::Init() {
	ALLEGRO_BITMAP *tileImage;
	ALLEGRO_BITMAP *pointImage;
	ALLEGRO_BITMAP *rocketImage;
	ALLEGRO_BITMAP *pikaImage;
	ALLEGRO_BITMAP *speedImage;
	std::cout << "SceneManager initialize" << std::endl;
	try {
		if (al_init_image_addon()) {// 이미지 추가 기능 초기화 
			m_blueprint = gMapManager.LoadLevel("level1.txt"); // 설계도 생성

			tileImage = CImageManager::Instance().GetImage("puzzle.png"); // 타일 이미지
			pointImage = CImageManager::Instance().GetImage("pokecoin.png"); // 포인트 이미지

			for (int i = 0; i < kTileY; i++) {
				for (int j = 0; j < kTileX; j++) {
					if (m_blueprint[i][j] == kWall) {
						CObject *tile = new CObject();
						tile->GetTransform()->y = i * al_get_bitmap_height(tileImage);
						tile->GetTransform()->x = j * al_get_bitmap_width(tileImage);

						tile->AddComponent<CSprite>()->SetSprite(tileImage);
						tile->AddComponent<CSolid>();
						m_objects.push_back(tile);
					}
					else if (m_blueprint[i][j] == kPoint) {
						CObject *pointManager = new CObject();
						pointManager->AddComponent<CPoint>();
						
						pointManager->AddComponent<CSprite>()->SetSprite(pointImage);
						pointManager->GetTransform()->y = i * al_get_bitmap_height(pointImage);
						pointManager->GetTransform()->x = j * al_get_bitmap_width(pointImage);
						m_objects.push_back(pointManager);
						//point->AddComponent<CSolid>();
					}
				}
			}

			for (int i = 1; i <= kRocketNumber; i++) {

				CObject *rocketManager = new CObject;
				CRocket *rocket = rocketManager->AddComponent<CRocket>();
				
				rocketImage = CImageManager::Instance().GetImage("team_rocket.png");
				rocket->SetSprite(rocketImage);
				rocketManager->GetTransform()->x = kDisplayWidth / 5 + i * 128;
				rocketManager->GetTransform()->y = 64;
				m_objects.push_back(rocketManager);
			}

			CObject *pikaManager = new CObject();
			m_pika = pikaManager->AddComponent<CPika>();
			m_pika->SetVector(&m_objects);
			m_objects.push_back(pikaManager);

			pikaImage = CImageManager::Instance().GetImage("pikachu.png");
			pikaManager->AddComponent<CSprite>()->SetSprite(pikaImage);

			pikaManager->GetTransform()->x = kDisplayWidth / 2;
			pikaManager->GetTransform()->y = kDisplayHeight / 2;

			CControllManager::Instance().RegisterListener(m_pika);
			

			CObject *speedManager = new CObject();
			speedManager->AddComponent<CSpeed>();
			speedImage = CImageManager::Instance().GetImage("razz-berry.png");
			speedManager->AddComponent<CSprite>()->SetSprite(speedImage);
			speedManager->GetTransform()->x = 64;
			speedManager->GetTransform()->y = 64;
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