#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>



long long calculate(long long arrInValues[10],int nbQty, char calcOperator)
{
	long long result = arrInValues[0];
	if (calcOperator == '*')
	{
		for (size_t i = 1; i < nbQty; i++)
		{
			result *= arrInValues[i];
		}
	}
	else if (calcOperator == '+')
	{
		for (size_t i = 1; i < nbQty; i++)
		{
			result += arrInValues[i];
		}
	}
	
	return result;
}

long long readFileAndCalcPartOne( std::string inputFileName)
{
	std::ifstream inputFile(inputFileName.c_str());
	std::string line = "";
	std::string nb = "";
	printf("Reading file line by line:\n");
	auto start = std::chrono::high_resolution_clock::now();
	int charvalue = 0, lineIndex = 0, indexChar = 0;
	int operatorQty = 0, nbQty = 0;
	bool firstSpaceFound = false;

	static long long arrValues[4][1000] = { 0 };
	static char arrOperators[1000] = { 0 };
	static long long arrResults[1000] = { 0 };

	while (std::getline(inputFile, line)) {
		indexChar = -1;
		do
		{
			indexChar++;
			charvalue = int(line[indexChar]);
		} while (charvalue == 32);

		if (charvalue > 47 && charvalue < 58)
		{
			nbQty = nbQty+1;
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
			// Process operator line
			for (size_t i = 0; i <= line.length() - 1; i++)
			{
				charvalue = int(line[i]);
				if (charvalue != 32)
				{
					arrOperators[indexArr] = line[i];
					indexArr++;
					operatorQty= operatorQty+1;
				}
			}

		}

		firstSpaceFound = false;
		lineIndex++;
	}
	inputFile.close();

	long long total = 0, result = 0;
	for (size_t i = 0; i < operatorQty; i++)
	{
		long long arrCalculationValues[4] = { arrValues[0][i], arrValues[1][i], arrValues[2][i], arrValues[3][i] };

		result = calculate(arrCalculationValues, nbQty, arrOperators[i]);
		arrResults[i] = result;
		total += result;
	}
	return total;
}
long long readFileAndCalcPartTwo(std::string inputFileName)
{
	std::ifstream inputFile(inputFileName.c_str());
	std::string line = "";
	std::string nb = "";
	printf("Reading file line by line:\n");
	auto start = std::chrono::high_resolution_clock::now();
	int charValue = 0, lineIndex = 0;
	static char arrInputChar[5][4000] = { { '0' },{'0'},{'0'},{'0'} };
	bool firstSpaceFound = false;
	long long total = 0;

	while (std::getline(inputFile, line)) {
		for (size_t i = 0; i <= line.length(); i++)
		{
			arrInputChar[lineIndex][i] = line[i];
		}
		lineIndex++;
	}
	inputFile.close();

	//get operator line nb
	int operatorLine = 0;
	for (size_t i = 2; i < sizeof(arrInputChar)/sizeof(*arrInputChar); i++)
	{
		if (int(arrInputChar[i][0]) == 42 || int(arrInputChar[i][0]) == 43)
		{
			operatorLine = i;
			break;
		}
	}

	long long arrCalculationValues[10] = { 0 };
	int charIndex = 0,nextOperatorIndex=0, indexCalculationValue=0;
	char calcOperator = ' ', currentChar=' ';
	bool lastOperation = false;
	
	std::string currentNb = "";
	while (charIndex < 3800)
	{
		for (size_t i = charIndex+1; i <= charIndex+10; i++)
		{
			currentChar = arrInputChar[operatorLine][i];
			if (int(currentChar) == 42 || int(currentChar) == 43)
			{
				nextOperatorIndex = i;
				break;
			}
			else if(int(currentChar) == 0)
			{
				lastOperation=true;
				nextOperatorIndex = i;
				break;
			}

		}
		if(!lastOperation)
		lastOperation = nextOperatorIndex == charIndex + 10;

		for (size_t i = 0; i < 10; i++)
		{
			arrCalculationValues[i] = 0;
		}
		
		indexCalculationValue = 0;
		for (int i = nextOperatorIndex-1; i >= charIndex; i--)
		{
			currentNb = "";
			for (size_t j = 0; j < operatorLine; j++)
			{
				currentChar = arrInputChar[j][i];

				if (int(currentChar)>47 && int(currentChar) < 58)
				{
					currentNb += currentChar;
				}
				
			}
			if (currentNb != "")
			{
				arrCalculationValues[indexCalculationValue] = std::stoll(currentNb);
				indexCalculationValue++;
			}

			;
		}
		calcOperator = arrInputChar[operatorLine][charIndex];
		total += calculate(arrCalculationValues, indexCalculationValue, calcOperator);
		if (lastOperation)
			break;
		charIndex = nextOperatorIndex;

	}



	return total;
}

int main()
{
	std::string inputFileName = "input.txt";
	//std::string inputFileName = "inputTest.txt";
	int operatorQty = 0, nbQty = 0;
	

	static long long arrValues[4][1000] = { 0 };
	static char arrOperators[1000] = { 0 };
	static long long arrResults[1000] = { 0 };
	long long total = 0;
	//total=readFileAndCalcPartOne(inputFileName);

	total = readFileAndCalcPartTwo(inputFileName);
	
	std::string outputStr = "";
	outputStr += "Good products: \n";
	outputStr += "Total :"+std::to_string(total)+"\n";
	printf(outputStr.c_str());
	std::ofstream outputFile("output.txt");
	outputFile << outputStr;
	outputFile.close();
	printf("Finished processing.\n");
}
