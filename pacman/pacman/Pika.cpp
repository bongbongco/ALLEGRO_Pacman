#include "Pika.h"
#include "GameManager.h"



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
					Stun();
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
		ALLEGRO_BITMAP *slideAnimation = al_load_bitmap((_state==ZZZ) ? "slide2.png":"slide1.png");
		for (int i = 1088; i > -544;) {
			al_draw_bitmap(slideAnimation, i, 0, 0);
			al_flip_display();
			i -= 26;
		}
}

void CPika::Stun() {
	m_boostFlag = false;
	m_speedBoostFrames = 0;
	m_speedMod = 1; // Boost Mode ����
	m_stunFlag = true;
	m_stunFrames = kStunDuration;
	StateUpdate(ZZZ);
	CSprite *sprite = GetObject()->GetComponent<CSprite>();
	ALLEGRO_BITMAP *pikaImage = CImageManager::Instance().GetImage("zzz.png");
	al_convert_mask_to_alpha(pikaImage, al_map_rgb(255, 255, 255));
	sprite->SetSprite(pikaImage);
	al_flip_display();
}

void CPika::Boost() {
	m_boostFlag = true;
	m_speedMod = kBoostMod;
	m_speedBoostFrames = kBoostDuration;
	StateUpdate(SPEED);
	CSprite *sprite = GetObject()->GetComponent<CSprite>();
	ALLEGRO_BITMAP *pikaImage = CImageManager::Instance().GetImage("speed.png");
	al_convert_mask_to_alpha(pikaImage, al_map_rgb(255, 255, 255));
	sprite->SetSprite(pikaImage);
	al_flip_display();
}

void CPika::Update() {
	CTransform *transform = GetObject()->GetTransform();

	if (m_speedBoostFrames > 0) {
		m_speedBoostFrames--;
	}
	else if (m_boostFlag && m_speedBoostFrames == 0) { // �ν��� ��� ����
		m_boostFlag = false;
		m_speedBoostFrames = 0;
		m_speedMod = 1;
		CSprite *sprite = GetObject()->GetComponent<CSprite>();
		ALLEGRO_BITMAP *pikaImage = CImageManager::Instance().GetImage("pikachu.png");
		al_convert_mask_to_alpha(pikaImage, al_map_rgb(255, 255, 255));
		sprite->SetSprite(pikaImage);
		al_flip_display();
	}

	if (m_stunFrames > 0) {
		m_stunFrames--; // ���� ���� ��� ���� �Ⱓ ���� 
	}
	else { // ���� ���� �ƴ� ��� ������
		if (m_stunFlag && m_stunFrames == 0) {
			m_stunFrames = 0;
			m_stunFlag = false;
			CSprite *sprite = GetObject()->GetComponent<CSprite>();
			ALLEGRO_BITMAP *pikaImage = CImageManager::Instance().GetImage("pikachu.png");
			al_convert_mask_to_alpha(pikaImage, al_map_rgb(255, 255, 255));
			sprite->SetSprite(pikaImage);
			al_flip_display();
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