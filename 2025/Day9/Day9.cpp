#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>
#include <future>


const int  inputHeight = 1100, inputWidth = 1000;
static std::vector< std::vector<long>> vInputCoord;
static  std::vector< std::vector<long long>> surfaces;
static  std::vector< std::vector<long long>> vWall;
static  std::vector< std::vector<long long>> hWall;
int lineCount = 0;
long minY = LONG_MAX, maxY = LONG_MIN, minX = LONG_MAX, maxX = LONG_MIN;


template<typename T>
void heapSortVector(std::vector<T>& v, int index)
{
	long start = v.size() / 2 - 1;
	long end = v.size();
	long iteration = 0;
	while (end > 1)
	{
		if (start > 0) //heap construction
		{
			start--;
		}
		else //heap extraction
		{
			end--;
			std::swap(v[0], v[end]);
		}
		//sift down
		long root = start;
		while (root * 2 + 1 < end)
		{
			long child = root * 2 + 1;

			if (child + 1 < end && v[child][index] < v[child + 1][index])
			{
				child++;
			}
			if (v[root][index] < v[child][index])
			{
				std::swap(v[root], v[child]);
				root = child;
			}
			else
			{
				break;
			}
		}
		iteration++;

	}
}

void readFile(std::string inputFileName)
{
	std::ifstream inputFile(inputFileName.c_str());
	std::string line = "";

	while (std::getline(inputFile, line)) {
		std::string nb = "";
		vInputCoord.push_back(std::vector<long>(2, 0));
		for (size_t i = 0; i < line.length(); i++)
		{
			if (int(line[i]) < 58 && int(line[i]) > 47)
			{
				nb += line[i];
			}
			else
			{
				long nbLong = stoll(nb);
				vInputCoord[lineCount][0] = nbLong;
				if (nbLong < minX)
				{
					minX = nbLong;
				}
				if (nbLong > maxX)
				{
					maxX = nbLong;
				}
				nb = "";
			}
		}
		long nbLong = stoll(nb);
		vInputCoord[lineCount][1] = nbLong;
		if (nbLong < minY)
		{
			minY = nbLong;
		}
		if (nbLong > maxY)
		{
			maxY = nbLong;
		}
		nb = "";
		lineCount++;
	}
	inputFile.close();
}
void calculateSurface()
{
	//coord 1 / coord 2 / surface
	long long rectIndex = 0, aire = 0, dx = 0, dy = 0;
	printf("start calculate surface\n");
	auto startChrono = std::chrono::high_resolution_clock::now();
	size_t length = vInputCoord.size() - 1;
	printf("lenght:");
	printf(std::to_string(length).c_str());
	printf("\n");
	for (size_t i = 0; i < vInputCoord.size() - 1; i++)
	{

		for (size_t j = i + 1; j < vInputCoord.size(); j++)
		{
			surfaces.push_back(std::vector<long long>(3, 0));
			surfaces[rectIndex][0] = i;
			surfaces[rectIndex][1] = j;
			dx = vInputCoord[i][0] - vInputCoord[j][0];
			dx = std::abs(dx) + 1;
			dy = vInputCoord[i][1] - vInputCoord[j][1];
			dy = std::abs(dy) + 1;
			aire = dx * dy;
			if (j == 120)
			{
				dx = std::abs(dx);
				int debug = 1;
			}
			surfaces[rectIndex][2] = aire;
			rectIndex++;
		}
		if (i % 10 == 0)
		{
			printf("iteration:");
			printf(std::to_string(i).c_str());
			printf("\n");
		}
	}
	printf("end calculate surfaces\n");
	printf("start sort surfaces\n");
	heapSortVector(surfaces, 2);
	printf("end sort surfaces\n");
	auto elapsedChrono = std::chrono::high_resolution_clock::now() - startChrono;
	printf("Elapsed time (ms): ");
	printf(std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(elapsedChrono).count()).c_str());
	printf("\n");
}

