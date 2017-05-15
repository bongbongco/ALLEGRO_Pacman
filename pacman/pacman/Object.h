#pragma once
#include "Component.h"
#include "Transform.h"
#include <vector>
#include <typeinfo>


class CObject { // 게임 내 모든 객체들
private:
	std::vector<CComponent *> m_components;
	CTransform *m_transform;
public:
	CObject() {
		m_transform = AddComponent<CTransform>();
	}

	~CObject() {
		for (int i = 0; i < m_components.size(); i++) {
			delete m_components[i];
		}
	}

	CTransform *GetTransform() {
		return m_transform;
	}

	void Update();
	void Render();

	template <class T> T* AddComponent() {
		T *component = new T(this);
		m_components.push_back(component);
		return component;
	}

	template <class T> int RemoveComponent(T* _component) {
		for (int i = 0; i < m_components.size(); i++) {
			if (m_components[i] == _component) {
				m_components.erase(m_components.begin() + i);
				return 1;
			}
		}
		return 0;
	}

	template <class T> T* GetComponent() {
		for (int i = 0; i < m_components.size(); i++) {
		if (typeid(*m_components[i]) == typeid(T)) { // 동일한 클래스인 컴포넌트
			return dynamic_cast<T*>(m_components[i]);
			}
		}
		return nullptr;
	}
};