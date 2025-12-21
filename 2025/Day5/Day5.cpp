#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>

int main()
{
	//std::ifstream inputFile("input.txt");
	std::ifstream inputFile("InputTest.txt");
	std::string line = "";
	std::string nb = "";
	static int arrRanges[1000][2] = { 0 };
	static int arrProducts[2000] = { 0 };
	int rangeQty = 0, productsQty = 0;
	bool rangesReading = true;

	printf("Reading file line by line:\n");
	while (std::getline(inputFile, line)) {

		if (rangesReading && line.find('-') != std::string::npos)
		{
			nb = "";
			for (size_t i = 0; i < line.length(); i++)
			{
				if (line[i] != '-')
				{
					nb += line[i];
				}
				else
				{
					arrRanges[rangeQty][0] = stoi(nb);
					nb = "";
				}
			}
			arrRanges[rangeQty][1] = stoi(nb);
			nb = "";
			rangeQty++;
		}
		else if (!rangesReading)
		{
			arrProducts[productsQty] = stoi(line);
			productsQty++;
		}
		else if (line == "")
		{
			rangesReading = false;
		}
	}

	inputFile.close();

	auto start = std::chrono::high_resolution_clock::now();

	auto elapsed = std::chrono::high_resolution_clock::now() - start;

	std::ofstream outputFile("output.txt");
	outputFile << "output";
	outputFile.close();
	printf("Finished processing.\n");


}
