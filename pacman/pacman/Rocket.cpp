#include "Rocket.h"

void CRocket::Move(int _x, int _y) {
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


			CPoint *point = m_otherObject->at(i)->GetComponent<CPoint>();

			if (point) {
				CObject *pointManager = m_otherObject->at(i);
				CGameManager::Instance().GetSceneManager()->RemoveObject(pointManager); // ����Ʈ ����
				m_otherObject->erase(m_otherObject->begin() + i);
				m_score++;
				std::cout << m_score << std::endl;
			}

			CSpeed *speed = m_otherObject->at(i)->GetComponent<CSpeed>();

			if (speed) {
				CObject *speedManager = m_otherObject->at(i);
				CGameManager::Instance().GetSceneManager()->RemoveObject(speedManager); // ���ǵ� �� ����
				m_otherObject->erase(m_otherObject->begin() + i);
				Boost(speed);
			}
		}
	}

	transform->x += _x;
	transform->y += _y;
	return 1;
}

void CRocket::Update() {
	CTransform *transform = GetObject()->GetTransform();
	// ��ã�� ���� �߰�
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