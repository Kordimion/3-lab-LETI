#include <iostream>
#include <algorithm>

#define MATRIX_SIZE 10

void combSort(int* leftPtr, int* rightPtr)
{
	const int size = rightPtr - leftPtr;
	int gap = size;
	bool isSorted = false;
	do
	{
		gap = std::max(1, gap * 10 / 13);
		isSorted = true;
		for (int i = 0; i < size - gap; ++i)
		{
			int& currItem = leftPtr[i];
			int& nextItem = leftPtr[i + gap];
			if (currItem > nextItem) {
				isSorted = false;
				std::swap(currItem, nextItem);
			}
		}
	} while (!isSorted || gap != 1);
}

void printIntArrResult(const int(* arr)[10], int size)
{
	std::cout << "resulting array: \n";

	for(int i = 0; i < size; ++i)
	{
		std::cout << '\n';
		for (int j = 0; j < size; ++j)
			printf("%3d", arr[i][j]);
	}

	std::cout << "\n\n";
}

bool Lab3Endpoints(const std::string command, int(* arr)[MATRIX_SIZE], int& arrSize)
{
	if(command == "resize")
	{
		int size;
		std::cin >> size;

		arrSize = size;

		for (int i = 0; i < arrSize; ++i)
			for (int j = 0; j < arrSize; ++j)
				arr[i][j] = 0;
	}
	else if(command == "+")
	{
		int num;
		std::cin >> num;

		for(int i = 0; i < arrSize; ++i)
			for(int j = 0; j < arrSize; ++j)
				arr[i][j] += num;
	}
	else if(command == "-")
	{
		int num;
		std::cin >> num;

		for(int i = 0; i < arrSize; ++i)
			for(int j = 0; j < arrSize; ++j)
				arr[i][j] -= num;
	}
	else if (command == "*")
	{
		int num;
		std::cin >> num;

		for(int i = 0; i < arrSize; ++i)
			for(int j = 0; j < arrSize; ++j)
				arr[i][j] *= num;
	}
	else if(command == "/")
	{
		int num;
		std::cin >> num;

		for(int i = 0; i < arrSize; ++i)
			for(int j = 0; j < arrSize; ++j)
				arr[i][j] /= num;
	}
	else if (command == "fill_snake")
	{
		int current = 1;
		for(int i = 0; i < arrSize; i+=2)
		{
			for(int column = 0; column < arrSize; ++column, ++current)
				arr[column][i] = current;

			for(int column = arrSize - 1; column >= 0; --column, ++current)
				arr[column][i+1] = current;
		}
	}
	else if (command == "fill_spiral")
	{
		int current = 1;

		for (int i = 0; i < arrSize / 2; ++i)
		{
			for (int j = i; j < arrSize - 1 - i; ++j, ++current)
				arr[i][j] = current;

			for (int j = i; j < arrSize - 1 - i; ++j, ++current)
				arr[j][arrSize - i - 1] = current;

			for (int j = i; j < arrSize - 1 - i; ++j, ++current)
				arr[arrSize - i - 1][arrSize - j - 1] = current;

			for (int j = i; j < arrSize - 1 - i; ++j, ++current)
				arr[arrSize - j - 1][i] = current;
		}

		if (arrSize % 2 == 1) arr[arrSize / 2][arrSize / 2] = current;
	}
	else if (command == "transform_vertical")
	{
		const int halfArraySize = arrSize / 2;

		for(int i = 0; i < halfArraySize; ++i)
			for(int j = 0; j < arrSize; ++j)
				std::swap(arr[i][j], arr[i + halfArraySize][j]);
	}
	else if (command == "transform_diagonal")
	{
		const int halfArraySize = arrSize / 2;

		for (int i = 0; i < halfArraySize; ++i)
			for (int j = 0; j < halfArraySize; ++j)
				std::swap(arr[i][j], arr[i + halfArraySize][j + halfArraySize]);

		for (int i = arrSize/2; i < arrSize; ++i)
			for (int j = 0; j < halfArraySize; ++j)
				std::swap(arr[i][j], arr[i - halfArraySize][j + halfArraySize]);
	}
	else if (command == "transform_diagonal")
	{
		const int halfArraySize = arrSize / 2;

		for (int i = 0; i < arrSize; ++i)
			for (int j = 0; j < halfArraySize; ++j)
				std::swap(arr[i][j], arr[i][j+halfArraySize]);

		printIntArrResult(arr, arrSize);
	}
	else if (command == "transform_rotate")
	{
		const int halfArraySize = arrSize / 2;

		for(int i = 0; i < halfArraySize; ++i)
		{
			for(int j = 0; j < halfArraySize; ++j)
			{
				const int saved = arr[i][j];
				arr[i][j] = arr[i + halfArraySize][j];
				arr[i + halfArraySize][j] = arr[i + halfArraySize][j + halfArraySize];
				arr[i + halfArraySize][j + halfArraySize] = arr[i][j + halfArraySize];
				arr[i][j + halfArraySize] = saved;
			}
		}
	}
	else if (command == "sort")
	{
		const int halfArraySize = arrSize / 2;

		for (int i = 0; i < halfArraySize; ++i)
			combSort(arr[i], arr[i] + arrSize);
	}
	else
	{
		return false;
	}

	printIntArrResult(arr, arrSize);
	return true;
}

int main()
{
	int arr[MATRIX_SIZE][MATRIX_SIZE]{};
	int arrSize = 6;

	std::string command;
	while(std::cin >> command)
	{
		const bool result = Lab3Endpoints(command, arr, arrSize);
		if(!result)
		{
			std::cout << "command not found";
		}	
	}
}

