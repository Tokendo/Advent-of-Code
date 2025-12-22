#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

const int inputWidth = 150, inputHeight = 150;
static char arrInputChar[inputHeight][inputWidth];
static char arrWorkChar[inputHeight][inputWidth];
static long long arrWorkLong[inputHeight][inputWidth];


int lineIndex = 0;

void readFile(std::string inputFileName)
{
	std::ifstream inputFile(inputFileName.c_str());
	std::string line = "";
	printf("Reading file line by line:\n");

	
	while (std::getline(inputFile, line)) {

		for (size_t i = 0; i <= line.length(); i++)
		{
			arrInputChar[lineIndex][i] = line[i];
		}
		lineIndex++;
	}
	inputFile.close();
	for (size_t i = 0; i < inputHeight; i++)
	{
		for (size_t j = 0; j < inputWidth; j++)
		{
			arrWorkChar[i][j] = arrInputChar[i][j];
			arrWorkLong[i][j] = 0;
		}
	}

}

long long  traceBeamsAndCountQuantumSplits()
{
	long long  totalPath = 0;
	for (size_t i = 1; i < inputHeight; i++)
	{
		if (int(arrWorkChar[i][0])==0)
		{
			break;
		}

		for (size_t j = 0; j < inputWidth; j++)
		{
			if (arrWorkChar	[i][j] == '.')
			{
				if (arrWorkChar[i - 1][j] == 'S' )
				{
					arrWorkChar[i][j] = '|';
					arrWorkLong[i][j] = 1;
				}
				else if (arrWorkChar[i - 1][j] == '|')
				{
					arrWorkChar[i][j] = '|';
					arrWorkLong[i][j] = arrWorkLong[i - 1][j];
				}
			}
			else if (arrWorkChar[i][j] == '^')
			{
				if (arrWorkChar[i - 1][j] == '|' && j > 0 && j < inputWidth - 1)
				{
					arrWorkLong[i][j - 1] = arrWorkLong[i][j - 1] + arrWorkLong[i - 1][j];
					arrWorkChar[i][j - 1] = '|';
					arrWorkLong[i][j + 1] = arrWorkLong[i][j + 1] + arrWorkLong[i - 1][j];
					arrWorkChar[i][j + 1] = '|';
				}
			}
			else if (arrWorkChar[i][j] == '|'&& arrWorkChar[i - 1][j] == '|')
			{
				arrWorkLong[i][j]= arrWorkLong[i][j]+ arrWorkLong[i-1][j];
			}
			
		}

	}
	for (size_t i = 0; i < inputWidth; i++)
	{
		totalPath += arrWorkLong[lineIndex-1][i];
	}
	return totalPath;
}
long  traceBeamsAndCountSplits()
{
	long  splitCount = 0;
	for (size_t i = 1; i < inputHeight; i++)
	{
		for (size_t j = 0; j < inputWidth; j++)
		{
			if (arrWorkChar[i][j] == '.')
			{
				if (arrWorkChar[i - 1][j] == 'S' || arrWorkChar[i - 1][j] == '|')
				{
					arrWorkChar[i][j] = '|';
				}
			}
			else if (arrWorkChar[i][j] == '^')
			{
				if (arrWorkChar[i - 1][j] == '|' && j > 0 && j < inputWidth - 1)
				{
					arrWorkChar[i][j - 1] = '|';
					arrWorkChar[i][j + 1] = '|';
					splitCount++;
				}
			}
		}
	}

	return splitCount;
}

int main()
{
	//std::string inputFileName = "inputTest.txt";
	std::string inputFileName = "input.txt";
	std::string outputStr = "";
	long long  result = 0;
	
	readFile(inputFileName);

	result= traceBeamsAndCountQuantumSplits();

	outputStr += std::to_string(result)+"\n";

	for (size_t i = 0; i < lineIndex; i++)
	{
		outputStr += arrWorkChar[i];
		outputStr += "\n";
	}
	std::cout << "Result: " << result << std::endl;
	std::ofstream outputFile("output.txt");
	outputFile << outputStr;
	outputFile.close();

}