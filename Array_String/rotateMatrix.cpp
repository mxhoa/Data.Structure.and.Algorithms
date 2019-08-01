#include <iostream>
#include <vector>

/**
 * @brief 	Rotate Matrix
 * @details Given an image represented by an NxN matrix, where each pixel in the image is 4 bytes, 
 * 			write a method to rotate the image by 90 degrees. Can you do this in place?
 * 
 * @build: g++ rotateMatrix.cpp -std=c++11 -o rotateMatrix 
 */
bool rotateMaxtrix(std::vector<std::vector<int>> &matrix)
{
	int n = matrix.size();

	for (int layer = 0; layer < n/2; layer++)
	{
		int first = layer;
		int last  = n - 1 - layer;

		for (int j = first; j < last; j++)
		{
			int offset = j - first;

			int top = matrix[first][j];
			
			/* Left -> Top */
			matrix[first][j] = matrix[last - offset][first];
			
			/* Bottom -> Left */
			matrix[last-offset][first] = matrix[last][last-offset];
			
			/* Right -> Bottom */
			matrix[last][last-offset] = matrix[j][last];

			/* Top -> Right */
			matrix[j][last] = top;
		}
	}
	return true;
}

void printMatrix(std::vector<std::vector<int>> &matrix)
{
	for (auto r : matrix)
	{
		for (auto c : r)
			std::cout << c << '\t';
		std::cout << "\n\n";
	}
}

int main()
{
	std::vector<std::vector<int>> matrix = 	{ {  1,  2,  3,  4,  5 }
								   			, {  6,  7,  8,  9, 10 }
											, { 11, 12, 13, 14, 15 }
											, { 16, 17, 18, 19, 20 }
											, { 21, 22, 23, 24, 25 }
											};

	std::cout << "++++++++ ORIGINAL ++++++++\n";
	printMatrix(matrix);	

	/* Rotate 90 */
	rotateMaxtrix(matrix);

	std::cout << "++++++++ ROTATE ++++++++\n";
	printMatrix(matrix);

	return 0;
}