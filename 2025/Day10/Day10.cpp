#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>
#include <future>


const int  inputHeight = 1100, inputWidth = 1000;
static std::vector< std::vector<bool>> vInputLight;
static  std::vector< std::vector<std::vector<bool>>> vInputWires;
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
	bool isWire = false, isLight = true;
	int indexWire = 0;
	std::string nb = "";

	while (std::getline(inputFile, line)) {
		std::string nb = "";
		vInputLight.push_back(std::vector<bool>(12, 0));
		vInputWires.push_back(std::vector<std::vector<bool>>(1, std::vector<bool>(12, 0)));
		
		indexWire = 0;
		for (size_t i = 1; i < line.length(); i++)
		{
			char c = line[i];
			if (c == ' ')
				continue;
			if (isLight)
			{
				isLight = !(int(c) ==93);
				
				vInputLight.back()[i - 1] = c == '#';
			}
			else if (c == '(')
			{
				if (isWire)
				{
					vInputWires.back().push_back(std::vector<bool>(12, 0));
				}
				isWire = true;
			}
			else if (isWire && int(c) > 47 && int(c) < 58)
			{
				nb += c;
			}
			else if(isWire && c == ',')
			{
				int pos = 0;
				pos = stoll(nb);
				vInputWires.back()[indexWire][pos] = true;
				nb = "";
			}
			else if (isWire && c == ')')
			{
				if (nb != "")
				{
					int pos = 0;
					pos = stoll(nb);
					vInputWires.back()[indexWire][pos] = true;
					nb = "";
				}
				indexWire++;
			}
			else if (c == '{')
			{
				isWire = false;
				break;
			}
		}
		printf("ligne");
		;
	}
	inputFile.close();
}
int main()
{

	std::string inputFileName = "inputTest.txt";
	//std::string inputFileName = "input.txt";
	std::string outputStr = "";

	readFile(inputFileName);


	outputStr = "bigger surface is:";
	printf(outputStr.c_str());

	std::ofstream outputFile("output.txt");
	outputFile << outputStr;
	outputFile.close();

}