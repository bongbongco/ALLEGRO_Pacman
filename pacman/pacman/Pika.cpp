#include "Pika.h"
#include "GameManager.h"


void CPika::Respawn() { // 포인트 재생성
	int **blueprint = CSceneManager::Instance().GetBlueprint(); // 설계도 불러오기

	for (int i = 0; i < kTileY; i++) { // 맵 생성. i 는 y축, j는 x축
		for (int j = 0; j < kTileX; j++) {
			if (blueprint[i][j] == kPoint) {  // 포인트
				CObject *pointManager = new CObject();
				pointManager->AddComponent<CPoint>();

				pointManager->AddComponent<CSprite>()->SetSprite(CImageManager::Instance().GetImage("resource/pokecoin.png"));
				pointManager->GetTransform()->y = i * 64;
				pointManager->GetTransform()->x = j * 64;
				CSceneManager::Instance().CreateObject(pointManager);
			}
		}
	}
	CObject *speedManager = new CObject(); // 스피드 업 생성
	speedManager->AddComponent<CSpeed>();
	speedManager->AddComponent<CSprite>()->SetSprite(CImageManager::Instance().GetImage("resource/razz-berry.png"));
	speedManager->GetTransform()->x = 64;
	speedManager->GetTransform()->y = 64;
	CSceneManager::Instance().CreateObject(speedManager);

	speedManager = new CObject(); // 스피드 업 생성
	speedManager->AddComponent<CSpeed>();
	speedManager->AddComponent<CSprite>()->SetSprite(CImageManager::Instance().GetImage("resource/razz-berry.png"));
	speedManager->GetTransform()->x = kDisplayWidth / 2;
	speedManager->GetTransform()->y = 256;
	CSceneManager::Instance().CreateObject(speedManager);
}

void CPika::SetVector(std::vector<CObject *> *_object) {
	m_otherObject = _object; // 오브젝트 정보
}

int CPika::Move(int _x, int _y) {
	_x *= m_speedMod;
	_y *= m_speedMod;

	CTransform *transform = GetObject()->GetTransform();

	int x = transform->x + _x;
	int y = transform->y + _y;

	for (int i = 0; i < m_otherObject->size(); i++) {
		if ((*m_otherObject)[i] == m_object) { // 비교할 객체가 동일할 경우 
			continue;
		}
		CTransform *otherTransform = m_otherObject->at(i)->GetTransform();

		if ((x + transform->width > otherTransform->x) &&
			(x < otherTransform->x + otherTransform->width) &&
			(y + transform->height > otherTransform->y) &&
			(y < otherTransform->y + otherTransform->height) // 동일 좌표 위에 존재하는 객체 존재 시
			) {

			if ((*m_otherObject)[i]->GetComponent<CSolid>()) { // 벽
				return 0; 
			}
			else {
				CRocket *rocket = (*m_otherObject)[i]->GetComponent<CRocket>();
				if (rocket) { // 로켓단과의 충돌 시 스턴 발생
					if (m_stunFrames > 0) { // 스턴 중에 다시 스턴 발생 방지
						continue;
					}
					Stun();
				}
			}

			CPoint *point = m_otherObject->at(i)->GetComponent<CPoint>();

			if (point) { // 포인트
				CObject *pointManager = m_otherObject->at(i);
				CGameManager::Instance().GetSceneManager()->RemoveObject(pointManager); // 포인트 제거
				m_otherObject->erase(m_otherObject->begin() + i);
				m_score += 10;
				if (m_score%1050 == 0) { // 모든 포인트 획득 시
					Respawn();
				}
				CSprite *sprite = GetObject()->GetComponent<CSprite>();
				sprite->SetScore(m_score); // 화면에 점수 반영
			}

			CSpeed *speed = m_otherObject->at(i)->GetComponent<CSpeed>();

			if (speed) { // 부스터
				CObject *speedManager = m_otherObject->at(i);
				CGameManager::Instance().GetSceneManager()->RemoveObject(speedManager); // 스피드 업 제거
				m_otherObject->erase(m_otherObject->begin() + i);
				Boost();
			}
		}
	}

	transform->x += _x;
	transform->y += _y;
	return 1;
}

