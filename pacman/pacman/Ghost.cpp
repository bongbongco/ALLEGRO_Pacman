#include "Ghost.h"
#include "GameManager.h"

static CGameManager gGameManager;

void CGhost::SetVector(std::vector<CObject *> *_object) {
	m_otherObject = _object;
}

int CGhost::Move(int _x, int _y) {
	_x *= m_speedMod;
	_y *= m_speedMod;
	
	CTransform *transform = this->GetObject()->GetTransform();

	int x = transform->x + _x;
	int y = transform->y + _y;

	for (int i = 0; i < m_otherObject->size(); i++) {
		if ((*m_otherObject)[i] == m_object) { // ���� ��ü�� ������ ��� 
			continue;
		}
		CTransform * otherTransform = m_otherObject->at(i)->GetTransform();

		if ((x + transform->x > otherTransform->x) &&
			(x < otherTransform->x + otherTransform->width) &&
			(y + transform->y > otherTransform->y) &&
			(y < otherTransform->y + otherTransform->height)
			) {

			if ((*m_otherObject)[i]->GetComponent<CCollision>()) {
				return 0;
			}
			else { // �浹�� �־��ٸ�
				CPacman *pacman = (*m_otherObject)[i]->GetComponent<CPacman>();
				if (pacman) { // �Ѹǰ��� �浹�̾��ٸ�
					ALLEGRO_BITMAP *pacmanImage = pacman->GetSprite();
					(*m_otherObject)[i]->RemoveComponent<CPacman>(pacman);
					m_object->AddComponent<CPacman>()->SetSprite(pacmanImage);

					CGhost *otherGhost = (*m_otherObject)[i]->GetComponent<CGhost>();
					if (otherGhost) {
						otherGhost->Stun();
					}
				}
			}

			CPoint *point = m_otherObject->at(i)->GetComponent<CPoint>();

			if (point && this->GetObject()->GetComponent<CPacman>()) {
				CObject *pointManager = m_otherObject->at(i);
				gGameManager.GetSceneManager()->RemoveObject(pointManager);// ����Ʈ ����
				m_score++;
				std::cout << m_score << std::endl;
			}

			CSpeed *speed = m_otherObject->at(i)->GetComponent<CSpeed>();

			if (speed) {
				CObject *speedManager = m_otherObject->at(i);
				gGameManager.GetSceneManager()->RemoveObject(speedManager);
				Boost(speed);
			}
		}
	}

	transform->x += _x;
	transform->y += _y;
	return 1;
}

void CGhost::Stun() {
	m_stunFrames = kStunDuration;
}

void CGhost::Boost(CSpeed *_speed) {
	m_speedMod = _speed->m_speed;
	m_speedBoostFrames = _speed->m_duration;
}

void CGhost::Update() {
	CTransform *transform = this->GetObject()->GetTransform();

	m_speedBoostFrames--;
	if (m_speedBoostFrames <= 0) { // �ν��� ��� ����
		m_speedMod = 1;
	}

	if (m_stunFrames > 0) {
		m_stunFrames--; // ���� ���� ��� ���� �Ⱓ ���� 
	}
	else { // ���� ���� �ƴ� ��� ������
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