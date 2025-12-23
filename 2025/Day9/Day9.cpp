#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>


const int  inputHeight = 1100, inputWidth = 1000;
static std::vector< std::vector<long>> vInputCoord;
static  std::vector< std::vector<long long>> surfaces;
const size_t arrWidth = 14, arrHeight=10;
static char arrMap[arrHeight][arrWidth] = {'.'};
int lineCount = 0;

void initArr()
{
	
	for (size_t i = 0; i < arrHeight; i++)
	{
		for (size_t j = 0; j < arrWidth; j++)
		{
			arrMap[i][j] = '.';
		}
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
				vInputCoord[lineCount][0] = stoll(nb);
				nb = "";
			}
		}
		vInputCoord[lineCount][1] = stoll(nb);
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
	auto elapsedChrono = std::chrono::high_resolution_clock::now() - startChrono;
	printf("Elapsed time (ms): ");
	printf(std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(elapsedChrono).count()).c_str());
	printf("\n");
}
void heapSort()
{
	auto startChrono = std::chrono::high_resolution_clock::now();
	printf("Starting heap sort\n");
	long start = surfaces.size() / 2 - 1;
	long end = surfaces.size();
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
			std::swap(surfaces[0], surfaces[end]);
		}
		//sift down
		long root = start;
		while (root * 2 + 1 < end)
		{
			long child = root * 2 + 1;

			if (child + 1 < end && surfaces[child][2] < surfaces[child + 1][2])
			{
				child++;
			}
			if (surfaces[root][2] < surfaces[child][2])
			{
				std::swap(surfaces[root], surfaces[child]);
				root = child;
			}
			else
			{
				break;
			}
		}
		iteration++;

	}

	auto elapsedChrono = std::chrono::high_resolution_clock::now() - startChrono;
	printf("\nHeap sort finished\n");
	printf("Elapsed time (ms): ");
	printf(std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(elapsedChrono).count()).c_str());
	printf("\n");
	printf("\n");
}
void checkSort()
{
	size_t length = surfaces.size();
	for (size_t i = 0; i < length - 1; i++)
	{
		if (surfaces[i][2] > surfaces[i + 1][2])
		{
			int debug = 1;
		}
	}

}
void drawLine(int indexPt1, int indexPt2)
{
	long pt1[2] = { vInputCoord[indexPt1][0],vInputCoord[indexPt1][1] };
	long pt2[2] = { vInputCoord[indexPt2][0],vInputCoord[indexPt2][1] };
	arrMap[pt1[1]][pt1[0]] = '#';
	arrMap[pt2[1]][pt2[0]] = '#';
	if (pt1[1] == pt2[1]) //horizontal
	{
		if (pt2[0] < pt1[0])
		{
			std::swap(pt1, pt2);
		}
		for (size_t i=pt1[0]+1;i<pt2[0];i++)
		{
			arrMap[pt1[1]][i] = 'V';
		}
	}
	else // vertical
	{
		if (pt2[1] < pt1[1])
		{
			std::swap(pt1, pt2);
		}
		for (size_t i = pt1[1]+1; i < pt2[1]; i++)
		{
			arrMap[i][pt1[0]] = 'V';
		}

	}
	;

}
void draw()
{
	size_t length = lineCount;
	for (size_t i = 0; i < length-1; i++)
	{
		drawLine(i, i+1);
	}
	drawLine(length - 1, 0);

}
void printArray()
{
	std::string line = "", outputStr = "";
	for (size_t i = 0; i < arrHeight; i++)
	{
		for (size_t j = 0; j < arrWidth; j++)
		{
			line+= arrMap[i][j];
		}
		
		printf(line.c_str());
		line = "";
		printf("\n");
	}
	printf(outputStr.c_str());

}

int main()
{
	initArr();
	std::string inputFileName = "inputTest.txt";
	//std::string inputFileName = "inputSmall.txt";
	//std::string inputFileName = "input.txt";
	std::string outputStr = "";

	readFile(inputFileName);

	draw();
	printArray();

	calculateSurface();
	heapSort();
	checkSort();



	outputStr = "bigger surface is:";
	outputStr += std::to_string(surfaces[surfaces.size() - 1][2]);
	printf(outputStr.c_str());

	std::ofstream outputFile("output.txt");
	outputFile << outputStr;
	outputFile.close();

}