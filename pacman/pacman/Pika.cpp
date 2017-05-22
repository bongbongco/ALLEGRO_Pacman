#include "Pika.h"
#include "GameManager.h"

void CPika::HealthCheck() {
	if (m_life == 0) {
		CGameManager::Instance().Retry();

	}
}

void CPika::StageClear() {
	//nextgame
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
		if ((*m_otherObject)[i] == m_object) { // ���� ��ü�� ������ ��� 
			continue;
		}
		CTransform *otherTransform = m_otherObject->at(i)->GetTransform();

		if ((x + transform->width > otherTransform->x) &&
			(x < otherTransform->x + otherTransform->width) &&
			(y + transform->height > otherTransform->y) &&
			(y < otherTransform->y + otherTransform->height) // ���� ��ǥ ���� �����ϴ� ��ü ���� ��
			) {

			if ((*m_otherObject)[i]->GetComponent<CSolid>()) {
				return 0; // ��
			}
			else {
				CRocket *rocket = (*m_otherObject)[i]->GetComponent<CRocket>();
				if (rocket) { // ���ϴܰ��� �浹 �� ���� �߻�
					if (m_stunFrames > 0) {
						continue;
					}
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
				CGameManager::Instance().GetSceneManager()->RemoveObject(pointManager); // ����Ʈ ����
				m_otherObject->erase(m_otherObject->begin() + i);
				m_score += 10;
				CSprite *sprite = GetObject()->GetComponent<CSprite>();
				sprite->SetScore(m_score);
			}

			CSpeed *speed = m_otherObject->at(i)->GetComponent<CSpeed>();

			if (speed) {
				CObject *speedManager = m_otherObject->at(i);
				CGameManager::Instance().GetSceneManager()->RemoveObject(speedManager); // ���ǵ� �� ����
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

void CPika::Stun() {
	m_boostFlag = false;
	m_speedBoostFrames = 0;
	m_speedMod = 2; // Boost Mode ����
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
	else if (m_boostFlag && m_speedBoostFrames == 0) { // �ν��� ��� ����
		m_boostFlag = false;
		m_speedBoostFrames = 0;
		m_speedMod = 2;
		StateUpdate(NORMAL);
	}

	if (m_stunFrames >= 150) {
		m_stunFrames--; // ���� ���� ��� ���� �Ⱓ ���� 
		if (m_stunFrames == 150) {
			StateUpdate(GRACE);
			m_speedMod = kBoostMod;
		}
	}
	else { // ���� ���� �ƴ� ��� ������
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

		if (transform->x > kDisplayWidth) { // X ��ǥ�� ȭ�� ũ�⺸�� Ŭ �� �ݴ�������
			transform->x = 0;
		}
		if (transform->x < 0) { // X ��ǥ�� 0���� ���� �� �ݴ�������
			transform->x = kDisplayWidth;
		}
		if (transform->y > kDisplayHeight) { // Y ��ǥ�� ȭ�� ũ�⺸�� Ŭ �� �ݴ�������
			transform->y = 0;
		}
		if (transform->y < 0) { // Y ��ǥ�� 0���� ���� �� �ݴ�������
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