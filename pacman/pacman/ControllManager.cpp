#include "ControllManager.h"

void CControllManager::HandleEvent(ALLEGRO_EVENT _event) {

	for (int i = 0; i < m_listeners.size(); i++) {
		switch (_event.keyboard.keycode) {
		case ALLEGRO_KEY_W: // ���� 
			m_listeners[i]->Up();
			break;
		case ALLEGRO_KEY_S: // �Ʒ���
			m_listeners[i]->Down();
			break;
		case ALLEGRO_KEY_A: // ��������
			m_listeners[i]->Left();
			break;
		case ALLEGRO_KEY_D: // ����������
			m_listeners[i]->Right();
			break;
		}
	}

}