void CPika::StateUpdate(State _state) { // 캐릭터 상태 변경 및 슬라이드 애니메이션 효과
	std::string ImagePath;
	if (_state != NORMAL && _state != GRACE) {
		ALLEGRO_BITMAP *slideAnimation = al_load_bitmap((_state == ZZZ) ? "resource/slide2.png" : "resource/slide1.png");
		for (int i = 1088; i > -544;) {
			al_draw_bitmap(slideAnimation, i, 0, 0);
			al_flip_display();
			i -= 4;
		}
	}
	switch (_state) {
	case NORMAL:
		ImagePath = "resource/pikachu.png";
		break;
	case ZZZ:
		ImagePath = "resource/zzz.png";
		break;
	case SPEED:
		ImagePath = "resource/speed.png";
		break;
	case GRACE:
		ImagePath = "resource/pokeball.png";
		break;
	}
	CSprite *sprite = GetObject()->GetComponent<CSprite>();
	ALLEGRO_BITMAP *pikaImage = CImageManager::Instance().GetImage(ImagePath.c_str());
	al_convert_mask_to_alpha(pikaImage, al_map_rgb(255, 255, 255));
	sprite->SetSprite(pikaImage);
}

void CPika::Stun() { // 스턴 시작
	m_boostFlag = false;
	m_speedBoostFrames = 0;
	m_speedMod = 2; // Boost Mode 종료
	m_stunFlag = true;
	m_stunFrames = kStunDuration;
	StateUpdate(ZZZ);
}

void CPika::Boost() { // 부스터 모드 시작
	m_boostFlag = true;
	m_speedMod = kBoostMod;
	m_speedBoostFrames = kBoostDuration;
	StateUpdate(SPEED);
}

void CPika::Update() {
	CTransform *transform = GetObject()->GetTransform();
	SetDirectionRocket(transform->x, transform->y);

	if (m_speedBoostFrames > 0) {
		m_speedBoostFrames--; // 부스터 모드인 경우 부스터 기간 감소
	}
	else if (m_boostFlag && m_speedBoostFrames == 0) { // 부스터 모드 종료
		m_boostFlag = false;
		m_speedBoostFrames = 0;
		m_speedMod = 2;
		StateUpdate(NORMAL);
	}

	if (m_stunFrames >= 150) {
		m_stunFrames--; // 스턴 중일 경우 스턴 기간 감소 
		if (m_stunFrames == 150) {
			StateUpdate(GRACE);
			m_speedMod = kBoostMod;
		}
	}
	else { // 스턴 중이 아닐 경우 움직임
		if (m_stunFrames > 0) {
			m_stunFrames--;
		}
		else if (m_stunFlag && m_stunFrames == 0) {
			m_stunFrames = 0;
			m_stunFlag = false;
			m_speedMod = 2;
			StateUpdate(NORMAL);
		}
		switch (m_direction) {
		case N:
			Move(0, -1);
			break;
		case S:
			Move(0, 1);
			break;
		case W:
			Move(-1, 0);
			break;
		case E:
			Move(1, 0);
			break;
		}

		if (transform->x > kDisplayWidth) { // X 좌표가 화면 크기보다 클 때 반대편으로
			transform->x = 0;
		}
		if (transform->x < 0) { // X 좌표가 0보다 작을 때 반대편으로
			transform->x = kDisplayWidth;
		}
		if (transform->y > kDisplayHeight) { // Y 좌표가 화면 크기보다 클 때 반대편으로
			transform->y = 0;
		}
		if (transform->y < 0) { // Y 좌표가 0보다 작을 때 반대편으로
			transform->y = kDisplayHeight;
		}
	}
}

void CPika::SetDirectionRocket(int _x, int _y) { // 피카츄 움직임에 따른 로켓단 방향 설정
	for (int i = 0; i < m_otherObject->size(); i++) {
		CRocket *rocket = (*m_otherObject)[i]->GetComponent<CRocket>();
		if (rocket) {
			CTransform *rocketTransform = rocket->GetObject()->GetTransform();
			rocket->SetNode(CNode::Instance().FindPath((*m_otherObject)[i]->GetTransform()->x, (*m_otherObject)[i]->GetTransform()->y, _x, _y));
			rocket->Update();
		}
	}
}