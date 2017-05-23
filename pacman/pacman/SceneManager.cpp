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

	m_rocketImageName.push_back("resource/rosa.png"); // ���ϴ� - �λ�
	m_rocketImageName.push_back("resource/roy.png"); // ���ϴ� - ����
	m_rocketImageName.push_back("resource/cat.png"); // ���ϴ� - �����

	try {
		if (al_init_image_addon()) {// �̹��� �߰� ��� �ʱ�ȭ 
			m_blueprint = CMapManager::Instance().LoadLevel("resource/level1.txt"); // ���赵 ����
			CNode::Instance().SetBlueprint(m_blueprint); // �� ã�⸦ ���� ��� ��ü�� ���赵 ����

			tileImage = CImageManager::Instance().GetImage("resource/puzzle.png"); // Ÿ�� �̹���
			pointImage = CImageManager::Instance().GetImage("resource/pokecoin.png"); // ����Ʈ �̹���

			for (int i = 0; i < kTileY; i++) { // �� ����. i �� y��, j�� x��
				for (int j = 0; j < kTileX; j++) {
					if (m_blueprint[i][j] == kWall) { // ��
						CObject *tile = new CObject();
						tile->GetTransform()->y = i * al_get_bitmap_height(tileImage);
						tile->GetTransform()->x = j * al_get_bitmap_width(tileImage);

						tile->AddComponent<CSprite>()->SetSprite(tileImage);
						tile->AddComponent<CSolid>();
						m_objects.push_back(tile);
					}
					else if (m_blueprint[i][j] == kPoint) { // ����Ʈ
						CObject *pointManager = new CObject();
						pointManager->AddComponent<CPoint>();
						
						pointManager->AddComponent<CSprite>()->SetSprite(pointImage);
						pointManager->GetTransform()->y = i * al_get_bitmap_height(pointImage);
						pointManager->GetTransform()->x = j * al_get_bitmap_width(pointImage);
						m_objects.push_back(pointManager);
					}
				}
			}

			CObject *speedManager = new CObject(); // ���ǵ� �� ����
			speedManager->AddComponent<CSpeed>();
			speedImage = CImageManager::Instance().GetImage("resource/razz-berry.png");
			speedManager->AddComponent<CSprite>()->SetSprite(speedImage);
			speedManager->GetTransform()->x = 64;
			speedManager->GetTransform()->y = 64;
			m_objects.push_back(speedManager);

			speedManager = new CObject(); // ���ǵ� �� ����
			speedManager->AddComponent<CSpeed>();
			speedManager->AddComponent<CSprite>()->SetSprite(speedImage);
			speedManager->GetTransform()->x = kDisplayWidth / 2;
			speedManager->GetTransform()->y = 256;
			m_objects.push_back(speedManager);

			for (int i = 1; i <= kRocketNumber; i++) { // ���ϴ� ����
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

			CObject *pikaManager = new CObject(); // ��ī�� ����
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
	al_flip_display(); // ȭ�鿡 ����
}

int CSceneManager::RemoveObject(CObject *_object) { // ��ī��� �浹�� ���� ������Ʈ ����
	for (int i = 0; m_objects.size(); i++) {
		if (m_objects[i] == _object) {
			m_objects.erase(m_objects.begin() + i);
			return 1;
		}
	}
	delete _object;
	return 0;
}

int **CSceneManager::GetBlueprint() { // ���赵 ��ȯ
	return m_blueprint;
}