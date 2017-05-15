#include "SceneManager.h"


static CMapManager gMapManager;
static CImageManager gImageManager;
static CControllManager gControllManager;

void CSceneManager::Init() {
	std::cout << "SceneManager initialize" << std::endl;
	try {
		if (al_init_image_addon()) {// �̹��� �߰� ��� �ʱ�ȭ
			m_blueprint = gMapManager.LoadLevel("level1.txt"); // ���赵 ����

			m_tileImage = gImageManager.GetImage("tile.png"); // Ÿ�� �̹���
			m_pointImage = gImageManager.GetImage("point.png"); // ����Ʈ �̹���

			for (int i = 0; i < kTileY; i++) {
				for (int j = 0; j < kTileX; j++) {
					if (m_blueprint[i][j] == kWall) {
						CObject *tile = new CObject();
						tile->GetTransform()->y = i * al_get_bitmap_height(m_tileImage);
						tile->GetTransform()->x = j * al_get_bitmap_width(m_tileImage);

						std::cout << "�� "; // �׽�Ʈ �ڵ�
						std::cout << "y : " << tile->GetTransform()->y; // �׽�Ʈ �ڵ�
						std::cout << ", x : "<< tile->GetTransform()->x << std::endl; // �׽�Ʈ �ڵ�
						
						tile->AddCompont<CSprite>()->SetSprite(m_tileImage);
						tile->AddCompont<CCollision>();
						m_objects.push_back(tile);
					}
					else if (m_blueprint[i][j] == kPoint) {
						CObject *point = new CObject();
						point->GetTransform()->y = i * al_get_bitmap_height(m_pointImage);
						point->GetTransform()->x = i * al_get_bitmap_width(m_pointImage);

						std::cout << "����Ʈ"; // �׽�Ʈ �ڵ�
						std::cout << "y : " << point->GetTransform()->y; // �׽�Ʈ �ڵ�
						std::cout << ", x : " << point->GetTransform()->x << std::endl; // �׽�Ʈ �ڵ�

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
			CGhost *ghost = ghostManager->AddCompont<CGhost>();
			ghost->SetVector(&m_objects);
			m_objects.push_back(ghostManager);
			m_ghosts.push_back(ghost);

			if (al_init_image_addon()) { //
				ALLEGRO_BITMAP *ghostImage = gImageManager.GetImage("ghost.png");
				ghostManager->AddCompont<CSprite>()->SetSprite(ghostImage);

				ghostManager->GetTransform()->x = kDisplayWidth / 2 + i * 50;
				ghostManager->GetTransform()->y = kDisplayHeight / 2;
			}
			gControllManager.RegisterListener(ghost);
		}


	}
	catch(std::string _exception) {
		std::cout << _exception << std::endl;
	}

	CObject *speedManager = new CObject();
	speedManager->AddCompont<CSpeed>();
	ALLEGRO_BITMAP *speedImage = gImageManager.GetImage("cherry.png");
	speedManager->AddCompont<CSprite>()->SetSprite(speedImage);
	speedManager->GetTransform()->x = 16;
	speedManager->GetTransform()->y = 55;
	m_objects.push_back(speedManager);

	speedManager = new CObject();
	speedManager->AddCompont<CSpeed>();
	speedManager->GetComponent<CSprite>()->SetSprite(speedImage);
	speedManager->GetTransform()->x = kDisplayWidth/2;
	speedManager->GetTransform()->y = 174;
	m_objects.push_back(speedManager);
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

	al_flip_display(); // ȭ�鿡 ����
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