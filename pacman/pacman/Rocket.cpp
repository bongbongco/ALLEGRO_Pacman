#include "Rocket.h"

void CRocket::Move(int _x, int _y) {
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


			CPoint *point = m_otherObject->at(i)->GetComponent<CPoint>();

			if (point) {
				CObject *pointManager = m_otherObject->at(i);
				CGameManager::Instance().GetSceneManager()->RemoveObject(pointManager); // 포인트 제거
				m_otherObject->erase(m_otherObject->begin() + i);
				m_score++;
				std::cout << m_score << std::endl;
			}

			CSpeed *speed = m_otherObject->at(i)->GetComponent<CSpeed>();

			if (speed) {
				CObject *speedManager = m_otherObject->at(i);
				CGameManager::Instance().GetSceneManager()->RemoveObject(speedManager); // 스피드 업 제거
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
	// 길찾기 로직 추가
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