void drawWalls()
{

	for (size_t i = 0; i < vInputCoord.size(); i++)
	{
		int in = i + 1;
		if (in == vInputCoord.size())
		{
			in = 0;
		}
		long x1 = vInputCoord[i][0];
		long y1 = vInputCoord[i][1];
		long x2 = vInputCoord[in][0];
		long y2 = vInputCoord[in][1];

		if (x1 == x2) //vertical wall
		{
			vWall.push_back(std::vector<long long>(3, 0));
			vWall.back()[0] = x1;
			vWall.back()[1] = std::min(y1, y2);
			vWall.back()[2] = std::max(y1, y2);
		}
		else //horizontal wall
		{
			hWall.push_back(std::vector<long long>(3, 0));
			hWall.back()[0] = y1;
			hWall.back()[1] = std::min(x1, x2);
			hWall.back()[2] = std::max(x1, x2);
		}
	}
	heapSortVector(vWall, 0);
	heapSortVector(hWall, 0);
}
int countWall(long x1, long y1, long x2, long y2)
{
	int count = 0, corner=0;
	if (x1==x2) //check for horizontal wall
	{
		if (y1 > y2) //bottom to top
		{
			for (size_t i =y1; i > y2; i--)
			{
				for (size_t j = hWall.size() - 1; j>0; j--)
				{
					if(hWall[j][0]<i)
						{
						break;
					}
					if (hWall[j][0]==i&& hWall[j][1] <x1&& hWall[j][2] > x1)
					{
						count++;
					}

				}
			}
			for (size_t i = 0; i < vWall.size(); i++)
			{
				if (vWall[i][0]==x1&& vWall[i][1]>y2)
				{
					count++;
				}
			}
		}
		else //top to bottom
		{
			for (size_t i = y1; i < y2; i++)
			{
				for (size_t j = 0; j < hWall.size(); j++)
				{
					if (hWall[j][0] > i)
					{
						break;
					}
					if (hWall[j][0] == i && hWall[j][1] < x1 && hWall[j][2] > x1)
					{
						count++;
					}
				}
			}
			for (size_t i = 0; i < vWall.size(); i++)
			{
				if (vWall[i][0] == x1 && vWall[i][2] < y2)
				{
					count++;
				}
			}
		}

	}
	else if (y1==y2) //check for vertical wall
	{
		if (x1 > x2) //right to left
		{
			for (size_t i = x1; i > x2; i--)
			{
				for (size_t j = vWall.size() - 1; j > 0; j--)
				{
					if (vWall[j][0] < i)
					{
						break;
					}
					if (vWall[j][0] == i && vWall[j][1] < y1 && vWall[j][2] > y1)
					{
						count++;
					}
				}
			}
			for (size_t i = 0; i < hWall.size(); i++)
			{
				if (hWall[i][0] == y1 && hWall[i][1] > x2)
				{
					count++;
				}
			}
		}
		else //left to right
		{
			for (size_t i = x1; i < x2; i++)
			{
				for (size_t j = 0; j < vWall.size(); j++)
				{
					if (vWall[j][0] > i)
					{
						break;
					}
					if (vWall[j][0] == i && vWall[j][1] < y1 && vWall[j][2] > y1)
					{
						count++;
					}
				}
			}
			for (size_t i = 0; i < hWall.size(); i++)
			{
				if (hWall[i][0] == y1 && hWall[i][2] < x2)
				{
					count++;
				}
			}
		}
	}
	return count;
}
bool checkIfInside(int x, int y)
{
	auto left = std::async(countWall, minX - 1, y, x, y);
	auto right = std::async(countWall, maxX + 1, y, x, y);
	auto up = std::async(countWall, x, minY - 1, x, y);
	auto down = std::async(countWall, x, maxY + 1, x, y);

	int leftCount = left.get();
	int rightCount = right.get();
	int upCount = up.get();
	int downCount = down.get();

	bool leftIsInside = false;
	bool rightIsInside = false;
	bool upIsInside = false;
	bool downIsInside = false;

	leftIsInside = (leftCount % 2 == 1);
	rightIsInside = (rightCount % 2 == 1);
	upIsInside = (upCount % 2 == 1);
	downIsInside = (downCount % 2 == 1);

	if (leftIsInside && rightIsInside && upIsInside && downIsInside)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool checkRect(int rect)
{
	long coordX1 = vInputCoord[surfaces[rect][0]][0];
	long coordY1 = vInputCoord[surfaces[rect][0]][1];
	long coordX2 = vInputCoord[surfaces[rect][1]][0];
	long coordY2 = vInputCoord[surfaces[rect][1]][1];
	long minRectX = std::min(coordX1, coordX2);
	long maxRectX = std::max(coordX1, coordX2);
	long minRectY = std::min(coordY1, coordY2);
	long maxRectY = std::max(coordY1, coordY2);
	long x = 0, y = 0;
	for (size_t i = 0; i < vInputCoord.size(); i++)
	{
		x = vInputCoord[i][0];
		y = vInputCoord[i][1];
		if (minRectX < x && maxRectX > x)
		{
			if (minRectY < y && maxRectY > y)
			{
				return false;
			}
		}
	}
	for (size_t x = minRectX+1; x < maxRectX; x++)
	{
		for (size_t i = 0; i < vWall.size(); i++)
		{
			if (vWall[i][0] == x)
			{
				if (vWall[i][1] <= minRectY && vWall[i][2] >= maxRectY)
				{
					return false;
				}
			}
		}
	}
	for (size_t y = minRectY+1; y < maxRectY; y++)
	{
		for (size_t i = 0; i < hWall.size(); i++)
		{
			if (hWall[i][0] == y)
			{
				if (hWall[i][1] <= minRectX && hWall[i][2] >= maxRectX)
				{
					return false;
				}
			}
		}
	}

	return(checkIfInside(minRectX + 3, minRectY +3));
}
long long getBiggerSurface()
{

	for (size_t i = surfaces.size() - 1; i > 0; i--)
	{
		printf("checking rect:");
		printf(std::to_string(i).c_str());
		printf("\n");
		if (i == 18)
		{
			int debug = 1;
		}
		if (checkRect(i))
		{
			return surfaces[i][2];
		}
	}

	return 0;
}

int main()
{

	//std::string inputFileName = "inputTest.txt";
	std::string inputFileName = "input.txt";
	std::string outputStr = "";

	readFile(inputFileName);


	calculateSurface();
	drawWalls();



	long long result = getBiggerSurface();
	if (result >= 4534997222)
	{
		int tooBig = 1;
	}

	outputStr = "bigger surface is:";
	outputStr += std::to_string(surfaces[surfaces.size() - 1][2]);
	printf(outputStr.c_str());

	std::ofstream outputFile("output.txt");
	outputFile << outputStr;
	outputFile.close();

}