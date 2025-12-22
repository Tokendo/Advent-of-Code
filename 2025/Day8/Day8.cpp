#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

const int inputWidth = 150, inputHeight = 150;
static char arrInputChar[inputHeight][inputWidth];

int lineIndex = 0; int lineIndex = 0;

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
}
int main()
{
	//std::string inputFileName = "inputTest.txt";
	std::string inputFileName = "input.txt";
	std::string outputStr = "";
	long long  result = 0;

	readFile(inputFileName);

	result = result;

	outputStr += std::to_string(result) + "\n";

	for (size_t i = 0; i < lineIndex; i++)
	{
		outputStr += "1";
		outputStr += "\n";
	}
	std::cout << "Result: " << result << std::endl;
	std::ofstream outputFile("output.txt");
	outputFile << outputStr;
	outputFile.close();

}