#include "Pika.h"
#include "GameManager.h"

void CPika::HealthCheck() {
	if (m_life == 0) {
		CGameManager::Instance().End();
	}
}

void CPika::SetVector(std::vector<CObject *> *_object) {
	m_otherObject = _object;
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

			if ((*m_otherObject)[i]->GetComponent<CSolid>()) {
				return 0; // 벽
			}
			else {
				CRocket *rocket = (*m_otherObject)[i]->GetComponent<CRocket>();
				if (rocket) { // 로켓단과의 충돌 시 스턴 발생
					Stun();
					m_life -= 1;
					CSprite *sprite = GetObject()->GetComponent<CSprite>();
					sprite->SetLife(m_life);
					HealthCheck();
				}
			}

			CPoint *point = m_otherObject->at(i)->GetComponent<CPoint>();

			if (point) {
				CObject *pointManager = m_otherObject->at(i);
				CGameManager::Instance().GetSceneManager()->RemoveObject(pointManager); // 포인트 제거
				m_otherObject->erase(m_otherObject->begin() + i);
				m_score += 10;
				CSprite *sprite = GetObject()->GetComponent<CSprite>();
				sprite->SetScore(m_score);
			}

			CSpeed *speed = m_otherObject->at(i)->GetComponent<CSpeed>();

			if (speed) {
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

void CPika::StateUpdate(State _state) {
	std::string ImagePath;
	if (_state != NORMAL) {
		ALLEGRO_BITMAP *slideAnimation = al_load_bitmap((_state == ZZZ) ? "slide2.png" : "slide1.png");
		for (int i = 1088; i > -544;) {
			al_draw_bitmap(slideAnimation, i, 0, 0);
			al_flip_display();
			i -= 4;
		}
	}
	switch (_state) {
	case NORMAL:
		ImagePath = "pikachu.png";
		break;
	case ZZZ:
		ImagePath = "zzz.png";
		break;
	case SPEED: 
		ImagePath = "speed.png";
		break;
	}
	CSprite *sprite = GetObject()->GetComponent<CSprite>();
	ALLEGRO_BITMAP *pikaImage = CImageManager::Instance().GetImage(ImagePath.c_str());
	al_convert_mask_to_alpha(pikaImage, al_map_rgb(255, 255, 255));
	sprite->SetSprite(pikaImage);
}

void CPika::Stun() {
	m_boostFlag = false;
	m_speedBoostFrames = 0;
	m_speedMod = 2; // Boost Mode 종료
	m_stunFlag = true;
	m_stunFrames = kStunDuration;
	StateUpdate(ZZZ);
}

void CPika::Boost() {
	m_boostFlag = true;
	m_speedMod = kBoostMod;
	m_speedBoostFrames = kBoostDuration;
	StateUpdate(SPEED);
}

void CPika::Update() {
	CTransform *transform = GetObject()->GetTransform();
	SetDirectionRocket(transform->x, transform->y);

	if (m_speedBoostFrames > 0) {
		m_speedBoostFrames--;
	}
	else if (m_boostFlag && m_speedBoostFrames == 0) { // 부스터 모드 종료
		m_boostFlag = false;
		m_speedBoostFrames = 0;
		m_speedMod = 2;
		StateUpdate(NORMAL);
	}

	if (m_stunFrames > 0) {
		m_stunFrames--; // 스턴 중일 경우 스턴 기간 감소 
	}
	else { // 스턴 중이 아닐 경우 움직임
		if (m_stunFlag && m_stunFrames == 0) {
			m_stunFrames = 0;
			m_stunFlag = false;
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

void CPika::SetDirectionRocket(int _x, int _y) {
	for (int i = 0; i < m_otherObject->size(); i++) {
		CRocket *rocket = (*m_otherObject)[i]->GetComponent<CRocket>();
		if (rocket) {
			CTransform *rocketTransform = rocket->GetObject()->GetTransform();
			rocket->SetNode(CNode::Instance().FindPath((*m_otherObject)[i]->GetTransform()->x, (*m_otherObject)[i]->GetTransform()->y, _x, _y));
			rocket->Update();
		}
	}
}