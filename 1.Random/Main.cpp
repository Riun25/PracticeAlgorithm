#include <iostream>
#include <stdlib.h>
#include <time.h>

// �ּ�/�ִ� �� ������ ������ ��ȯ�ϴ� �Լ�
int RandomRange(int _min, int _max)
{
	// ����
	int diff = (_max - _min) + 1;
	return ((rand() * diff) / (RAND_MAX + 1)) + _min;
}

int main()
{
	// �õ�(seed, ����) ����
	srand(static_cast<unsigned int>(time(nullptr)));// Ÿ�ӿ� nullptr�� �־��ָ� ���� �ð��� ����Ѵ�.
	
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