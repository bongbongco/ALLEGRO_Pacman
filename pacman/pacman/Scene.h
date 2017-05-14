#pragma once

class CScene {
protected:
	CScene() {}
public:
	virtual void Init() {}
	virtual void Update() {}
	virtual void Render() {}

	virtual ~CScene() {}
};