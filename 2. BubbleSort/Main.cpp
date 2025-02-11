#include <iostream>

void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

// ���� ���� �Լ�
void BubbleSort(int* array, int length)
{
	// ����
	for (int i = 0; i < length - 1; ++i)
	{
		for (int j = 0; j < length - 1; ++j)
		{
			// �� ���� ��
			if (array[j] > array[j + 1])
			{
				Swap(array[j], array[j + 1]);
			}
		}
	}
}

// ��� �Լ�
void PrintArray(int* array, int length)
{
	for (int i = 0; i < length; ++i)
	{
		std::cout << array[i] << " ";
	}

	std::cout << "\n";
}

int main()
{
	// �迭
	int array[]{ 5, 4, 2, 8, 10, 15, 20, 23 };

	// �迭 ����.
	int length = sizeof(array) / sizeof(int);

	// ���
	std::cout << "���� ��: ";
	PrintArray(array, length);

	// ����
	BubbleSort(array, length);

	std::cout << "���� ��: ";
	PrintArray(array, length);

	std::cin.get();
}