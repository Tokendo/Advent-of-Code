#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>

void sortRanges(long long arrRanges[][2], int rangeQty)
{
	bool sorted = false;
	// protection si aucun élément ou un seul
	if (rangeQty <= 1)
		return;

	while (!sorted)
	{
		sorted = true;
		for (int j = 0; j < rangeQty - 1; j++)
		{
			// comparer par start, puis par end si start égaux
			if (arrRanges[j][0] > arrRanges[j + 1][0]
				|| (arrRanges[j][0] == arrRanges[j + 1][0] && arrRanges[j][1] > arrRanges[j + 1][1]))
			{
				long long temp0 = arrRanges[j][0];
				long long temp1 = arrRanges[j][1];
				arrRanges[j][0] = arrRanges[j + 1][0];
				arrRanges[j][1] = arrRanges[j + 1][1];
				arrRanges[j + 1][0] = temp0;
				arrRanges[j + 1][1] = temp1;
				sorted = false;
			}
		}
	}
}

int main()
{
	auto timeFirstLine = std::chrono::high_resolution_clock::now();
	std::ifstream inputFile("input.txt");
	//std::ifstream inputFile("InputTest.txt");
	std::string line = "";
	std::string nb = "";
	static long long arrRanges[200][2] = { LLONG_MAX };
	static long long arrProducts[1000][2] = { 0 };
	int rangeQty = 0, productsQty = 0;
	bool rangesReading = true;

	for (size_t i = 0; i < (sizeof(arrRanges) / sizeof(*arrRanges)); i++)
	{
		arrRanges[i][0] = LLONG_MAX;
		arrRanges[i][1] = LLONG_MAX;
	}

	printf("Reading file line by line:\n");
	auto start = std::chrono::high_resolution_clock::now();
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
					arrRanges[rangeQty][0] = stoll(nb);
					nb = "";
				}
			}
			arrRanges[rangeQty][1] = stoll(nb);
			nb = "";
			rangeQty++;
		}
		else if (!rangesReading)
		{
			arrProducts[productsQty][0] = stoll(line);
			productsQty++;
		}
		else if (line == "")
		{
			rangesReading = false;
		}
	}
	inputFile.close();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	printf("File read in %lld microseconds.\n", std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count());

	// Processing part 1
	printf("starting processing...\n");
	start = std::chrono::high_resolution_clock::now();
	int goodProducts = 0;
	for (size_t i = 0; i < productsQty; i++)
	{
		for (size_t j = 0; j < rangeQty; j++)
		{
			if (arrProducts[i][0] >= arrRanges[j][0])
			{
				if (arrProducts[i][0] <= arrRanges[j][1])
				{
					arrProducts[i][1] = 1;
					goodProducts++;
					break;
				}
			}
		}
	}


	elapsed = std::chrono::high_resolution_clock::now() - start;
	printf("Processing finished in %lld microseconds.\n", std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count());

	sortRanges(arrRanges, rangeQty);

	// merge overlapping ranges
	int tmprangeRemoved = 0, indexRange=0;
	for (size_t i = 1; i < (sizeof(arrRanges) / sizeof(*arrRanges)); i++)
	{
		if (arrRanges[i][0] == LLONG_MAX)
		{
			indexRange = i;
			break;
		}
		if (arrRanges[i][0] <= arrRanges[i - 1][1] && arrRanges[i][1] >= arrRanges[i - 1][1])
		{
			arrRanges[i][0] = arrRanges[i - 1][0];
			arrRanges[i - 1][1] = LLONG_MAX;
			arrRanges[i - 1][0] = LLONG_MAX;
			tmprangeRemoved++;
		}
	}
	sortRanges(arrRanges, rangeQty);
	rangeQty -= tmprangeRemoved;
	tmprangeRemoved = 0;
	// remove ranges inside other ranges
	for (size_t i = 1; i < rangeQty - 1; i++)
	{
		if (arrRanges[i][0] >= arrRanges[i - 1][0] && arrRanges[i][1] <= arrRanges[i - 1][1])
		{
			arrRanges[i][1] = LLONG_MAX;
			arrRanges[i][0] = LLONG_MAX;
			tmprangeRemoved++;
			continue;
		}
		if (arrRanges[i][0] == arrRanges[i + 1][0] && arrRanges[i][1] <= arrRanges[i + 1][1])
		{
			arrRanges[i][1] = LLONG_MAX;
			arrRanges[i][0] = LLONG_MAX;
			tmprangeRemoved++;
		}
	}

	sortRanges(arrRanges, rangeQty);
	rangeQty -= tmprangeRemoved;
	tmprangeRemoved = 0;

	long long totalId = 0;
	for (size_t i = 0; i < rangeQty; i++)
	{
		if (arrRanges[i][0] == LLONG_MAX)
		{
			break;
		}
		if (arrRanges[i][0] != 0 || arrRanges[i][1] != 0)
		{
			totalId += arrRanges[i][1] - arrRanges[i][0] + 1;
		}
	}

	if (totalId < 2114120685)
	{
		printf("result too low");
	}

	auto totalelapsed = std::chrono::high_resolution_clock::now() - timeFirstLine;
	std::string outputStr = "";
	outputStr += "Good products: " + std::to_string(goodProducts) + "\n";
	outputStr += "Total ID: " + std::to_string(totalId) + "\n";
	outputStr += "Total time: " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(totalelapsed).count()) + " milliseconds.\n";
	printf(outputStr.c_str());
	std::ofstream outputFile("output.txt");
	outputFile << outputStr;
	outputFile.close();
	printf("Finished processing.\n");


}