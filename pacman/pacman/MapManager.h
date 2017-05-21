#pragma once
#include "allegro5\allegro.h"
#include "Common.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

class CMapManager {
private:
	std::ifstream m_mapFileIn; // 맵 설계 파일 읽을 변수
	char m_tmp[kTileX + 1]; // 맵 가로 배열
	int **m_blueprint; // 설계도
public:
	static CMapManager& Instance() {
		static CMapManager gInstance;
		return gInstance;
	}

	int** LoadLevel(const char *_mapFilePath);
	int DecodeScatch(char _scatch);
};