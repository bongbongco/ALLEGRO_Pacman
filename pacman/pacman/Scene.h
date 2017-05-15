#pragma once
#include <iostream>
class CScene {
protected:
	CScene() {}
public:
	virtual void Init() {}
	virtual void Update() {}
	virtual void Render() {
		std::cout << "Scene Render()" << std::endl;
	}

	virtual ~CScene() {}
};