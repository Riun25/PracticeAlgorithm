#include <iostream>
#include <stdlib.h>
#include <time.h>

// 최소/최대 값 사이의 랜덤을 반환하는 함수
int RandomRange(int _min, int _max)
{
	// 차이
	int diff = (_max - _min) + 1;
	return ((rand() * diff) / (RAND_MAX + 1)) + _min;
}

int main()
{
	// 시드(seed, 종자) 설정
	srand(static_cast<unsigned int>(time(nullptr)));// 타임에 nullptr을 넣어주면 현재 시간을 출력한다.
	
	for (int i = 0; i < 10; ++i)
	{
		//std::cout << "Random Number: " << rand() << "\n";
	}

	for (int i = 0; i < 10; ++i)
	{
		std::cout << "Random Number: " << RandomRange(3, 10) << "\n";
	}

	std::cin.get();
}