#pragma once
#include "allegro5\allegro.h"
#include "Common.h"
#include <iostream>
#include <fstream>
#include <string>

class CMapManager {
private:
	std::ifstream m_mapFileIn;
	char m_tmp[kTileX + 1];
	int **m_blueprint;
public:
	int** LoadLevel(const char *_mapFilePath);
	int DecodeScatch(char _scatch);
};