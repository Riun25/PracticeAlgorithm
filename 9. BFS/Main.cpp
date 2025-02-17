#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>

// �̷� Ž�� ����
// ��ġ ����ü
struct Location
{
	Location(int row = 0, int col = 0)
		:row(row), col(col)
	{
	}

	int row;
	int col;
};

// �� ����
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
		std::cout << "�������� �ʴ� �����Դϴ�.\n";
		__debugbreak();
		return false;
	}

	FILE* file = nullptr;
	fopen_s(&file, filePath.c_str(), "rb");

	// ���� ó��
	if (file == nullptr)
	{
		std::cout << "���� ���� ����.\n";
		__debugbreak();
		return false;
	}

	// ���� �б�
	fseek(file, 0, SEEK_END);
	size_t readSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* buffer = new char[readSize + 1];
	size_t bytesRead = fread(buffer, 1, readSize, file);

	if (readSize != bytesRead)
	{
		std::cout << "�о�� ũ�Ⱑ �ٸ�\n";
		__debugbreak();
		return false;
	}

	buffer[readSize] = '\0';

	/// ù �� �б�
	std::istringstream fileStream(buffer);
	std::string line;

	if (!std::getline(fileStream, line))
	{
		std::cout << "������ ��� ����\n";
		delete[] buffer;
		return false;
	}

	int size = 0;
	if (sscanf_s(line.c_str(), "size: %d start: %c destination: %c", &size, &startMark, 1, &destinationMark, 1) != 3)
	{
		std::cout << "ù �� ���� ����\n";
		delete[] buffer;
		return false;
	}

	startMark = startMark;
	destinationMark = destinationMark;

	// �� ũ�� ���
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
		else if (buffer[i] != ',') // ',' ����
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


	// ���� ���� �� ����� �ε���
	int index = 0;
	// ��ǥ ����� ���� ���� ����
	int posX = 0;
	int posY = 0;
	firstLineSkipped = false;

	while (index < static_cast<int>(bytesRead))
	{
		// �� ���ھ� �б�
		char mapChar = buffer[index++];

		if (firstLineSkipped == false)
		{
			if (mapChar == '\n')
			{
				firstLineSkipped = true;
			}
			continue;
		}

		// ���� ������ ��� ó��
		if (mapChar == '\n')
		{
			++posY;
			posX = 0;
			continue;
		}

		if (mapChar == ',') // ',' ����
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

// �̵��Ϸ��� ��ġ�� �̵� ������ ��ġ���� Ȯ���ϴ� �Լ�
bool IsValid(int row, int col)
{
	// Out of index �˻�
	if (row < 0 || row >= mazeSize || col < 0 || col >= mazeSize)
	{
		return false;
	}

	return map[row][col] == '0' || map[row][col] == destinationMark;
}

// �� ��� �� ���� ��ġ �˻� �Լ�
void FindStartLocation(int& row, int& col)
{
	// ��
	for (int ix = 0; ix < mazeSize; ++ix)
	{
		// ��
		for (int jx = 0; jx < mazeSize; ++jx)
		{
			// ���� ��ġ�� ã������ ������ �Ķ���Ϳ� ���
			if (map[ix][jx] == startMark)
			{
				row = ix;
				col = jx;
			}
			// �� ���
			std::cout << map[ix][jx] << " ";
		}
		// ����
		std::cout << "\n";
	}
}

void EscapeMaze()
{
	// ���� ��ġ
	int row = 0;
	int col = 0;
	FindStartLocation(row, col);

	// Ž���� ����� ť ����
	std::queue<Location> queue;

	// ���� ��ġ �߰�
	queue.emplace(Location(row, col));

	// Ž��
	while (!queue.empty())
	{
		// ť���� ���� �տ� ��ġ�� �����͸� ����
		Location current = queue.front();
		queue.pop();

		// Ž���� ��ġ ���
		std::cout << "(" << current.row << ", " << current.col << ") ";

		// Ż�� ���� (��ǥ ������ ������ ���)
		if (map[current.row][current.col] == destinationMark)
		{
			std::cout << "\n �̷� Ž�� ����\n";
			return;
		}

		// �湮�� ��ġ�� �ٸ� ���ڷ� ����
		map[current.row][current.col] = '.';

		// Ž���� ��ġ�� ť�� �ֱ�
		// ��/��/��/��
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

	// Ž�� ����
	std::cout << "\n �̷� Ž�� ����\n";
}

int main()
{
	char a = 'e';
	char b = 'x';

	if (ParseMap("../Assets/Map.txt", a, b) == true)
	{
		// �̷� Ž�� ���� ����
		EscapeMaze();
	}

	std::cin.get();
}