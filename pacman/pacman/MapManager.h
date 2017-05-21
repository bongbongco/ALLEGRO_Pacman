#pragma once
#include "allegro5\allegro.h"
#include "Common.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

class CMapManager {
private:
	std::ifstream m_mapFileIn; // �� ���� ���� ���� ����
	char m_tmp[kTileX + 1]; // �� ���� �迭
	int **m_blueprint; // ���赵
public:
	static CMapManager& Instance() {
		static CMapManager gInstance;
		return gInstance;
	}

	int** LoadLevel(const char *_mapFilePath);
	int DecodeScatch(char _scatch);
};