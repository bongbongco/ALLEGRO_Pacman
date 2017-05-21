#include "MapManager.h"


int **CMapManager::LoadLevel(const char *_mapFilePath) {
	try {
		m_mapFileIn.open(_mapFilePath); // �� ���� �б�
	}
	catch (const std::ifstream::failure& e) {
		std::cout << "Map ���� ���� ���� " << e.what() <<std::endl;
	}

	m_blueprint = new int *[kTileY + 1]; // ���赵 �迭
	for (int i = 0; i < kTileY; ++i) {
		m_blueprint[i] = new int[kTileX];

		if (!m_mapFileIn.eof()) {
			m_mapFileIn.getline(m_tmp, kTileX + 1); // �� ����ġ ���� ���� �� �б�
		}

		for (int j = 0; j < kTileX; ++j) {
			m_blueprint[i][j] = DecodeScatch(m_tmp[j]); // �� ����ġ�� ���� ���·� ��ȯ�Ͽ� ���赵�� ����
		}
	}
	return m_blueprint;
}

int CMapManager::DecodeScatch(char _scatch) {
	switch (_scatch) {
	case '=':
		return kWall; // ��
	case '.':
		return kPoint; // ����Ʈ
	case ' ':
		return kEmpty;  // ����
	default:
		return kEmpty;
	}
}