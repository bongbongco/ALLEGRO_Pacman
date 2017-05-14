#include "SceneManager.h"


static CMapManager gMapManager;
static CImageManager gImageManager;

void CSceneManager::Init() {
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

						std::cout << "벽 "; // 테스트 코드
						std::cout << "y : " << tile->GetTransform()->y; // 테스트 코드
						std::cout << ", x : "<< tile->GetTransform()->x << std::endl; // 테스트 코드
						
						tile->AddCompont<CSprite>()->SetSprite(m_tileImage);
						tile->AddCompont<CCollision>();
						m_objects.push_back(tile);
					}
					else if (m_blueprint[i][j] == kPoint) {
						CObject *point = new CObject();
						point->GetTransform()->y = i * al_get_bitmap_height(m_pointImage);
						point->GetTransform()->x = i * al_get_bitmap_width(m_pointImage);

						std::cout << "포인트"; // 테스트 코드
						std::cout << "y : " << point->GetTransform()->y; // 테스트 코드
						std::cout << ", x : " << point->GetTransform()->x << std::endl; // 테스트 코드

						point->AddCompont<CSprite>()->SetSprite(m_pointImage);
						point->AddCompont<CCollision>();
						m_objects.push_back(point);
					}
				}
			}
			CObject *pacmanManager = new CObject;
			m_pacman = pacmanManager->AddCompont<CPacman>();
			m_pacmanImage = gImageManager.GetImage("deadpac.png");
			m_pacman->SetSprite(m_pacmanImage);
			m_objects.push_back(pacmanManager);
		}
		else {
			throw kAllegroImageInitError;
		}

		for (int i = 0; i < kGhostNumber; i++) {
			CObject *ghostManager = new CObject();
			
		}


	}
	catch(std::string _exception) {
		std::cout << _exception << std::endl;
	}
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