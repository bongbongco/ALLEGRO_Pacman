#pragma once

class CObject;

class CComponent { // ���� �� ��� ��������� �⺻ Ŭ����
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