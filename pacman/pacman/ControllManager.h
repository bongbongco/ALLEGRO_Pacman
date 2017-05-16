#pragma once
#include "allegro5\allegro.h"
#include <iostream> 
#include <vector>
#include "ControllListener.h"

class CControllManager {
private:
	std::vector<CControllListener *> m_listeners;
	bool m_controllerIn;

public:
	static CControllManager& Instance() {
		static CControllManager gInstance;
		return gInstance;
	}
	void HandleEvent(ALLEGRO_EVENT _event);
	void RegisterListener(CControllListener *_listener) {
		m_listeners.push_back(_listener);
	}
};