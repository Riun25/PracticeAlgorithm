#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>

// 미로 탐색 예제
// 위치 구조체
struct Location
{
	Location(int row = 0, int col = 0)
		:row(row), col(col)
	{
	}

	int row;
	int col;
};

// 맵 선언
int mazeSize = 6;
char startMark = 'e';
char destinationMark = 'x';

std::vector<std::vector<char>> map =
{
	/*{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','x'},
	{'1','1','1','1','1','1'}*/
};

bool ParseMap(const char* path, char& startMark, char& destnationMark)
{
	std::string filePath = path;
	//startMark = startMark;
	//destinationMark = destnationMark;

	if (filePath == "")
	{
		std::cout << "존재하지 않는 파일입니다.\n";
		__debugbreak();
		return false;
	}

	FILE* file = nullptr;
	fopen_s(&file, filePath.c_str(), "rb");

	// 파일 처리
	if (file == nullptr)
	{
		std::cout << "파일 열기 실패.\n";
		__debugbreak();
		return false;
	}

	// 파일 읽기
	fseek(file, 0, SEEK_END);
	size_t readSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* buffer = new char[readSize + 1];
	size_t bytesRead = fread(buffer, 1, readSize, file);

	if (readSize != bytesRead)
	{
		std::cout << "읽어온 크기가 다름\n";
		__debugbreak();
		return false;
	}

	buffer[readSize] = '\0';

	/// 첫 줄 읽기
	std::istringstream fileStream(buffer);
	std::string line;

	if (!std::getline(fileStream, line))
	{
		std::cout << "파일이 비어 있음\n";
		delete[] buffer;
		return false;
	}

	int size = 0;
	if (sscanf_s(line.c_str(), "size: %d start: %c destination: %c", &size, &startMark, 1, &destinationMark, 1) != 3)
	{
		std::cout << "첫 줄 형식 오류\n";
		delete[] buffer;
		return false;
	}

	startMark = startMark;
	destinationMark = destinationMark;

	// 맵 크기 계산
	int width = 0, height = 0, currentWidth = 0;
	bool firstLineSkipped = false;

	for (int i = 0; i < readSize; ++i)
	{
		if (firstLineSkipped == false)
		{
			if (buffer[i] == '\n')
			{
				firstLineSkipped = true;
			}
			continue;
		}

		if (buffer[i] == '\n')
		{
			++height;
			if (currentWidth > width)
			{
				width = currentWidth;
			}
			currentWidth = 0;
		}
		else if (buffer[i] != ',') // ',' 무시
		{
			++currentWidth;
		}
	}

	if (currentWidth > 0)
	{
		++height;
		if (currentWidth > width)
		{
			width = currentWidth;
		}
	}

	map.assign(height, std::vector<char>(width, '0'));


	// 파일 읽을 때 사용할 인덱스
	int index = 0;
	// 좌표 계산을 위한 변수 선언
	int posX = 0;
	int posY = 0;
	firstLineSkipped = false;

	while (index < static_cast<int>(bytesRead))
	{
		// 한 문자씩 읽기
		char mapChar = buffer[index++];

		if (firstLineSkipped == false)
		{
			if (mapChar == '\n')
			{
				firstLineSkipped = true;
			}
			continue;
		}

		// 개행 문자인 경우 처리
		if (mapChar == '\n')
		{
			++posY;
			posX = 0;
			continue;
		}

		if (mapChar == ',') // ',' 무시
		{
			continue;
		}

		if (posY < height && posX < width)
		{
			map[posY][posX] = mapChar;
		}

		++posX;
	}

	delete[] buffer;
	return true;
}

// 이동하려는 위치가 이동 가능한 위치인지 확인하는 함수
bool IsValid(int row, int col)
{
	// Out of index 검사
	if (row < 0 || row >= mazeSize || col < 0 || col >= mazeSize)
	{
		return false;
	}

	return map[row][col] == '0' || map[row][col] == destinationMark;
}

// 맵 출력 및 시작 위치 검색 함수
void FindStartLocation(int& row, int& col)
{
	// 행
	for (int ix = 0; ix < mazeSize; ++ix)
	{
		// 열
		for (int jx = 0; jx < mazeSize; ++jx)
		{
			// 시작 위치를 찾았으면 전달한 파라미터에 출력
			if (map[ix][jx] == startMark)
			{
				row = ix;
				col = jx;
			}
			// 맵 출력
			std::cout << map[ix][jx] << " ";
		}
		// 개행
		std::cout << "\n";
	}
}

void EscapeMaze()
{
	// 시작 위치
	int row = 0;
	int col = 0;
	FindStartLocation(row, col);

	// 탐색에 사용할 큐 선언
	std::queue<Location> queue;

	// 시작 위치 추가
	queue.emplace(Location(row, col));

	// 탐색
	while (!queue.empty())
	{
		// 큐에서 가장 앞에 위치한 데이터를 추출
		Location current = queue.front();
		queue.pop();

		// 탐색한 위치 출력
		std::cout << "(" << current.row << ", " << current.col << ") ";

		// 탈출 조건 (목표 지점에 도달한 경우)
		if (map[current.row][current.col] == destinationMark)
		{
			std::cout << "\n 미로 탐색 성공\n";
			return;
		}

		// 방문한 위치를 다른 문자로 설정
		map[current.row][current.col] = '.';

		// 탐색할 위치를 큐에 넣기
		// 상/하/좌/우
		if (IsValid(current.row - 1, current.col))
		{
			queue.emplace(Location(current.row - 1, current.col));
		}
		if (IsValid(current.row + 1, current.col))
		{
			queue.emplace(Location(current.row + 1, current.col));
		}
		if (IsValid(current.row, current.col - 1))
		{
			queue.emplace(Location(current.row, current.col - 1));
		}
		if (IsValid(current.row, current.col + 1))
		{
			queue.emplace(Location(current.row, current.col + 1));
		}
	}

	// 탐색 실패
	std::cout << "\n 미로 탐색 실패\n";
}

int main()
{
	char a = 'e';
	char b = 'x';

	if (ParseMap("../Assets/Map.txt", a, b) == true)
	{
		// 미로 탐색 데모 실행
		EscapeMaze();
	}

	std::cin.get();
}