#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>


int main()
{
	auto timeFirstLine = std::chrono::high_resolution_clock::now();
	//std::ifstream inputFile("input.txt");
	std::ifstream inputFile("inputTest.txt");
	std::string line = "";
	std::string nb = "";
	static long long arrValues[4][1000] = { 0 };
	static char arrOperators[1000] = { 0 };
	int valuesCollumns = 0, valuesDepth = 0;

	/*for (size_t i = 0; i < (sizeof(arrValues) / sizeof(*arrValues)); i++)
	{
		arrValues[i][0] = LLONG_MAX;
		arrValues[i][1] = LLONG_MAX;
	}*/

	printf("Reading file line by line:\n");
	auto start = std::chrono::high_resolution_clock::now();
	int charvalue = 0, lineIndex = 0, indexChar = 0;
	bool firstSpaceFound = false, firstChar=true;
	while (std::getline(inputFile, line)) {
		indexChar = -1;
		do
		{
			indexChar++;
			charvalue = int(line[indexChar]);
		} while (charvalue == 32);

		if (charvalue > 47 && charvalue < 58)
		{
			int indexArr = 0;
			// Process numeric line
			
			for (size_t i = 0; i <= line.length(); i++)
			{
				charvalue = int(line[i]);
				if (charvalue > 47 && charvalue < 58)
				{
					nb += line[i];
					firstSpaceFound = false;
				}
				else if (!firstSpaceFound)
				{
					if (nb != "")
					{
						long long value = std::stoll(nb);
						arrValues[lineIndex][indexArr] = value;
						indexArr++;
						nb = "";
					}
					firstSpaceFound = true;
				}
			}
		}
		else
		{
			int indexArr = 0;
			// Process numeric line
			for (size_t i = 0; i <= line.length(); i++)
			{
				charvalue = int(line[i]);
				if (charvalue != 32 )
				{
					arrOperators[indexArr] = line[i];
					indexArr++;
				}
			}

		}

		firstSpaceFound = false;
		lineIndex++;
	}
	inputFile.close();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	printf("File read in %lld microseconds.\n", std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count());


	auto totalelapsed = std::chrono::high_resolution_clock::now() - timeFirstLine;
	std::string outputStr = "";
	outputStr += "Good products: \n";
	outputStr += "Total ID: \n";
	outputStr += "Total time: " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(totalelapsed).count()) + " milliseconds.\n";
	printf(outputStr.c_str());
	std::ofstream outputFile("output.txt");
	outputFile << outputStr;
	outputFile.close();
	printf("Finished processing.\n");
}