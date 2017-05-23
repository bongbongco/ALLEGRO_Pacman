#include "Pika.h"
#include "GameManager.h"


void CPika::Respawn() { // 포인트 재생성
	for (int i = 0; i < m_otherObject->size(); i++) {
		CPoint *point = m_otherObject->at(i)->GetComponent<CPoint>();
		if (point) {
			CObject *pointManager = m_otherObject->at(i);
			point->state = true;
			StateUpdate(COIN, pointManager->GetComponent<CSprite>());
		}

		CSpeed *speed = m_otherObject->at(i)->GetComponent<CSpeed>();
		if (speed) {
			CObject *speedManager = m_otherObject->at(i);
			speed->state = true;
			StateUpdate(BOOST, speedManager->GetComponent<CSprite>());
		}
	}
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
				if (!point->state) {
					continue;
				}
				CObject *pointManager = m_otherObject->at(i);
				point->state = false;
				StateUpdate(BLANK, pointManager->GetComponent<CSprite>());
				
				m_score += 10;
				if (m_score%1050 == 0) { // 모든 포인트 획득 시
					Respawn();
				}
				CSprite *sprite = GetObject()->GetComponent<CSprite>();
				sprite->SetScore(m_score); // 화면에 점수 반영
			}

			CSpeed *speed = m_otherObject->at(i)->GetComponent<CSpeed>();

			if (speed) { // 부스터
				if (!speed->state) {
					continue;
				}
				CObject *speedManager = m_otherObject->at(i);
				speed->state = false;
				StateUpdate(BLANK, speedManager->GetComponent<CSprite>());
				Boost();
			}
		}
	}

	transform->x += _x;
	transform->y += _y;
	return 1;
}

void CPika::StateUpdate(State _state, CSprite *_sprite) { // 캐릭터 상태 변경 및 슬라이드 애니메이션 효과
	std::string ImagePath;
	if (_state == ZZZ || _state == SPEED) {
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
	case BLANK:
		ImagePath = "resource/blank.png";
		break;
	case COIN:
		ImagePath = "resource/pokecoin.png";
		break;
	case BOOST:
		ImagePath = "resource/razz-berry.png";
		break;
	}
	ALLEGRO_BITMAP *Image = CImageManager::Instance().GetImage(ImagePath.c_str());
	al_convert_mask_to_alpha(Image, al_map_rgb(255, 255, 255));
	_sprite->SetSprite(Image);
}

void CPika::Stun() { // 스턴 시작
	m_boostFlag = false;
	m_speedBoostFrames = 0;
	m_speedMod = 2; // Boost Mode 종료
	m_stunFlag = true;
	m_stunFrames = kStunDuration;
	StateUpdate(ZZZ, GetObject()->GetComponent<CSprite>());
}

void CPika::Boost() { // 부스터 모드 시작
	m_boostFlag = true;
	m_speedMod = kBoostMod;
	m_speedBoostFrames = kBoostDuration;
	StateUpdate(SPEED, GetObject()->GetComponent<CSprite>());
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
		StateUpdate(NORMAL, GetObject()->GetComponent<CSprite>());
	}

	if (m_stunFrames >= 150) {
		m_stunFrames--; // 스턴 중일 경우 스턴 기간 감소 
		if (m_stunFrames == 150) {
			StateUpdate(GRACE, GetObject()->GetComponent<CSprite>());
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
			StateUpdate(NORMAL, GetObject()->GetComponent<CSprite>());
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