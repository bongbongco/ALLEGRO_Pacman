#include "Object.h"
#include <iostream>

void CObject::Update() {
	for (int i = 0; i < m_components.size(); i++) {
		m_components[i]->Update();
	}
}

void CObject::Render() {
	for (int i = 0; i < m_components.size(); i++) {
		m_components[i]->Render();
	}
}