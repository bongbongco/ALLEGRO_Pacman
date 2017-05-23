#include "Rocket.h"


void CRocket::SetSpeed(int _speed) {
	m_speed = _speed;
}

void CRocket::SetVector(std::vector<CObject *> *_object) {
	m_otherObject = _object;
}

void CRocket::SetDirection(Direction _direction) {
	m_direction = _direction;
}

std::pair<int, int> CRocket::GetPrevLocation() {
	return std::make_pair(m_prevX, m_prevY);
}

Direction CRocket::GetDirection() {
	return m_direction;
}

void CRocket::SetNode(CNode *_telescope) {
	m_telescope = _telescope;
	std::vector<CNode *> node;

	CTransform *transform = GetObject()->GetTransform();
	int sourceX = transform->x/kTileWidth;
	int sourceY = transform->y/kTileHeight;
	
	if (m_telescope != NULL) {
		CNode *child;

		while (m_telescope->m_parent != NULL) {
			child = m_telescope;
			m_telescope = m_telescope->m_parent; // ���� ������ ���� ����
			if (m_telescope->m_x == sourceX && m_telescope->m_y == sourceY) {
				int targetX = child->m_x;
				int targetY = child->m_y;

				if (targetX - sourceX > 0) {
					m_direction = E;
				}
				else if (targetX - sourceX < 0) {
					m_direction = W;
				}
				else if (targetY - sourceY > 0) {
					m_direction = S;
				}
				else if (targetY - sourceY < 0) {
					m_direction = N;
				}
			}
		}
	}
}

int CRocket::Move(int _x, int _y) {
	CTransform *transform = GetObject()->GetTransform();
	m_prevX = transform->x;
	m_prevY = transform->y;
	
	int x = transform->x + _x * m_speed;
	int y = transform->y + _y * m_speed;

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
		}
	}

	transform->x += _x;
	transform->y += _y;
	return 1;
}

void CRocket::Update() {
	CTransform *transform = GetObject()->GetTransform();

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