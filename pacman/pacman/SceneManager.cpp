#include "SceneManager.h"
#include "ControllManager.h"
#include "MapManager.h"
#include "ImageManager.h"



void CSceneManager::Init() {
	ALLEGRO_BITMAP *tileImage;
	ALLEGRO_BITMAP *pointImage;
	ALLEGRO_BITMAP *rocketImage;
	ALLEGRO_BITMAP *pikaImage;
	ALLEGRO_BITMAP *speedImage;

	m_rocketImageName.push_back("resource/rosa.png"); // 로켓단 - 로사
	m_rocketImageName.push_back("resource/roy.png"); // 로켓단 - 로이
	m_rocketImageName.push_back("resource/cat.png"); // 로켓단 - 고양이

	try {
		if (al_init_image_addon()) {// 이미지 추가 기능 초기화 
			m_blueprint = CMapManager::Instance().LoadLevel("resource/level1.txt"); // 설계도 생성
			CNode::Instance().SetBlueprint(m_blueprint); // 길 찾기를 위해 노드 객체에 설계도 저장

			tileImage = CImageManager::Instance().GetImage("resource/puzzle.png"); // 타일 이미지
			pointImage = CImageManager::Instance().GetImage("resource/pokecoin.png"); // 포인트 이미지

			for (int i = 0; i < kTileY; i++) { // 맵 생성. i 는 y축, j는 x축
				for (int j = 0; j < kTileX; j++) {
					if (m_blueprint[i][j] == kWall) { // 벽
						CObject *tile = new CObject();
						tile->GetTransform()->y = i * al_get_bitmap_height(tileImage);
						tile->GetTransform()->x = j * al_get_bitmap_width(tileImage);

						tile->AddComponent<CSprite>()->SetSprite(tileImage);
						tile->AddComponent<CSolid>();
						m_objects.push_back(tile);
					}
					else if (m_blueprint[i][j] == kPoint) { // 포인트
						CObject *pointManager = new CObject();
						pointManager->AddComponent<CPoint>();
						
						pointManager->AddComponent<CSprite>()->SetSprite(pointImage);
						pointManager->GetTransform()->y = i * al_get_bitmap_height(pointImage);
						pointManager->GetTransform()->x = j * al_get_bitmap_width(pointImage);
						m_objects.push_back(pointManager);
					}
				}
			}

			CObject *speedManager = new CObject(); // 스피드 업 생성
			speedManager->AddComponent<CSpeed>();
			speedImage = CImageManager::Instance().GetImage("resource/razz-berry.png");
			speedManager->AddComponent<CSprite>()->SetSprite(speedImage);
			speedManager->GetTransform()->x = 64;
			speedManager->GetTransform()->y = 64;
			m_objects.push_back(speedManager);

			speedManager = new CObject(); // 스피드 업 생성
			speedManager->AddComponent<CSpeed>();
			speedManager->AddComponent<CSprite>()->SetSprite(speedImage);
			speedManager->GetTransform()->x = kDisplayWidth / 2;
			speedManager->GetTransform()->y = 256;
			m_objects.push_back(speedManager);

			for (int i = 1; i <= kRocketNumber; i++) { // 로켓단 생성
				CObject *rocketManager = new CObject;
				CRocket *rocket = rocketManager->AddComponent<CRocket>();
				rocket->SetLabel(i);
				rocket->SetVector(&m_objects);
				rocket->SetSpeed(i);

				rocketImage = CImageManager::Instance().GetImage(m_rocketImageName.at(i-1));
				al_convert_mask_to_alpha(rocketImage, al_map_rgb(255, 255, 255));
				rocketManager->AddComponent<CSprite>()->SetSprite(rocketImage);
				
				rocketManager->GetTransform()->x = kDisplayWidth  - (i*256);
				rocketManager->GetTransform()->y = 128 * i;
				
				rocket->SetNode(CNode::Instance().FindPath(rocketManager->GetTransform()->x,
					rocketManager->GetTransform()->y, kDisplayWidth / 4, kDisplayHeight / 4, true));
				m_objects.push_back(rocketManager);
			}

			CObject *pikaManager = new CObject(); // 피카츄 생성
			m_pika = pikaManager->AddComponent<CPika>();
			m_pika->SetVector(&m_objects);
			m_objects.push_back(pikaManager);

			pikaImage = CImageManager::Instance().GetImage("resource/pikachu.png");
			pikaManager->AddComponent<CSprite>()->SetSprite(pikaImage);
			pikaManager->GetComponent<CSprite>()->SetText("Player");
			pikaManager->GetTransform()->x = 64;
			pikaManager->GetTransform()->y = 128;

			CControllManager::Instance().RegisterListener(m_pika);

		}
		else {
			throw kAllegroImageInitError;
		}
	}
	catch(std::string _exception) {
		std::cout << _exception << std::endl;
	}
}

void CSceneManager::Update() {
	for (int i = 0; i < m_objects.size(); i++) {
		if(i==151)
			m_objects[i]->Update();
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

int CSceneManager::RemoveObject(CObject *_object) { // 피카츄와 충돌에 의한 오브젝트 제거
	for (int i = 0; m_objects.size(); i++) {
		if (m_objects[i] == _object) {
			m_objects.erase(m_objects.begin() + i);
			return 1;
		}
	}
	delete _object;
	return 0;
}

int **CSceneManager::GetBlueprint() { // 설계도 반환
	return m_blueprint;
}