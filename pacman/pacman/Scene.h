#pragma once
#include <iostream>
class CScene {
protected:
	CScene() {}
public:
	virtual void Init() {}
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual ~CScene() {}
};