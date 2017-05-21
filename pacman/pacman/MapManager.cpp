#include "MapManager.h"


int **CMapManager::LoadLevel(const char *_mapFilePath) {
	try {
		m_mapFileIn.open(_mapFilePath); // 맵 파일 읽기
	}
	catch (const std::ifstream::failure& e) {
		std::cout << "Map 파일 열기 실패 " << e.what() <<std::endl;
	}

	m_blueprint = new int *[kTileY + 1]; // 설계도 배열
	for (int i = 0; i < kTileY; ++i) {
		m_blueprint[i] = new int[kTileX];

		if (!m_mapFileIn.eof()) {
			m_mapFileIn.getline(m_tmp, kTileX + 1); // 맵 스케치 파일 라인 별 읽기
		}

		for (int j = 0; j < kTileX; ++j) {
			m_blueprint[i][j] = DecodeScatch(m_tmp[j]); // 맵 스케치를 숫자 형태로 변환하여 설계도로 저장
		}
	}
	return m_blueprint;
}

int CMapManager::DecodeScatch(char _scatch) {
	switch (_scatch) {
	case '=':
		return kWall; // 벽
	case '.':
		return kPoint; // 포인트
	case ' ':
		return kEmpty;  // 공백
	default:
		return kEmpty;
	}
}