#include "ControllManager.h"

void CControllManager::HandleEvent(ALLEGRO_EVENT _event) {
	int i = 0;
//	for (int i = 0; i < m_listeners.size(); i++) {
		switch (_event.keyboard.keycode) {
		case ALLEGRO_KEY_W: // ���� 
			std::cout << "W" << std::endl;
			m_listeners[i]->Up();
			break;
		case ALLEGRO_KEY_S: // �Ʒ���
			std::cout << "S" << std::endl;
			m_listeners[i]->Down();
			break;
		case ALLEGRO_KEY_A: // ��������
			std::cout << "A" << std::endl;
			m_listeners[i]->Left();
			break;
		case ALLEGRO_KEY_D: // ����������
			std::cout << "D" << std::endl;
			m_listeners[i]->Right();
			break;
		}
	//}

}