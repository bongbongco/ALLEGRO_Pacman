#include "ControllManager.h"

void CControllManager::HandleEvent(ALLEGRO_EVENT _event) {
	int i = 0;
//	for (int i = 0; i < m_listeners.size(); i++) {
		switch (_event.keyboard.keycode) {
		case ALLEGRO_KEY_W: // 위로 
			std::cout << "W" << std::endl;
			m_listeners[i]->Up();
			break;
		case ALLEGRO_KEY_S: // 아래로
			std::cout << "S" << std::endl;
			m_listeners[i]->Down();
			break;
		case ALLEGRO_KEY_A: // 왼쪽으로
			std::cout << "A" << std::endl;
			m_listeners[i]->Left();
			break;
		case ALLEGRO_KEY_D: // 오른쪽으로
			std::cout << "D" << std::endl;
			m_listeners[i]->Right();
			break;
		}
	//}

}