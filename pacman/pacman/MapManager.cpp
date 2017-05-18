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

CNode *CNode::FindPath(int _startX, int _startY, int _endX, int _endY, bool _first) {
	if (_first == true) { // 시작점

		CNode *newNode = new CNode;

		m_startX = _startX;
		m_startY = _startY;
		m_endX = _endX;
		m_endY = _endY;

		newNode->m_g = 0;
		newNode->m_h = 10 * (abs(_startX - _endX) + abs(_startY - _endY)); // 맨하탄 거리
		newNode->m_f = newNode->m_g + newNode->m_h;

		newNode->m_parent = NULL;
		newNode->m_x = _startX;
		newNode->m_y = _startY;

		gOpenList[0].m_f = m_f;
		gOpenList[0].m_parent = newNode;
	}

	while (true) { // 길 찾기
		if (EmptyCheck() == true) { // OpenList가 비었다면
			return nullptr;
		}

		CNode *newParent = MinimumF(); // 최소값 F를 가지는 Node  
		Erase(newParent);
		gCloseList[newParent->m_y][newParent->m_x] = newParent;

		if (newParent->m_x == m_endX && newParent->m_y == m_endY) { // 목적지에 도달했다면
			return newParent;
		}
		int movingX = newParent->m_x;
		int movingY = newParent->m_y;

		MakeNode(newParent, 10, movingX, movingY - 1);
		//3시
		MakeNode(newParent, 10, movingX + 1, movingY);
		//6시
		MakeNode(newParent, 10, movingX, movingY + 1);
		//9시
		MakeNode(newParent, 10, movingX - 1, movingY);

		//2시
		MakeNode(newParent, 14, movingX + 1, movingY - 1);
		//5시
		MakeNode(newParent, 14, movingX + 1, movingY + 1);
		//8시
		MakeNode(newParent, 14, movingX - 1, movingY + 1);
		//11시
		MakeNode(newParent, 14, movingX - 1, movingY - 1);
	}
	return nullptr;
}
CNode *CNode::MinimumF() { // OpenList 최소 F 값
	int minimumValue = 999999;
	int minimumIndex;

	for (int i = 0; i < kMax; i++) {
		if ((gOpenList[i].m_f < minimumValue) && (gOpenList[i].m_f != NULL)) {
			minimumValue = gOpenList[i].m_f;
			minimumIndex = i;
		}
	}
	return gOpenList[minimumIndex].m_parent;
}
bool CNode::EmptyCheck() { // OpenList empty check
	for (int i = 0; i < kMax; i++) {
		if (gOpenList[i].m_f != NULL) {
			return false;
		}
	}
	return true;
}

void CNode::Erase(CNode *_target) { // OpenList에서 제거
	for (int i = 0; i < kMax; i++) {
		if (gOpenList[i].m_parent == _target) {
			gOpenList[i].m_f = NULL;
			gOpenList[i].m_parent = NULL;
			return;
		}
		return;
	}
}
bool CNode::ClassifyNode(CNode *_parent) { // True : OpenList, False : CloseList
	for (int i = 0; i < kMax; i++) {
		if (gOpenList[i].m_f == NULL) {
			gOpenList[i].m_f = _parent->m_f;
			gOpenList[i].m_parent = _parent;
			return true;
		}
	}
	return false;
}
CNode *CNode::Search(int _x, int _y, bool _list) { // True : OpenList, False : CloseList
	if (_list == false) {
		if (gCloseList[_y][_x] != NULL) {
			return gCloseList[_y][_x];
		}
		return NULL;
	}
	else if (_list == true) {
		for (int i = 0; i < kMax; i++) {
			if (gOpenList[i].m_f != NULL) {
				if (gOpenList[i].m_parent->m_x == _x &&
					gOpenList[i].m_parent->m_y == _y) {

					return gOpenList[i].m_parent;
				}
			}
		}
		return NULL;
	}
	return NULL;

}
void CNode::MakeNode(CNode *_parent, int _movingCost, int _x, int _y) { // 부모인자로 노드 생성
	int **m_blueprint = CMapManager::Instance().LoadLevel("level1.txt"); // 설계도 생성

	if (_x < 0 || _x > kTileX) { // x축 최소, 최대 값 한정 
		return;
	}
	if (_y < 0 || _y > kTileY) { // y축 최소, 최대 값 한정
		return;
	}

	if (m_blueprint[_y][_x] == kWall) { // 벽(갈 수 없음)
		return;
	}

	CNode *newNode = new CNode; // Node 셋팅

	newNode->m_parent = _parent;
	newNode->m_x = _x;
	newNode->m_y = _y;

	newNode->m_h = 10 * (abs(_x - m_endX) + abs(_y - m_endY));
	newNode->m_g = _parent->m_g + _movingCost;
	newNode->m_f = newNode->m_h + newNode->m_g;

	CNode *parent = Search(_x, _y, false); //CloseList 검색
	if (parent != NULL) {
		if (parent->m_f > newNode->m_f) {
			parent->m_f = newNode->m_f;
			parent->m_g = newNode->m_g;
			parent->m_h = newNode->m_h;
			parent->m_parent = newNode->m_parent;
		}
		delete newNode;
		return;
	}

	parent = Search(_x, _y, true); //OpenList 검색
	if (parent != NULL) {
		if (parent->m_f > newNode->m_f) {
			parent->m_f = newNode->m_f;
			parent->m_g = newNode->m_g;
			parent->m_h = newNode->m_h;
			parent->m_parent = newNode->m_parent;
		}
		delete newNode;
		return;
	}

	ClassifyNode(newNode); // OpenList로 분류
	return;
}