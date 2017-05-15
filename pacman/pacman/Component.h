#pragma once

class CObject;

class CComponent { // 게임 내 모든 구성요소의 기본 클래스
public:
	CObject *m_object;
	CComponent(CObject *_Object) {
		m_object = _Object;
	}
	virtual ~CComponent() {}
	
	CObject *GetObject() {
		return m_object;
	}

	virtual void Update() = 0;
	virtual void Render() = 0;
};