#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <cmath>


static std::vector< std::vector<bool>> vInputLight;
static  std::vector< std::vector<std::vector<bool>>> vInputWires;
static std::vector< std::vector<int>> vInputJoltage;


int lineCount = 0;

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
	bool isWire = false, isLight = true, isJoltage=false;
	int indexWire = 0,indexJoltage=0;
	std::string nb = "";

	while (std::getline(inputFile, line)) {
		std::string nb = "";
		vInputLight.push_back(std::vector<bool>(12, 0));
		vInputJoltage.push_back(std::vector<int>(12,0));
		vInputWires.push_back(std::vector<std::vector<bool>>(1, std::vector<bool>(12, 0)));
		isLight = true;
		indexWire = 0, indexJoltage=0;
		for (size_t i = 1; i < line.length(); i++)
		{
			char c = line[i];
			if (c == ' ')
				continue;
			if (isLight)
			{
				isLight = !(int(c) == 93);

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
			else if (isWire && c == ',')
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
				isJoltage = true;
			}
			else if (isJoltage && int(c) > 47 && int(c) < 58)
			{
				nb += c;
				//complete
			}
			else if (isJoltage && c == ',')
			{
				vInputJoltage.back()[indexJoltage] = stoll(nb);
				indexJoltage++;
				nb = "";
			}
			else if (c == '}')
			{
				if (nb != "")
				{
					vInputJoltage.back()[indexJoltage] = stoll(nb);
					nb = "";
				}
				isJoltage = false;
				break;
			}

			

		}
		//printf("ligne");
		;
	}
	inputFile.close();
}

long long iterativeCalculation(int index)
{
	int circuitsCount = vInputWires[index].size();
	int nbLength = vInputLight[index].size();
	int component[20] = {-1};
	std::vector < std::vector<bool>> operations;
	bool result[12] = { false };
	bool target[12] = { false };
	
	int componentIndex = 0;

	for (size_t i = 0; i < 20; i++)
	{
		component[i] = -1;
	}

	for (size_t i = 0; i < nbLength; i++)
	{
		target[i] = vInputLight[index][i];
	}

	for (size_t x = 0; x < 10000000; x++)
	{
		operations.clear();
		
		for (size_t y = 0; y < circuitsCount; y++)
		{
			if (component[y] != -1)
			{
				operations.push_back(vInputWires[index][component[y]]);
			}
			else
			{
				break;
			}
		}
		
		for (size_t i = 0; i < 12; i++)
		{
			result[i] = false;
		}
		for (size_t i = 0; i < operations.size(); i++)
		{
			for (size_t j = 0; j < 12; j++)
			{
				result[j] = result[j] ^ operations[i][j];
			}
		}
		
		if (result[0] == target[0]&&
			result[1] == target[1] &&
			result[2] == target[2] &&
			result[3] == target[3] &&
			result[4] == target[4] &&
			result[5] == target[5] &&
			result[6] == target[6] &&
			result[7] == target[7] &&
			result[8] == target[8] &&
			result[9] == target[9] &&
			result[10] == target[10] &&
			result[11] == target[11] 
			)
		{
			
			printf(" iterations: ");
			printf(std::to_string(x).c_str());
			return operations.size();
		}
		component[0]++;
		for (size_t i = 0; i < 19; i++)
		{
			if (component[i] >= circuitsCount)
			{
				component[i + 1]++;
				component[i] = 0;
			}
			else
			{
				break;
			}
		}
	}
	return -1;
}
long long getTotalIteration()
{
	size_t length = vInputLight.size();
	long long result = 0;
	long long iterations = 0;
	for (size_t i = 0; i < length; i++)
	{
		printf("ligne: ");
		printf(std::to_string(i + 1).c_str());
		iterations = iterativeCalculation(i);
		result += iterations;
		
		printf(" Buttons pressed: ");
		printf(std::to_string(iterations).c_str());
		printf("\n");
	}
	return result;
}
long computeJoltage(int index)
{

}

long  getTotalButtonsForJoltage()

{
	size_t length = vInputLight.size();
	long totalBtnPressed = 0;
	for (size_t i = 0; i < length; i++)
	{
		totalBtnPressed+=computeJoltage(i);
	}

	return totalBtnPressed;
}

int main()
{
	long  result1 = 0, result2 = 0;

	//std::string inputFileName = "inputTest.txt";
	std::string inputFileName = "input.txt";
	std::string outputStr = "";

	readFile(inputFileName);

	//brutForceResult part 1

	//result1 = getTotalIteration();
	result2 = getTotalButtonsForJoltage();



	outputStr = "Result1 is:";
	outputStr += std::to_string(result1).c_str();
	outputStr = "\n Result2 is:";
	outputStr += std::to_string(result2).c_str();


	printf(outputStr.c_str());

	std::ofstream outputFile("output.txt");
	outputFile << outputStr;
	outputFile.close();

}