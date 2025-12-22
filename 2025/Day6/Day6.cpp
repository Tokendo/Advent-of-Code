#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>



long long calculate(long long arrInValues[100],int nbQty, char calcOperator)
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

int main()
{
	auto timeFirstLine = std::chrono::high_resolution_clock::now();
	//std::ifstream inputFile("input.txt");
	std::ifstream inputFile("inputTest.txt");
	std::string line = "";
	std::string nb = "";
	static long long arrValues[4][1000] = { 0 };
	static char arrOperators[1000] = { 0 };
	static long long arrResults[1000] = { 0 };
	int valuesCollumns = 0, valuesDepth = 0;

	printf("Reading file line by line:\n");
	auto start = std::chrono::high_resolution_clock::now();
	int charvalue = 0, lineIndex = 0, indexChar = 0, operatorQty=0, nbQty=0;
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
			nbQty++;
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
			for (size_t i = 0; i <= line.length()-1; i++)
			{
				charvalue = int(line[i]);
				if (charvalue != 32 )
				{
					arrOperators[indexArr] = line[i];
					indexArr++;
					operatorQty++;
				}
			}

		}

		firstSpaceFound = false;
		lineIndex++;
	}
	inputFile.close();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	printf("File read in %lld microseconds.\n", std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count());
	long long total = 0,result=0;
	for (size_t i = 0; i < operatorQty; i++)
	{
		long long arrCalculationValues[4] = { arrValues[0][i], arrValues[1][i], arrValues[2][i], arrValues[3][i] };

		result = calculate(arrCalculationValues,nbQty, arrOperators[i]);
		arrResults [i] = result;
		total += result;
	}



	auto totalelapsed = std::chrono::high_resolution_clock::now() - timeFirstLine;
	std::string outputStr = "";
	outputStr += "Good products: \n";
	outputStr += "Total :"+std::to_string(total)+"\n";
	outputStr += "Total time: " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(totalelapsed).count()) + " milliseconds.\n";
	printf(outputStr.c_str());
	std::ofstream outputFile("output.txt");
	outputFile << outputStr;
	outputFile.close();
	printf("Finished processing.\n");
}
